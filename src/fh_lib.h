#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#ifndef FHLIB_H
#define FHLIB_H

struct fNode
{
	int degree;
	int key;
	char value;
	bool mark;
	struct fNode* parent;
	struct fNode* child;
	struct fNode* left;
	struct fNode* right;
};

struct fHeap
{
	struct fNode* min;
	int nnodes;
};

struct fHeap *fh_insert(struct fHeap *heap, char *key, char *value);
void FibHeapAddNodeToRootList(struct fNode *node, struct fNode *h);
struct fNode *fh_min(struct fHeap *heap);
struct fHeap *FibHeapUnion(struct fHeap *heap1, struct fHeap *heap2);
struct fNode *FibHeapLinkLists(struct fNode *heap1, struct fNode *heap2);
int FibHeapDeleteMin(struct fHeap *heap);
void FibHeapConsolidate(struct fHeap *heap);
int D(int n);
void FibHeapLink(struct fHeap *heap, struct fNode *y, struct fNode *x);
void FibHeapDecreaseKey(struct fNode *heap, struct fNode *x, char *newkey);
void FibHeapCut(struct fHeap *heap, struct fHeap *x, struct fHeap *y);
void FibHeapCascadingCut(struct fHeap *heap, struct fHeap *y);
void FibHeapDelete(struct fHeap *heap, struct fHeap *x);

#endif