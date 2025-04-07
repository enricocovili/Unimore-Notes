#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

struct point {
  int32_t x, y;
};
struct rect {
  struct point a, b;
};

extern bool rect_load(FILE *f, struct rect *r);