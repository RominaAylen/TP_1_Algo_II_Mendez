#include "string.h"
#include "stdio.h"
#include "stdlib.h"
// #include "src/cajas.h"
#include "src/pokemon.h"

#define ERROR -1
#define CANTIDAD_FLAGS 3
#define NOMBRE_ARCHIVO_ENTRADA "prueba.csv"
#define NOMBRE_ARCHIVO_SALIDA "nuevo.csv"
#define LONGITUD_LINEA_LEIDA 40

struct _pokemon_t
{
	char nombre[30];
	int nivel;
	int poder_ataque;
	int poder_defensa;
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

	FILE *t_entrada = NULL;
	FILE *t_salida = NULL;
	char linea_leida[LONGITUD_LINEA_LEIDA] = "";

	if (argc != CANTIDAD_FLAGS || strcmp(argv[1], NOMBRE_ARCHIVO_ENTRADA) || strcmp(argv[2], NOMBRE_ARCHIVO_SALIDA))
	{
		printf("Error en los parametros de ejecución. El programa será terminado\n");
		return ERROR;
	}

	t_entrada = fopen(NOMBRE_ARCHIVO_ENTRADA, "r");

	if (!t_entrada)
	{
		perror("No se pudo abrir el archivo de lectura");
		return ERROR;
	}

	t_salida = fopen(NOMBRE_ARCHIVO_SALIDA, "w");
	if (!t_salida)
	{
		perror("No se pudo abrir el archivo de escritura");
		fclose(t_entrada);
		return ERROR;
	}

	int leidos = 1;
	while (leidos == 1 && !feof(t_entrada))
	{
		leidos = fscanf(t_entrada, "%s\n", linea_leida);
		pokemon_t *pokemon = pokemon_crear_desde_string(linea_leida);
		printf("puntero pokemon: %p\n", (void *)pokemon);
		printf("nombre pokemon: %s\n", pokemon->nombre);
		printf("nivel pokemon: %i\n", pokemon->nivel);
		printf("poder ataque pokemon: %i\n", pokemon->poder_ataque);
		printf("poder defensa pokemon: %i\n", pokemon->poder_defensa);
		pokemon_destruir(pokemon);
	};

	fclose(t_entrada);
	fclose(t_salida);
	printf("todo joya :P\n");

	return 0;
}
