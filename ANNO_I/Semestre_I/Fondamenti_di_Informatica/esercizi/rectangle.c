#include "rectangle.h"

#include <stdbool.h>
#include <stdlib.h>

extern bool rect_load(FILE *f, struct rect *r) {
  if (f == NULL) {
    return false;
  }
  for (int i = 0; i < 4; i++) {
    int32_t *val = NULL;
    switch (i) {
      case 0:
        val = &r->a.x;
        break;
      case 1:
        val = &r->a.y;
        break;
      case 2:
        val = &r->b.x;
        break;
      case 3:
        val = &r->b.y;
        break;
      default:
        break;
    }
    int ret_code = fread(val, sizeof(int32_t), 1, f);
    if (ret_code != 1) {
      return false;
    }
  }
  return true;
}