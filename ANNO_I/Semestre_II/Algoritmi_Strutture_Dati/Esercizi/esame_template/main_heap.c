#include "minheap.h"
#include <stdlib.h>
#include <stdio.h>

int main(void){
	ElemType v[] = {1,5,4,6,12,23};
	ElemType* v = malloc(sizeof(int) * sizeof(v)/sizeof(ElemType));

	Heap* h_test = HeapCreateEmpty();
	h_test->data = v1;
	h_test->size = sizeof(v)/sizeof(ElemType);
	
	HeapDelete(h_test);
	return 0;
}
