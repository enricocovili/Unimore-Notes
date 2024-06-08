//
// Created by enri on 5/30/24.
//

#include <stdlib.h>
#include <memory.h>
#include "minheap.h"
#include "math.h"

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

extern void HeapMinMoveUpRec(Heap *h, int i) {
    if (i == 0)
        return;
    if (ElemCompare(HeapGetNodeValue(h, i), HeapGetNodeValue(h, HeapParent(i))) < 0)
        return HeapMinMoveUpRec(h, HeapParent(i));
    else
        ElemSwap(HeapGetNodeValue(h, i), HeapGetNodeValue(h, HeapParent(i)));
}

//int main(void) {
//    size_t size = 10;
//    ElemType vector[] = {2, 5, 6, 9, 1, 4, 3, 7, 8, 0};
//    Heap* test = HeapMinHeapify(vector, size);
//    return 0;
//}