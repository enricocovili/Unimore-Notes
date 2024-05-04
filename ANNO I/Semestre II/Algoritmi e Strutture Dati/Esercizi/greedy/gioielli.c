#include "gioielli.h"

int compare (const Gioiello * a, const Gioiello * b)
{
//    a = (Gioiello*)a;
//    b = (Gioiello *)b;
    double rapp = (a->prezzo / a->peso) - (b->prezzo / b->peso);
    if (rapp < 0) return -1;
    if (rapp == 0) return 0;
    return 1;
}

extern Gioiello *CompraGioielli(const char *filename, float budget, size_t *ret_size) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        return NULL;
    }
    Gioiello *gioielli_all = malloc(sizeof(Gioiello));
    int nGioielli = 1;
    while(fscanf(f, "%d %f %f", &gioielli_all[nGioielli-1].codice, &gioielli_all[nGioielli-1].peso, &gioielli_all[nGioielli-1].prezzo) >= 3) {
        gioielli_all = realloc(gioielli_all, (++nGioielli)*sizeof(Gioiello));
    }
    fclose(f);
    nGioielli--;
    gioielli_all = realloc(gioielli_all, (nGioielli)*sizeof(Gioiello));
    qsort(gioielli_all, nGioielli, sizeof(Gioiello),compare);
    Gioiello *result = malloc(sizeof(Gioiello)*nGioielli);
    size_t c=0;
    for (int i=0; i<nGioielli; i++) {
        if (gioielli_all[i].prezzo <= budget) {
            budget -= gioielli_all[i].prezzo;
            result[c] = gioielli_all[i];
            c++;
        }
    }
    free(gioielli_all);
    result = realloc(result, c*sizeof(Gioiello));
    *ret_size = c;
    return result;
}

//int main() {
//    size_t *test_size = malloc(sizeof(size_t));
//    Gioiello *test = CompraGioielli("gioielli_1.txt", 121, test_size);
//    free(test_size);
//    free(test);
//    return 0;
//}