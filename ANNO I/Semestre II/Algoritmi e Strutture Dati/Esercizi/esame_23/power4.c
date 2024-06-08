//
// Created by enri on 6/2/24.
//

#include <stdlib.h>
#include <stdio.h>

int power4(long n, int level) {
    if (n == 1) {
        return level;
    }
    if (n < 4) {
        return -1;
    }
    return power4(n/4 + n%4, level+1);
}

int main(int argc, char** argv) {
    char* endptr;
    if (argc != 2)
        return 1;
    long n = strtol(argv[1], &endptr, 10);
    int res = power4(n, 0);
    if (res == -1)
        printf("!p4");
    else
        printf("4^%d = %ld", res, n);
    return 0;
}