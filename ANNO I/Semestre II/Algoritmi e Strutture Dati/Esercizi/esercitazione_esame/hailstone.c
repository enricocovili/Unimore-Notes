//
// Created by enri on 5/31/24.
//

#include <stdlib.h>
#include <stdio.h>

int hailstone(long n, int count) {
    count++;
    if (n == 1) {
        printf("1");
        return count;
    }
    printf("%ld, ", n);
    if (n % 2 == 0) {
        return hailstone(n/2, count);
    } else {
        return hailstone(n*3+1, count);
    }
}

int main(int argc, char** argv) {
    if (argc != 2)
        return -1;
    char* endptr;
    long n = strtol(argv[1], &endptr, 10);
    if (n <= 0)
        return 0;
    int aa = hailstone(n, 0);
    return aa;
}