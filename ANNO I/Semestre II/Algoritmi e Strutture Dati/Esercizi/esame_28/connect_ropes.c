//
// Created by enri on 5/26/24.
//

#include "minheap.h"
#include <stdlib.h>

extern size_t ConnectRopes(Heap *ropes) {
    size_t len = 0;
    while (ropes->size > 2) {
        ElemType min = ropes->data[0];
        if (ropes->data[1] < ropes->data[2]) {
            ropes->data[0] += ropes->data[1];
            ropes->data[1] = ropes->data[--ropes->size];
            HeapMinMoveDown(ropes, 1);
        } else {
            ropes->data[0] += ropes->data[2];
            ropes->data[2] = ropes->data[--ropes->size];
            HeapMinMoveDown(ropes, 2);
        }
        len += ropes->data[0];
        HeapMinMoveDown(ropes, 0);
    }
    len += ropes->data[0]+ropes->data[1];
    return len;
}

//int main(void) {
//    Heap test;
//    test.data = malloc(sizeof(ElemType)*5);
//    test.size = 5;
//    test.data[0] = 1;
//    test.data[1] = 3;
//    test.data[2] = 4;
//    test.data[3] = 6;
//    test.data[4] = 4;
//    size_t aa = ConnectRopes(&test);
//
//    return 0;
//}