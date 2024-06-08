//
// Created by enri on 5/31/24.
//

#include "prezzo.h"

extern void TrovaArticoliRec(const struct Articolo *a, size_t a_size, int sum,
                            bool* curr, int curr_sum, int level) {
    // binary choice
    if (curr_sum == sum) {
        for (size_t i = 0; i < a_size; ++i) {
            if (curr[i] == true)
                printf("%s, ", a[i].nome);
        }
        printf("\n");
        return;
    }

    if (level == a_size)
        return;

    // no choice
    TrovaArticoliRec(a, a_size, sum, curr, curr_sum, level+1);
    // keep it
    curr[level] = true;
    TrovaArticoliRec(a, a_size, sum, curr, curr_sum+a[level].prezzo, level+1);
    curr[level] = false;
}

extern void TrovaArticoli(const struct Articolo *a, size_t a_size, int sum) {
    if (a == NULL)
        return;
    bool* curr = calloc(a_size, sizeof(bool));
    TrovaArticoliRec(a, a_size, sum, curr, 0, 0);
    free(curr);
}

//int main(void) {
//    struct Articolo test[] = {{"prova1", 1}, {"prova2", 2}, {"prova3", 3}};
//    TrovaArticoli(test, 3, 3);
//}