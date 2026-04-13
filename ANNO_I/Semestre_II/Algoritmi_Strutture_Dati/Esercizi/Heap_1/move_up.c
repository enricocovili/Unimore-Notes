//
// Created by enri on 5/30/24.
//

#include "minheap.h"
#include <stdlib.h>
#include <memory.h>
#include <math.h>

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

extern void HeapMinMoveUpRec(Heap *h, int i) {
    if (i == 0)
        return;
    if (ElemCompare(HeapGetNodeValue(h, i), HeapGetNodeValue(h, HeapParent(i))) < 0) {
        ElemSwap(HeapGetNodeValue(h, i), HeapGetNodeValue(h, HeapParent(i)));
        return HeapMinMoveUpRec(h, HeapParent(i));
    }
}

//int main(void) {
//    size_t size = 6;
//    ElemType vector[] = {1, 5, 4, 6, 3, 23};
//    Heap* test = HeapMinHeapify(vector, size);
//    HeapMinMoveUpRec(test, 4);
//    return 0;
//}