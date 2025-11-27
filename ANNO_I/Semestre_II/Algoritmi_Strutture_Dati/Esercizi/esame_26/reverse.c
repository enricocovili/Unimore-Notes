//
// Created by enri on 5/29/24.
//

#include "list.h"

extern Item* ReverseList(Item* list) {
    Item* prev = list;
    Item* curr = list->next;
    Item *next = NULL;
    // now reverse the linked list
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;

        prev = curr;
        curr = next;
    }
    list->next = NULL;
    list = prev;
    return list;
}

extern Item* Reverse(Item *list, int left) {
    if (list == NULL)
        return list;
    if (left < 0)
        left = 0;
    Item** iter = &list;
    int count = 0;
    while (true) {
        if (count == left) {
            *iter = ReverseList(*iter);
            return list;
        }
        iter = &((*iter)->next);
        count++;
        if (*iter == NULL || (*iter)->next == NULL)
            return list;
    }
}

//int main(void) {
//    ElemType e1[] = { 3, 4, 2, 0, 45, 1, 3 };
//    size_t size_e1 = sizeof(e1) / sizeof(ElemType);
//    Item* i1 = ListCreateEmpty();
//    for (size_t i = 0; i < size_e1; i++)
//    {   //peffavolle
//        i1 = ListInsertBack(i1, &e1[i]);
//    }
//    ListWriteStdout(i1);
//    Reverse(i1, 3);
//    ListWriteStdout(i1);
//    return 0;
//}