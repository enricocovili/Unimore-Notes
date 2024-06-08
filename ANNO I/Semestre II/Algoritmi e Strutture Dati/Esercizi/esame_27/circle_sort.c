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

extern void CircleSortRec(int *v, size_t start, size_t end) {
    if (start == end)
        return; // 1 element vector
    bool change = false;
    for (size_t i = start; i < end; i++) {
        if (v[i] > v[end-i-1]) {
            swap(v+i, v+end-i-1);
            change = true;
        }
    }
    if (end-start % 2 != 0 && v[(end+start)/2] > v[(end+start)/2+1]) {
        swap(v+(end+start)/2, v+(end+start)/2+1);
        change = true;
    }
    if (change) {
        if (end-start % 2 != 0) {
            CircleSortRec(v, start, end / 2 +1);
            CircleSortRec(v, end / 2 + 1, end);
        } else {
            CircleSortRec(v, start, end / 2);
            CircleSortRec(v, end / 2, end);
        }
    }
}

extern void CircleSort(int *v, size_t v_size) {
    if (v_size <= 1)
        return;
    CircleSortRec(v, 0, v_size/2);
}

int main(void) {
    int v[] = {3,1,-1};
    CircleSort(v, sizeof(v)/sizeof(int));
    return 0;
}