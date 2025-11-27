//
// Created by enri on 6/5/24.
//

#include "minheap.h"
#include <stdlib.h>
#include <stdio.h>

extern Heap* MergeHeap(const Heap* h1, const Heap* h2) {
    Heap* res = HeapCreateEmpty();
    res->data = malloc(sizeof(ElemType)*(h1->size+h2->size));
    for (int i = 0; i < h1->size; ++i) {
        res->size++;
        res->data[res->size-1] = h1->data[i];
        HeapMinMoveUp(res, res->size-1);
    }
    for (int i = 0; i < h2->size; ++i) {
        res->size++;
        res->data[res->size-1] = h2->data[i];
        HeapMinMoveUp(res, res->size-1);
    }
    return res;
}

//int main(void){
//    int* v1 = malloc(sizeof(int) * 6);
//    int* v2 = malloc(sizeof(int) * 8);
//    int* v3 = malloc(sizeof(int) * 9);
//    int* v4 = malloc(sizeof(int) * 4);
//    int* v5 = malloc(sizeof(int));
//
//    v1[0] = 1; v1[1] = 5; v1[2] = 4; v1[3] = 6; v1[4] = 12; v1[5] = 23;
//    v2[0] = 5; v2[1] = 6; v2[2] = 7; v2[3] = 8; v2[4] = 12; v2[5] = 7; v2[6] = 9; v2[7] = 10;
//    v3[0] = 0; v3[1] = 2; v3[2] = 4; v3[3] = 8; v3[4] = 12; v3[5] = 18; v3[6] = 77; v3[7] = 21; v3[8] = 9;
//    v4[0] = -1; v4[1] = 3; v4[2] = 6; v4[3] = 4;
//    v5[0] = 3;
//
//    Heap* quasi_completo = HeapCreateEmpty(); quasi_completo->data = v1; quasi_completo->size = 6;
//    Heap* last_solo = HeapCreateEmpty(); last_solo->data = v2; last_solo->size = 8;
//    Heap* lungo = HeapCreateEmpty(); lungo->data = v3; lungo->size = 9;
//    Heap* corto = HeapCreateEmpty(); corto->data = v4; corto->size = 4;
//    Heap* vuoto = HeapCreateEmpty();
//    Heap* solo_root = HeapCreateEmpty(); solo_root->data = v5; solo_root->size = 1;
//
//    Heap* test = MergeHeap(corto, lungo);
//
//    HeapDelete(quasi_completo); HeapDelete(last_solo); HeapDelete(lungo);
//    HeapDelete(corto); HeapDelete(vuoto); HeapDelete(solo_root);
//    return 0;
//}