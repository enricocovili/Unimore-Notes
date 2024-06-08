//
// Created by enri on 5/19/24.
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

extern void SuccessoreRec(const Node* curr, const Node* target, Node** min) {
    if (curr == NULL) {
        return;
    }
    if (
            ElemCompare(&curr->value, &target->value) > 0 &&
            (*min == NULL || ElemCompare(&curr->value, &(*min)->value) < 0)
    ) {
        *min = curr;
    }
    SuccessoreRec(TreeLeft(curr), target, min);
    SuccessoreRec(TreeRight(curr), target, min);
}

extern const Node* Successore(const Node *t, const Node *n) {
    if (TreeIsEmpty(t) || TreeIsLeaf(t))
        return NULL;
    Node *min = NULL;
    SuccessoreRec(t, n, &min);
    return min;
}

//int main(void) {
//    // create sample tree
//    Node* t = TreeCreateEmpty();
//    ElemType e1[] = { 3, 4, 2, 5 , 6, 7, 8};
//    size_t size_e1 = sizeof(e1) / sizeof(ElemType);
//    t = CreateTreeFromVector(e1, size_e1);
////    TreeWriteStdoutInOrder(t);
//    const Node *minKey = Successore(t, TreeLeft(t));
//    TreeWriteStdoutInOrder(t);
//    return 0;
//}