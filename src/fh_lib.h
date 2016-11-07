#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#ifndef FHLIB_H
#define FHLIB_H

struct fnode
{
	int degree;
	char key;
	char value;
	struct fnode* parent;
	struct fnode* child;
	struct fnode* left;
	struct fnode* right;
	bool mark;
};

struct fheap
{
	struct fnode* min;
	int nnodes;
};

struct fheap *fh_insert(struct fheap *heap, char *key, char *value);
void FibHeapAddNodeToRootList(struct fnode *node, struct fnode *h);
struct fnode *fh_min(struct fheap *heap);
struct fheap *FibHeapUnion(struct fheap *heap1, struct fheap *heap2);
struct fnode *FibHeapLinkLists(struct fnode *heap1, struct fnode *heap2);
struct fnode *FibHeapDeleteMin(struct fheap *heap);
void FibHeapConsolidate(struct fheap *heap);
int D(int n);
void FibHeapLink(heap, y, x);
void FibHeapDecreaseKey(struct fheap *heap, struct fheap *x, char *newkey);

#endif