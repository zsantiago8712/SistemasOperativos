#include "funciones.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

pthread_mutex_t lock;

void llenarArray(int* array, const int size_array) {
    srand(time(NULL));
    for (int i = 0; i < size_array; i++) {
        array[i] = rand() % 100;
    }
}

void* bubleSort(void* args) {
    ThreadArgs* actualArgs = (ThreadArgs*)args;
    int aux;

    pthread_mutex_lock(&lock);

    for (int i = actualArgs->left; i < actualArgs->righ; i++) {
        for (int j = actualArgs->left; j < actualArgs->righ; j++) {
            if (actualArgs->array[j] > actualArgs->array[j + 1]) {
                aux = actualArgs->array[j];
                actualArgs->array[j] = actualArgs->array[j + 1];
                actualArgs->array[j + 1] = aux;
            }
        }
    }

    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

void merge(int* array, int left, int middle, int right) {
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
