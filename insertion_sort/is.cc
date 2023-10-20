#include <stdio.h>
#include <stdlib.h>
#define DATA_SIZE 1000000

void insertionSort(int* arr, int size) {
    int i, j, key;

    for (i = 1; i < size; i++) {
        key = arr[i];

        for (j = i - 1; j >= 0 && arr[j] > key; j--) {
            arr[j + 1] = arr[j];
        }

        arr[j + 1] = key;
    }
}

int main() {
    int i;
    int arr[DATA_SIZE];
    for (i = 0; i < DATA_SIZE; i++) {
        arr[i] = rand() % 1000000;
    }

    printf("Before : ");
    for (i = 0; i < DATA_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    insertionSort(arr, DATA_SIZE);

    printf("After : ");
    for (i = 0; i < DATA_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    for (i = 1; i < DATA_SIZE; i++) {
        if (arr[i] < arr[i - 1]) {
            printf("Error: Sorting failed at index %d.\n", i);
            break;
        }
    }

    return 0;
}
