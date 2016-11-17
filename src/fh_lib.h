#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

#ifndef FHLIB_H
#define FHLIB_H

struct fNode
{
	int degree;
	int key;
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

struct fHeap *fh_create();
struct fNode *fh_insert(struct fHeap *heap, int key);
void FibHeapAddNodeToRootList(struct fNode *node, struct fNode *h);
struct fNode *fh_min(struct fHeap *heap);
struct fHeap *FibHeapUnion(struct fHeap *heap1, struct fHeap *heap2);
void FibHeapLinkLists(struct fNode *node1, struct fNode *node2);
int FibHeapDeleteMin(struct fHeap *heap);
void FibHeapConsolidate(struct fHeap *heap);
int D(int n);
//void FibHeapLink(struct fHeap *heap, struct fNode *y, struct fNode *x);
void FibHeapDecreaseKey(struct fHeap *heap, struct fNode *x, int newkey);
void FibHeapCut(struct fHeap *heap, struct fNode *x, struct fNode *y);
void FibHeapCascadingCut(struct fHeap *heap, struct fNode *y);
void FibHeapDelete(struct fHeap *heap, struct fNode *x);
void fibPrint(struct fNode *node, int level);
void printFibHeap(struct fHeap* heap);

#endif