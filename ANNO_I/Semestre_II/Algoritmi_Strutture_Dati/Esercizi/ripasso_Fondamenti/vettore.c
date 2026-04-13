#include "vettore.h"

extern void Push(struct vettore *v, int d) {
  v->data = realloc(v->data, sizeof(int) * (v->size + 1));
  v->size++;
  v->data[v->size - 1] = d;
}

extern int Pop(struct vettore *v) {
  int res = v->data[0];
  for (int i = 1; i < v->size; i++) {
    v->data[i - 1] = v->data[i];
  }
  v->data = realloc(v->data, sizeof(int) * (v->size - 1));
  v->size--;
  return res;
}

// int main() {
//   struct vettore test;
//   test.size = 5;
//   test.data = malloc(sizeof(int) * test.size);
//   for (int i = 0; i < test.size; i++) {
//     test.data[i] = i + 1;
//   }
//   Push(&test, 6);
//   Pop(&test);
//   return 0;
// }