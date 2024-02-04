#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

void llenarArray(int* array, const int size_array) {
    
    srand(time(NULL));
    for (int i = 0; i < size_array; i++) {
        array[i] = rand() % 100;
    }
}
void bubleSort(int* array, int inicio, int fin) {
    int aux;
    for (int i = inicio; i < fin; i++) {
        for (int j = inicio; j < fin - 1; j++) {
            if (array[j] > array[j + 1]) {
                aux = array[j];
                array[j] = array[j + 1];
                array[j + 1] = aux;
            }
        }
    }
}



void merge(int *array, int left, int middle, int right) {
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Crear arrays temporales
    int L[n1], R[n2];

    // Copiar datos a los arrays temporales L[] y R[]
    for (i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (j = 0; j < n2; j++)
        R[j] = array[middle + 1 + j];

    // Fusionar los arrays temporales de vuelta en array[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de L[] y R[], si hay alguno
    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
}


int min(int a, int b) {
    return (a < b) ? a : b;
}
