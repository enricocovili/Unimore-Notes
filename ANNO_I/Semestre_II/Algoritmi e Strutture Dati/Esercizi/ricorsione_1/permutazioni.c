#include <stdio.h>
#include <stdlib.h>

void print_vector(int vect[], int l) {
  for (int i = 0; i < l; i++) {
    printf("%d ", vect[i]);
  }
  printf("\n");
}

void permutation(int n, int i, int vcurr[], int *nsol) {
  if (i == n) {
    print_vector(vcurr, n);
    *nsol = *nsol + 1;
    return;
  }
  for (int j = i; j < n; j++) {
    int tmp;
    tmp = vcurr[i];
    vcurr[i] = vcurr[j];
    vcurr[j] = tmp;

    permutation(n, i + 1, vcurr, nsol);

    tmp = vcurr[i];
    vcurr[i] = vcurr[j];
    vcurr[j] = tmp;
  }
}

int main() {
  int vect[] = {1, 2, 3};
  int n = 3;
  int *nsol = malloc(sizeof(int));
  permutation(n, 0, vect, nsol);
  printf("number of permutations: %d\n", *nsol);
}