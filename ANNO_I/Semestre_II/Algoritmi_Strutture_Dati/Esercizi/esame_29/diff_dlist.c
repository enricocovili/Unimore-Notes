//
// Created by enri on 5/19/24.
//

#include "diff_dlist.h"

size_t listLen(const Item* list) {
    size_t len = 0;
    Item* iterator = list;
    while (iterator != NULL) {
        iterator = iterator->next;
        len++;
    }
    return len;
}

extern Item* DListDiff(const Item *i1, const Item *i2) {
    if (i1 == NULL)
        return DListCreateEmpty();
    Item* result = DListCreateEmpty();
    size_t l1 = listLen(i1);
    size_t l2 = listLen(i2);
    Item* iter1 = i1;
    Item* iter2 = i2;
    for (size_t i=0; i<l1-l2; i++) {
        result = DListInsertBack(result, &iter1->value);
        iter1 = iter1->next;
    }
    while(iter1 != NULL) {
        ElemType val = iter1->value - iter2->value;
        result = DListInsertBack(result, &val);
        iter1 = iter1->next;
        iter2 = iter2->next;
    }
    Item* res_iter = result;
    while (res_iter != NULL) {
        if (res_iter->value < 0) {
            res_iter->prev->value -= 1;
            res_iter->value = 10+res_iter->value;
            res_iter = result;
            continue;
        }
        res_iter = res_iter->next;
    }
    return result;
}

//int main(void) {
//    ElemType e1[] = { 1, 0, 0, 0 };
//    size_t size_e1 = sizeof(e1) / sizeof(ElemType);
//    Item* i1 = DListCreateEmpty();
//    for (size_t i = 0; i < size_e1; i++)
//    {
//        i1 = DListInsertBack(i1, &e1[i]);
//    }
//    ElemType e2[] = { 9 };
//    size_t size_e2 = sizeof(e2) / sizeof(ElemType);
//    Item* i2 = DListCreateEmpty();
//    for (size_t i = 0; i < size_e2; i++)
//    {
//        i2 = DListInsertBack(i2, &e2[i]);
//    }
//    Item* res = DListDiff(i1,i2);
//    return 0;
//}