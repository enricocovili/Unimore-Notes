//
// Created by enri on 5/31/24.
//

#ifndef ESERCIZI_PREZZO_H
#define ESERCIZI_PREZZO_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct Articolo {
    char nome[11];
    int prezzo;
};

extern void TrovaArticoli(const struct Articolo *a, size_t a_size, int sum);

#endif //ESERCIZI_PREZZO_H
