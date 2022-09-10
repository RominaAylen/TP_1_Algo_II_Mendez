#include "string.h"
#include "stdio.h"
// #include "src/cajas.h"
// #include "src/pokemon.h"

#define ERROR -1
#define CANTIDAD_FLAGS 3
#define NOMBRE_ARCHIVO_ENTRADA "prueba.csv"
#define NOMBRE_ARCHIVO_SALIDA "nuevo.csv"

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

	fclose(t_entrada);
	fclose(t_salida);
	printf("todo joya :P\n");

	return 0;
}
