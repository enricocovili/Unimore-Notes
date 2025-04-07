#include <stdbool.h>
#include <stdlib.h>

extern bool check_parenthesis(const char *s) {
  if (s == NULL) {
    return false;
  }
  int balance = 0;
  for (size_t i = 0; s[i] != '\0'; i++) {
    if (s[i] == '(') {
      balance++;
    } else if (s[i] == ')') {
      balance--;
    }
    if (balance < 0) {
      return false;
    }
  }
  if (balance == 0) {
    return true;
  }
  return false;
}