CC = gcc
CFLAGS  = -g -Wall -w

default: shell

shell:   shell.o
		$(CC) $(CFLAGS) -o shell shell.o

shell.o:  shell.c
	$(CC) $(CFLAGS) -c shell.c

clean:
	$(RM) shell *.o *~
