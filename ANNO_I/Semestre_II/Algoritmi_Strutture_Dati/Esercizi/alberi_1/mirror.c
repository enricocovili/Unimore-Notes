//
// Created by enri on 5/24/24.
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

extern bool TreeIsMirrorRec(const Node* t1, const Node* t2) {
    if (t1 == NULL && t2 == NULL)
        return true;

    if (t1 == NULL || t2 == NULL || ElemCompare(&t1->value, &t2->value) != 0)
        return false;

    return TreeIsMirrorRec(TreeLeft(t1), TreeRight(t2)) && TreeIsMirrorRec(TreeRight(t1), TreeLeft(t2));
}

extern bool TreeIsMirror(const Node *t) {
    if (TreeIsLeaf(t) || TreeIsEmpty(t)) {
        return true;
    }
    return TreeIsMirrorRec(TreeLeft(t), TreeRight(t));
}

//int main(void) {
//    // create sample tree
//    Node* t = TreeCreateEmpty();
//    ElemType e1[] = { 4, 7, 7, 1 , 1, 1, 1};
//    size_t size_e1 = sizeof(e1) / sizeof(ElemType);
//    t = CreateTreeFromVector(e1, size_e1);
//    TreeWriteStdoutInOrder(t);
//    bool test = TreeIsMirror(t);
//    TreeWriteStdoutInOrder(t);
//    return 0;
//}
