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

int main(int argc, char *argv[])
{
	// En este archivo .c tenes que poner tu programa principal.

	// No se pide nada concreto, pero básicamente tenés que escribir un
	// programa de demostración que sirva para ver cómo funciona tu
	// biblioteca de cajas pokemon.

	// Por ejemplo podes leer dos o 3 archivos de cajas, mostrar su
	// contenido, combinar un par y mostrar el contenido de la caja
	// combinada.

	// if (argc != CANTIDAD_FLAGS || strcmp(argv[1], NOMBRE_ARCHIVO_ENTRADA) || strcmp(argv[2], NOMBRE_ARCHIVO_SALIDA))
	// {
	// 	printf("Error en los parametros de ejecución. El programa será terminado\n");
	// 	return ERROR;
	// }

	caja_t *caja_creada = caja_cargar_archivo(argv[1]);

	if (!caja_creada)
	{
		printf("NO SE CREO BIEN LA CAJA\n");
		return ERROR;
	}

	pokemon_t pokemon_1 = *(caja_creada->pokemones_guardados[0]);

	printf("nombre pokemon 1: %s\n", pokemon_1.nombre);
	printf("cantidad pokemones: %i\n", caja_creada->cantidad_pokemones_guardados);
	free(caja_creada);

	// t_salida = fopen(NOMBRE_ARCHIVO_SALIDA, "w");
	// if (!t_salida)
	// {
	// 	perror("No se pudo abrir el archivo de escritura");
	// 	fclose(t_entrada);
	// 	return ERROR;
	// }

	// fclose(t_entrada);
	// fclose(t_salida);
	printf("todo joya :P\n");

	return 0;
}
