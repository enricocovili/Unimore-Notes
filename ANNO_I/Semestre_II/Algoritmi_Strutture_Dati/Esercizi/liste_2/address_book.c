#include "elemtype.h"
#include "list.h"

extern const ElemType *Find(const Item *i, const char *name) {
    Item* iterator = i;
    while (iterator != NULL) {
        if (strcmp(iterator->value.name, name) == 0)
            return &(iterator->value);
        iterator = iterator->next;
    }
    return NULL;
}

extern Item *Delete(Item *i, const char *name) {
    Item* iterator = i;
    while (iterator != NULL) {
        if (iterator->next != NULL && strcmp(iterator->next->value.name, name) == 0) {
            Item* next = iterator->next->next;
            free(iterator->next);
            iterator->next = next;
            break;
        }
        iterator = iterator->next;
    }
    return i;
}

extern Item *Sort(Item *i) {
    Item* iterI = i;
    while (iterI != NULL) {
        Item* min = iterI;
        Item* iterJ = iterI->next;
        while (iterJ != NULL) {
            if (ElemCompare(&(iterJ->value), &(min->value)) < 0) {
                min = iterJ;
            }
            iterJ = iterJ->next;
        }
        ElemSwap(&(iterI->value), &(min->value));
        iterI = iterI->next;
    }
    return i;
}

Item *Filtra(const Item *i, const char *city) {
    Item* filtered = ListCreateEmpty();
    while (i != NULL) {
        if (strcmp(i->value.city, city) == 0) {
            filtered = ListInsertBack(filtered, &i->value);
        }
        i = i->next;
    }
    return filtered;
}

Item *Reverse(const Item *i) {
    Item* reversed = ListCreateEmpty();
    Item* original = i;
    while (i != NULL) {
        reversed = ListInsertHead(&i->value, reversed);
        i = i->next;
    }
    i = original;
    return reversed;
}

Item *Append(const Item *i1, const Item *i2) {
    Item* result = ListCreateEmpty();
    Item* iterator = i1;
    while(iterator != NULL) {
        result = ListInsertBack(result, &iterator->value);
        iterator = iterator->next;
    }
    iterator = i2;
    while (iterator != NULL) {
        result = ListInsertBack(result, &iterator->value);
        iterator = iterator->next;
    }
    return result;
}

//int main(void) {
//    // create a sample "Address" array of 3 elements
//    ElemType a1 = {"Mario Rossi", "Via Roma", 10, "Roma", "RM", "00100"};
//    ElemType a2 = {"Luca Verdi", "Via Milano", 20, "Milano", "MI", "20100"};
//    ElemType a3 = {"Paolo Bianchi", "Via Torino", 30, "Torino", "TO", "10100"};
//    Item *i = NULL;
//    i = ListInsertBack(i, &a1);
//    i = ListInsertBack(i, &a2);
//    i = ListInsertBack(i, &a3);
//    // print the list
//    ListWriteStdout(i);
//    Item* test = Append(i);
//    ListWriteStdout(test);
//}