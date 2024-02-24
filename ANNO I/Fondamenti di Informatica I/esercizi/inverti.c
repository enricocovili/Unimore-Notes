#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


extern unsigned int inverti (unsigned int i) {
    unsigned int res = 0;
    while (i != 0) {
        res += i%10;
        i /= 10;
        if (i == 0)
            break;
        res *= 10;
    }
    return res;
}