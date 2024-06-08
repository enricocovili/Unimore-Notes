//
// Created by enri on 5/18/24.
//

#include <stdlib.h>
#include <stdio.h>

void printTree(int* nums, int n) {
    printf("{");
    for (int i=0; i<n; i++) {
        if (nums[i] != 0) {
            printf("%d, ", nums[i]);
        }
    }
    printf("},");
}

// albero scelta binaria
void SommaKRec(int* nums, int n, int k, int tempSum, int* res, int level) {
    if (tempSum == k) {
        (*res)++;
        printTree(nums, level);
        return;
    }
    if (tempSum > k || level == n) {
        return;
    }
    SommaKRec(nums, n, k, tempSum + nums[level], res, level+1);
    int cpy = nums[level];
    nums[level] = 0;
    SommaKRec(nums, n, k, tempSum, res, level+1);
    nums[level] = cpy;
}

extern int SommaK(int n, int k) {
    int res = 0;
    int* nums = malloc(sizeof(int)*n);
    for (int i=0; i<n; i++) {
        nums[i] = i+1;
    }
    SommaKRec(nums, n, k, 0, &res, 0);
    free(nums);
    return res;
}

//int main(void) {
//    printf("%d", SommaK(6,9));
//    return 0;
//}