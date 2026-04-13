#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
  if (argc != 2) {
    return 1;
  }
  char* full_input = malloc(sizeof(char));
  int i = 0;
  for (i = 0;; i++) {
    int input = getchar();
    if (input == EOF || feof(stdin) != 0) {
      break;
    }
    full_input[i] = input;
    full_input = realloc(full_input, (i + 2) * sizeof(char));
  }
  full_input[i] = '\0';
  for (int i = 0; full_input[i] != '\0'; i++) {
    int found = 0;
    for (int j = 0; argv[1][j] != '\0'; j++) {
      if (argv[1][j] == full_input[i]) {
        found = 1;
        break;
      }
    }
    if (!found) {
      printf("%c", full_input[i]);
    }
  }
  free(full_input);
  return 0;
}