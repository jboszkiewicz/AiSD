// Sorting algorythms.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include <random>
#include <chrono>

using namespace std;

typedef struct {
	int swaps;
	int comparisons;
	double time;
} CompareData;

void printarr(int array[], int n);
void swap(int* a, int* b);
void selectionSort(int array[], int n);
void insertionSort(int array[], int n);

int partition(int array[], int left, int right);
void quickSort(int* array, int left, int right);

void MinHeapify(int array[], int i);
void BuildMinHeap(int array[], int n);
void heapSort(int array[], int n);

void shellSort(int* array, int n);

int main()
{
	int array[10] = { 10, 1, 9, 2, 8, 3, 7, 4, 6, 5 };
	printarr(array, 10);
	selectionSort(array, 10);
	//insertionSort(array, 10);
	//quickSort(array, 0, 9);
	//heapSort(array, 10);
	shellSort(array, 10);
	printarr(array, 10);
	system("pause");

	return 0;
}

void printarr(int array[], int n) {
	for (int i = 0; i < n; i++)
		printf(" %d,", array[i]);
	puts("");
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void selectionSort(int array[], int n) {
	int min, i;

	auto start = chrono::steady_clock::now();

	while (n > 0)
	{
		min = 0;
		for (i = 1; i < n; i++)
			if (array[i] < array[min])
				min = i;
		swap(&array[min], &array[n-1]);

		n--;
	}

	auto end = chrono::steady_clock::now();
	
	printf("Time: %f\n", chrono::duration_cast<chrono::milliseconds>(end - start).count());

}

void insertionSort(int array[], int n) {

	int i, j, key;

	for (i = 1; i < n; i++) {
		key = array[i];
		for (j = i - 1; j >= 0 && array[j] < key; j--)
			array[j + 1] = array[j];
		array[j + 1] = key;
	}
}

int partition(int array[], int left, int right) {
	int pivot = array[left];
	int i = left;
	int j = right;

	while (1)
	{
		while (array[i] > pivot) i++;
		while (array[j] < pivot) j--;
		if (i < j) {
			swap(&array[i++], &array[j--]);
		}
		else {
			return j;
		}
	}
}

void quickSort(int* array, int left, int right) {
	int partindex;
	if (left < right){
		partindex= partition(array, left, right);
		quickSort(array, left, partindex);
		quickSort(array, partindex + 1, right);
	}
}

int heapSize;

void MinHeapify(int array[], int i) {

	int smallest;
	int l = 2 * i;
	int r = 2 * i + 1;

	if (l <= heapSize && array[l] < array[i])
		smallest = l;
	else
		smallest = i;
	if (r <= heapSize && array[r] < array[smallest])
		smallest = r;
	if (smallest != i) {
		swap(&array[i], &array[smallest]);
		MinHeapify(array, smallest);
	}
}

void BuildMinHeap(int array[], int n) {
	heapSize = n - 1;
	for (int i = heapSize / 2; i >= 0; i--)
		MinHeapify(array, i);
}

void heapSort(int array[], int n) {

	BuildMinHeap(array, n);
	for (int i = n-1; i > 0; i--) {
		swap(&array[0], &array[i]);
		heapSize--;
		MinHeapify(array, 0);
	}
}

void shellSort(int* array, int n) {
	int gap = 1;
	while (gap < n / 3) {
		gap = 3 * gap + 1;
	}

	while (gap > 0) {
		for (int i = gap; i < n; i += gap) {
			for (int j = i; j > 0 && array[j] < array[j - gap]; j -= gap) {
				swap(&array[j], &array[j - gap]);
			}
		}
		gap = --gap / 3;
	}
}

int* randomgen(int size, char mode) {
	int* array = (int*)malloc(sizeof(int) * size);
	int sign = 1;
	switch (mode) {
	case 'v':
		for (int i = 0; i < size; i++) {
			sign = -sign;
			array[i] = size - size;
		}
		break;
	case 'a':
		for (int i = 0; i < size; i++);
		
		
		break;
	case 'd':
		for (int i = 0; i < size; i++) array[i] = size - i - 1;
		break;

	default:
		for (int i = 0; i < size; i++) array[i] = i + 1;
		break;
	}
	return array;
}



