#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include "funciones.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <tamaño del arreglo> <número de procesos>\n",
                argv[0]);
        return 1;
    }

    puts(
        "La sincronización en este código se logra mediante el uso de procesos "
        "hijos para ordenar segmentos del arreglo en paralelo y el uso de "
        "wait() en el proceso padre para asegurarse de que todos los procesos "
        "hijos hayan terminado antes de proceder a fusionar los segmentos "
        "ordenados. Los procesos hijos usan munmap() para desasociar la "
        "memoria compartida antes de terminar, pero esto no afecta la "
        "disponibilidad de la memoria para el proceso padre, que realiza la "
        "fusión final y luego libera la memoria compartida.");

    clock_t tiempo_inicio = clock();
    const int size_array = atoi(argv[1]);
    const int num_procesos = atoi(argv[2]);
    const int segmentSize = size_array / num_procesos;

    int pid;
    // Crear memoria compartida para el arreglo
    int* array = mmap(NULL, size_array * sizeof(int), PROT_READ | PROT_WRITE,
                      MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (array == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    llenarArray(array, size_array);
    printf("Array inicial: ");
    // for (int i = 0; i < size_array; i++) {
    //     printf("%d; ", array[i]);
    // }
    printf("\n");

    for (int i = 0; i < num_procesos; i++) {
        int inicio = i * segmentSize;
        int fin = (i == num_procesos - 1) ? size_array : inicio + segmentSize;

        pid = fork();
        if (pid == 0) {
            bubleSort(array, inicio, fin);
            munmap(array, size_array * sizeof(int));
            return 0;
        }
    }

    // Esperar a que todos los procesos hijos terminen
    for (int i = 0; i < num_procesos; i++) {
        int status;
        wait(&status);
    }

    // Fusionar los segmentos ordenados aquí
    for (int size = segmentSize; size < size_array; size = 2 * size) {
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
        "\nTardo en ordenar un arreglo de tamaño %d con %d procesos en un "
        "tiempo "
        "%f segundos\n",
        size_array, num_procesos, tiempo_transcurrido);

    // Imprimir el arreglo ordenado
    // printf("Array ordenado: \n");
    // for (int i = 0; i < size_array; i++) {
    //     printf("%d ", array[i]);
    // }
    // printf("\n");

    munmap(array, size_array * sizeof(int));
    return 0;
}
