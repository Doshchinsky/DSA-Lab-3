#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "fh_lib.h"

struct fheap *fh_insert(struct fheap *heap, char *key, char *value)
{
	struct fnode *node = malloc(sizeof(*node));
	node->key = *key;
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

	return heap;
}

void FibHeapAddNodeToRootList(struct fnode *node, struct fnode *h)
{
	struct fnode *lnode;

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

struct fnode *fh_min(struct fheap *heap)
{
	return heap->min;
}

struct fheap *FibHeapUnion(struct fheap *heap1, struct fheap *heap2)
{
	struct fheap *heap = (struct fheap*)malloc(sizeof(struct fheap));
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

struct fnode *FibHeapLinkLists(struct fnode *heap1, struct fnode *heap2)
{
	if (heap1 == NULL || heap2 == NULL)
		return NULL;
	struct fnode *left1 = heap1->left;
	struct fnode *left2 = heap2->left;
	left1->right = heap2;
	heap2->left = left1;
	heap1->left = left2;
	left2->right = heap1;

	return heap1;
}

struct fnode *FibHeapDeleteMin(struct fheap *heap)
{
	struct fnode *z = heap->min;
	struct fnode *x;
	
	if (z == NULL)
		return NULL;
	
	x = z->child;	
	FibHeapAddNodeToRootList(x, heap);		/* Добавляем дочерний узел x в список корней */
	x->parent= NULL;
	
	FibHeapRemoveNodeFromRootList(z, heap);	/* Удаляем z из списка корней */
	
	if (z == z->right)
		heap->min = NULL;
	else {
		heap->min= z->right;
		FibHeapConsolidate(heap);
	}
	
	heap->nnodes = heap->nnodes - 1;
	
	return z;
}

void FibHeapConsolidate(struct fheap *heap)
{
	struct fnode *w, *x, *y;
	int d, i;

	for (i= 0; i < D(heap->nnodes); i++)
		A[i] = NULL; /* Цикл по всем узлам списка корней */
	for each w in heap->min {
		x = w;
		d = x.degree;
		while (A[d] != NULL) {
			y = A[d]					/* Степень y совпадает со степенью x */
			if (x->key > y->key)
				FibHeapSwap(x, y);		/* Обмениваем x и y */
			FibHeapLink(heap, y, x);
			A[d] = NULL;
			d = d + 1 ;
		}
		A[d] = x;
	}
	/*	Находим минимальный узел */
	heap->min = NULL;
	for (i = 0; i < D(heap->nnodes); i++) {
		if (A[i] != NULL) {
			/* Добавляем A[i] в список корней */
			FibHeapAddNodeToRootList(A[i], heap);
			if (heap->min= NULL || A[i]->key < heap->min->key)
				heap->min= A[i];
		}
	}
}

int D(int n)
{
	return floor(log(2, n));
}

void FibHeapLink(heap, y, x)
{
	x->degree = x->degree + 1;
	
	/* Делаем y дочерним узлом x */
	
	FibHeapRemoveNodeFromRootList(y, heap);
	
	y->parent= x;
	
	FibHeapAddNodeToRootList(y, x->child);
	
	y->mark = FALSE;
}

void FibHeapDecreaseKey(struct fheap *heap, struct fheap *x, char *newkey)
{
	if (newkey > x->key)
		return;	/* Новый ключ больше текущего значения ключа */
	
	x->key = newkey;
	struct fheap *y = x->parent;
	
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

void FibHeapCut(struct fheap *heap, struct fheap *x, struct fheap *y)
{
	/* Удаляем x из списка дочерних узлов y */
	FibHeapRemoveNodeFromChildList(x, y);
	y->degree= y->degree - 1;
	/* Добавляем x в список корней кучи heap */
	FibHeapAddNodeToRootList(x, heap);
	x->parent= NULL;
	x->mark= FALSE;
}

void FibHeapCascadingCut(struct fheap *heap, struct fheap *y)
{
	struct fheap *z = y->parent;

	if (z == NULL)
		return;
	if (y->mark == FALSE)
		y->mark = TRUE;
	else
	{
		FibHeapCut(heap, y, z);
		FibHeapCascadingCut(heap, z);
	}
}

void FibHeapDelete(struct fheap *heap, struct fheap *x)
{
	FibHeapDecreaseKey(heap, x, -Infinity);
	FibHeapDeleteMin(heap);
}