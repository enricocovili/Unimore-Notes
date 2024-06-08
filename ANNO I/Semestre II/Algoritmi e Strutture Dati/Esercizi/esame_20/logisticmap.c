//
// Created by enri on 6/5/24.
//

#include <stdlib.h>
#include <stdio.h>

void ricorsione(double x, double r, long n, long level) {
    if (level == n) {
        printf("%f", x);
        return;
    }
    ricorsione(r*x*(1-x), r, n, level+1);
}

//int main(int argc, char** argv) {
//    if (argc != 4)
//        return 1;
//    char* endptr;
//    double x0 = strtof(argv[1], &endptr);
//    double r = strtof(argv[2], &endptr);
//    long n = strtol(argv[3], &endptr, 10);
//    if (x0 < 0 || x0 > 1 || r < 0 || n < 0)
//        return 1;
//    ricorsione(x0, r, n, 0);
//    return 0;
//}