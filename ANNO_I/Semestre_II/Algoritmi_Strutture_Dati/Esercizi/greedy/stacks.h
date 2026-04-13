#ifndef ESERCIZI_STACKS_H
#define ESERCIZI_STACKS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    unsigned *elements;
    size_t m;
} Stack;

extern unsigned MaxSumNStack(Stack *stacks, size_t n);
extern unsigned *StackSums(Stack *stacks, size_t n);

#endif //ESERCIZI_STACKS_H
