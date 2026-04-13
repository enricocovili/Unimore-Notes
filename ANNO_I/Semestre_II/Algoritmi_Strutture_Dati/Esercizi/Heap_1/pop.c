//
// Created by enri on 5/30/24.
//

#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <math.h>
#include "minheap.h"

//extern Heap *HeapMinHeapify(const ElemType *v, size_t v_size) {
//    Heap* result = malloc(sizeof(Heap));
//    if (v == NULL){
//        result->data = NULL;
//        result->size = 0;
//        return result;
//    }
//    result->size = v_size;
//    result->data = malloc(sizeof(ElemType)*v_size);
//    memmove(result->data, v, sizeof(ElemType)*v_size);
//    int max_ix = (int)pow(2, (int)log2(v_size));
//    for (int i = max_ix; i >= 0; i--) {
//        HeapMinMoveDown(result, i);
//    }
//    return result;
//}

extern bool HeapMinPop(Heap *h, ElemType *e) {
    if (HeapIsEmpty(h))
        return false;
    *e = h->data[0];
    ElemSwap(HeapGetNodeValue(h, 0), HeapGetNodeValue(h, h->size-1));
    h->size -= 1;
    HeapMinMoveDown(h, 0);
    return true;
}

//int main(void) {
//    size_t size = 10;
//    ElemType vector[] = {2, 5, 6, 9, 1, 4, 3, 7, 8, 0};
//    Heap* test = HeapMinHeapify(vector, size);
//    HeapMinPop(test, 0);
//    return 0;
//}