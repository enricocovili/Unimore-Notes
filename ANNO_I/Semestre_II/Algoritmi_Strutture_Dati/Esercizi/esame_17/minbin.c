#include "elemtype.h"
#include "tree.h"

extern ElemType getMinIx(const ElemType *v, int start, int end) {
    int min = start;
    for (int i = start+1; i < end; ++i) {
        if (v[min] > v[i])
            min = i;
    }
    return min;
}

extern Node* CreateMinBinTreeRec(const ElemType *v, size_t v_size,
                                 int start, int end) {
    if (start >= v_size || start >= end || end <= 0)
        return NULL;
    ElemType min = getMinIx(v, start, end);
    Node *t = TreeCreateRoot(v+min, NULL, NULL);
    t->left = CreateMinBinTreeRec(v, v_size, start, min);
    t->right = CreateMinBinTreeRec(v, v_size, min+1, end);
    return t;
}

extern Node *CreateMinBinTree(const ElemType *v, size_t v_size) {
    if (v_size == 0 || v == NULL) {
        return NULL;
    }
    return CreateMinBinTreeRec(v, v_size, 0, v_size);
}

//int main(void) {
//    int v[] = {3,2,1,6,8,5};
//    Node *t = CreateMinBinTree(v, sizeof(v)/sizeof(int));
//    return 0;
//}