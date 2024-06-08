//
// Created by enri on 5/30/24.
//

#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include "minheap.h"

extern Heap *HeapMinHeapify(const ElemType *v, size_t v_size) {
    Heap* result = malloc(sizeof(Heap));
    if (v == NULL){
        result->data = NULL;
        result->size = 0;
        return result;
    }
    result->size = v_size;
    result->data = malloc(sizeof(ElemType)*v_size);
    memmove(result->data, v, sizeof(ElemType)*v_size);
    int max_ix = (int)pow(2, (int)log2(v_size));
    for (int i = max_ix; i >= 0; i--) {
        HeapMinMoveDown(result, i);
    }
    return result;
}

void HeapMinHeapsort(Heap *h)
{
    size_t origin_size = h->size;
    while(h->size >= 2) {
        ElemSwap(HeapGetNodeValue(h, 0), HeapGetNodeValue(h, h->size - 1));
        h->size--;
        HeapMinMoveDown(h, 0);
    }
    h->size = origin_size;
    // reverse
//    for (int i = 0; i < h->size / 2 - 1; i++) {
//        ElemSwap(HeapGetNodeValue(h, i), HeapGetNodeValue(h, (int)h->size - 1 - i));
//    }
}

//int main(void) {
//    size_t size = 10;
//    ElemType vector[] = {2, 5, 6, 9, 1, 4, 3, 7, 8, 0};
//    Heap* test = HeapMinHeapify(vector, size);
//    HeapMinHeapsort(test);
//    return 0;
//}