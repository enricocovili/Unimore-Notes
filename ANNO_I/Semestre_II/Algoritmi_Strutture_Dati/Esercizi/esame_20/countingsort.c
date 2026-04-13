//
// Created by enri on 6/4/24.
//

#include <stdlib.h>

extern void CountingSort(int *v, size_t v_size) {
    if (v == NULL || v_size == 0)
        return;
    int min = v[0], max = v[0];
    for (size_t i = 1; i < v_size; i++) {
        if (v[i] < min)
            min = v[i];
    }
    for (size_t i = 1; i < v_size; i++) {
        if (v[i] > max)
            max = v[i];
    }
    int *tmp = calloc(max-min+1, sizeof(int));
    for (size_t i = 0; i < v_size; i++) {
        tmp[v[i]-min]++;
    }
    int c = 0;
    for (int i = 0; i < max-min+1; i++) {
        for (int j = 0; j < tmp[i]; j++) {
            v[c] = i+min;
            c++;
        }
    }
    free(tmp);
}

//int main(void) {
//    int v[] = {1,6,2,4,5,5,5};
//    CountingSort(v, sizeof(v)/sizeof(int));
//    return 0;
//}