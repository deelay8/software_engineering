#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000000

// Function to perform binary search on an array
int BinarySearch(int array[], int arraySize, int key)
{
        int low, high, mid;

        low = 0;
        high = arraySize;
        while (low <= high)
        {
                mid = (low + high) / 2;
                if (key == array[mid])
                {
                        return mid; // Key found, return its index
                }
                else if (key > array[mid])
                        low = mid + 1; // Adjust the lower bound
                else if (key < array[mid])
                        high = mid - 1; // Adjust the upper bound
        }
        return -1; // Key not found in the array
}

int main() {

        int array[SIZE];
        int i;
        array[0] = 1;

        // Generate and populate the array with random values
        for (i = 0; i < SIZE; i++)
        {
                array[i+1] = array[i] + (rand() % 1000000) + 1;
        }
        int arraySize = SIZE; // Size of the array
        int key;

        for (i = 0; i < SIZE; i++)
        {
                key = array[i];
                printf("%d\n", BinarySearch(array, arraySize, key)); // Print the result of binary search
                fflush(stdout);
                int ret = BinarySearch(array, arraySize, key);
                if (ret == -1) {
                        printf("Error\n"); // Print an error message if the key is not found
                        exit(0);
                }
        }

        return 0;
}

