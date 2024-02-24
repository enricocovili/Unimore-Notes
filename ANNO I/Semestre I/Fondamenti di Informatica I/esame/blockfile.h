#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct block {
  uint8_t name[9];  // Nel file il nome è composto da 8 byte
  uint64_t pos;
  uint64_t len;
  uint8_t *values;
};

extern struct block *blockfile_load(const char *filename, size_t *size,
                                    bool get_data);