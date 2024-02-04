#pragma once

typedef struct{

    int* array;
    
    int left;
    int righ;

} ThreadArgs;


void llenarArray(int* array, const int size_array);

void* bubleSort(void* args);
void merge(int *array, int left, int middle, int right);
int min(int a, int b);