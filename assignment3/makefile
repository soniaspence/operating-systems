CC = gcc
EXEC = assignment3

default: clean assignment3 run

assignment3: assignment3.c
	${CC} $^ -o ${EXEC} -pthread

run:
	./${EXEC}

clean:
	rm -f ${EXEC}
