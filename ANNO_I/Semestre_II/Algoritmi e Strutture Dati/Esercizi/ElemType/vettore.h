#pragma once

#include <stdlib.h>

#include "elemtype.h"

typedef struct {
  size_t capacity;
  size_t size;
  ElemType *data;
} Vector;

Vector *VectorRead(const char *filename);
Vector *VectorReadSorted(const char *filename);
int PushBack(Vector *v, ElemType *elem);
void VectorSort(Vector* v);
int VectorFind(const Vector *v, const ElemType *e);