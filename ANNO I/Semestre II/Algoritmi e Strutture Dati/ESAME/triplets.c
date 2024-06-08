//
// Created by enri on 6/7/24.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void printTriplet(const int *v, const bool* selection, size_t v_size) {
    int c = 0;
    for (size_t i = 0; i < v_size; ++i) {
        if (selection[i] == true) {
            c++;
            if (c < 3)
                printf("%d, ",v[i]);
            else
            {
                printf("%d\n", v[i]);
                break;
            }
        }
    }
}

extern void TripletsRec(const int *v, size_t v_size, int n,
                        bool* curr, int currC, int currSum, size_t level,
                        int* tot) {
    if (currSum <= n && currC == 3) {
        *tot += 1;
        printTriplet(v, curr, v_size);
        return;
    }
    if (level == v_size) {
        return;
    }
    curr[level] = 0;
    TripletsRec(v, v_size, n, curr, currC, currSum, level+1, tot);
    if (currSum+v[level] > n)
        return;
    curr[level] = 1;
    TripletsRec(v, v_size, n, curr, currC+1, currSum+v[level], level+1, tot);
    curr[level] = 0;
}


extern int Triplets(const int *v, size_t v_size, int n) {
    if (v == NULL)
        return 0;
    int count = 0;
    bool* curr = calloc(v_size, v_size);
    TripletsRec(v, v_size, n, curr, 0, 0, 0, &count);
    free(curr);
    return count;
}

//int main(void) {
//    int v[] = {1, 3, 2, 5, 7, 6, 4};
//    int res = Triplets(v, sizeof(v)/sizeof(int), 9);
//    return 0;
//}