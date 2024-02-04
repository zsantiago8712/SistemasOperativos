#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funciones.h"

int main(int argc, char** argv) {
    if (argc < 2 && atoi(argv[1]) < 0 && atoi(argv[2]) < 0) {
        perror("Faltan argumentos o el argumento no es valido");
        exit(-1);
    }

    puts(
        "La sincronizacion de este programa se logra atravez de hilos para "
        "ordenar segmentos del arreglo en paralelo y el uso de pthread_join() "
        "en el proceso padre para asegurarse de que todos los hilos"
        "terminen antes de proceder a fusionar los segmentos ordenados.");

    clock_t tiempo_inicio = clock();
    const int size_array = atoi(argv[1]);
    const int num_hilos = atoi(argv[2]);

    int array[size_array];
    pthread_t threads[num_hilos];
    ThreadArgs args[num_hilos];
    pthread_attr_t attr;

    int num_arrays = 0;
    int inicio = 0;

    if (num_hilos > size_array && (size_array * 2) % num_hilos == 0 &&
        num_hilos < (size_array * 2)) {
        perror(
            "El numero de hilos no puede ser mayor que el tamaño del array, "
            "como minimo el tamaño debe de ser el doble que el tamano del "
            "array");
        exit(-1);
    }
    llenarArray(array, size_array);
    num_arrays = size_array / num_hilos;

    // printf("Primer array\n");
    // for (int i = 0; i < size_array; i++) {
    //     printf("%d ", array[i]);
    // }

    pthread_attr_init(&attr);

    for (int i = 0; i < num_hilos; i++) {
        args[i].array = array;
        args[i].left = inicio;
        args[i].righ = inicio + num_arrays - 1;

        pthread_create(&threads[i], &attr, bubleSort, &args[i]);

        inicio += num_arrays;
    }

    for (int i = 0; i < num_hilos; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int size = num_arrays; size < size_array; size = 2 * size) {
        for (int leftStart = 0; leftStart < size_array; leftStart += 2 * size) {
            int middle = min(leftStart + size - 1, size_array - 1);
            int rightEnd = min(leftStart + 2 * size - 1, size_array - 1);

            merge(array, leftStart, middle, rightEnd);
        }
    }

    clock_t tiempo_fin = clock();
    double tiempo_transcurrido =
        (double)(tiempo_fin - tiempo_inicio) / CLOCKS_PER_SEC;

    printf(
        "\n\nTardo en ordenar un arreglo de tamaño %d con %d hilos en un "
        "tiempo "
        "%f segundos\n",
        size_array, num_hilos, tiempo_transcurrido);

    // printf("\n\nArray ordenado\n");
    // for (int i = 0; i < size_array; i++) {
    //     printf("%d ", array[i]);
    // }

    return 0;
}
