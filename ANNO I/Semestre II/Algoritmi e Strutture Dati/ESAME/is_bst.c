//
// Created by enri on 6/7/24.
//

#include "tree.h"

extern bool IsBST(Node *t) {
    if (t == NULL || TreeIsLeaf(t))
        return true;
    if ((t->left == NULL || ElemCompare(&t->left->value, &t->value) <= 0) &&
        (t->right == NULL || ElemCompare(&t->right->value, &t->value) > 0) ) {
        return IsBST(t->left) && IsBST(t->right);
    }
    return false;
}

//int main(void) {
//    ElemType v1[] = { 5, 3, 8, 2, 4, 7, 8 };
//    // albero completo di 7 nodi (radice compresa)
//    Node* TreeTest =
//            TreeCreateRoot(v1 + 0,
//                           TreeCreateRoot(v1 + 1,
//                                            TreeCreateRoot(v1 + 3, NULL, NULL),
//                                            TreeCreateRoot(v1 + 4, NULL, NULL)
//                                          ),
//                           TreeCreateRoot(v1 + 2,
//                                            TreeCreateRoot(v1 + 5, NULL, NULL),
//                                            TreeCreateRoot(v1 + 6, NULL, NULL)));
//    bool test = IsBST(TreeTest);
//    TreeDelete(TreeTest);
//}