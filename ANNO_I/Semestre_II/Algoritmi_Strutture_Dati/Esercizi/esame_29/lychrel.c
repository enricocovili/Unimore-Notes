//
// Created by enri on 5/19/24.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

long inverse(long n) {
    long n_cpy = n;
    long inverse = 0;
    while (n > 0) {
        inverse += (long)(pow(10, (long)(log10(n))))*(n%10);
        n /= 10;
    }
    return inverse;
}

bool LychrelRec(long n, long i, long c) {
    if (c > i) {
        return true;
    }
    long inv = inverse(n);
    if (n == inv) {
        return false;
    }
    return LychrelRec(n+inv, i, c+1);
}

bool Lychrel(long n, long i) {
    return LychrelRec(n, i, 0);
}

//int main(int argc, char** argv) {
//    if (argc != 3) {
//        return 1;
//    }
//    char* endptr;
//    long n = strtol(argv[1], &endptr, 10);
//    long i = strtol(argv[2], &endptr, 10);
//    if (n < 0) {
//        return 1;
//    }
//    printf(Lychrel(n, i) ? "Lychrel" : "Non di Lychrel");
//    return 0;
//}