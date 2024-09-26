
#include "collatz.h"


int main(int argc, char *argv[]){

    int num = atoi(argv[1]);
    int MIN = atoi(argv[2]);
    int MAX = atoi(argv[3]);
    //char *policy = atoi(argv[4]);
    int cache_size = atoi(argv[4]);

    srand(time(NULL));

    initialize_cache(cache_size);

    FILE* file = fopen("results.csv", "w");

    fprintf(file,"Random Number, Steps\n");


    for (int ix = 0; ix < num; ix++){
        int value = MIN + rand() % (MAX - MIN + 1);  //Random value between min and max
        int steps = collatz_steps_cached(value);
        fprintf(file, "%d,%d\n", value, steps);   
    }

    fclose(file);

    free_cache();

    return 0;
}
