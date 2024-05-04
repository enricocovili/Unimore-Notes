#include "stacks.h"

extern bool areAllEqual(const unsigned* sums, size_t n) {
    for (size_t i=0; i<n-1; i++) {
        if (sums[i] != sums[i+1]) {
            return false;
        }
    }
    return true;
}

extern size_t getMax(const unsigned* sums, size_t n) {
    size_t max = 0;
    size_t max_ix = 0;
    for (size_t i = 0; i<n; i++) {
        if (sums[i] > max) {
            max_ix = i;
            max = sums[i];
        }
    }
    return max_ix;
}

extern unsigned *StackSums(Stack *stacks, size_t n) {
    unsigned *res = calloc(n, sizeof(unsigned));
    for (int i=0; i<n; i++) {
        for (int j=0; j<stacks[i].m; j++) {
            res[i] += stacks[i].elements[j];
        }
    }
    return res;
}

extern unsigned MaxSumNStack(Stack *stacks, size_t n) {
    unsigned *stacksSums = StackSums(stacks, n);
    while (!areAllEqual(stacksSums, n)) {
        size_t maxStack = getMax(stacksSums, n);
        stacksSums[maxStack] -= stacks[maxStack].elements[stacks[maxStack].m-1];
        stacks[maxStack].m -= 1;
    }
    unsigned best = stacksSums[0];
    free(stacksSums);
    return best;
}

//int main() {
//    unsigned elements[][5] = {{1, 1, 1, 2, 3}, {2, 3, 4}, {1, 4, 5, 2}};
//    Stack test[3];
//    test[0].m = 5;
//    test[1].m = 3;
//    test[2].m = 4;
//    test[0].elements = elements[0];
//    test[1].elements = elements[1];
//    test[2].elements = elements[2];
//    unsigned best = MaxSumNStack(test, 3);
//    return 0;
//}