//
// Created by enri on 6/2/24.
//

#include "next_greater.h"

extern size_t listLen(const Item* list) {
    Item* iter = list;
    size_t c = 0;
    while (iter != NULL) {
        iter = iter->next;
        c++;
    }
    return c;
}

extern ElemType* NextGreater(const Item *list, size_t *answer_size) {
    if (ListIsEmpty(list)) {
        *answer_size = 0;
        return NULL;
    }
    size_t n = listLen(list);
    *answer_size = n;
    ElemType* answer = malloc(n*sizeof(ElemType));
    Item* i = list;
    Item* j = NULL;
    size_t c = 0;
    while (i != NULL) {
        bool found = false;
        j = i->next;
        while (j != NULL) {
            if (ElemCompare(ListGetHeadValue(j), ListGetHeadValue(i)) > 0) {
                answer[c] = *ListGetHeadValue(j);
                c++;
                found = true;
                break;
            }
            j = j->next;
        }
        if (!found) {
            answer[c] = INT_MIN;
            c++;
        }
        i = i->next;
    }
    return answer;
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
//    ElemType e5[] = { 1, 4, 3, 2 };
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
//    size_t test = 0;
//    ElemType* res = NextGreater(disordinata, &test);
//    return 0;
//}