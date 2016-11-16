#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include "fh_lib.h"

struct fHeap *fh_create()
{
	struct fHeap* ret = (struct fHeap*)malloc(sizeof(struct fHeap));
	ret->min = NULL;
	ret->nnodes = 0;
	return ret;
}

struct fNode *fh_insert(struct fHeap *heap, int key, char *value)
{
	struct fNode* node = (struct fNode*)malloc(sizeof(struct fNode));
	node->key = key;
	node->value = *value;
	node->degree = 0;
	node->mark = false;
	node->parent = NULL;
	node->child = NULL;
	node->left = node;
	node->right = node;

	FibHeapAddNodeToRootList(node, heap->min); /* Добавляем node в список корней heap */
	
	if (heap->min == NULL || node->key < heap->min->key)
		heap->min = node;
	heap->nnodes = heap->nnodes+ 1;

	return node;
}

void FibHeapAddNodeToRootList(struct fNode *node, struct fNode *h)
{
	struct fNode *lnode;

	if (h == NULL)
		return;
	if (h->left == h) {		/* Случай 1: список h содержит 1 корень */
		h->left = node;
		h->right= node;
		node->right= h;
		node->left = h;
	} else {				/* Случай 2: список h содержит > 1 корня */
		lnode = h->left;
		h->left= node;
		node->right= h;
		node->left= lnode;
		lnode->right= node;
	}
}

struct fNode *fh_min(struct fHeap *heap)
{
	return heap->min;
}

struct fHeap *FibHeapUnion(struct fHeap *heap1, struct fHeap *heap2)
{
	struct fHeap *heap = (struct fHeap*)malloc(sizeof(struct fHeap));
	heap->min = heap1->min;
	FibHeapLinkLists(heap1->min, heap2->min);
	
	if ((heap1->min == NULL) || (heap2->min != NULL && heap2->min->key < heap1->min->key)) {
		heap->min= heap2->min;
	}
	
	heap->nnodes = heap1->nnodes + heap2->nnodes;
	
	free(heap1);
	free(heap2);
	
	return heap;
}

struct fNode *FibHeapLinkLists(struct fNode *heap1, struct fNode *heap2)
{
	if (heap1 == NULL || heap2 == NULL)
		return NULL;
	struct fNode *left1 = heap1->left;
	struct fNode *left2 = heap2->left;
	left1->right = heap2;
	heap2->left = left1;
	heap1->left = left2;
	left2->right = heap1;

	return heap1;
}

int FibHeapDeleteMin(struct fHeap *heap)
{
	int ret;
	int i;
	struct fNode* ptr;
	struct fNode* ptr2;

	ret = heap->min->key;
	ptr = heap->min->child;
	for (i = 0; i < heap->min->degree; i++)
	{
		ptr2 = ptr->right;
		ptr->right = heap->min;
		ptr->left = heap->min->left;
		heap->min->left->right = ptr;
		heap->min->left = ptr;
		ptr = ptr2;
	}

	ptr = heap->min;
	ptr->right->left = ptr->left;
	ptr->left->right = ptr->right;

	if(ptr == ptr->right)
		heap->min = NULL;
	else
	{
		heap->min = ptr->right;
		FibHeapConsolidate(heap);
	}
	heap->nnodes = heap->nnodes - 1;

	free(ptr);
	return ret;
}

void FibHeapConsolidate(struct fHeap *heap)
{
	int i, d, D;
	struct fNode* x;
	struct fNode* w;
	struct fNode* v;
	struct fNode* y;
	struct fNode* tmp;
	struct fNode** A;

	D = ceil(log2((float)(heap->nnodes)));
	A = (struct fNode**)calloc(D * sizeof(struct fNode*), sizeof(struct fNode*));

	v = heap->min;
	w = heap->min;
	do
	{
		x = w;
		w = w->right;
		d = x->degree;
		while (A[d] != NULL)
		{
			y = A[d];
			if(x->key > y->key)
			{
				tmp = x;
				x = y;
				y = tmp;
			}
			FibHeapLinkLists(y, x);
			A[d] = NULL;
			d++;
		}
		A[d] = x;
	} while (w != v);

	heap->min = NULL;
	for (i = 0; i < D; i++)
	{
		if(A[i] != NULL)
		{
			if(heap->min == NULL)
			{
				heap->min = A[i];
				heap->min->left = heap->min;
				heap->min->right = heap->min;
			}
			else
			{
				A[i]->right = heap->min;
				A[i]->left = heap->min->left;
				heap->min->left->right = A[i];
				heap->min->left = A[i];

				if(A[i]->key < heap->min->key)
					heap->min = A[i];
			}
		}
	}

	free(A);
	return;
}

int D(int n)
{
	return floor(log(2));
}

/*void FibHeapLink(struct fHeap *heap, struct fNode *y, struct fNode *x)
{
	x->degree = x->degree + 1;
	
	 Делаем y дочерним узлом x 
	
	FibHeapRemoveNodeFromRootList(y, heap);
	
	y->parent= x;
	
	FibHeapAddNodeToRootList(y, x->child);
	
	y->mark = FALSE;
}*/

void FibHeapDecreaseKey(struct fHeap *heap, struct fNode *x, int newkey)
{
	if (newkey > x->key)
		return;	/* Новый ключ больше текущего значения ключа */
	
	x->key = newkey;
	struct fNode *y = x->parent;
	
	if (y != NULL && x->key < y->key)
	{
		/* Нарушены свойства 	min	-	heap: 	ключ родителя больше 	*/
		/* Вырезаем 	x 	и переносим его в список корней 	*/
		FibHeapCut(heap, x, y);
		FibHeapCascadingCut(heap, y);
	}
	/* 	Корректируем указатель на минимальный узел 	*/
	if (x->key < heap->min->key)
	heap->min = x;
}

void FibHeapCut(struct fHeap *heap, struct fNode *x, struct fNode *y)
{
	y->degree--;

	if (x->right == x)
	{
		y->child = NULL;
	}
	else
	{
		y->child = x->right;
		x->right->left = x->left;
		x->left->right = x->right;
	}
	x->right = heap->min;
	x->left = heap->min->left;
	heap->min->left->right = x;
	heap->min->left = x;

	x->parent = NULL;
	x->mark = false;

	return;
}

void FibHeapCascadingCut(struct fHeap *heap, struct fNode *y)
{
	struct fNode *z = y->parent;

	if (z == NULL)
		return;
	if (y->mark == false)
		y->mark = true;
	else
	{
		FibHeapCut(heap, y, z);
		FibHeapCascadingCut(heap, z);
	}
}

void FibHeapDelete(struct fHeap *heap, struct fNode *x)
{
	FibHeapDecreaseKey(heap, x, INT_MIN);
	FibHeapDeleteMin(heap);
}

void fibPrint(struct fNode *node, int level)
{
	struct fNode *end = node;
	do
	{
		printf("%d ", node->key);
		if (node->child == NULL)
		{
			printf("\n");
			if (node->right != end)
			for (int i = 0; i < 2 * level + level; i++)
				printf("\t");
			node = node->right;
			continue;
		}
		else
		{
			fibPrint(node->child, level + 1);
			node = node->right;
		}
	} while (node != end);
	return;
}

void printFibHeap(struct fHeap* heap)
{
	fibPrint(heap->min, 0);
}