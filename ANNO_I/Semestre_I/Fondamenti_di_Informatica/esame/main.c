#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "blockfile.h"

int main(int argc, char **argv) {
  size_t size = 0;
  struct block *blocks = blockfile_load("file01.bin", &size, true);
  return 0;
}
