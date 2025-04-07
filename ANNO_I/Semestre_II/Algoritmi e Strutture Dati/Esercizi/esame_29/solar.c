//
// Created by enri on 5/19/24.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// appetibilità = quadrato maggiore nel numero
extern int* SolarCut(int A, size_t *sol_size) {
    int* pannelli = NULL;
    size_t tot_size = 0;
    while (A > 0) {
        int area = pow((int)sqrt(A), 2);
        A -= area;
        tot_size++;
        pannelli = realloc(pannelli, tot_size*sizeof(int));
        pannelli[tot_size-1] = area;
    }
    *sol_size = tot_size;
    return pannelli;
}

//int main(void) {
//    size_t size = 0;
//    int *res = SolarCut(12, &size);
//    return 0;
//}