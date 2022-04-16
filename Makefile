CC  = tcc
SRC = panda-note.c
OBJ = ${SRC:.c=.o}
PREFIX = /usr/local

all: options panda-note

panda-note: ${SRC}
	${CC} -o $@ ${SRC} 

debug: options ${SRC}
	${CC} -g -o $@ ${SRC} 
	
options:
	@echo "build options:"
	@echo "CC = ${CC}"

install: all
	mv panda-note ${PREFIX}/bin
	chmod 755 ${PREFIX}/bin/panda-note
	chmod u+s ${PREFIX}/bin/panda-note 

clean:
	rm -f panda-note ${PREFIX}/bin/panda-note

.PHONY: options panda-note install clean
