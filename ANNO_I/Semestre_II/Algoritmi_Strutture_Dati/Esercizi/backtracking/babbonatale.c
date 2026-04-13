#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void BabboNataleRec(const int *pacchi, size_t pacchi_size, int p,
                    unsigned int i, bool *vcurr, bool *vbest, int *max, int cnt,
                    int sum) {
  if (sum > p) {
    return;
  }
  if (cnt > *max) {
    memcpy(vbest, vcurr, pacchi_size);
    *max = cnt;
  }
  if (i == pacchi_size) {
    return;
  }
  vcurr[i] = 0;
  BabboNataleRec(pacchi, pacchi_size, p, i + 1, vcurr, vbest, max, cnt, sum);

  vcurr[i] = 1;
  cnt++;
  sum += pacchi[i];
  BabboNataleRec(pacchi, pacchi_size, p, i + 1, vcurr, vbest, max, cnt, sum);
  vcurr[i] = 0;
}

extern void BabboNatale(const int *pacchi, size_t pacchi_size, int p) {
  bool *vbest = calloc(sizeof(bool), pacchi_size);
  int max = 0;
  bool *vcurr = calloc(sizeof(bool), pacchi_size);
  BabboNataleRec(pacchi, pacchi_size, p, 0, vcurr, vbest, &max, 0, 0);
  for (size_t i = 0; i < pacchi_size - 1; i++) {
    printf("%d ", vbest[i]);
  }
  printf("%d", vbest[pacchi_size - 1]);
  free(vbest);
  free(vcurr);
  return;
}

// int main() {
//   int pacchi[] = {10, 11, 1, 3, 3};
//   BabboNatale(pacchi, 5, 20);
//   return 0;
// }