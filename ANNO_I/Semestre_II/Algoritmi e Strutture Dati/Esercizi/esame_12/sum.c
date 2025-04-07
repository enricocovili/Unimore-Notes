//
// Created by enri on 6/5/24.
//

#include "list.h"

extern Item* Sum(const Item *i1, const Item *i2) {
    if (i1 == NULL && i2 == NULL)
        return NULL;
    Item *result = ListCreateEmpty();
    Item *iter1 = i1, *iter2 = i2;
    while (iter1 != NULL || iter2 != NULL) {
        if (iter1 == NULL) {
            result = ListInsertBack(result, &iter2->value);
            iter2 = iter2->next;
        } else if (iter2 == NULL) {
            result = ListInsertBack(result, &iter1->value);
            iter1 = iter1->next;
        } else {
            ElemType sum = iter1->value+iter2->value;
            result = ListInsertBack(result, &sum);
            iter1 = iter1->next;
            iter2 = iter2->next;
        }
    }
    Item *iterRes = result;
    while (iterRes != NULL) {
        if (iterRes->value > 9) {
            if (iterRes->next == NULL) {
                ElemType placeholder = 1;
                result = ListInsertBack(result, &placeholder);
            } else {
                iterRes->next->value += 1;
            }
            iterRes->value -= 10;
        }
        iterRes = iterRes->next;
    }
    return result;
}

//int main(void){
//    Item *vuota = ListCreateEmpty();
//    Item *ordinata = ListCreateEmpty(), *disordinata = ListCreateEmpty();
//    Item *doppioni = ListCreateEmpty(), *distinti = ListCreateEmpty();
//    Item *corta = ListCreateEmpty(), *lunga = ListCreateEmpty();
//
//    ElemType e1[] = { 3, 4, 5, 6, 12, 18, 21 };
//    ElemType e2[] = { 3, 3, 4, 5, 6, 12, 18, 18, 21 };
//    ElemType e3[] = { 3, 6, 1, 2, 9, 10, 4, 13 };
//    ElemType e4[] = { 2, 3, 1, 4, 7, 2 };
//    ElemType e5[] = { 1, 5, 3, 2 };
//    ElemType e6[] = { 1, 3, 6, 8, 7, 4, 9, 5, 2, 10, 6, 13 };
//
//    for (int i = 0; i < 7; i++)
//        ordinata = ListInsertBack(ordinata, e1 + i);
//    for (int i = 0; i < 9; i++)
//        doppioni = ListInsertBack(doppioni, e2 + i);
//    for (int i = 0; i < 8; i++)
//        distinti = ListInsertBack(distinti, e3 + i);
//    for (int i = 0; i < 6; i++)
//        disordinata = ListInsertBack(disordinata, e4 + i);
//    for (int i = 0; i < 4; i++)
//        corta = ListInsertBack(corta, e5 + i);
//    for (int i = 0; i < 12; i++)
//        lunga = ListInsertBack(lunga, e6 + i);
//
//    Item* res = Sum(corta, corta);
//    return 0;
//}