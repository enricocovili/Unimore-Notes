#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 4) {
        return 1;
    }
    double nums[3];
    for (int i=1; i<4; i++) {
        char* pEnd;
        nums[i-1] = strtod(argv[i], &pEnd);
        if (*pEnd != '\0' || nums[i-1] <= 0) {
            return 1;
        }
    }
    double a = nums[0], b = nums[1], c = nums[2];
    double res = sqrt((a+b+c)*(-a+b+c)*(a-b+c)*(a+b-c))/4;
    printf("%.6lf", res);
    return 0;
}
