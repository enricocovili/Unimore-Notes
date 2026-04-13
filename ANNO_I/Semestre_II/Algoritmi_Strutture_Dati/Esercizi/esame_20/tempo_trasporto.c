//
// Created by enri on 6/5/24.
//

#include <stdlib.h>
#include <memory.h>

int TempoTrasporto(int n, const int* t, int p) {
    if (p == 0 || n == 0 || n == 1)
        return 0;
    int *c = calloc(n, sizeof(int));
    int *c_prev = calloc(n, sizeof(int));
    c[0] = p;
    c_prev[0] = p;
    int res = 0;
    while (c[n-1] != p) {
        for (int i = 0; i < n-1; i++) {
            if (c_prev[i] <= 0)
                continue;
            if (c_prev[i] <= t[i]) {
                c[i+1] += c[i];
                c[i] = 0;
            }
            else {
                c[i+1] += t[i];
                c[i] -= t[i];
            }
        }
        memmove(c_prev, c, n*sizeof(int));
        res++;
    }
    free(c);
    free(c_prev);
    return res;
}

//int main() {
//    int t[] = {3,2,4};
//    int res = TempoTrasporto(4, t, 5);
//    return 0;
//}