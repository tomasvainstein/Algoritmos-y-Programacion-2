VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS =-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2
CC = gcc

all: clean valgrind

escape_pokemon: escape_pokemon.c src/*
	$(CC) $(CFLAGS) src/*.c escape_pokemon.c -o escape_pokemon 2>&1

valgrind: escape_pokemon
	valgrind $(VALGRIND_FLAGS) ./escape_pokemon ejemplo/objetos.txt ejemplo/interacciones.txt 2>&1

valgrind-pruebas: pruebas
	valgrind $(VALGRIND_FLAGS) ./pruebas 2>&1

pruebas: src/*.c pruebas.c
	$(CC) $(CFLAGS) src/*.c pruebas.c -o pruebas 2>&1

clean:
	rm -f ejemplo *.o pruebas 2>&1
