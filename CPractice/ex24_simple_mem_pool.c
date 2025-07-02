/**********************************************************************
 * \file        ex24_simple_mem_pool.c
 *
 * \brief       Create your own simple memory pool allocator using arrays and pointers.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        02.VII.2025 02:20AM
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FREE 0
#define BUSY 1

#define MEM_POOL_BLOCK_SIZE 100
#define MEM_POOL_BLOCK_NB 10

struct PoolHandlerArray{
    char memPool[MEM_POOL_BLOCK_NB][MEM_POOL_BLOCK_SIZE];
    char trackBlocks[MEM_POOL_BLOCK_NB];
};

struct PoolHandlerPointer{
    char** memPool;
    char trackBlocks[MEM_POOL_BLOCK_NB];
};

typedef struct PoolHandlerArray poolHandlerArray;
typedef struct PoolHandlerPointer poolHandlerPointer;

int initPoolArray(poolHandlerArray* const pool);
int initPoolPointer(poolHandlerPointer* const pool);
void* poolArrayAlloc(poolHandlerArray* const pool, const int size, int* index);
void* poolPointerAlloc(poolHandlerPointer* const pool, const int size, int* index);
void poolArrayPrint(const poolHandlerArray* const pool);
void poolPointerPrint(const poolHandlerPointer* const pool);
int poolArrayFree(poolHandlerArray* const pool,const int index);
int poolPointerFree(poolHandlerPointer* const pool,const int index);
void poolArrayDestroy(poolHandlerArray* pool);
void poolPointerDestroy(poolHandlerPointer* pool);

int main(void){
    poolHandlerArray poolArray;
    poolHandlerPointer poolPointer;

    //init the pools
    if(initPoolArray(&poolArray)==1){
        printf("Cannot init memory pool for array.\n");
        return 1;
    }    
    if(initPoolPointer(&poolPointer)==1){
        printf("Cannot init memory pool for pointer.\n");
        return 1;
    }

    printf("Pools statsus after init:\n");
    poolArrayPrint(&poolArray);
    poolPointerPrint(&poolPointer);

    //allocate pools
    int indexS,indexS1,indexS2,indexS3,indexS4,indexS5;
    char* string=(char*)poolArrayAlloc(&poolArray, MEM_POOL_BLOCK_SIZE/2,&indexS); //allocate half of block
    if(string == NULL) printf("Failed to allocate string.\n");
    char* string1=(char*)poolArrayAlloc(&poolArray, MEM_POOL_BLOCK_SIZE,&indexS1); //allocate one block
    if(string1 == NULL) printf("Failed to allocate string1.\n");
    char* string2=(char*)poolArrayAlloc(&poolArray, MEM_POOL_BLOCK_SIZE*2,&indexS2); //allocate two blocks
    if(string2 == NULL) printf("Failed to allocate string2.\n");
    char* string3=(char*)poolPointerAlloc(&poolPointer, MEM_POOL_BLOCK_SIZE/2,&indexS3); //allocate half of block
    if(string3 == NULL) printf("Failed to allocate string3.\n");
    char* string4=(char*)poolPointerAlloc(&poolPointer, MEM_POOL_BLOCK_SIZE,&indexS4); //allocate one block
    if(string4 == NULL) printf("Failed to allocate string4.\n");
    char* string5=(char*)poolPointerAlloc(&poolPointer, MEM_POOL_BLOCK_SIZE*2,&indexS5); //allocate two blocks
    if(string5 == NULL) printf("Failed to allocate string5.\n");
    printf("Pools statsus after first allocate:\n");
    poolArrayPrint(&poolArray);
    poolPointerPrint(&poolPointer);

    //free pools
    if(poolArrayFree(&poolArray,indexS) == 1) printf("Failed to free pool array 0.\n");
    if(poolArrayFree(&poolArray,5) == 1) printf("Failed to free pool array 5.\n");
    if(poolPointerFree(&poolPointer,indexS) == 1) printf("Failed to free pool pointer 0.\n");
    if(poolPointerFree(&poolPointer,5) == 1) printf("Failed to free pool pointer 5.\n");
    printf("Pools statsus after free:\n");
    poolArrayPrint(&poolArray);
    poolPointerPrint(&poolPointer);

    poolArrayDestroy(&poolArray);
    poolPointerDestroy(&poolPointer);

    return 0;
}

int initPoolArray(poolHandlerArray* const pool){
    if(pool == NULL) return 1;

    for(int i=0;i<MEM_POOL_BLOCK_NB;i++){
        for(int j=0;j<MEM_POOL_BLOCK_SIZE;j++){
            pool->memPool[i][j]=0;
        }
        pool->trackBlocks[i]=FREE;
    }

    return 0;
}

int initPoolPointer(poolHandlerPointer* const pool){
    if(pool == NULL) return 1;

    char** p=(char**)calloc(MEM_POOL_BLOCK_NB,sizeof(char*));
    if(p == NULL){
        printf("Cannot allocate memPoolPointer.\n");
        return 1;
    }
    for(int i=0; i<MEM_POOL_BLOCK_NB; i++){
        p[i]=(char*)calloc(MEM_POOL_BLOCK_SIZE,sizeof(char));
        if(p[i] == NULL){
            printf("Cannot allocate memPoolPointer[%d].\n",i);
            for(int j=0;j<i;j++) free(p[j]);
            free(p);
            return 1;
        }
        pool->trackBlocks[i]=FREE;
    }
    pool->memPool=p;
    return 0;
}

void* poolArrayAlloc(poolHandlerArray* const pool, const int size, int* index){
    if(pool == NULL) return NULL;
    if(size > MEM_POOL_BLOCK_SIZE) return NULL;

    //find empty block
    int i=0;
    for(;i<MEM_POOL_BLOCK_NB;i++){
        if(pool->trackBlocks[i]==FREE){
            pool->trackBlocks[i]=BUSY;
            break;
        }
    }

    //no free blocks
    if(i==MEM_POOL_BLOCK_NB) return NULL;
    //reserve the block  
    *index=i;
    return pool->memPool[i];
}

void* poolPointerAlloc(poolHandlerPointer* const pool, const int size, int* index){
    if(pool == NULL) return NULL;
    if(size > MEM_POOL_BLOCK_SIZE) return NULL;

    //find empty block
    int i=0;
    for(;i<MEM_POOL_BLOCK_NB;i++){
        if(pool->trackBlocks[i]==FREE){
            pool->trackBlocks[i]=BUSY;
            break;
        }
    }
    
    //no free blocks
    if(i==MEM_POOL_BLOCK_NB) return NULL;

    //reserve the block  
    *index=i;
    return pool->memPool[i];
}

void poolArrayPrint(const poolHandlerArray* const pool){
    printf("Pool array status is:\n");
    for(int i=0;i<MEM_POOL_BLOCK_NB;i++){
        printf("trackBlocks[%d]=%s\n",i,(pool->trackBlocks[i])?"BUSY":"FREE");
    }
}
void poolPointerPrint(const poolHandlerPointer* const pool){
    printf("Pool pointer status is:\n");
    for(int i=0;i<MEM_POOL_BLOCK_NB;i++){
        printf("trackBlocks[%d]=%s\n",i,(pool->trackBlocks[i])?"BUSY":"FREE");
    }
}


int poolArrayFree(poolHandlerArray* const pool,const int index){
    if(pool == NULL) return 1;
    if(index >= MEM_POOL_BLOCK_NB || index < 0) return 1;

    //find BUSY block
    int i=0;
    for(;i<MEM_POOL_BLOCK_NB;i++){
        if((pool->trackBlocks[i]==BUSY)&&(i==index)){
            pool->trackBlocks[i]=FREE;
            break;
        }
    }

    //no BUSY blocks
    if(i==MEM_POOL_BLOCK_NB) return 1;

    return 0;
}
int poolPointerFree(poolHandlerPointer* const pool,const int index){
    if(pool == NULL) return 1;
    if(index >= MEM_POOL_BLOCK_NB || index < 0) return 1;

    //find BUSY block
    int i=0;
    for(;i<MEM_POOL_BLOCK_NB;i++){
        if((pool->trackBlocks[i]==BUSY)&&(i==index)){
            pool->trackBlocks[i]=FREE;
            break;
        }
    }

    //no BUSY blocks
    if(i==MEM_POOL_BLOCK_NB) return 1;

    return 0;
}

void poolArrayDestroy(poolHandlerArray* pool){
    if (pool) {
        memset(pool->memPool, 0, sizeof(pool->memPool));
        memset(pool->trackBlocks, 0, sizeof(pool->trackBlocks));
    }
}

void poolPointerDestroy(poolHandlerPointer* pool){
    if(pool->memPool != NULL){
        for(int i=0; i<MEM_POOL_BLOCK_NB; i++){
            if(pool->memPool[i] != NULL){
                free(pool->memPool[i]);
            }
        } 
        free(pool->memPool);  
    }
    pool=NULL;
}