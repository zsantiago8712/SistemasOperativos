#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funciones.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <tamaño del arreglo>\n", argv[0]);
        return 1;
    }

    clock_t tiempo_inicio = clock();
    const int size_array = atoi(argv[1]);

    int array[size_array];

    llenarArray(array, size_array);
    printf("Array inicial: ");
    // for (int i = 0; i < size_array; i++) {
    //     printf("%d; ", array[i]);
    // }
    // printf("\n");

    bubleSort(array, size_array);

    clock_t tiempo_fin = clock();
    double tiempo_transcurrido =
        (double)(tiempo_fin - tiempo_inicio) / CLOCKS_PER_SEC;

    printf(
        "\nTardo en ordenar un arreglo de tamaño %d en un "
        "tiempo %f segundos\n",
        size_array, tiempo_transcurrido);

    // Imprimir el arreglo ordenado
    // printf("Array ordenado: \n");
    // for (int i = 0; i < size_array; i++) {
    //     printf("%d ", array[i]);
    // }
    printf("\n");

    return 0;
}
