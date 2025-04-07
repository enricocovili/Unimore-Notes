 #include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
 
extern bool crescente(unsigned int x) {
    unsigned int last = x%10;
    x /= 10;
    if (x == 0)
        return true; // 1 cifra
    for(size_t i=0; x > 0; i++) {
        if (last != x%10+1) {
            return false;
        }
        last = x%10;
        x /= 10;
    }
    return true;
}