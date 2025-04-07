#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//int main(void) {
//    return 0;
//}

/* ALBERI
    ElemType v1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    // albero completo di 7 nodi (radice compresa)
    Node* TreeTest =
            TreeCreateRoot(v1 + 0,
                           TreeCreateRoot(v1 + 1,
                                          TreeCreateRoot(v1 + 3, NULL, NULL),
                                          TreeCreateRoot(v1 + 4, NULL, NULL)),
                           TreeCreateRoot(v1 + 2,
                                          TreeCreateRoot(v1 + 5, NULL, NULL),
                                          TreeCreateRoot(v1 + 6, NULL, NULL)));

    TreeDelete(TreeTest);
*/

/* LISTE
    Item *i1 = ListCreateEmpty();
    Item *i2 = ListCreateEmpty();

    ElemType e1[] = { 3, 6, 1, 2, 9, 10, 4, 13 };
    ElemType e2[] = { 2, 3, 1, 4, 7, 2 };

    for (int i = 0; i < sizeof(e1)/sizeof(ElemType); i++)
        i1 = ListInsertBack(i1, e1 + i);
    for (int i = 0; i < sizeof(e2)/sizeof(ElemType); i++)
        i2 = ListInsertBack(i2, e2 + i);
*/

/* MIN HEAP
    ElemType v[] = {1,5,4,6,12,23};
	ElemType* v = malloc(sizeof(int) * sizeof(v)/sizeof(ElemType));

	Heap* h_test = HeapCreateEmpty();
	h_test->data = v1;
	h_test->size = sizeof(v)/sizeof(ElemType);

	HeapDelete(h_test);
 */