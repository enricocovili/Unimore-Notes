#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

struct libro {
    char *titolo;
    uint16_t *anni_ristampe;
};

extern bool libro_scrivi(const struct libro *p, FILE *f);