//
// Created by enri on 5/26/24.
//

#include "pulce.h"

extern const Item* CalcolaPercorso(const Item *start, size_t n) {
    if (DListIsEmpty(start))
        return NULL;
    int counter = 0;
    Item* iterator = start;
    while (true) {
        ElemType tmpCounter = iterator->value;
        int step;
        if (tmpCounter < 0) {
            step = -1;
            tmpCounter = -tmpCounter;
        } else if (tmpCounter > 0) {
            step = 1;
        } else {
            break;
        }
        while (tmpCounter > 0 && counter <= n) {
            if (step == 1) {
                if (iterator->next != NULL) {
                    iterator = iterator->next;
                } else {
                    step = -step;
                    iterator = iterator->prev;
                }
            } else {
                if (iterator->prev != NULL) {
                    iterator = iterator->prev;
                } else {
                    step = -step;
                    iterator = iterator->next;
                }
            }
            tmpCounter--;
            counter++;
        }
        if (counter > n)
            break;
    }
    return iterator;
}

//int main(void) {
//    // create a list with elements 2,-3,4,1,0,5,-12,3
//    ElemType a[] = {2,-3,4,1,0,5,-12,3};
//    Item* i = DListCreateEmpty();
//    for (size_t j = 0; j < 8; j++) {
//        i = DListInsertBack(i, &a[j]);
//    }
//    // call the function
//    const Item* result = CalcolaPercorso(i->next->next, 12);
//    return 0;
//}