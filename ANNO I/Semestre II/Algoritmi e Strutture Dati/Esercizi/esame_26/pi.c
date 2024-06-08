//
// Created by enri on 5/29/24.
//

#include <stdlib.h>
#include <stdio.h>

double pi(long n) {
    if (n == 0)
        return 4.0f;
    int sign = n%2 != 0 ? -1 : 1;
    return 4/(double)(2*n+1)*sign + pi(n-1);
}

//int main(int argc, char** argv) {
//    char* endptr;
//    if (argc != 2)
//        return 1;
//    long n = strtol(argv[1], &endptr, 10);
//    if (n < 0)
//        return 1;
//    printf("%f",pi(n));
//    return 0;
//}