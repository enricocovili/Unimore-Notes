//
// Created by enri on 6/7/24.
//

#ifndef ESAME_FLOODFILL_H
#define ESAME_FLOODFILL_H

#include <stdlib.h>

struct Matrix {
    size_t rows, cols;
    char *data;
};

extern void FloodFill(struct Matrix *img, int x, int y, char old_color, char new_color);

#endif //ESAME_FLOODFILL_H
