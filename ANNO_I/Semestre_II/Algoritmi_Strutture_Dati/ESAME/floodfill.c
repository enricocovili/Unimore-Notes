//
// Created by enri on 6/7/24.
//

#include "floodfill.h"

extern void FloodFill(struct Matrix *img, int x, int y, char old_color, char new_color) {
    if (x < 0 || x >= (int)img->cols || y < 0 || y >= (int)img->rows) {
        return;
    }
    if (img->data[y * img->cols + x] == old_color) {
        img->data[y * img->cols + x] = new_color;
        FloodFill(img, x+1, y, old_color, new_color);
        FloodFill(img, x-1, y, old_color, new_color);
        FloodFill(img, x, y+1, old_color, new_color);
        FloodFill(img, x, y-1, old_color, new_color);
    }
}

//int main(void) {
//    char data[] = {1,1,3,4,4,1,3,4,3,1,3,3,3,1,3,3,4,1,1,1};
//    struct Matrix test = {.cols = 4, .rows = 5, .data=data};
//    FloodFill(&test, 0, 0, 1, 5);
//    return 0;
//}