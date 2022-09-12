# TP1 - CAJAS DE ALMACENAMIENTO POKEMON

Como todos sabemos, un entrenador Pokemon no puede cargar consigo mismo mas de 6 Pokemon a la vez. Esto puede representar un problema para aquellos entrenadores que les gusta capturar muchos Pokemon.

Para solucionar este inconveniente, el investigador Bill inventó el Sistema de almacenamiento Pokemon. Este sistema permite que los entrenadores almacenen a sus Pokemon en cajas especiales de almacenamiento que mantienen a los Pokemon guardados hasta que el entrenador los necesite. El sistema de cajas puede ser accedido muy fácilmente desde el centro Pokemon mas cercano.

En esta oportunidad queremos replicar el Sistema de almacenamiento Pokemon de Bill utilizando el lenguaje de programación C. Para ello se te va a entregar un archivo con la interfaz del sistema de cajas. El objetivo de este primer TP es implementar la funcionalidad de dicha interfaz con los requerimientos especificados en este enunciado y en el propio archivo .h.

## FUNCIONALIDAD PEDIDA

Básicamente se piden 3 cosas:

* Leer/escribir Pokemon desde/hacia archivos csv.
* Almacenar los Pokemon leídos en memoria (seguramente un vector dinámico).
* Implementar funciones que permitan consultar los datos leídos.

## FORMATO DE LOS ARCHIVOS
Los archivos csv contienen una o mas líneas con información de los Pokemon. La información presente es (en orden): Nombre (máximo 20 caracteres), nivel (entero), poder de ataque (entero) y poder de defensa (entero). A continuación se muestra el ejemplo de un archivo que contiene 2 Pokemon, siendo el primero un Pikachu de nivel 10, ataque 15 y defensa 10:

Pikachu;10;15;10
Charmander;6;20;5

## AYUDITA

El trabajo tiene 3 partes bien definidas:

* Manejo de archivos (lectura y escritura de datos de un archivo)
* Manejo de vectores dinámicos (malloc, realloc y punteros)
* Manejo de punteros a función

Si logras escribir 3 programas separados (3 main separados) que logren cada uno de los puntos de alguna forma, el resto es cuestión de tiempo.

No es obligatorio ni parte de la entrega, pero te propongo 3 programas que te van a ayudar a aprobar el trabajo:

El primer programa define una estructura de datos simple (quizás un struct simple con dos enteros) y hace 2 cosas:
Abre un archivo llamado "datos.csv" que contiene dos enteros, los lee y los carga en una estructura.
Abre un archivo llamado "nuevo.csv" y escribe en este archivo los dos enteros separados ; por. El contenido del archivo debería ser idéntico al primero.

El segundo programa crea un vector de enteros con malloc (o realloc) se invoca en un for varias veces una función que agrega un elemento nuevo al vector de enteros.
Ojo que este se puede complicar. Intenta después cambiar el entero por estructuras y fijate que funcione todo bien con Valgrind.
Recordá que en C siempre se pasan los parámetros por copia, si modificas una copia no se modifica el original.

El tercer programa crea 2 funciones diferentes (con diferente número y tipo de parámetros) y en el main las invoca pero mediante punteros a función.
Una vez que eso compile y funcione, agrega una tercer función que se invoca desde el main y que reciba los dos punteros a función. Que ahora sea esta tercer función la que invoque a las otras dos mediante los punteros recibidos.

## COMPILACIÓN Y CORRIDA CON VALGRIND

Para compilar y correr los trabajos se usan los siguientes flags de gcc/clang:

-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2
Y para correr se usan los siguientes flags de Valgrind:

--leak-check=full --track-origins=yes --show-reachable=yes --show-leak-kinds=all


## CONSEJOS PARA LA ELABORACIÓN DEL TP
Para la correcta implementación de este trabajo se requiere el uso de punteros y memoria dinámica. Tené en cuenta que el mal uso de los mismos puede ocasionar que el programa aborte durante cualquier punto de su ejecución. Para lograr encontrar los motivos por los cuales el programa no funciona, recomendamos el uso de Valgrind y gdb durante el desarrollo.

Adicionalmente te dejamos algunas recomendaciones que te van a sacar las papas del fuego (si las seguís):

* NUNCA implementar mas de 10 o 15 líneas de código máximo sin probar que compile. Compilar a cada rato salva vidas. Los IDEs modernos suelen marcar en rojo o amarillo cuando existen problemas de compilación sin necesidad de intentar compilar manualmente. No lo ignoren.
* Intenta probar cada parte del trabajo de forma individual mientras lo desarrollas. Implementar todo (o casi todo) el trabajo para después probarlo al final es la receta del desastre. Nunca va a funcionar. No lo intentes.
* Asegurate de entender bien los conceptos de memoria dinámica y punteros. Preguntá en Discord si hay algo que no entendiste.
* NUNCA dejes el trabajo para último momento. Sabemos que es muy posible que esta no sea la única materia que cursas y que tenés otros trabajos para hacer, pero no te duermas. Si te trabas con algo consultalo. Estamos para ayudarte.
* Los punteros se pueden complicar, intentá dibujar las interacciones de punteros para ver qué está pasando.

## ENTREGA

La entrega se hace mediante Chanutron't en Discord. Recordá que la entrega tiene fecha límite y no se aceptan entregas fuera de término.

El archivo entregado tiene que contener el código solicitado en el enunciado (y tiene que pasar las pruebas) y un informe que explique los siguientes temas:

Explicación de las estructuras definidas y cómo se usan para implementar la funcionalidad pedida.
Explicación de cómo funciona malloc y realloc y su correcto uso.
Explicación de qué es y cómo funcionan los punteros.
Te recomendamos que uses dibujos/diagramas/esquemas para apoyarte en las explicaciones y que tu corrector pueda entender. Un informe ideal explica los conceptos pedidos de forma tal que alguien que no sabe nada de la materia puede entender por lo menos de qué se habla.

## CRITERIOS BÁSICOS DE CORRECCIÓN

### GENERAL
 Cada malloc tiene su verificación
 Libera(cierra) memoria(archivos) en los casos de error
 Los realloc se hacen sobre punteros auxiliares
 No hay fragmentos de código comentados (sin usar)
 No hay printfs donde no es necesario
 Los entregables compilan y corren sin error
    Si se entrega makefile, debe funcionar correctamente
    Si no se entrega makefile, debe especificarse cómo compilar y correr el programa
 Verifica los punteros recibidos en las funciones públicas
 No hay variables globales
 No reserva memoria cuando no es necesario
 Usa constantes y tienen sentido

### ESTILO
 El estilo es el apropiado
 Los nombres de función me dicen lo que hacen
 No hay variables con nombre confuso

### SPECÍFICOS DEL TP1
 Todos los tamaños son dinámicos (excepciones: nombre de los pokemon y longitud máxima de línea de los archivos)
 Cada realloc aumenta el tamaño del vector dinámico en 1 (en esta instancia se pide que sea O(n))
 Las estructuras son privadas (son conocidas solamente en el .c correspondiente a su implementación)
 No utiliza qsort para ordenar los elementos del vector
 La caja combinada no contiene los mismos punteros que las cajas originales (los pokemon son copias de los originales)
Ayudita 1: Pokemon -> string -> nuevo Pokemon
Ayudita 2: guardar combinado -> cargar
 Explica los tema teóricos pedidos en el informe