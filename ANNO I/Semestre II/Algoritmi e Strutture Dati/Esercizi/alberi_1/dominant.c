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

void CountDominantRec(const Node *t, int* count) {
    if (TreeIsLeaf(t))
        return;
    ElemType tmpSum = 0;
    if (t->left != NULL)
        tmpSum += t->left->value;
    if (t->right != NULL) {
        tmpSum += t->right->value;
    }
    if (ElemCompare(TreeGetRootValue(t), &tmpSum) > 0) {
        *count += 1;
    }
    CountDominantRec(TreeLeft(t), count);
    CountDominantRec(TreeRight(t), count);
}

extern int CountDominant(const Node *t) {
    if (TreeIsEmpty(t)) return 0;
    int count = 0;
    CountDominantRec(t, &count);
    return count;
}

//int main(void) {
//    // create sample tree
//    Node* t = TreeCreateEmpty();
//    ElemType e1[] = { 4, 3, 7, 1 , 1, 5, 8};
//    size_t size_e1 = sizeof(e1) / sizeof(ElemType);
//    t = CreateTreeFromVector(e1, size_e1);
//    TreeWriteStdoutInOrder(t);
//    int test = CountDominant(t);
//    TreeWriteStdoutInOrder(t);
//    return 0;
//}