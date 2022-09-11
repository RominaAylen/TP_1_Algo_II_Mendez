#include "cajas.h"
#include "pokemon.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ERROR 0
#define MAX_NOMBRE_POKEMON 30
#define CAJA_VACIA 0
#define ELEMENTO_CERO 0
#define LONGITUD_LINEA_LEIDA 40
#define FORMATO_ESCRITURA "%s;%i;%i;%i\n"

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

void ordenar_alfabeticamente_pokemones(pokemon_t **pokemones, int cantidad_pokemones)
{
	int i, j;
	pokemon_t *ptr_aux_pokemon = NULL;
	for (i = 1; i < cantidad_pokemones; i++)
	{
		j = i;
		ptr_aux_pokemon = pokemones[i];
		while ((j > 0) && (strcmp(ptr_aux_pokemon->nombre, pokemones[j - 1]->nombre) < 0))
		{
			pokemones[j] = pokemones[j - 1];
			j--;
		}
		pokemones[j] = ptr_aux_pokemon;
	}
}

caja_t *caja_cargar_archivo(const char *nombre_archivo)
{
	if (!nombre_archivo)
	{
		return NULL;
	}

	char linea_leida[LONGITUD_LINEA_LEIDA] = "";

	FILE *t_entrada = fopen(nombre_archivo, "r");

	if (!t_entrada)
	{
		perror("No se pudo abrir el archivo de lectura");
		printf("%s\n", nombre_archivo);
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

	caja_nueva->cantidad_pokemones_guardados = 0;
	caja_nueva->pokemones_guardados = NULL;

	while (leidos && !feof(t_entrada))
	{
		pokemon_t *puntero_pokemon_nuevo = NULL;
		leidos = fscanf(t_entrada, "%s\n", linea_leida);

		if (leidos)
		{
			puntero_pokemon_nuevo = pokemon_crear_desde_string(linea_leida);
		}

		if (!puntero_pokemon_nuevo)
		{
			caja_destruir(caja_nueva);
			fclose(t_entrada);
			printf("No se pudo reservar memoria para el nuevo pokemon leido\n");
			return NULL;
		};

		pokemon_t **nuevos_pokemones = realloc(caja_nueva->pokemones_guardados, (unsigned long)(caja_nueva->cantidad_pokemones_guardados + 1) * sizeof(pokemon_t *));

		if (!nuevos_pokemones)
		{
			caja_destruir(caja_nueva);
			fclose(t_entrada);
			printf("No se pudo reallocar los pokemones\n");
			return NULL;
		}

		nuevos_pokemones[caja_nueva->cantidad_pokemones_guardados] = puntero_pokemon_nuevo;
		caja_nueva->cantidad_pokemones_guardados = caja_nueva->cantidad_pokemones_guardados + 1;
		caja_nueva->pokemones_guardados = nuevos_pokemones;
	};

	fclose(t_entrada);

	ordenar_alfabeticamente_pokemones(caja_nueva->pokemones_guardados, caja_nueva->cantidad_pokemones_guardados);

	return caja_nueva;
}

int caja_guardar_archivo(caja_t *caja, const char *nombre_archivo)
{
	if (!caja || !nombre_archivo)
	{
		return ERROR;
	}

	FILE *t_salida = fopen(nombre_archivo, "w");

	if (!t_salida)
	{
		perror("No se pudo crear el archivo de escritura");
		return ERROR;
	}

	int cantidad_pokemones_escritos = 0;

	int i = 0;

	while (i < caja->cantidad_pokemones_guardados)
	{
		pokemon_t *pokemon = caja->pokemones_guardados[i];
		fprintf(t_salida, FORMATO_ESCRITURA, pokemon->nombre, pokemon->nivel, pokemon->poder_ataque, pokemon->poder_defensa);
		i++;
		cantidad_pokemones_escritos++;
	}

	fclose(t_salida);
	return cantidad_pokemones_escritos;
}

caja_t *caja_combinar(caja_t *caja1, caja_t *caja2)
{
	if (!caja1 || !caja2 || (caja1->cantidad_pokemones_guardados < CAJA_VACIA) || caja2->cantidad_pokemones_guardados < CAJA_VACIA)
	{
		return NULL;
	}

	caja_t *ptr_caja_combinada = malloc(sizeof(caja_t));
	if (!ptr_caja_combinada)
	{
		return NULL;
	}

	int cantidad_pokemones_guardados = caja1->cantidad_pokemones_guardados + caja2->cantidad_pokemones_guardados;
	pokemon_t **ptr_pokemones = malloc((long unsigned)cantidad_pokemones_guardados * sizeof(pokemon_t *));

	int i = 0;

	for (int j = 0; j < caja1->cantidad_pokemones_guardados; j++)
	{
		pokemon_t *pokemon = malloc((long unsigned)(i + 1) * sizeof(pokemon_t));
		memcpy(pokemon, caja1->pokemones_guardados[j], sizeof(pokemon_t));
		ptr_pokemones[i] = pokemon;
		i++;
	}

	for (int k = 0; k < caja2->cantidad_pokemones_guardados; k++)
	{
		pokemon_t *pokemon = malloc((long unsigned)(i + 1) * sizeof(pokemon_t));
		memcpy(pokemon, caja2->pokemones_guardados[k], sizeof(pokemon_t));
		ptr_pokemones[i] = pokemon;
		i++;
	}

	ptr_caja_combinada->pokemones_guardados = ptr_pokemones;
	ptr_caja_combinada->cantidad_pokemones_guardados = cantidad_pokemones_guardados;
	ordenar_alfabeticamente_pokemones(ptr_caja_combinada->pokemones_guardados, ptr_caja_combinada->cantidad_pokemones_guardados);
	return ptr_caja_combinada;
}

int caja_cantidad(caja_t *caja)
{
	if (!caja)
	{
		return ERROR;
	}
	return caja->cantidad_pokemones_guardados;
}

pokemon_t *caja_obtener_pokemon(caja_t *caja, int n)
{
	if (!caja || n < ELEMENTO_CERO || n >= caja->cantidad_pokemones_guardados)
	{
		return NULL;
	}

	return (caja->pokemones_guardados[n]);
}

int caja_recorrer(caja_t *caja, void (*funcion)(pokemon_t *))
{
	if (!caja || !funcion || caja->cantidad_pokemones_guardados == CAJA_VACIA)
	{
		return ERROR;
	}

	int cantidad_de_pokemon_aplicados = 0;

	for (int i = 0; i < caja->cantidad_pokemones_guardados; i++)
	{
		funcion(caja->pokemones_guardados[i]);
		cantidad_de_pokemon_aplicados++;
	}
	return cantidad_de_pokemon_aplicados;
}

void caja_destruir(caja_t *caja)
{
	if (caja)
	{
		caja_recorrer(caja, &pokemon_destruir);
		free(caja->pokemones_guardados);
		free(caja);
	}
}
