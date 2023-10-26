#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DATA_SIZE 1000000
#define HASH_BUCKET_SIZE 2000000
#define Delta 3

int Data[DATA_SIZE]; // Array to store randomly generated data
int Hash[HASH_BUCKET_SIZE]; // Array representing the hash table

// Function to generate random data and populate the hash table
void hash(){

    Data[0] = rand() % 8;

    // Generate and populate the Data array
    for(int i = 1; i < DATA_SIZE; i++){
        Data[i+1] = Data[i] + rand() % 10 + 1;
    }

    // Initialize the Hash array with -1 (indicating empty slots)
    for(int i = 0; i < HASH_BUCKET_SIZE; i++){
        Hash[i] = -1;
    }

    // Hashing and placing data into the hash table
    for(int i = 0; i < DATA_SIZE; i++){
        int key = Data[i];
        int ad = key % HASH_BUCKET_SIZE;
        
        while(Hash[ad] != -1){
            ad += Delta;
            if(ad >= HASH_BUCKET_SIZE){
                ad -= HASH_BUCKET_SIZE;
            }
        }
        Hash[ad] = key;
    }
}

// Function to search for a key in the hash table
void hash_search(int key){

    int ad = key % HASH_BUCKET_SIZE;
    int count = 0;

    while(true){
        count++;
        if(Hash[ad] == -1){
            break; // Key is not found in the hash table
        }
        else if(Hash[ad] == key){
            printf("%d is found (count : %d)\n", Hash[ad], count);
            break; // Key is found in the hash table
        }
        else {
            ad += Delta;
            if(ad >= HASH_BUCKET_SIZE) 
                ad -= HASH_BUCKET_SIZE;
        }
    }
}

int main(){
    hash(); // Generate data and populate hash table

    // Search for each key in the hash table
    for(int i = 0; i < DATA_SIZE; i++){
        int key = Data[i];
        hash_search(key);
    }

    return 0;
}
