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

extern Node *DeleteBstNode(Node *n, const ElemType *key) {
    // Base case
    if (n == NULL)
        return n;

    // If the key to be deleted is smaller than the n's key, then it lies in the left subtree
    if (ElemCompare(key, &n->value) < 0) {
        n->left = DeleteBstNode(n->left, key);
        return n;
    }
    // If the key to be deleted is greater than the n's key, then it lies in the right subtree
    else if (ElemCompare(key, &n->value) > 0) {
        n->right = DeleteBstNode(n->right, key);
        return n;
    }

    // If key is same as n's key, then this is the node to be deleted
    // Node with only one child or no child
    if (n->left == NULL) {
        struct Node* temp = n->right;
//        TreeDelete(n);
        return temp;
    }
    else if (n->right == NULL) {
        struct Node* temp = n->left;
//        TreeDelete(n);
        return temp;
    }

    // Node with two children: Get the inorder successor (smallest in the right subtree)
    struct Node* succParent = n;
    struct Node* succ = n->left;
    while (succ->right != NULL) {
        succParent = succ;
        succ = succ->right;
    }

    // Copy the inorder successor's content to this node
    n->value = succ->value;

    // Delete the inorder successor
    if (succParent->left == succ)
        succParent->left = succ->right;
    else
        succParent->right = succ->right;

//    TreeDelete(succ);
    return n;
}

//int main(void) {
//    // create sample tree
//    Node* t = TreeCreateEmpty();
//    ElemType e1[] = { 4, 3, 7, 1 , 6, 5, 8};
//    size_t size_e1 = sizeof(e1) / sizeof(ElemType);
//    t = CreateTreeFromVector(e1, size_e1);
//    TreeWriteStdoutInOrder(t);
//    ElemType test = 4;
//    t = DeleteBstNode(t, &test);
//    TreeWriteStdoutInOrder(t);
//    return 0;
//}