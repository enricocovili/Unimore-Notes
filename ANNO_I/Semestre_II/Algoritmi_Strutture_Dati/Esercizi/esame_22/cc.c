//
// Created by enri on 6/4/24.
//

#include "cc.h"

bool isIn(const ElemType* v, size_t v_size, ElemType elem) {
  for (size_t i = 0; i < v_size; i++) {
    if (elem == v[i]) return true;
  }
  return false;
}

extern int ComponentiConnesse(const Item* i, const ElemType* v, size_t v_size) {
  if (v == NULL || i == NULL) return 0;
  Item* iter = i;
  int c = 0;
  while (iter != NULL) {
    if (isIn(v, v_size, *ListGetHeadValue(iter))) {
      c++;
      while (iter->next != NULL &&
             isIn(v, v_size, *ListGetHeadValue(iter->next))) {
        iter = iter->next;
      }
    }
    iter = iter->next;
  }
  return c;
}

// int main(void){
//     Item *vuota = ListCreateEmpty();
//     Item *ordinata = ListCreateEmpty(), *disordinata = ListCreateEmpty();
//     Item *doppioni = ListCreateEmpty(), *distinti = ListCreateEmpty();
//     Item *corta = ListCreateEmpty(), *lunga = ListCreateEmpty();
//
//     ElemType e1[] = { 3, 4, 5, 6, 12, 18, 21 };
//     ElemType e2[] = { 3, 3, 4, 5, 6, 12, 18, 18, 21 };
//     ElemType e3[] = { 0, 1, 3, 4, 5, 6 ,8 ,7};
//     ElemType v[] =  { 7, 8, 0, 4, 6};
//     ElemType e4[] = { 2, 3, 1, 4, 7, 2 };
//     ElemType e5[] = { 1, 4, 3, 2 };
//     ElemType e6[] = { 1, 3, 6, 8, 7, 4, 9, 5, 2, 10, 6, 13 };
//
//     for (int i = 0; i < 7; i++)
//         ordinata = ListInsertBack(ordinata, e1 + i);
//     for (int i = 0; i < 9; i++)
//         doppioni = ListInsertBack(doppioni, e2 + i);
//     for (int i = 0; i < 8; i++)
//         distinti = ListInsertBack(distinti, e3 + i);
//     for (int i = 0; i < 6; i++)
//         disordinata = ListInsertBack(disordinata, e4 + i);
//     for (int i = 0; i < 4; i++)
//         corta = ListInsertBack(corta, e5 + i);
//     for (int i = 0; i < 12; i++)
//         lunga = ListInsertBack(lunga, e6 + i);
//
//     int res = ComponentiConnesse(distinti, v, sizeof(v)/sizeof(int));
//
//     return 0;
// }