//
// Created by enri on 5/19/24.
//

#include <stdlib.h>
#include <stdbool.h>

extern void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

extern void CocktailSort(int *v, size_t v_size) {
    if (v_size <= 1)
        return;
    bool changes = true;
    size_t end = v_size, start = 0;
    while (changes && start < end) {
        changes = false;
        for (size_t i = start; i < end-1; i++) {
            if (v[i] > v[i+1]) {
                changes = true;
                swap(v+i,v+i+1);
            }
        }
        end--;
        for (size_t i = end-1; i > start; i--) {
            if (v[i] < v[i-1]) {
                changes = true;
                swap(v+i,v+i-1);
            }
        }
        start++;
    }
}

//int main(void) {
//    int vect[] = {1,3,5,4,2};
//    CocktailSort(vect, sizeof(vect)/sizeof(int));
//    return 0;
//}