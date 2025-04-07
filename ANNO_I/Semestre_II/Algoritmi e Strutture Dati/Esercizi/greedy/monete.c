#include <stdlib.h>

extern int *Monete(const int *tagli, size_t tagli_size, int budget) {
    if (budget <= 0) {
        return NULL;
    }
    int* result = calloc(tagli_size, sizeof(int));
    for (int i=0; i<tagli_size; i++) {
        while (tagli[i] <= budget) {
            budget -= tagli[i];
            result[i]++;
        }
    }
    return result;
}

//int main() {
//    int tagli[] = {50,20,10,5,2,1};
//    int budget = 126;
//    int* result = Monete(tagli, 6, 126);
//    return 0;
//}