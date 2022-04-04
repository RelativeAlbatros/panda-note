#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include "hacking.h"

void usage() {
	printf("Usage: panda-note <data to add to /tmp/notes> <datafile> <options>\n"
            "\t-h: prints this helpful message\n");
	exit(1);
}
void fatal(char *);
void *ec_malloc(unsigned int);
char *input_note();
void read_notes(char *);
//char *format_note(char *);

int main(int argc, char **argv) {
	int userid, fd;
	char *buffer = (char *) ec_malloc(200);
	char *datafile = (char *) ec_malloc(20);

	if (argc < 2){
        strcpy(buffer, input_note());
	} else {
        strcpy(buffer, argv[1]);
    }
	if (argc > 2)
		strcpy(datafile, argv[2]);
	else
		strcpy(datafile, "/var/notes.txt");
    for(int i=1; i<argc; i++){
        if(strcmp(argv[i], "-h") == 0){
            usage();
        } else if(strcmp(argv[i], "-r") == 0){
            read_notes(datafile);
        }
    }

    if (buffer[strlen(buffer)-1] != '\n')
        strcat(buffer, "\n");
    FILE *file = fopen(datafile, "a");
	if (file == NULL)
        fatal("in main() while opening file");
	fwrite(buffer, sizeof(char), strlen(buffer), file);
    fclose(file);
	printf("Note has been saved.\n");
	free(datafile);
	free(buffer);
}

char *input_note(){
    char *buffer = (char *) ec_malloc(200);
    printf("Input Note: ");
    fgets(buffer, 199, stdin);
    return buffer;
}

void read_notes(char *datafile){
    char *buffer = (char *) ec_malloc(1023);
    FILE *file = fopen(datafile, "r");
    fread(buffer, 1, 1023, file);
    printf("=== start of %s dump ===\n", datafile);
    printf("%s", buffer);
    printf("=== end   of %s dump ===\n", datafile);
    fclose(file);
    exit(0);
}

/* char *format_note(char *note) {
    char *buffer = (char *) ec_malloc(230);
    strcpy(buffer, sprintf("from %s:\n%s\n", getenv("USERPROFILE"), note));
    return buffer;
} */
