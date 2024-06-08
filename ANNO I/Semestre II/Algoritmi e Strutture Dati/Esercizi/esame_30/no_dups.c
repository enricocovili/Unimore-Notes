//
// Created by enri on 5/18/24.
//

#include "no_dups.h"

extern Item *RemoveDuplicates(const Item* i) {
    Item* res = ListCreateEmpty();
    Item* iterI = i;
    size_t counter = 0;
    while (iterI != NULL) {
        Item* iterJ = res;
        bool duplicate = false;
        while (iterJ != NULL) {
            if (ElemCompare(&iterI->value, &iterJ->value) == 0) {
                duplicate = true;
                break;
            }
            iterJ = iterJ->next;
        }
        if (!duplicate)
            res = ListInsertBack(res, &iterI->value);
        duplicate = false;
        iterI = iterI->next;
    }
    return res;
}

//int main(void) {
//    // sample list with duplicates
//    ElemType e1[] = { 3, 4, 2, 0, 45, 1, 3 };
//    size_t size_e1 = sizeof(e1) / sizeof(ElemType);
//    Item* i1 = ListCreateEmpty();
//    for (size_t i = 0; i < size_e1; i++)
//    {
//        i1 = ListInsertBack(i1, &e1[i]);
//    }
//    ListWriteStdout(i1);
//    Item* i2 = RemoveDuplicates(i1);
//    ListWriteStdout(i2);
//    return 0;
//}