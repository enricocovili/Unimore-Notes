//
// Created by enri on 5/29/24.
//

#include "tree.h"

extern Node* CreateTreeFromVectorRec(const ElemType *v, size_t size, size_t i) {
    if (i >= size) {
        return TreeCreateEmpty();
    }
    Node *l = CreateTreeFromVectorRec(v, size, 2 * i + 1);
    Node *r = CreateTreeFromVectorRec(v, size, 2 * i + 2);
    return TreeCreateRoot(&v[i], l, r);
}

extern Node* CreateTreeFromVector(const ElemType *v, size_t size) {
    return CreateTreeFromVectorRec(v, size, 0);
}

extern void LevelSumRec(const Node *t, size_t level_target, size_t curr_level, int* totSum) {
    if (TreeIsEmpty(t))
        return;
    if (curr_level == level_target) {
        *totSum += t->value;
        return;
    }
    LevelSumRec(t->left, level_target, curr_level+1, totSum);
    LevelSumRec(t->right, level_target, curr_level+1, totSum);
}

extern int LevelSum(const Node *t, size_t level) {
    if (TreeIsEmpty(t))
        return 0;
    int sum = 0;
    LevelSumRec(t, level, 0, &sum);
    return sum;
}

//int main(void) {
//    // create sample tree
//    Node *t = TreeCreateEmpty();
//    ElemType e1[] = {3, 4, 2, 5, 6, 7, 8};
//    size_t size_e1 = sizeof(e1) / sizeof(ElemType);
//    t = CreateTreeFromVector(e1, size_e1);
//    TreeWriteStdoutInOrder(t);
//    int res = LevelSum(t, 1);
//    TreeWriteStdoutInOrder(t);
//    return 0;
//}