#include "cajas.h"
#include "pokemon.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_NOMBRE_POKEMON 30
#define LONGITUD_LINEA_LEIDA 40

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

caja_t *caja_cargar_archivo(const char *nombre_archivo)
{
	FILE *t_entrada = fopen(nombre_archivo, "r");
	char linea_leida[LONGITUD_LINEA_LEIDA] = "";

	if (!t_entrada)
	{
		perror("No se pudo abrir el archivo de lectura");
		return NULL;
	}

	caja_t *caja_nueva = malloc(sizeof(caja_t));
	if (!caja_nueva)
	{
		fclose(t_entrada);
		printf("No se pudo reservar memoria para la caja\n");
		return NULL;
	}

	int leidos = 1;

	pokemon_t **puntero_pokemones_inicial = malloc(sizeof(pokemon_t *));
	if (!puntero_pokemones_inicial)
	{
		fclose(t_entrada);
		printf("No se pudo reservar memoria los pokemones\n");
		return NULL;
		return NULL;
	}

	long unsigned int cantidad_pokemones_guardados = 0;

	while (leidos == 1 && !feof(t_entrada))
	{
		// printf("dentro while\n");
		leidos = fscanf(t_entrada, "%s\n", linea_leida);
		pokemon_t *puntero_pokemon_nuevo = pokemon_crear_desde_string(linea_leida);
		// printf("nombre: pokemon %s", puntero_pokemon_nuevo->nombre);

		if (!puntero_pokemon_nuevo)
		{
			// printf("FALLO POKEMON");

			return NULL;
		};

		pokemon_t **nuevos_pokemones = realloc(puntero_pokemones_inicial, (cantidad_pokemones_guardados + 1) * sizeof(pokemon_t *));

		if (!nuevos_pokemones)
		{
			// printf("FALLO nuevos pokemones");
			return NULL;
		}

		nuevos_pokemones[cantidad_pokemones_guardados] = puntero_pokemon_nuevo;
		printf("nombre: pokemon %s\n", nuevos_pokemones[cantidad_pokemones_guardados]->nombre);
		cantidad_pokemones_guardados++;

		caja_nueva->pokemones_guardados = nuevos_pokemones;
		caja_nueva->cantidad_pokemones_guardados = (int)cantidad_pokemones_guardados;
	};

	fclose(t_entrada);
	return caja_nueva;
}

int caja_guardar_archivo(caja_t *caja, const char *nombre_archivo)
{
	// FILE *t_salida = NULL;
	return 0;
}

caja_t *caja_combinar(caja_t *caja1, caja_t *caja2)
{
	return NULL;
}

int caja_cantidad(caja_t *caja)
{
	return 0;
}

pokemon_t *caja_obtener_pokemon(caja_t *caja, int n)
{
	return NULL;
}

int caja_recorrer(caja_t *caja, void (*funcion)(pokemon_t *))
{
	return 0;
}

void caja_destruir(caja_t *caja)
{
}
