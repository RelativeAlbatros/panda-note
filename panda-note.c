#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>
#include "config.h"

static void die(char *, ...);
static void print_notes(char *);
static void write_note(char *, char*);
static char *format_note(char *, int);
static void usage(void);

static void die(char *message, ...) {
    va_list ap;
    va_start(ap, message);
    vfprintf(stderr, message, ap);
    va_end(ap);
    exit(1);
}

static void print_notes(char *datafile){
    char *notes = (char *) malloc(1023);
    FILE *file = fopen(datafile, "r");
    fread(notes, 1, 1023, file);
    printf("%s", notes);
    fclose(file);
    exit(0);
}

static void write_note(char *notes, char *datafile){
    if (notes[strlen(notes)-1] != '\n')
        strcat(notes, "\n");
    FILE *file = fopen(datafile, "a");
	if (file == NULL)
        die("panda-note: opening %s", datafile);
	fwrite(notes, sizeof(char), strlen(notes), file);
    fclose(file);
    printf("Note saved.\n");
}

static char *format_note(char *note, int uid) {
    char *buffer = (char *) malloc(230);
    // time
    char *time_buffer = (char *) malloc(100);
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(time_buffer, 100, "%D %T", timeinfo);
    // time
    sprintf(buffer, "#%d %s %s\n", uid, time_buffer, note);
    return buffer;
}

static void usage(void) {
	die("Usage: panda-note <data to add to %s> <options>\n"
        "   -h: prints this helpful message\n"
        "   -r: prints contents of %s\n", datafile, datafile);
}

int main(int argc, char **argv) {
	unsigned int userid = getuid();
	char *notes = (char *) malloc(200);

	if (argc < 2)
        usage();
	else
        strcpy(notes, argv[1]);
    for(int i=1; i<argc; i++){
        if(strcmp(argv[i], "-h") == 0){
            usage();
        } else if(strcmp(argv[i], "-r") == 0){
            print_notes(datafile);
            exit(0);
        }
    }
    write_note(format_note(notes, userid), datafile);
    printf("Have a good day!\n");
	free(notes);
}
