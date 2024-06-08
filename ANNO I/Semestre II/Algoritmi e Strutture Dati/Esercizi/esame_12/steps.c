//
// Created by enri on 6/5/24.
//

#include <stdlib.h>
#include <stdio.h>

extern void StepsRec(int n, int *curr, int curr_sum, int* tot, int level) {
    if (curr_sum == n) {
        printf("[");
        for (int i = 0; i < level - 1; i++) {
            printf("%d, ", curr[i]);
        }
        printf("%d], ", curr[level-1]);
        *tot += 1;
        return;
    }
    if (level == n) {
        return;
    }

    for (int i = 1; i <= 3; i++) {
        if (curr_sum + i <= n) {
            curr[level] = i;
            StepsRec(n, curr, curr_sum+i, tot, level+1);
            curr[level] = 0;
        }
    }
}

extern int Steps(int n) {
    if (n <= 0)
        return 0;
    int tot = 0;
    int *curr = calloc(n, sizeof(int));
    StepsRec(n, curr, 0, &tot, 0);
    free(curr);
    return tot;
}

//int main() {
//    int res = Steps(3);
//    return 0;
//}