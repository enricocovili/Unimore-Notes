//
// Created by enri on 5/26/24.
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

extern bool isColoredTree(const Node *t) {
    if (TreeIsLeaf(t) || t == NULL) {
        return true;
    }
    if (t->right != NULL && t->right->value == t->value) {
        return isColoredTree(t->right);
    }
    if (t->left != NULL && t->left->value == t->value) {
        return isColoredTree(t->left);
    }
    return false;
}

extern void getInfo(const Node *t, int height, int *totHeight, int *nodes) {
    if (*totHeight < height) {
        *totHeight = height;
    }
    *nodes += 1;
    if (TreeIsLeaf(t))
        return;
    if (t->left != NULL)
        getInfo(t->left, height+1, totHeight, nodes);
    if (t->right != NULL)
        getInfo(t->right, height+1, totHeight, nodes);
}

extern const void BiggestColoredTreeRec(const Node *t, Node **best, int h, int* bestH, int n, int *bestN) {
    if (!isColoredTree(t)) {
        h = 0;
        n = 0;
        if (t->left != NULL)
            BiggestColoredTreeRec(t->left, best, h, bestH, n, bestN);
        if (t->right != NULL)
            BiggestColoredTreeRec(t->right, best, h, bestH, n, bestN);
    } else {
        getInfo(t, 0, &h, &n);
        if (n >= *bestN) {
            if (h > *bestH) {
                *bestN = n;
                *best = t;
                *bestH = h;
            }
        }
    }
}

extern const Node* BiggestColoredTree(const Node *t) {
    if (TreeIsEmpty(t) || TreeIsLeaf(t))
        return t;
    Node* best;
    int h=-1,n=0;
    BiggestColoredTreeRec(t, &best, 0, &h, 0, &n);
    return best;
}

//int main(void) {
//    // create sample tree
//    Node* t = TreeCreateEmpty();
//    ElemType e1[] = { 'r', 'b', 'b', 'b' , 'b', 'r', 'g'};
//    size_t size_e1 = sizeof(e1) / sizeof(ElemType);
//    t = CreateTreeFromVector(e1, size_e1);
//    TreeWriteStdoutInOrder(t);
//    Node* test = BiggestColoredTree(t);
//    TreeWriteStdoutInOrder(t);
//    return 0;
//}