#include "maxheap.h"
#include <stdlib.h>
#include <stdio.h>
#include "math.h"

extern int MangiaCaramelle(Heap *h, int k) {
    if (h == NULL || h->size == 0)
        return 0;
    for(int i = 0; i < k; i++) {
        h->data[0] -= (h->data[0] - (int)sqrt(h->data[0]));
        HeapMaxMoveDown(h, 0);
    }
    int sum = 0;
    for (int i = 0; i < h->size; i++) {
        sum += h->data[i];
    }
    return sum;
}

//int main(void){
//    int* v1 = malloc(sizeof(int) * 6);
//    int* v2 = malloc(sizeof(int) * 8);
//    int* v3 = malloc(sizeof(int) * 9);
//    int* v4 = malloc(sizeof(int) * 4);
//    int* v5 = malloc(sizeof(int));
//
//    v1[0] = 23; v1[1] = 15; v1[2] = 16; v1[3] = 6; v1[4] = 2; v1[5] = 1;
//    v2[0] = 5; v2[1] = 6; v2[2] = 7; v2[3] = 8; v2[4] = 12; v2[5] = 7; v2[6] = 9; v2[7] = 10;
//    v3[0] = 0; v3[1] = 2; v3[2] = 4; v3[3] = 8; v3[4] = 12; v3[5] = 18; v3[6] = 77; v3[7] = 21; v3[8] = 9;
//    v4[0] = 100; v4[1] = 25; v4[2] = 64; v4[3] = 9; v4[4] = 4;
//    v5[0] = 3;
//
//    Heap* quasi_completo = HeapCreateEmpty(); quasi_completo->data = v1; quasi_completo->size = 6;
//    Heap* last_solo = HeapCreateEmpty(); last_solo->data = v2; last_solo->size = 8;
//    Heap* lungo = HeapCreateEmpty(); lungo->data = v3; lungo->size = 9;
//    Heap* corto = HeapCreateEmpty(); corto->data = v4; corto->size = 5;
//    Heap* vuoto = HeapCreateEmpty();
//    Heap* solo_root = HeapCreateEmpty(); solo_root->data = v5; solo_root->size = 1;
//
//    int res = MangiaCaramelle(vuoto, 4);
//
//    HeapDelete(quasi_completo); HeapDelete(last_solo); HeapDelete(lungo);
//    HeapDelete(corto); HeapDelete(vuoto); HeapDelete(solo_root);
//    return 0;
//}