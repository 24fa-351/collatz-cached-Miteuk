#include "collatz.h"


#define MAX_CACHE_SIZE 100000000


CacheItem *cache = NULL;
int cache_size = MAX_CACHE_SIZE;
int policy = 0;
int current_cache_count = 0;  // Tracks how many times the cache has been accessed
int usaged_counter = 0;
int cache_hits = 0;
int cache_misses = 0;

void initialize_cache(const char *cache_policy, int size) {
    cache_size = size;
    current_cache_count = 0;
    usaged_counter = 0;
    cache_hits = 0;
    cache_misses = 0;

    if(strcmp(cache_policy, "none")==0) {
        policy = 0; // No caching
    } else if(strcmp(cache_policy,"LRU")==0) {
        policy = 1; // LRU
    } else if(strcmp(cache_policy,"LIFO")==0) {
        policy = 2; // MRU 
    }

    if(policy != 0) {
     cache = (CacheItem *)malloc(sizeof(CacheItem) * cache_size);
        for (int iy = 0; iy < cache_size; iy++) {
            cache[iy].number = -1;
            cache[iy].steps = -1;
            cache[iy].lastUsed = 0;
        }
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

void free_cache()
{
    if(cache != NULL){
        free(cache);
        cache = NULL;
    }
}

int get_lru_pos(){
    int index = 0;
    for (int i = 1; i < cache_size; i++){
        if(cache[i].lastUsed< cache[index].lastUsed){
            index = i;
            cache_misses++;
        }
    }
    return index;
}

int get_mru_pos(){
    cache_misses++;
    return current_cache_count - 1;
}

int collatz_steps_cached(int n) {

    if(policy == 0){
        return collatz_steps(n);
    }

   for (int ix = 0; ix < current_cache_count; ix++){
        if (cache[ix].number == n) {
            cache_hits++;
            usaged_counter++;
            cache[ix].lastUsed = usaged_counter;
            return cache[ix].steps;
        }
    }

    cache_misses++;
    int steps = collatz_steps(n);
  
    // USED FOR DEBUGGING
    // printf("Policy %d\n ", policy);
    // printf("current_cache_count %d\n ",current_cache_count);
    // printf("cache_size %d\n ",cache_size);

    if(current_cache_count < cache_size){
        //If cache isnt full
        usaged_counter++;
        cache[current_cache_count].number = n;
        cache[current_cache_count].steps = steps;
        cache[current_cache_count].lastUsed = usaged_counter;
        current_cache_count++;
    } 
    if (policy == 1){ 
        //LRU
        int index = get_lru_pos();
        cache[index].number = n;
        cache[index].steps = steps;
        cache[index].lastUsed = usaged_counter;
    } 
    if (policy == 2) {
        // LIFO/MRU
        int index = get_mru_pos();
        cache[index].number = n; // Replace the most recently added item
        cache[index].steps = steps;
        cache[index].lastUsed = usaged_counter;


        //USED FOR DEBUGGING
        // printf("did it get in here?");
        // printf("Cache size: %d\n",cache_size);
        // printf("cache lastUsed: %d\n",cache[index].steps);
        // printf("Cache steps: %d\n",cache[index].lastUsed);
        // printf("Cache number: %d\n",cache[index].number);
        // exit(0);
   
    }


    
    return steps;
}
