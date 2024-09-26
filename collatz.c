#include "collatz.h"

CacheItem *cache = NULL;
int cache_size;
int cache_count = 0;  // Tracks how many times the cache has been accessed

void initialize_cache(int size) {
    cache_size = size;
    cache_count = 0;
    cache = (CacheItem *)malloc(sizeof(CacheItem) * cache_size);
    for (int iy = 0; iy < cache_size; iy++) {
        cache[iy].number = -1;
    }
}

// Function to calculate Collatz steps
int collatz_steps(int n) {
    int steps = 0;
    while (n != 1) {
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = 3 * n + 1;
        }
        steps++;
    }
    return steps;
}

int collatz_steps_cached(int n) {
   for (int ix = 0; ix < cache_size; ix++){
        if (cache[ix].number != -1) {
            return cache[ix].steps; 
        }
    }

    // Cache miss, compute the steps
    int steps = collatz_steps(n);

    if(cache_count<cache_size){
        cache[cache_count].number = n;
        cache[cache_count].steps = steps;
        cache_count++;
    }

    return steps;
}

void free_cache()
{
    free(cache);
}