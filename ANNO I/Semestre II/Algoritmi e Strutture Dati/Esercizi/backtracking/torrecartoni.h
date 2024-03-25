#pragma once

#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned p;  // Peso
  unsigned a;  // Altezza
  unsigned l;  // Limite
} Cartone;

extern void TorreCartoni(const Cartone *c, size_t n);