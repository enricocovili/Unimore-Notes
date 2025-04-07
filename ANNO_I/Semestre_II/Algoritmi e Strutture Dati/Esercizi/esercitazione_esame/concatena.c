//
// Created by enri on 5/31/24.
//

#include "doublelist.h"

extern Item *ConcatenaN(Item **v, size_t v_size) {
    if (v_size == 0)
        return NULL;
    int c = 0;
    while (v[c] == NULL) {
        c++;
        if (c == v_size - 1)
            return NULL;
    }
    Item* result = v[c];
    for (size_t i = c; i < v_size - 1; ++i) {
        Item* iterator = v[i];
        while (iterator != NULL && iterator->next != NULL) {
            iterator = iterator->next;
        }
        if (iterator != NULL) {
            while (v[i+1] == NULL && i < v_size-1) {
                i++;
            }
            iterator->next = v[i+1];
            if (i+1 < v_size)
                v[i+1]->prev = iterator;
        }
    }
    return result;
}

//int main(void) {
//    Item* l1 = DListCreateEmpty();
//    Item* l2 = DListCreateEmpty();
//    Item* l3 = DListCreateEmpty();
//    ElemType a = 1;
//    ElemType b = 2;
//    l2 = DListInsertHead(&a, l2);
//    l2 = DListInsertHead(&b, l2);
////    l3 = DListInsertHead(&a, l3);
////    l3 = DListInsertHead(&b, l3);
//    Item* arr[3] = {l1, l2, l3};
//    Item* final = ConcatenaN(arr, 3);
//    return 0;
//}
