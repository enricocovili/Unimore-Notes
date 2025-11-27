#include <stdlib.h>
#include <stdio.h>

void ricorsione(long n) {
    return;
}

int main(int argc, char** argv) {
    char* endptr;
    long n = strtol(argv[1], &endptr, 10);
    ricorsione(n);
    return 0;
}