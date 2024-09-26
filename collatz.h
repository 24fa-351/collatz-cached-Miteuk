#ifndef COLLATZ_H
#define COLLATZ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct CacheItem{
    int number;
    int steps;
    int lastUsed;
} CacheItem;

void initialize_cache(int size);
int collatz_steps(int n);
int collatz_steps_cached(int n);
void free_cache();


#endif 