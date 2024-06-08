#include "../elemtype.h"
#include "../list.h"

const ElemType *MaxElement(const Item *i) {
    ElemType* max = NULL;
    Item* iterator = i;
    while(iterator != NULL) {
        if (max == NULL || iterator->value > *max) {
            max = &iterator->value;
        }
        iterator = iterator->next;
    }
    return max;
}

//int main(void) {
//    ElemType e1[] = { 3, 4, 2, 0, 45, 1, 3 };
//    size_t size_e1 = sizeof(e1) / sizeof(ElemType);
//    Item* i1 = ListCreateEmpty();
//    for (size_t i = 0; i < size_e1; i++)
//    {
//        i1 = ListInsertBack(i1, &e1[i]);
//    }
//    ListWriteStdout(i1);
//    const ElemType* max = MaxElement(i1);
//    return 0;
//}