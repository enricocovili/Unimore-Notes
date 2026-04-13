//
// Created by enri on 5/31/24.
//

#include "tree.h"
#include <stdio.h>

extern void TreeReadRecursive(FILE *f, Node **actual) {
    char tmp = ' ';
    while (tmp == ' ' || tmp == '\t' || tmp == '\r' || tmp == '\n' || tmp == '\v' || tmp == '\f') {
        int check = fscanf(f, "%c", &tmp);
        if (check <= 0)
            return;
    }
    if (tmp == '.') {
        fscanf(f, "%c", &tmp);
        while (tmp == ' ' || tmp == '\t' || tmp == '\r' || tmp == '\n' || tmp == '\v' || tmp == '\f') {
            fscanf(f, "%c", &tmp);
        }
        *actual = TreeCreateRoot(&tmp, NULL, NULL);
        return;
    }

    (*actual) = TreeCreateRoot(&tmp, NULL, NULL);

    TreeReadRecursive(f, &((*actual)->left));
    TreeReadRecursive(f, &((*actual)->right));
}

extern Node *TreeRead(const char *filename) {
    if (filename == NULL)
        return NULL;
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        return NULL;
    char a = 'f';
    Node* result = TreeCreateRoot(&a, NULL, NULL);
    TreeReadRecursive(f, &result);
    fclose(f);
    return result;
}




//int main(void) {
//    // create sample tree
//    Node* t = TreeCreateEmpty();
//    ElemType e1[] = { 3, 4, 2, 5 , 6, 7, 8};
//    size_t size_e1 = sizeof(e1) / sizeof(ElemType);
//    TreeWriteStdoutInOrder(t);
//    Node* res = TreeRead("albero.txt");
//    TreeWriteStdoutInOrder(t);
//    return 0;
//}