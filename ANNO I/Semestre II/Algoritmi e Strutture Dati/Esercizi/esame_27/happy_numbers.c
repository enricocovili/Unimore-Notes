//
// Created by enri on 5/27/24.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool ricorsione(long n) {
    if (n == 0 || n == 4)
        return false;
    if (n == 1)
        return true;
    long new = 0;
    while (n > 0) {
        new += ((n%10) * (n%10));
        n /= 10;
    }
    return ricorsione(new);
}

//int main(int argc, char** argv) {
//    char* endptr;
//    if (argc != 2)
//        return 1;
//    long n = strtol(argv[1], &endptr, 10);
//    if (n < 0)
//        return 1;
//    printf("%s", ricorsione(n) ? "Felice" : "Infelice");
//    return 0;
//}