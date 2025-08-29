.SUFFIXES: .c .o

CC = gcc
CCFLAGS = -std=c99 -pedantic -Wall
VPATH = src:./src

EXEC = seagb
OBJS = seagb.o rom.o gb.o

${EXEC}: ${OBJS}
	${CC} ${CCFLAGS} -o ${EXEC} ${OBJS}

.c.o:
	${CC} ${CCFLAGS} -c $<

run: ${EXEC}
	./${EXEC}

valgrind: ${EXEC}
	valgrind --leak-check=full ./${EXEC}

gdb: ${EXEC}
	gdb ./${EXEC}

clean:
	rm -f ${EXEC} ${OBJS}


seagb.o: seagb.c common.h
gb.o: gb.c gb.h common.h
rom.o: rom.c rom.h common.h