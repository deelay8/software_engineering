#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000000

int BinarySearch(int array[], int arraySize ,int key)
{
        int low,high,mid;

        low = 0;
        high = arraySize;
        while(low <= high)
        {
                mid = (low + high) / 2;
                if(key == array[mid])
                {
                        return mid;
                }
                else if(key > array[mid])
                        low = mid + 1;
                else if(key < array[mid])
                        high = mid - 1;
        }
        return -1;
}

int main() {

        int array[SIZE];
        int i;
        array[0] = 1;
        for(i = 0; i <= SIZE; i++)
        {
                array[i+1] = array[i] + (rand() % 1000000) + 1;
        }
        int arraySize = sizeof(array) - 1;
        int key;

        for(i = 0; i < SIZE; i++)

        {

                key = array[i];
                printf("%d\n",BinarySearch(array, arraySize ,key));
                fflush(stdout);
                int ret = BinarySearch(array, arraySize ,key);
                if (ret == -1) {
                        printf("Error\n");
                        exit(0);
                }
        }

}
