#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void print_boolVec(bool vec[], int n) {
  for (int i = 0; i < n; i++) {
    if (vec[i]) {
      printf("1,");
    } else {
      printf("0 ");
    }
  }
  printf("\n");
}

void OmbrelloniRec(int k, int n, int i, bool *vcurr, int cnt, int *nsol) {
  if (cnt == k) {
    // print_boolVec(vcurr, n);
    for (int j = 0; j < n - 1; j++) {
      if (vcurr[j] == 1 && vcurr[j + 1] == 1) {
        return;
      }
    }
    // valid
    (*nsol)++;
    printf("%4d) ", *nsol);
    for (int j = 0; j < n - 1; j++) {
      printf("%d ", vcurr[j]);
    }
    printf("%d\n", vcurr[n - 1]);
    return;
  }
  if (i == n) {
    return;
  }

  vcurr[i] = 0;
  OmbrelloniRec(k, n, i + 1, vcurr, cnt, nsol);

  vcurr[i] = 1;
  OmbrelloniRec(k, n, i + 1, vcurr, cnt + 1, nsol);
  vcurr[i] = 0;
}

extern int Ombrelloni(int k, int n) {
  if (k < 0 || n < 0) {
    return 0;
  }
  bool *vcurr = calloc(sizeof(bool), n);
  int nsol = 0;
  OmbrelloniRec(k, n, 0, vcurr, 0, &nsol);
  free(vcurr);
  return nsol;
}

// int main(void) {
//   Ombrelloni(2, 4);
//   return 0;
// }