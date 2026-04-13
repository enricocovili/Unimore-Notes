//
// Created by enri on 6/2/24.
//

#include "list.h"
#include <stdlib.h>
#include <stdio.h>

extern Item *PariDispari(Item *i) {
    if (ListIsEmpty(i))
        return NULL;
    Item* i1 = i;
    Item* i1prev = i;
    Item* i2 = i->next;
    Item* i2prev = i;
    while (i2 != NULL) {
        if (i1->value % 2 == 0) {
            i1prev = i1;
            i1 = i1->next;
            i2prev = i2;
            i2 = i2->next;
        } else {
            if (i2->value % 2 == 0) {
                Item* tmp = i2;
                i1->next = i2->next;
                i2->next = i1;
                i1prev->next = i2;
                i1 = i2;
            } else {
                i2prev = i2;
                i2 = i2->next;
            }
        }
    }
    return i;
}

int main(void){
    Item *vuota = ListCreateEmpty();
    Item *ordinata = ListCreateEmpty(), *disordinata = ListCreateEmpty();
    Item *doppioni = ListCreateEmpty(), *distinti = ListCreateEmpty();
    Item *corta = ListCreateEmpty(), *lunga = ListCreateEmpty();

    ElemType e1[] = { 3, 4, 5, 6, 12, 18, 21 };
    ElemType e2[] = { 3, 3, 4, 5, 6, 12, 18, 18, 21 };
    ElemType e3[] = { 3, 6, 1, 2, 9, 10, 4, 13 };
    ElemType e4[] = { 2, 3, 1, 4, 7, 2 };
    ElemType e5[] = { 1, 4, 3, 2 };
    ElemType e6[] = { 1, 3, 6, 8, 7, 4, 9, 5, 2, 10, 6, 13 };

    for (int i = 0; i < 7; i++)
        ordinata = ListInsertBack(ordinata, e1 + i);
    for (int i = 0; i < 9; i++)
        doppioni = ListInsertBack(doppioni, e2 + i);
    for (int i = 0; i < 8; i++)
        distinti = ListInsertBack(distinti, e3 + i);
    for (int i = 0; i < 6; i++)
        disordinata = ListInsertBack(disordinata, e4 + i);
    for (int i = 0; i < 4; i++)
        corta = ListInsertBack(corta, e5 + i);
    for (int i = 0; i < 12; i++)
        lunga = ListInsertBack(lunga, e6 + i);
    corta = PariDispari(corta);
    return 0;
}