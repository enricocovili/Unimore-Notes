//
// Created by enri on 6/5/24.
//

#include <stdlib.h>

extern void swap(int *a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

extern void GnomeSort(int *v, size_t v_size) {
    int index = 0;
    while(index != v_size) {
        if (index == 0) {
            index++;
        }
        else if (v[index] < v[index-1]) {
            swap(v+index, v+index-1);
            index--;
        }
        else {
            index++;
        }
    }
}

//int main() {
//    int v[] = {3,0,4,7,1,-1};
//    GnomeSort(v, sizeof(v)/sizeof(int));
//    return 0;
//}
