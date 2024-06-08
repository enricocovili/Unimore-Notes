//
// Created by enri on 5/27/24.
//

#include "doublelist.h"
#include <stdlib.h>

extern Item* DListSum(const Item *i1, const Item *i2) {
    Item* iter1 = i1;
    Item* iter2 = i2;
    while (iter1 != NULL && iter1->next != NULL)
        iter1 = iter1->next;
    while (iter2 != NULL && iter2->next != NULL)
        iter2 = iter2->next;
    Item *res = DListCreateEmpty();
    while (iter1 != NULL || iter2 != NULL) {
        if (iter1 == NULL) {
            res = DListInsertHead(&iter2->value, res);
            iter2 = iter2->prev;
        } else if (iter2 == NULL){
            res = DListInsertHead(&iter1->value, res);
            iter1 = iter1->prev;
        } else {
            ElemType e_tmp = iter2->value + iter1->value;
            res = DListInsertHead(&e_tmp, res);
            iter1 = iter1->prev;
            iter2 = iter2->prev;
        }
    }
    Item* iterRes = res;
    while (iterRes != NULL && iterRes->next != NULL) {
        iterRes = iterRes->next;
    }
    while (iterRes != NULL) {
        if (iterRes->value > 9) {
            if (iterRes->prev != NULL) {
                iterRes->prev->value += 1;
            } else {
                ElemType e_tmp = 1;
                res = DListInsertHead(&e_tmp, res);
            }
            iterRes->value -= 10;
        }
        iterRes = iterRes->prev;
    }
    return res;
}


//int main(void) {
//    ElemType e1[] = { 9, 9, 9, 9 };
//    size_t size_e1 = sizeof(e1) / sizeof(ElemType);
//    Item* i1 = DListCreateEmpty();
//    for (size_t i = 0; i < size_e1; i++)
//    {
//        i1 = DListInsertBack(i1, &e1[i]);
//    }
//    ElemType e2[] = { 1 };
//    size_t size_e2 = sizeof(e2) / sizeof(ElemType);
//    Item* i2 = DListCreateEmpty();
//    for (size_t i = 0; i < size_e2; i++)
//    {
//        i2 = DListInsertBack(i2, &e2[i]);
//    }
//    Item* res = DListSum(i1,i2);
//    return 0;
//}