//
// Created by enri on 5/16/24.
//

#include "no_cycle.h"

extern bool isIn(Item** seen, size_t size, Item* i) {
    for (size_t j = 0; j<size; j++) {
        if (seen[j] == i) {
            return true;
        }
    }
    return false;
}

extern void RemoveCycle(Item* i) {
    if (i == NULL)
        return;
    Item **seen = malloc(sizeof(Item*));
    seen[0] = i;
    int counter = 1;
    while (i != NULL) {
        if (isIn(seen, counter, i->next) && i->next != NULL) {
            i->next = NULL;
            break;
        }
        seen = realloc(seen, sizeof(Item*)*(counter+1));
        seen[counter] = i->next;
        i = i->next;
        counter++;
    }
    free(seen);
}

//int main(void) {
//    ElemType e1[] = { 3, 4, 2, 0, 45, 1, 3 };
//    size_t size_e1 = sizeof(e1) / sizeof(ElemType);
//    Item* i1 = ListCreateEmpty();
//    for (size_t i = 0; i < size_e1-1; i++)
//    {
//        i1 = ListInsertBack(i1, &e1[i]);
//    }
//    i1 = ListInsertBack(i1, &e1[0]);
//    RemoveCycle(i1);
//    ListWriteStdout(i1);
//    return 0;
//}