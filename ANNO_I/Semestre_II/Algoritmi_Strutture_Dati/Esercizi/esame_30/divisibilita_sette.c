//
// Created by enri on 5/18/24.
//

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

bool divisibilita(long n) {
    if (n < 10) {
        if (n == 0 || n == 7)
            return true;
        return false;
    }
    return divisibilita((long)abs(n/10-(n%10)*2));
}

//int main(int argc, char** argv) {
//    if (argc != 2)
//        return 1;
//    char *endptr;
//    long n = strtol(argv[1], &endptr, 10);
//    if (n < 0)
//        return 1;
//    if (divisibilita(n)) {
//        printf("Multiplo di 7.");
//    } else {
//        printf("Non multiplo di 7.");
//    }
//    return 0;
//}