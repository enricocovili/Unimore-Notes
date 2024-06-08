//
// Created by enri on 5/16/24.
//

#ifndef ESERCIZI_NO_CYCLE_H
#define ESERCIZI_NO_CYCLE_H

#include "elemtype.h"
#include "list.h"
#include <stdlib.h>

extern bool isIn(Item** seen, size_t size, Item* i);
extern void RemoveCycle(Item* i);

#endif //ESERCIZI_NO_CYCLE_H
