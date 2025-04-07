#include "../elemtype.h"
#include "../list.h"

Item *ListLoad(const char *filename) {
    Item *result = ListCreateEmpty();
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        return result;
    ElemType temp;
    while(fscanf(f, "%d", &temp) > 0) {
        result = ListInsertHead(&temp, result);
    }
    fclose(f);
    return result;
}

//int main(void) {
//    Item *test = ListLoad("data_00.txt");
//    return 0;
//}