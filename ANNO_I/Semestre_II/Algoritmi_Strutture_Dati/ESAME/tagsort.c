//
// Created by enri on 6/7/24.
//

#include <stdlib.h>
#include <stdbool.h>

bool isIn(const int *v, size_t v_size, int val) {
    for (size_t i = 0; i < v_size; i++) {
        if (v[i] == val)
            return true;
    }
    return false;
}

extern int* TaggedSort(const int *v, size_t v_size) {
    if (v == NULL)
        return NULL;
    int* mins = malloc(sizeof(int)*v_size);
    for (size_t i = 0; i < v_size; i++) {
        mins[i] = -1;
    }
    for (int i = 0; i < (int)v_size; i++) {
        int min = i;
        for (int j = 0; j < (int)v_size; j++) {
            if ((mins[i] == -1 || v[j] < v[min]) && !isIn(mins, v_size, j)) { // evito copia di V
                min = j;
                mins[i] = j;
            }
        }
        mins[i] = min;
    }
    return mins;
}

//int main(void) {
//    int v[] = {6, 3, 1, 4, 12, 24};
//    int *res = TaggedSort(v, sizeof(v)/sizeof(int));
//    return 0;
//}