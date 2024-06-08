//
// Created by enri on 5/24/24.
//

#include "tree.h"

//extern Node* CreateTreeFromVectorRec(const ElemType *v, size_t size, size_t i) {
//    if (i >= size) {
//        return TreeCreateEmpty();
//    }
//    Node *l = CreateTreeFromVectorRec(v, size, 2 * i + 1);
//    Node *r = CreateTreeFromVectorRec(v, size, 2 * i + 2);
//    return TreeCreateRoot(&v[i], l, r);
//}
//
//extern Node* CreateTreeFromVector(const ElemType *v, size_t size) {
//    return CreateTreeFromVectorRec(v, size, 0);
//}


extern const ElemType *BstTreeMax(const Node *n) {
    if (TreeIsEmpty(n))
        return NULL;
    if (n->right == NULL) {
        return &n->value;
    }
    BstTreeMax(TreeRight(n));
}

void TreeMaxRec(const Node *t, ElemType **max) {
    if (TreeIsEmpty(t))
        return;
    if (ElemCompare(&t->value, *max) > 0) {
        *max = &t->value;
    }
    TreeMaxRec(TreeLeft(t), max);
    TreeMaxRec(TreeRight(t), max);
}

extern const ElemType *TreeMax(const Node *n) {
    if (TreeIsEmpty(n))
        return NULL;
    ElemType *max = TreeGetRootValue(n);
    TreeMaxRec(n, &max);
    return max;
}

//int main(void) {
//    // create sample tree
//    Node* t = TreeCreateEmpty();
//    ElemType e1[] = { 4, 3, 7, 1 , 1, 5, 8};
//    size_t size_e1 = sizeof(e1) / sizeof(ElemType);
//    t = CreateTreeFromVector(e1, size_e1);
//    TreeWriteStdoutInOrder(t);
//    ElemType *test = TreeMax(t);
//    TreeWriteStdoutInOrder(t);
//    return 0;
//}

