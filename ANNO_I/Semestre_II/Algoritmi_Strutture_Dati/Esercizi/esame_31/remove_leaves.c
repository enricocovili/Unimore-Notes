//
// Created by enri on 5/19/24.
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

extern Node* RemoveLeaves(Node *t) {
    if (TreeIsEmpty(t)) {
        return t;
    }
    if (TreeIsLeaf(t)) {
        TreeDelete(t);
        t = NULL;
        return t;
    }
    if (TreeIsLeaf(TreeLeft(t))) {
        TreeDelete(TreeLeft(t));
        t->left = NULL;
    }
    if (TreeIsLeaf(TreeRight(t))) {
        TreeDelete(TreeRight(t));
        t->right = NULL;
    }
    RemoveLeaves(TreeLeft(t));
    RemoveLeaves(TreeRight(t));
    return t;
}

//int main(void) {
//    // create sample tree
//    Node* t = TreeCreateEmpty();
//    ElemType e1[] = { 3, 4, 2, 5 , 6, 7, 8};
//    size_t size_e1 = sizeof(e1) / sizeof(ElemType);
//    t = CreateTreeFromVector(e1, size_e1);
//    TreeWriteStdoutInOrder(t);
//    t = RemoveLeaves(t);
//    TreeWriteStdoutInOrder(t);
//    return 0;
//}