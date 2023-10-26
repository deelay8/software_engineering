# include <stdio.h>
# include <stdlib.h>
# define DATA_SIZE 1000000

// Function to swap two integers
void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Function to partition the array and return the pivot index
int partition(int arr[], int p, int r){
    int x = arr[r]; // Choose the rightmost element as the pivot
    int i = (p - 1); // Initialize the index of smaller element

    // Traverse through all elements
    for(int j = p; j <= r -1; j++){
        if(arr[j] <= x){
            i++;
            swap(&arr[i], &arr[j]); // Swap if the current element is less than or equal to pivot
        }
    }
    swap(&arr[i + 1], &arr[r]); // Swap the pivot element with the element at (i + 1)
    return (i + 1); // Return the index of pivot element
}

// Recursive function to perform quicksort
void quicksort(int arr[], int p, int r){
    if(p < r){
        int q = partition(arr, p, r); // Get the pivot index
        quicksort(arr, p, q - 1); // Recursively sort elements before the pivot
        quicksort(arr, q + 1, r); // Recursively sort elements after the pivot
    }
}

int main(void){
    int i;
    int arr[DATA_SIZE];

    // Initialize the array with random values and print them
    for(i = 0; i < DATA_SIZE; i++){
        arr[i] = rand() % 1000;
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Sort the array using quicksort
    quicksort(arr, 0, DATA_SIZE - 1);

    // Count the number of elements that are not in sorted order
    int count = 0;
    for(i = 1; i < DATA_SIZE; i++){
        if(arr[i-1] > arr[i]){
            count++;
        }
    }
    printf("Not sorted count : %d", count);

    return 0;
}
