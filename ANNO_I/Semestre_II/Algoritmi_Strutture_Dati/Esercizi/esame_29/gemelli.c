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

extern void getTreeInfo(const Node *t, int* left, int* right) {
//    if (t == NULL)
//        return;
    if (!TreeIsEmpty(TreeLeft(t))) {
        *left += 1;
        getTreeInfo(TreeLeft(t), left, right);
    }
    if (!TreeIsEmpty(TreeRight(t))) {
        *right += 1;
        getTreeInfo(TreeRight(t), left, right);
    }
}

extern bool TreesAreTwins(const Node *t1, const Node *t2) {
    if (t1 == t2 || (TreeIsLeaf(t1) && TreeIsLeaf(t2))) {
        return true; // checks also for emtpy trees
    }
    int t1_l=0, t1_r=0, t2_l=0, t2_r=0;
    getTreeInfo(t1, &t1_l, &t1_r);
    getTreeInfo(t2, &t2_l, &t2_r);
    return (t1_r == t2_r && t1_l == t2_l);
}

//int main(void) {
//    // create sample tree
//    Node* t = TreeCreateEmpty();
//    ElemType e1[] = { 3, 4, 2, 5 , 6, 7, 8};
//    size_t size_e1 = sizeof(e1) / sizeof(ElemType);
//    t = CreateTreeFromVector(e1, size_e1);
//    TreeWriteStdoutInOrder(t);
//    // funzione(argomenti)
//    TreeWriteStdoutInOrder(t);
//    return 0;
//}