#include "../elemtype.h"
#include "../list.h"

Item *Diff(const Item *i1, const Item *i2) {
    Item* diff = ListCreateEmpty();
    if (ListIsEmpty(i1)) {
        return diff;
    }
    Item* temp1 = i1;
    Item* temp2 = i2;
    bool found = false;
    while (temp1 != NULL) {
        temp2 = i2;
        while (temp2 != NULL) {
            if (temp2->value == temp1->value) {
                found = true;
                break;
            }
            temp2 = temp2->next;
        }
        if (!found)
            diff = ListInsertBack(diff, &temp1->value);
        found = false;
        temp1 = temp1->next;
    }
    return diff;
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
//    Item* r = Diff(i1, i2);
//    ListWriteStdout(r);
//    return 0;
//}