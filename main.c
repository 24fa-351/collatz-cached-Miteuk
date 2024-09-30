#include "collatz.h"

extern int cache_hits;
extern int cache_misses;

int main(int argc, char *argv[]){

    unsigned long long num = atoi(argv[1]);
    unsigned long long MIN = atoi(argv[2]);
    unsigned long long MAX = atoi(argv[3]);
    const char *policy = argv[4];
    unsigned long long cache_size = atoi(argv[5]);

    initialize_cache(policy, cache_size);

    srand(time(NULL));

    FILE* file = fopen("results.csv", "w");
    fprintf(file,"Random Number, Steps\n");

    //starts measuring the time for collatz
    clock_t start = clock();

    // Does Collatz
    for (int ix = 0; ix < num; ix++){
        int value = MIN + rand() % (MAX - MIN + 1);  //Random value between min and max
        unsigned long long steps = collatz_steps_cached(value);
        fprintf(file, "%d, %llu\n", value, steps);   

        if(policy != 0 && steps != -1){
            cache_hits++;
        } else {
            cache_misses++;
        }
    }

    clock_t end = clock();

    double total_time = (double)(end - start) / CLOCKS_PER_SEC;
    //Calculates the average time for num
    double mean_time = total_time / num;

    fclose(file);

    printf("Total time : %.6f seconds\n", total_time);
    printf("Mean time per number: %.6f seconds\n", mean_time);

    if (policy != 0) {
        printf("Cache Hits: %d\n", cache_hits);
        printf("Cache Misses: %d\n", cache_misses);
        if (cache_hits + cache_misses > 0) {
            printf("Cache Hit Rate: %.2f%%\n", (double)cache_hits / (cache_hits + cache_misses) * 100.0);
    }
    } else {
        printf("No cache policy was used.\n");
    }
   
    free_cache();

    return 0;
}
