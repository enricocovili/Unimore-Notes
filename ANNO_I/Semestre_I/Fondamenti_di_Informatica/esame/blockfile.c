#include "blockfile.h"

extern struct block *blockfile_load(const char *filename, size_t *size,
                                    bool get_data) {
  FILE *f = fopen(filename, "rb");
  if (f == NULL) {
    return NULL;
  }
  *size = 0;
  char *dummy = malloc(sizeof(char) * 8);
  while (true) {
    dummy = malloc(sizeof(char) * 8);
    if (fread(dummy, sizeof(char), 8, f) != 8) {
      break;
    }
    uint64_t len = 0;
    fread(&len, sizeof(uint64_t), len, f);
    uint8_t *dump = calloc(len, sizeof(uint8_t));
    fread(dump, 1, len, f);
    free(dump);
    *size = *size + 1;
  }
  struct block *blocks = malloc(sizeof(struct block) * (*size));
  rewind(f);
  for (int i = 0; i < *size; i++) {
    if (fread(dummy, sizeof(char), 8, f) != 8) {
      break;
    }
    blocks[i].pos = ftell(f) - 8;  // il blocco inizia dal nome
    memcpy(blocks[i].name, dummy, 8);
    fread(&blocks[i].len, 1, sizeof(uint64_t), f);
    if (get_data) {
      blocks[i].values = calloc(blocks[i].len, sizeof(uint8_t));
      fread(&blocks[i].values, sizeof(uint8_t), blocks[i].len, f);
    } else {
      uint8_t *dump = calloc(blocks[i].len, sizeof(uint8_t));
      fread(dump, sizeof(uint8_t), blocks[i].len, f);
      free(dump);
    }
  }
  free(dummy);
  fclose(f);
  return blocks;
}
