#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void llenarArray(int* array, const int size_array) {
    srand(time(NULL));
    for (int i = 0; i < size_array; i++) {
        array[i] = rand() % 100;
    }
}

void bubleSort(int* array, const int size_array) {
    int aux;
    for (int i = 0; i < size_array; i++) {
        for (int j = 0; j < size_array - 1; j++) {
            if (array[j] > array[j + 1]) {
                aux = array[j];
                array[j] = array[j + 1];
                array[j + 1] = aux;
            }
        }
    }
}
