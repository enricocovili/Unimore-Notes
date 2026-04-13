#ifndef ESERCIZI_GIOIELLI_H
#define ESERCIZI_GIOIELLI_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int codice;
    float peso;
    float prezzo;
} Gioiello;

extern Gioiello *CompraGioielli(const char *filename, float budget, size_t *ret_size);

#endif //ESERCIZI_GIOIELLI_H
