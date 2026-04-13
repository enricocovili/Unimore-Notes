#include <stdlib.h>
#include <string.h>

extern char *sostituisci(const char *str, const char *vecchia,
                         const char *nuova) {
  if (str == NULL || vecchia == NULL || nuova == NULL) {
    return NULL;
  }
  if (strlen(str) == 0) {
    char *res = malloc(1 * sizeof(char));
    res[0] = '\0';
    return res;
  }
  if (strlen(vecchia) == 0) {
    char *res = malloc((strlen(str) + 1) * sizeof(char));
    strcpy(res, str);
    return res;
  }
  char *res = calloc(200, sizeof(char));
  int start = 0, end = 0;
  int deltasize = strlen(nuova) - strlen(vecchia);
  while (1) {
    char *search = strstr(str + start, vecchia);
    if (search == NULL) {
      if (str[start] != '\0') {
        strcat(res, str + start);
      }
      break;
    }
    end = search - str;
    memcpy(res + strlen(res), str + start, end - start);
    strcat(res, nuova);
    start = end + strlen(vecchia);
    if (start > strlen(str)) {
      break;
    }
  }
  return res;
}