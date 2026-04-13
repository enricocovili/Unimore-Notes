//
// Created by enri on 6/5/24.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

extern void printP(int *n, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (n[i] == 1)
            printf("(");
        else
            printf(")");
    }
    printf("\n");
}

extern void ParentesiRec(int n, int *tot, int *curr, int sum, int level) {
    if (level == n) {
        if (sum == 0) {
            printP(curr, n);
            *tot += 1;
        }
        return;
    }
    curr[level] = 1;
    ParentesiRec(n, tot, curr, sum+1, level+1);
    curr[level] = -1;
    if (sum - 1 >= 0)
        ParentesiRec(n, tot, curr, sum-1, level+1);
    curr[level] = 0;
}

extern int Parentesi(int n) {
    if (n < 0)
        return -1;
    int res = 0;
    int *curr = calloc(n*2, sizeof(int));
    ParentesiRec(n*2, &res, curr, 0, 0);
    free(curr);
    return res;
}

//int main() {
//    Parentesi(3);
//}