//
// Created by enri on 5/30/24.
//

#include <memory.h>
#include <stdlib.h>

#include "minheap.h"

int compare_ints(const void* a, const void* b) {
  int arg1 = *(const int*)a;
  int arg2 = *(const int*)b;

  if (arg1 < arg2) return -1;
  if (arg1 > arg2) return 1;
  return 0;
}

extern ElemType KthLeast(const Heap* h, int k) {
  ElemType* copy = calloc(h->size, sizeof(ElemType));
  memmove(copy, h->data, sizeof(ElemType) * h->size);
  qsort(copy, h->size, sizeof(ElemType), compare_ints);
  ElemType result = copy[k - 1];
  free(copy);
  return result;
}

// int main(void) {
//
// }