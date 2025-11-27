//
// Created by enri on 5/27/24.
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

Node *TreeCopy(const Node *t) {
    if (TreeIsEmpty(t)) {
        return NULL;
    }
    Node* n = TreeCreateRoot(TreeGetRootValue(t), NULL, NULL);
    n->left = TreeCopy(TreeLeft(t));
    n->right = TreeCopy(TreeRight(t));
    return n;
}

extern void MergeTreeRec(const Node *t1, const Node* t2, Node **t) {
    if (t1 == NULL && t2 == NULL)
        return;
    if (t1 == NULL) {
        *t = TreeCreateRoot(&t2->value, NULL, NULL);
        MergeTreeRec(t1, t2->right, &(*t)->right);
        MergeTreeRec(t1, t2->left, &(*t)->left);
    }
    else if (t2 == NULL) {
        *t = TreeCreateRoot(&t1->value, NULL, NULL);
        MergeTreeRec(t1->right, t2, &(*t)->right);
        MergeTreeRec(t1->left, t2, &(*t)->left);
    } else {
        ElemType e_sum = t1->value + t2->value;
        (*t) = TreeCreateRoot(&e_sum, NULL, NULL);
        MergeTreeRec(t1->right, t2->right, &(*t)->right);
        MergeTreeRec(t1->left, t2->left, &(*t)->left);
    }
}

extern Node* MergeTree(const Node *t1, const Node* t2) {
    Node* t = TreeCreateEmpty();
    MergeTreeRec(t1, t2, &t);
    return t;
}

//int main(void) {
//    // create sample tree
//    Node* t = TreeCreateEmpty();
//    Node *t2 = TreeCreateEmpty();
//    ElemType e1[] = { 3, 4, 2, 5 , 6, 7, 8};
//    ElemType e2[] = { 3, 4, 2, 5 , 6, 7, 8};
//    size_t size_e1 = sizeof(e1) / sizeof(ElemType);
//    size_t size_e2 = sizeof(e2) / sizeof(ElemType);
//    t = CreateTreeFromVector(e1, size_e1);
//    t2 = CreateTreeFromVector(e2, size_e2);
////    TreeWriteStdoutInOrder(t);
//    Node* res = MergeTree(NULL,t2);
//    TreeWriteStdoutInOrder(t);
//    return 0;
//}