#include "vettore.h"

#include <memory.h>

int PushBack(Vector *v, ElemType *elem) {
  if (v->capacity == v->size) {
    (v->capacity) *= 2;
    v->data = realloc(v->data, v->capacity * sizeof(ElemType));
  }
  v->data[v->size] = *elem;
  (v->size)++;
  return 0;
}

Vector *VectorRead(const char *filename) {
  if (filename == NULL) return NULL;
  FILE *f = fopen(filename, "r");
  if (f == NULL) return NULL;

  Vector *vec = malloc(sizeof(Vector));
  vec->capacity = 1;
  vec->size = 0;
  vec->data = malloc(sizeof(ElemType));

  while (true) {
    ElemType temp;
    if (ElemRead(f, &temp) <= 0) {
      break;
    }
    PushBack(vec, &temp);
  }
  fclose(f);
  return vec;
}

Vector *VectorReadSorted(const char *filename) {
  if (filename == NULL) return NULL;
  FILE *f = fopen(filename, "r");
  if (f == NULL) return NULL;

  Vector *vec = malloc(sizeof(Vector));
  vec->capacity = 1;
  vec->size = 0;
  vec->data = calloc(1, sizeof(ElemType));

  while (true) {
    ElemType temp;
    if (ElemRead(f, &temp) <= 0) {
      break;
    }
    if (vec->capacity == vec->size) {
      (vec->capacity) *= 2;
      vec->data = realloc(vec->data, vec->capacity * sizeof(ElemType));
    }
    (vec->size)++;
    bool found = false;
    for (size_t i = 0; i < vec->size; i++) {
      if (ElemCompare(&temp, vec->data + i) == -1) {
        for (size_t j = vec->size - 1; j > i; j--) {
          vec->data[j] = vec->data[j - 1];
        }
        vec->data[i] = temp;
        found = true;
        break;
      }
    }
    if (!found) {
      vec->data[vec->size - 1] = temp;
    }
  }
  fclose(f);
  return vec;
}

void VectorSort(Vector *v) {
  if (v == NULL) {
    return;
  }
  for (size_t i = 0; i < v->size; i++) {
    for (size_t j = i + 1; j < v->size; j++) {
      if (v->data[j] < v->data[i]) {
        ElemSwap(v->data + j, v->data + i);
      }
    }
  }
}

int VectorFind(const Vector *v, const ElemType *e) {
  if (v == NULL || e == NULL) {
    return -1;
  }
  for (int i = 0; i < v->size; i++) {
    if (ElemCompare(v->data + i, e) == 0) {
      return i;
    }
  }
  return -1;
}

/*int main(void) {  //   Vector v = {.capacity = 1, .size = 0, .data =
  malloc(sizeof(ElemType));
  Vector *test = VectorRead("input_int_01.txt");
  VectorSort(test);
  for (int i = 0; i < test->size; i++) {
    printf("%d,", test->data[i]);
  }
  ElemType e = 1;
  printf("posizione 1: %d", VectorFind(test, &e));
  free(test->data);
  free(test);
  return 0;
}*/