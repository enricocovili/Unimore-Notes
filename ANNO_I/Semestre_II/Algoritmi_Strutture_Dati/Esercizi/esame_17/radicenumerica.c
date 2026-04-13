//
// Created by enri on 5/14/24.
//

#include <stdio.h>
#include <stdlib.h>

long radiceNumerica(long value) {
    if (value < 10)
        return value;
    int partialSum = 0;
    while (value > 0) {
        partialSum += value % 10;
        value /= 10;
    }
    return radiceNumerica(partialSum);
}

//int main(int argc, char **argv) {
//    if (argc != 2) {
//        return 1;
//    }
//    char *endptr = malloc(sizeof(char));
//    long n = strtol(argv[1], &endptr, 10);
//    if (*endptr != '\0' || n < 0) {
//        return 1;
//    }
//    printf("%ld", radiceNumerica(n));
//    return 0;
//}