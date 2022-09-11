#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "src/cajas.h"
#include "src/pokemon.h"

#define ERROR -1
#define CANTIDAD_FLAGS 3
#define NOMBRE_ARCHIVO_ENTRADA "prueba.csv"
#define NOMBRE_ARCHIVO_SALIDA "nuevo.csv"
#define MAX_NOMBRE_POKEMON 30

struct _pokemon_t
{
	char nombre[MAX_NOMBRE_POKEMON];
	int nivel;
	int poder_ataque;
	int poder_defensa;
};

struct _caja_t
{
	pokemon_t **pokemones_guardados;
	int cantidad_pokemones_guardados;
};

void info_pokemon(pokemon_t *pokemon)
{
	if (!pokemon)
	{
		printf("Puntero NULO\n");
		return;
	}

	printf("Nombre pokemon: %s\n", pokemon->nombre);
	printf("Nivel pokemon: %i\n", pokemon->nivel);
	printf("Ataque pokemon: %i\n", pokemon->poder_ataque);
	printf("Defensa pokemon: %i\n", pokemon->poder_defensa);
	printf("-----\n");
}

int main(int argc, char *argv[])
{
	// En este archivo .c tenes que poner tu programa principal.

	// No se pide nada concreto, pero básicamente tenés que escribir un
	// programa de demostración que sirva para ver cómo funciona tu
	// biblioteca de cajas pokemon.

	// Por ejemplo podes leer dos o 3 archivos de cajas, mostrar su
	// contenido, combinar un par y mostrar el contenido de la caja
	// combinada.

	caja_t *caja_creada = caja_cargar_archivo("prueba.csv");

	if (!caja_creada)
	{
		printf("NO SE CREO BIEN LA CAJA 1\n");
		return ERROR;
	}

	caja_t *caja_creada2 = caja_cargar_archivo("prueba3.csv");

	if (!caja_creada2)
	{
		caja_destruir(caja_creada);
		printf("NO SE CREO BIEN LA CAJA 2\n");
		return ERROR;
	}

	int existosos = caja_recorrer(caja_creada, &info_pokemon);
	printf("Pokemones Aplicados Exitosos: %i\n", existosos);

	for (int i = 0; i < caja_creada->cantidad_pokemones_guardados; i++)
	{
		printf("i: %i\n", i);
		pokemon_t *pokemon_0 = caja_obtener_pokemon(caja_creada, i);
		info_pokemon(pokemon_0);
	}
	caja_t *caja_combinada = caja_combinar(caja_creada, caja_creada2);

	int escritos = caja_guardar_archivo(caja_combinada, "nuevo.csv");
	printf("Escritos: %i\n", escritos);
	caja_destruir(caja_creada);
	caja_destruir(caja_creada2);
	caja_destruir(caja_combinada);

	printf("todo joya :P\n");

	return 0;
}
