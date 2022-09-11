compilar:
	gcc main.c src/pokemon.c src/cajas.c -o tp1 -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2

valgrind:
	sudo valgrind --leak-check=full --track-origins=yes --show-reachable=yes --show-leak-kinds=all ./tp1

ejecutar:
	sudo ./tp1