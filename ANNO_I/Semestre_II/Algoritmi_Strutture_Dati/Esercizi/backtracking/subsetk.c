
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void SubsetKRec(int n, int k, int i, bool vcurr[], int *nsol, int count) {
  if (count == k) {
    (*nsol)++;
    for (int j = 0; j < i; j++) {
      if (vcurr[j] == 1) {
        printf("%d,", j);
      }
    }
    printf("\n");
    return;
  }
  if (i == n) {
    return;
  }
  vcurr[i] = 0;
  SubsetKRec(n, k, i + 1, vcurr, nsol, count);
  vcurr[i] = 1;
  SubsetKRec(n, k, i + 1, vcurr, nsol, count + 1);
}

int SubsetK(int n, int k) {
  int nsol = 0;
  bool *vcurr = malloc(sizeof(int) * sizeof(bool));
  SubsetKRec(n, k, 0, vcurr, &nsol, 0);
  free(vcurr);
  return nsol;
}

int main(void) {
  SubsetK(4, 2);
  return 0;
}