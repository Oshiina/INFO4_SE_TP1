CC=gcc
CFLAGS=-Wall -g

all: tst shell

tst: tst.o readcmd.o

shell: shell.o readcmd.o

tst.o: tst.c
	gcc -Wall -c tst.c

reamcdm.o: readcmd.c
	gcc -Wall -c readcmd.c

shell.o: shell.c
	gcc -Wall -c shell.c

clean:
	rm -f shell shell.o readcmd.o tst tst.o
