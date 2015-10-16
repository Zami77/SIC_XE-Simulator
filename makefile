.SUFFIXES: .c .o
CC = gcc
CFLAGS = -g

.c.o:
	$(CC) $(CFLAGS) -c $<

a.out: main.o lineByLine.o opcodes.o symbols.o
	gcc main.o lineByLine.o opcodes.o symbols.o -o a.out

main.o: functions.h main.c
lineByLine.o: functions.h lineByLine.c
opcodes.o: functions.h opcodes.c
symbols.o: functions.h symbols.c

clean:
	rm -f *.o core
