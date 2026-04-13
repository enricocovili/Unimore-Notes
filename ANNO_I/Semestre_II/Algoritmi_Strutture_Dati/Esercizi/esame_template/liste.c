#include "list.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){
    Item *corta = ListCreateEmpty();
    Item *distinti = ListCreateEmpty();

    ElemType e1[] = { 3, 6, 1, 2, 9, 10, 4, 13 };
    ElemType e2[] = { 2, 3, 1, 4, 7, 2 };

    for (int i = 0; i < 8; i++)
        distinti = ListInsertBack(distinti, e3 + i);
    for (int i = 0; i < 6; i++)
        disordinata = ListInsertBack(disordinata, e4 + i);

    return 0;
}
