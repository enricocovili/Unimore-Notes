//
// Created by enri on 6/6/24.
//

#include "tree.h"

extern void getNodeInfo(Node* current, int val, Node **parent, int* height, int h) {
    if (current == NULL)
        return;
    if (current->left != NULL && current->left->value == val) {
        *parent = current;
        *height = h;
        return;
    }
    if (current->right != NULL && current->right->value == val) {
        *parent = current;
        *height = h;
        return;
    }
    getNodeInfo(current->left, val, parent, height, h+1);
    getNodeInfo(current->right, val, parent, height, h+1);
}

extern bool Cugini(const Node* t, int a, int b) {
    if (t == NULL)
        return false;
    if (TreeIsLeaf(t))
        return false;
    Node* aParent = NULL;
    int a_h = 0;
    getNodeInfo(t, a, &aParent, &a_h, 0);
    Node* bParent = 0;
    int b_h = 0;
    getNodeInfo(t, b, &bParent, &b_h, 0);
    return b_h == a_h && bParent != aParent;
}

int main(void){
    ElemType ValoriAlberi[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
    // albero completo di 7 nodi (radice compresa)
    Node* AlberoCompleto =
            TreeCreateRoot(ValoriAlberi + 0,
                           TreeCreateRoot(ValoriAlberi + 1,
                                          TreeCreateRoot(ValoriAlberi + 3, NULL, NULL),
                                          TreeCreateRoot(ValoriAlberi + 4, NULL, NULL)),
                           TreeCreateRoot(ValoriAlberi + 2,
                                          TreeCreateRoot(ValoriAlberi + 5, NULL, NULL),
                                          TreeCreateRoot(ValoriAlberi + 6, NULL, NULL)));

    bool test = Cugini(AlberoCompleto, 4, 7);

    TreeDelete(AlberoCompleto);
    return 0;
}