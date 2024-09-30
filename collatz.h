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

void initialize_cache(const char *cache_policy, int size);
int collatz_steps(int n);
int collatz_steps_cached(int n);
void free_cache();
int get_lru_pos();
int get_mru_pos();

#endif 