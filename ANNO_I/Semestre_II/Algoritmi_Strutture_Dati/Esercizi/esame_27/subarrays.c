//
// Created by enri on 5/27/24.
//

#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

extern void OptimalSubarrayRec(const int *v, size_t n,
                               int* bestSum, int currSum, int level) {
    currSum += v[level];
    if (currSum > *bestSum) {
        *bestSum = currSum;
    }
    if (level == n-1)
        return;
    OptimalSubarrayRec(v,n,bestSum, currSum, level+1);
}

extern int OptimalSubarray(const int *v, size_t n) {
    if (n == 0)
        return 0;
    int bestSum = 0;
    for (size_t i=0; i<n; i++)
        OptimalSubarrayRec(v, n, &bestSum, 0, i);
    return bestSum;
}

//int main(int argc, char** argv) {
//    int v[] = { -100, 5, 6, -3, 1, 2, 1 };
//    OptimalSubarray(v, 7);
//    return 0;
//}