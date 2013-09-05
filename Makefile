CC=gcc
OBJS=main.o matriz.o

all: tp0

tp0: $(OBJS)
	gcc $(OBJS) -o $@

main.o: main.c
	gcc -c $< -o $@

matriz.o: matriz.c
	gcc -c $< -o $@



