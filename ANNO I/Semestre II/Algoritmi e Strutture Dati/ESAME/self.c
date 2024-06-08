//
// Created by enri on 6/7/24.
//

#include "self.h"

extern Item* SelfOrganizingFind(Item* i, const ElemType *e) {
    Item* iter = i;
    Item* res = i;
    while (iter != NULL && iter->next != NULL) {
        if (ElemCompare(e, ListGetHeadValue(iter->next)) == 0) {
            res = iter->next;
            iter->next = iter->next->next;
            res->next = i;
            break;
        }
        iter = iter->next;
    }
    return res;
}


//int main(void) {
//    Item *i1 = ListCreateEmpty();
//    Item *i2 = ListCreateEmpty();
//
//    ElemType e1[] = { 3, 6, 1, 2, 9, 10, 4, 13 };
//    ElemType e2[] = { 2, 3, 1, 4, 7, 2 };
//
//    for (int i = 0; i < sizeof(e1)/sizeof(ElemType); i++)
//        i1 = ListInsertBack(i1, e1 + i);
//    for (int i = 0; i < sizeof(e2)/sizeof(ElemType); i++)
//        i2 = ListInsertBack(i2, e2 + i);
//
//    ElemType target = 1;
//    i1 = SelfOrganizingFind(i1, &target);
//    return 0;
//}