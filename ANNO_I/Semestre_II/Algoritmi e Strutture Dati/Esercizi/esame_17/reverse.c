#include "../list.h"
#include "../elemtype.h"

extern Item *Reverse(Item *i) {
    Item* prev = NULL, *curr = i, *next = NULL;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

int main(void) {
    ElemType e1[] = { 7, 4, 2, 0, 45, 1, 5 };
    size_t size_e1 = sizeof(e1) / sizeof(ElemType);
    Item* i1 = ListCreateEmpty();
    for (size_t i = 0; i < size_e1; i++)
    {
        i1 = ListInsertBack(i1, &e1[i]);
    }
    ElemType e2[] = { 8, 5, 2, 3, 45, 7 };
    size_t size_e2 = sizeof(e2) / sizeof(ElemType);
    Item* i2 = ListCreateEmpty();
    for (size_t i = 0; i < size_e2; i++)
    {
        i2 = ListInsertBack(i2, &e2[i]);
    }
    ListWriteStdout(i1);
    i1 = Reverse(i1);
    ListWriteStdout(i1);
    return 0;
}