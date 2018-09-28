/******************************************************************************
 * INF 610 - Estruturas de Dados e Algoritmos - 2018/2                        *
 *                                                                            *
 * Trabalho prático 1                                                         *
 *                                                                            *
 * Marcelo de Matos Menezes - 75254                                           *
 *                                                                            *
 * Program for benchmarking different uses of the sorting and partial sorting *
 * algorithms.                                                                *
 *                                                                            *
 *****************************************************************************/


#include "partialSorting.hpp"
#include "sorting.hpp"

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

void partialSortingBenchmark(int n, int k) {
	// Using two arrays to preserve random elements between sorts
	int* random;
	int* ordered;
	unsigned time;
	chrono::time_point<chrono::steady_clock> clock;

	random = new int[n];
	ordered = new int[n];

	for (int i = 0; i < n; i++)
		random[i] = rand();

	cout << "Partial selection sort took: ";
	copyArray(random, ordered, n);
	clock = chrono::steady_clock::now();
	partialSelectionSort(ordered, k, n);
	time = (chrono::steady_clock::now() - clock).count();
	cout << setw(10) << time << " nanoseconds.\n";

	cout << "Partial insertion sort took: ";
	copyArray(random, ordered, n);
	clock = chrono::steady_clock::now();
	partialInsertionSort(ordered, k, n);
	time = (chrono::steady_clock::now() - clock).count();
	cout << setw(10) << time << " nanoseconds.\n";

	cout << "Partial quicksort took:      ";
	copyArray(random, ordered, n);
	clock = chrono::steady_clock::now();
	partialQuickSort(ordered, k, n);
	time = (chrono::steady_clock::now() - clock).count();
	cout << setw(10) << time << " nanoseconds.\n";

	cout << "Partial merge sort took:     ";
	copyArray(random, ordered, n);
	clock = chrono::steady_clock::now();
	partialMergeSort(ordered, k, n);
	time = (chrono::steady_clock::now() - clock).count();
	cout << setw(10) << time << " nanoseconds.\n";

	cout << "Partial heapsort took:       ";
	copyArray(random, ordered, n);
	clock = chrono::steady_clock::now();
	partialHeapSort(ordered, k, n);
	time = (chrono::steady_clock::now() - clock).count();
	cout << setw(10) << time << " nanoseconds.\n";

	delete[] random;
	delete[] ordered;
}

void sortingBenchmark(int n) {
	// Using two arrays to preserve random elements between sorts
	int* random;
	int* ordered;
	unsigned time;
	chrono::time_point<chrono::steady_clock> clock;

	random = new int[n];
	ordered = new int[n];

	for (int i = 0; i < n; i++)
		random[i] = rand();

	cout << "Selection sort took: ";
	copyArray(random, ordered, n);
	clock = chrono::steady_clock::now();
	selectionSort(ordered, n);
	time = (chrono::steady_clock::now() - clock).count();
	cout << setw(10) << time << " nanoseconds.\n";

	cout << "Insertion sort took: ";
	copyArray(random, ordered, n);
	clock = chrono::steady_clock::now();
	insertionSort(ordered, n);
	time = (chrono::steady_clock::now() - clock).count();
	cout << setw(10) << time << " nanoseconds.\n";

	cout << "Quicksort took:      ";
	copyArray(random, ordered, n);
	clock = chrono::steady_clock::now();
	quickSort(ordered, n);
	time = (chrono::steady_clock::now() - clock).count();
	cout << setw(10) << time << " nanoseconds.\n";

	cout << "Merge sort took:     ";
	copyArray(random, ordered, n);
	clock = chrono::steady_clock::now();
	mergeSort(ordered, n);
	time = (chrono::steady_clock::now() - clock).count();
	cout << setw(10) << time << " nanoseconds.\n";

	cout << "Heapsort took:       ";
	copyArray(random, ordered, n);
	clock = chrono::steady_clock::now();
	heapSort(ordered, n);
	time = (chrono::steady_clock::now() - clock).count();
	cout << setw(10) << time << " nanoseconds.\n";

	delete[] random;
	delete[] ordered;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	srand(time(nullptr));

	cout << "n = 1000, k = 100\n\n";
	partialSortingBenchmark(1000, 100);
	cout << "\nn = 1000, k = 500\n\n";
	partialSortingBenchmark(1000, 500);
	cout << "\nn = 1000, k = 1000\n\n";
	partialSortingBenchmark(1000, 1000);
	cout << "\nn = 1000\n\n";
	sortingBenchmark(1000);

	cout << "\nn = 10000, k = 100\n\n";
	partialSortingBenchmark(10000, 100);
	cout << "\nn = 10000, k = 1000\n\n";
	partialSortingBenchmark(10000, 500);
	cout << "\nn = 10000, k = 5000\n\n";
	partialSortingBenchmark(10000, 5000);
	cout << "\nn = 10000, k = 1000\n\n";
	partialSortingBenchmark(10000, 10000);
	cout << "\nn = 10000\n\n";
	sortingBenchmark(10000);

	cout << "\nn = 100000, k = 1000\n\n";
	partialSortingBenchmark(100000, 1000);
	cout << "\nn = 100000, k = 10000\n\n";
	partialSortingBenchmark(100000, 1000);
	cout << "\nn = 100000, k = 25000\n\n";
	partialSortingBenchmark(100000, 25000);
	cout << "\nn = 100000, k = 50000\n\n";
	partialSortingBenchmark(100000, 50000);
	cout << "\nn = 100000, k = 100000\n\n";
	partialSortingBenchmark(100000, 100000);
	cout << "\nn = 100000\n\n";
	sortingBenchmark(100000);

	cout << "\nn = 500000, k = 1000\n\n";
	partialSortingBenchmark(100000, 1000);
	cout << "\nn = 500000, k = 25000\n\n";
	partialSortingBenchmark(100000, 1000);
	cout << "\nn = 500000, k = 100000\n\n";
	partialSortingBenchmark(100000, 25000);
	cout << "\nn = 500000, k = 250000\n\n";
	partialSortingBenchmark(100000, 50000);
	cout << "\nn = 500000, k = 500000\n\n";
	partialSortingBenchmark(100000, 100000);
	cout << "\nn = 500000\n\n";
	sortingBenchmark(500000);
}