//
// Created by enri on 5/24/24.
//
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

extern Node *BstInsert(const ElemType *e, Node *n) {
    if (TreeIsEmpty(n)) {
        return TreeCreateRoot(e, NULL, NULL);
    }
    Node *root = n;
    while (n != NULL) {
        if (ElemCompare(e, TreeGetRootValue(n)) <= 0) {
            if (TreeLeft(n) == NULL) {
                n->left = TreeCreateRoot(e, NULL, NULL);
                break;
            }
            n = n->left;
        } else {
            if (TreeRight(n) == NULL) {
                n->right = TreeCreateRoot(e, NULL, NULL);
                break;
            }
            n = n->right;
        }
    }
    return root;
}

extern Node *BstInsertRec(const ElemType *e, Node *n) {
    if (TreeIsEmpty(n)) {
        n = TreeCreateRoot(e, NULL, NULL);
        return n;
    }
    if (ElemCompare(e, TreeGetRootValue(n)) <= 0) {
        n->left = BstInsert(e, TreeLeft(n));
    } else {
        n->right = BstInsert(e, TreeRight(n));
    }
    return n;
}

//int main(void) {
//    // create sample tree
//    Node* t = TreeCreateEmpty();
//    ElemType e1[] = { 4, 3, 7, 1 , 4, 5, 8};
//    size_t size_e1 = sizeof(e1) / sizeof(ElemType);
//    t = CreateTreeFromVector(e1, size_e1);
//    TreeWriteStdoutInOrder(t);
//    ElemType test = 2;
//    BstInsert(&test, t);
//    TreeWriteStdoutInOrder(t);
//    return 0;
//}