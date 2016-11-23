#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "fh_lib.h"

int main(int argc, char *argv[])
{
	struct fHeap *heap, *hp;
	struct fNode *n, *m;

	printf("Создаем кучу...\n");
	heap = fh_create();

	printf("Вставляем элементы...\n");
	fh_insert(heap, 10);
	fh_insert(heap, 15);
	fh_insert(heap, 7);
	fh_insert(heap, 23);
	n = fh_insert(heap, 96);
	fh_insert(heap, 43);
	m = fh_insert(heap, 80);
	fh_insert(heap, 24);
	fh_insert(heap, 26);
	fh_insert(heap, 35);
	fh_insert(heap, 46);
	printFibHeap(heap);

	printf("Извлекаем минимум: %d\n", FibHeapDeleteMin(heap));

	printf("После извлечения минимума:\n");
	printFibHeap(heap);

	printf("Понижение 80 -> 55\n");
	FibHeapDecreaseKey(heap, m, 55);
	FibHeapDelete(heap, n);
	printFibHeap(heap);

	printf("Создаем вторую кучу...\nВставляем элементы...\n");
	
	hp = fh_create();
	fh_insert(hp, 100);
	fh_insert(hp, 200);
	fh_insert(hp, 300);
	printFibHeap(hp);

	printf("Вторая куча: Извлекаем минимум: %d\n", FibHeapDeleteMin(hp));

	printf("Вторая куча: После извлечения\n");
	printFibHeap(hp);

	printf("Объединяем\n");
	heap = FibHeapUnion(heap, hp);
	printf("После объединения\n");
	printFibHeap(heap);

	printf("\nНаходим минимальный элемент: %d\n", heap->min->key);
	return EXIT_SUCCESS;
}