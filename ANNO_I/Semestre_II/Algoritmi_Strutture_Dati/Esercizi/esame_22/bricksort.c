//
// Created by enri on 6/4/24.
//

#include <stdlib.h>
#include <stdbool.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

extern void BrickSort(int* v, size_t v_size) {
    if (v_size <= 1)
        return;
    bool changes = true;
    while (changes) {
        changes = false;
        for (int i = 0; i < v_size - 1; i+=2) {
            if (v[i] > v[i+1]) {
                swap(v+i+1, v+i);
                changes = true;
            }
        }
        for (int i = 1; i < v_size - 1; i+=2) {
            if (v[i] > v[i+1]) {
                swap(v+i+1, v+i);
                changes = true;
            }
        }
    }
}

//int main(void) {
//    int v[] = {3,1,-1, -5};
//    BrickSort(v, sizeof(v)/sizeof(int));
//    return 0;
//}