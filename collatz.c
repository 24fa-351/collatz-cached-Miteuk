#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int collatz_steps(int n)
{
    int steps = 0;

    while (n != 1){
        if(n % 2 == 0){
            n /= 2;
        } else {
            n = 3 * n + 1;
        }
        steps++;
    }
    return steps;
}

int main(int argc, char *argv[]){

    int num = atoi(argv[1]);
    int MIN = atoi(argv[2]);
    int MAX = atoi(argv[3]);

    srand(time(NULL));

    FILE* file = fopen("results.csv", "w");

    printf("Random Number, Steps\n");

    for (int ix = 0; ix < num; ix++){
        int value = rand() % (MAX - MIN + 1) + MIN;  //Random value between min and max
        int steps = collatz_steps(value);
        fprintf(file, "%ld,%d\n", value, steps);   
    }

    fclose(file);

}