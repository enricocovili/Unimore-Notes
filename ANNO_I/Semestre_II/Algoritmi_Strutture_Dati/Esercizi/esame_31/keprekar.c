#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int compare (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

int compare_reverse (const void * a, const void * b)
{
    return - ( *(int*)a - *(int*)b );
}

void keprekar(int n) {
    printf("%04d ", n);
    if (n == 6174) {
        return;
    }
    int values[4];
    for (int i=0; i<4; i++) {
        values[i] = n % 10;
        n/=10;
    }
    int res = 0;
    qsort (values, 4, sizeof(int), compare);
    for (int i=0; i<4; i++) {
        res -= values[i] * pow(10, 3-i);
    }
    qsort (values, 4, sizeof(int), compare_reverse);
    for (int i=0; i<4; i++) {
        res += values[i] * pow(10, 3-i);
    }
    keprekar(res);
}

//int main(int argc, char** argv) {
//    if (argc != 2)
//        return 1;
//    char *endptr;
//    int n = strtol(argv[1], &endptr, 10);
//    if (n < 0)
//        return 1;
//    if (strlen(argv[1]) > 4 || n == 0 || n % 1111 == 0 || *endptr != '\0') {
//        printf("Invalid number");
//        return 0;
//    }
//    keprekar(n);
//    return 0;
//}