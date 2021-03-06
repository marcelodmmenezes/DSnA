/******************************************************************************
 * INF 610 - Estruturas de Dados e Algoritmos - 2018/2                        *
 *                                                                            *
 * Trabalho prático 1                                                         *
 *                                                                            *
 * Marcelo de Matos Menezes - 75254                                           *
 *                                                                            *
 * Program for debugging the partial sorting algorithms implementations.      *
 *                                                                            *
 *****************************************************************************/


#include "partialSorting.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>


using namespace std;


template <typename T>
void copyArray(T* a, T* b, int size) {
	for (int i = 0; i < size; i++)
		b[i] = a[i];
}

template <typename T>
void printArray(T* a, int size) {
	for (int i = 0; i < size; i++)
		cout << setw(4) << a[i] << " ";
	cout << endl;
}

void visualDebug(int k) {
	const int SIZE = 12;

	// Using two arrays to preserve random elements between sorts
	int random[SIZE], ordered[SIZE];

	for (int i = 0; i < SIZE; i++)
		random[i] = rand() % 400 - 200;

	cout << "\nOriginal array: ";
	printArray(random, SIZE);

	cout << "Selection sort: ";
	copyArray(random, ordered, SIZE);
	partialSelectionSort(ordered, k, SIZE);
	printArray(ordered, SIZE);

	cout << "Insertion sort: ";
	copyArray(random, ordered, SIZE);
	partialInsertionSort(ordered, k, SIZE);
	printArray(ordered, SIZE);

	cout << "Quicksort:      ";
	copyArray(random, ordered, SIZE);
	partialQuickSort(ordered, k, SIZE);
	printArray(ordered, SIZE);

	cout << "Merge sort:     ";
	copyArray(random, ordered, SIZE);
	partialMergeSort(ordered, k, SIZE);
	printArray(ordered, SIZE);

	cout << "Heapsort:       ";
	copyArray(random, ordered, SIZE);
	partialHeapSort(ordered, k, SIZE);
	printArray(ordered, SIZE);
}

int main() {
	std::ios_base::sync_with_stdio(false);
	srand(time(nullptr));

	visualDebug(5);
	cout << endl;
}