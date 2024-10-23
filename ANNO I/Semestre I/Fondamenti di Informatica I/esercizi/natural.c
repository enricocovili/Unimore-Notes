#include <stdlib.h>
#include <string.h>

int strcmp_natural(const char* a, const char* b) {
  if (a == 0 || b == 0) return 0;
  if (strcmp(a, b) == 0) return 0;
  int i = 0, minore;
  if (strlen(a) < strlen(b))
    minore = strlen(a);
  else {
    minore = strlen(b);
  }
  while (a[i] == b[i] && i < minore) {
    i++;
  }
  if (i == minore) {
    if (strlen(a) < strlen(b)) return -1;
    return 1;
  }
  if ((a[i] < 48 || a[i] > 57) && (b[i] < 48 || b[i] > 57)) {
    if (a[i] > b[i]) return 1;
    if (a[i] < b[i]) return -1;
  }
  if ((a[i] >= 48 && a[i] <= 57) && (b[i] >= 48 && b[i] <= 57)) {
    if (i > 0 && (a[i - 1] >= 48 || a[i - 1] <= 57)) {
      i -= 1;
    }
    int t = strtol(a + i, NULL, 10);
    int tt = strtol(b + i, NULL, 10);
    if (t > tt) return 1;
    return -1;
  }
  if ((a[i] >= 48 && a[i] <= 57)) {
    return -1;
  }
  if ((b[i] >= 48 && b[i] <= 57)) {
    return 1;
  }
}

// int main(void) {
//   char* a = "Xiph Xlater 58";
//   char* b = "Xiph Xlater 5000";
//   printf("%d\n", strcmp_natural(a, b));
//   return 0;
// }