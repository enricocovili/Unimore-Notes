#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

bool isIn(int n, int* nums, int elem) {
    for (int i=0; i<n; i++) {
        if (nums[i] == elem)
            return true;
    }
    return false;
}

bool isValid(int n, int* grid, const int* s) {
    // rows
    double prev;
    double curr;
    for (int i = 0; i < n; i++) {
        curr = 1;
        for (int j = 0; j < n; j++) {
            curr *= s[grid[i*n+j]];
        }
        if (i == 0 || curr == prev) {
            prev = curr;
        } else {
            return false;
        }
    }
    // cols
    for (int i = 0; i < n; i++) {
        curr = 1;
        for (int j = 0; j < n; j++) {
            curr *= s[grid[i+j*n]];
        }
        if (i == 0 || curr == prev) {
            prev = curr;
        } else {
            return false;
        }
    }
    return true;
}

void RisolviProdottoRec(int n, const int* s,
                        int* current, int level,
                        int** solution) {
    if (level == n) {
        if (isValid((int)sqrt(n), current, s)) {
            *solution = calloc(sizeof(int), n*n);
            memmove(*solution, current, sizeof(int)*n*n);
        }
        return;
    }
    for (int i = 0; i < n && *solution == NULL; i++) {
        if (!isIn(n, current, i)) {
            current[level] = i;
            RisolviProdottoRec(n, s, current, level+1, solution);
            current[level] = -1;
        }
    }
}

extern int* RisolviProdotto(int n, const int *s) {
    int* nums = calloc(sizeof(int), n*n);
    for (int i = 0; i < n*n; i++) {
        nums[i] = -1;
    }
    int* solution = NULL;
    RisolviProdottoRec(n*n, s, nums, 0, &solution);
    free(nums);
    if (solution == NULL)
        return NULL;
    for (int i = 0; i < n*n; i++) {
        solution[i] = s[solution[i]];
    }
    return solution;
}

//int main(int argc, char** argv) {
//    int grid[] = {1, 2, 5, 8, 9, 16, 18, 40, 45};
//    int * res = RisolviProdotto(3, grid);
//    return 0;
//}