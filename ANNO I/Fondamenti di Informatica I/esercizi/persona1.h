#pragma once
#include <stdlib.h>

struct persona {
    int anni;
    char nome[50];
};

extern struct persona* leggi_persone(const char* filename, size_t* size);