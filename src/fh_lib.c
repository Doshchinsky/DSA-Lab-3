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
		return 0; /*Надо уточнить, что возвращать*/
	struct fnode *left1 = heap1->left;
	struct fnode *left2 = heap2->left;
	left1->right = heap2;
	heap2->left = left1;
	heap1->left = left2;
	left2->right = heap1;

	return heap1;
}