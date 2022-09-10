#include "pokemon.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NOMBRE_POKEMON 30
#define ERROR_PUNTERO 0
#define FORMATO_LECTURA "%[^;];%i;%i;%i\n"

struct _pokemon_t
{
	char nombre[MAX_NOMBRE_POKEMON];
	int nivel;
	int poder_ataque;
	int poder_defensa;
};

pokemon_t *pokemon_crear_desde_string(char *string)
{

	pokemon_t *pokemon_creado = malloc(sizeof(pokemon_t));

	if (pokemon_creado)
	{

		sscanf(string, FORMATO_LECTURA, pokemon_creado->nombre, &(pokemon_creado->nivel), &(pokemon_creado->poder_ataque), &(pokemon_creado->poder_defensa));
		return pokemon_creado;
	}

	return NULL;
}

int pokemon_nivel(pokemon_t *pokemon)
{
	if (!pokemon)
	{
		return ERROR_PUNTERO;
	}
	return pokemon->nivel;
}

int pokemon_ataque(pokemon_t *pokemon)
{
	if (!pokemon)
	{
		return ERROR_PUNTERO;
	}
	return pokemon->poder_ataque;
}

int pokemon_defensa(pokemon_t *pokemon)
{
	if (!pokemon)
	{
		return ERROR_PUNTERO;
	}
	return pokemon->poder_defensa;
}

const char *pokemon_nombre(pokemon_t *pokemon)
{
	if (!pokemon)
	{
		return ERROR_PUNTERO;
	}
	return pokemon->nombre;
}

void pokemon_destruir(pokemon_t *pokemon)
{
	if (pokemon)
	{
		free(pokemon);
	}
}
