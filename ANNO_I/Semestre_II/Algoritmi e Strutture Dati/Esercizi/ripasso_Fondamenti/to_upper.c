#include <stdlib.h>

extern void ToUpper(char *str) {
  if (str == NULL) {
    return;
  }
  for (int i = 0; *(str + i) != '\0'; i++) {
    char current = *(str + i);
    if (current >= 'a' && current <= 'z') {
      current -= 32;
    }
    *(str + i) = current;
  }
}

// int main() {
//   char test[] = "123abcDEF";
//   ToUpper(test);
//   return 0;
// }