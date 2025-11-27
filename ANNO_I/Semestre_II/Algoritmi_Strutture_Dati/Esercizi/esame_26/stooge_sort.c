//
// Created by enri on 6/4/24.
//

#include <stdlib.h>
#include "math.h"

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

extern void StoogeRec(int *v, size_t start, size_t end) {
    if (v[start] > v[end]) {
        swap(v+start, v+end);
    }
    if (end-start >= 3) {
        size_t len = end-start+1;
        StoogeRec(v, start, start + ceil((double)len*2/3));
        StoogeRec(v, start + ceil((double)len*2/3), end);
        StoogeRec(v, start, start + ceil((double)len*2/3));
    }
}

extern void Stooge(int *vector, size_t vector_size) {
    StoogeRec(vector, 0, vector_size-1);
}

int main(void) {
    int v[] = {3,1,-1, -5};
    Stooge(v, sizeof(v)/sizeof(int));
    return 0;
}