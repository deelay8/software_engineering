#include <stdio.h>
#include <stdlib.h>
#define DATA_SIZE 1000000

// Function to perform insertion sort on an array
void insertionSort(int* arr, int size) {
    int i, j, key;

    // Start from the second element
    for (i = 1; i < size; i++) {
        key = arr[i]; // Store the current element

        // Move elements of arr[0..i-1], that are greater than key, to one position ahead of their current position
        for (j = i - 1; j >= 0 && arr[j] > key; j--) {
            arr[j + 1] = arr[j];
        }

        arr[j + 1] = key; // Place the key in its correct position
    }
}

int main() {
    int i;
    int arr[DATA_SIZE];

    // Initialize the array with random values
    for (i = 0; i < DATA_SIZE; i++) {
        arr[i] = rand() % 1000000;
    }

    printf("Before : ");
    for (i = 0; i < DATA_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Sort the array using insertion sort
    insertionSort(arr, DATA_SIZE);

    printf("After : ");
    for (i = 0; i < DATA_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Check if the array is sorted correctly
    for (i = 1; i < DATA_SIZE; i++) {
        if (arr[i] < arr[i - 1]) {
            printf("Error: Sorting failed at index %d.\n", i);
            break;
        }
    }

    return 0;
}
