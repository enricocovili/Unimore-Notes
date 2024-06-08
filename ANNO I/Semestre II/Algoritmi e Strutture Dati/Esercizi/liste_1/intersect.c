#include "../elemtype.h"
#include "../list.h"

Item *Intersect(const Item *i1, const Item *i2) {
    Item *intersection = ListCreateEmpty();
    if (ListIsEmpty(i1) || ListIsEmpty(i2)) {
        return intersection;
    }
    Item* temp1 = i1;
    Item* temp2 = i2;
    while (temp1->next != NULL) {
        temp2 = i2;
        while (temp2->next != NULL) {
            if (temp2->value == temp1->value) {
                intersection = ListInsertBack(intersection, &temp2->value);
                break;
            }
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    return intersection;
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
//    ElemType e2[] = { 8, 5, 2, 3, 45, 7 };
//    size_t size_e2 = sizeof(e2) / sizeof(ElemType);
//    Item* i2 = ListCreateEmpty();
//    for (size_t i = 0; i < size_e2; i++)
//    {
//        i2 = ListInsertBack(i2, &e2[i]);
//    }
//    ListWriteStdout(i2);
//    Item* r = Intersect(i1, i2);
//    ListWriteStdout(r);
//    return 0;
//}