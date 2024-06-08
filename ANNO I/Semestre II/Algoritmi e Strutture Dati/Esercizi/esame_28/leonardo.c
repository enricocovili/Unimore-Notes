//
// Created by enri on 5/25/24.
//

#include <stdlib.h>
#include <stdio.h>

long leonardo(long n) {
    if (n <= 1)
        return 1;
    return leonardo(n-1)+ leonardo(n-2)+1;
}

//int main(int argc, char** argv) {
//    char* endptr;
//    if (argc != 2) {
//        return 1;
//    }
//    long n = strtol(argv[1], &endptr, 10);
//    if (n < 0) {
//        return 1;
//    }
//    for (long i=0; i<=n; i++)
//        printf("%ld, ", leonardo(i));
//    return 0;
//}