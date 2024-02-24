#pragma once

#include <stdio.h>
#include <stdlib.h>

struct value {
  char Date[11];
  double Open, High, Low, Close, AdjClose;
  long long Volume;
};

extern struct value *read_historical_series(const char *filename, size_t *n);