//
// Created by enri on 5/14/24.
//
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <stdio.h>

extern int getNSatisfied(const int *bam, size_t bam_size) {
    int count = 0;
    for (size_t i=0; i<bam_size; ++i) {
        if (bam[i] <= 0)
            count++;
    }
    return count;
}

extern void AssegnaBiscottiRec(int* bam, size_t bam_size,
                              const int* bis, bool *bisTaken, size_t bis_size,
                              size_t index,
                              int *best) {
    if (*best == bam_size)
        return;
    int currSatisfied = getNSatisfied(bam, bam_size);
    if (currSatisfied > *best) {
        *best = currSatisfied;
    }
    for (size_t i = index; i<bam_size; ++i) {
        if (bam[i] <= 0)
            continue;
        for (size_t j=0; j<bis_size; ++j) {
            if (bisTaken[j] == false) {
                bisTaken[j] = true;
                bam[i] -= bis[j];
                AssegnaBiscottiRec(bam, bam_size, bis, bisTaken, bis_size, i, best);
                bisTaken[j] = false;
                bam[i] += bis[j];
            }
        }
    }
}

extern int AssegnaBiscotti(const int* bam, size_t bam_size,
                           const int* bis, size_t bis_size) {
    int best = -1;
    bool *bisTaken = calloc(bis_size, sizeof(bool));
    int* mutableBam = calloc(bam_size, sizeof(int));
    memmove(mutableBam, bam, bam_size*sizeof(int));
    AssegnaBiscottiRec(mutableBam, bam_size, bis, bisTaken, bis_size, 0, &best);
    free(bisTaken);
    free(mutableBam);
    return best;
}

//int main(void) {
//    int bam[] = {10, 10, 10};
//    int bis[] = {10, 12, 14};
//
////    int bam[] = {10, 20, 30};
////    int bis[] = {10, 6, 7, 8};
////
////    int bam[] = {10, 20, 30};
////    int bis[] = {10, 50};
//
//    size_t bam_size = 3;
//    size_t bis_size = 3;
//    int res = AssegnaBiscotti(bam, bam_size, bis, bis_size);
//    return 0;
//}
