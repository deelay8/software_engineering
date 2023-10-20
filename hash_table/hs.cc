#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DATA_SIZE 1000000
#define HASH_BUCKET_SIZE 2000000
#define Delta 3

int Data[DATA_SIZE];
int Hash[HASH_BUCKET_SIZE];

void hash(){

    Data[0] = rand() % 8;
    for(int i = 1; i < DATA_SIZE; i++){
        Data[i+1] = Data[i] + rand() % 10 + 1;
        // printf("%d,", Data[i]);
    }

    for(int i = 0; i < HASH_BUCKET_SIZE; i++){
        Hash[i] = -1;
    }

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

    // for(int i = 0; i < HASH_BUCKET_SIZE; i++){
    //     printf("%d\n", Hash[i]);
    // }
}

void hash_search(int key){

    int ad = key % HASH_BUCKET_SIZE;
    int count = 0;

    while(true){
        count++;
        if(Hash[ad] == -1){
            // printf("%d is not found", key);
            break;
        }
        else if(Hash[ad] == key){
            printf("%d is found (count : %d)\n", Hash[ad], count);
            break;
        }
        else {
            ad += Delta;
            if(ad >= HASH_BUCKET_SIZE) 
                ad -= HASH_BUCKET_SIZE;
        }
    }
}

int main(){
    hash();

    for(int i = 0; i < DATA_SIZE; i++){
        int key = Data[i];
        hash_search(key);
    }

    return 0;
}

