#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int aux[], int index[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (arr[index[i]] <= arr[index[j]]) {
            aux[k++] = index[i++];
        } else {
            aux[k++] = index[j++];
        }
    }

    while (i <= mid) {
        aux[k++] = index[i++];
    }

    while (j <= right) {
        aux[k++] = index[j++];
    }

    for (int l = left; l <= right; l++) {
        index[l] = aux[l];
    }
}

void mergeSort(int arr[], int aux[], int index[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, aux, index, left, mid);
        mergeSort(arr, aux, index, mid + 1, right);
        merge(arr, aux, index, left, mid, right);
    }
}

int main() {
    int Array1[] = {0, 1, 2, 3, 4};
    int Array2[] = {6, 4, 8, 3, 5};
    int Array3[] = {0, 32, 1000, 1200, 1400};
    int size = sizeof(Array1) / sizeof(Array1[0]);

    printf("Initial Array2[]: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", Array2[i]);
    }
    printf("\n");

    printf("Initial Corresponding Array1[]: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", Array1[i]);
    }
    printf("\n");

    printf("Initial Corresponding Array3[]: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", Array3[i]);
    }
    printf("\n\n");

    int index[size];  // To maintain the mapping of sorted indices
    int aux[size];    // Auxiliary array for merging

    for (int i = 0; i < size; i++) {
        index[i] = i;
    }

    mergeSort(Array2, aux, index, 0, size - 1);

    printf("Sorted Array2[]: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", Array2[index[i]]);
    }
    printf("\n");

    printf("Corresponding Array1[]: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", Array1[index[i]]);
    }
    printf("\n");

    printf("Corresponding Array3[]: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", Array3[index[i]]);
    }
    printf("\n");

    return 0;
}

