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

struct _caja_t
{
	pokemon_t **pokemones_guardados;
	int cantidad_pokemones_guardados;
};

/*
 * Ordena alfabeticamente los pokemones cuya direccion de memoria
 * esta guardada en el vector dinamico de pokemones guardados de la caja recibida
 *
 * Si la direccion de memoria del vector es nulo, o algunos de las direcciones es nula
 * o la cantidad de pokemones a ordenar es 0 la funcion no hace nada
 */
void ordenar_alfabeticamente_pokemones(caja_t *caja)
{
	int i, j;
	pokemon_t *ptr_aux_pokemon = NULL;
	for (i = 1; i < caja_cantidad(caja); i++)
	{
		j = i;
		ptr_aux_pokemon = caja_obtener_pokemon(caja, i);
		while ((j > 0) && (strcmp(pokemon_nombre(ptr_aux_pokemon), pokemon_nombre(caja->pokemones_guardados[j - 1])) < 0))
		{
			caja->pokemones_guardados[j] = caja->pokemones_guardados[j - 1];
			j--;
		}
		caja->pokemones_guardados[j] = ptr_aux_pokemon;
	}
}

/*
 * Devuelve la direccion de memoria del primer elemento del vector dinamico correspondinte
 * a los pokemones guardado en la caja
 * si no, NULL
 */
pokemon_t **caja_obtener_pokemones(caja_t *caja)
{
	if (!caja || !(caja->pokemones_guardados))
	{
		return NULL;
	}
	return caja->pokemones_guardados;
}

/*
 * Devuelve un nuevo espacio de memoria con un pokemon de datos identicos al pokemon recibido
 * si no NULL
 */
pokemon_t *caja_copiar_pokemon(pokemon_t *pokemon)
{
	char linea[LONGITUD_LINEA_LEIDA] = " ";
	sprintf(linea, "%s;%i;%i;%i\n", pokemon_nombre(pokemon), pokemon_nivel(pokemon), pokemon_ataque(pokemon), pokemon_defensa(pokemon));
	return pokemon_crear_desde_string(linea);
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

		pokemon_t **nuevos_pokemones = realloc(caja_obtener_pokemones(caja_nueva), (unsigned long)(caja_cantidad(caja_nueva) + 1) * sizeof(pokemon_t *));

		if (!nuevos_pokemones)
		{
			caja_destruir(caja_nueva);
			fclose(t_entrada);
			printf("No se pudo reallocar los pokemones\n");
			return NULL;
		}

		nuevos_pokemones[caja_cantidad(caja_nueva)] = puntero_pokemon_nuevo;
		caja_nueva->cantidad_pokemones_guardados = caja_nueva->cantidad_pokemones_guardados + 1;
		caja_nueva->pokemones_guardados = nuevos_pokemones;
	};

	fclose(t_entrada);

	ordenar_alfabeticamente_pokemones(caja_nueva);

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

	while (i < caja_cantidad(caja))
	{
		pokemon_t *pokemon = caja_obtener_pokemon(caja, i);
		fprintf(t_salida, FORMATO_ESCRITURA, pokemon_nombre(pokemon), pokemon_nivel(pokemon), pokemon_ataque(pokemon), pokemon_defensa(pokemon));
		i++;
		cantidad_pokemones_escritos++;
	}

	fclose(t_salida);
	return cantidad_pokemones_escritos;
}

caja_t *caja_combinar(caja_t *caja1, caja_t *caja2)
{
	if (!caja1 || !caja2 || (caja_cantidad(caja1) < CAJA_VACIA) || caja_cantidad(caja2) < CAJA_VACIA)
	{
		return NULL;
	}

	caja_t *ptr_caja_combinada = malloc(sizeof(caja_t));
	if (!ptr_caja_combinada)
	{
		return NULL;
	}

	int cantidad_pokemones_guardados = caja_cantidad(caja1) + caja_cantidad(caja2);
	pokemon_t **ptr_pokemones = malloc((long unsigned)cantidad_pokemones_guardados * sizeof(pokemon_t *));

	int i = 0;

	for (int j = 0; j < caja_cantidad(caja1); j++)
	{
		pokemon_t *aux_pokemon = caja_copiar_pokemon(caja_obtener_pokemon(caja1, j));
		if (!aux_pokemon)
		{
			return NULL;
		}

		ptr_pokemones[i] = aux_pokemon;
		i++;
	}

	for (int k = 0; k < caja_cantidad(caja2); k++)
	{
		pokemon_t *aux_pokemon = caja_copiar_pokemon(caja_obtener_pokemon(caja2, k));
		if (!aux_pokemon)
		{
			return NULL;
		}

		ptr_pokemones[i] = aux_pokemon;
		i++;
	}

	ptr_caja_combinada->pokemones_guardados = ptr_pokemones;
	ptr_caja_combinada->cantidad_pokemones_guardados = cantidad_pokemones_guardados;
	ordenar_alfabeticamente_pokemones(ptr_caja_combinada);
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
	if (!caja || !funcion || caja_cantidad(caja) == CAJA_VACIA)
	{
		return ERROR;
	}

	int cantidad_de_pokemon_aplicados = 0;

	for (int i = 0; i < caja_cantidad(caja); i++)
	{
		funcion(caja_obtener_pokemon(caja, i));
		cantidad_de_pokemon_aplicados++;
	}
	return cantidad_de_pokemon_aplicados;
}

void caja_destruir(caja_t *caja)
{
	if (caja)
	{
		caja_recorrer(caja, &pokemon_destruir);
		free(caja_obtener_pokemones(caja));
		free(caja);
	}
}
