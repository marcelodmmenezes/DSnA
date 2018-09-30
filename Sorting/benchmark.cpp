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


const int NUMBER_OF_TESTS = 10;


template <typename T>
void copyArray(T* a, T* b, int size) {
	for (int i = 0; i < size; i++)
		b[i] = a[i];
}

void partialSortingBenchmark(int n, int k) {
	// Using two arrays to preserve random elements between sorts
	int** random;
	int* ordered;
	unsigned long long mean;
	chrono::time_point<chrono::steady_clock> clock;

	random = new int*[NUMBER_OF_TESTS];

	for (int i = 0; i < NUMBER_OF_TESTS; i++)
		random[i] = new int[n];

	ordered = new int[n];

	for (int i = 0; i < NUMBER_OF_TESTS; i++)
		for (int j = 0; j < n; j++)
			random[i][j] = rand();

	cout << "Partial selection sort took: ";

	mean = 0ull;

	for (int i = 0; i < NUMBER_OF_TESTS; i++) {
		copyArray(random[i], ordered, n);
		clock = chrono::steady_clock::now();
		partialSelectionSort(ordered, k, n);
		mean += (chrono::steady_clock::now() - clock).count();
	}

	mean /= NUMBER_OF_TESTS;

	cout << setw(10) << mean << " nanoseconds.\n";

	cout << "Partial insertion sort took: ";

	mean = 0ull;

	for (int i = 0; i < NUMBER_OF_TESTS; i++) {
		copyArray(random[i], ordered, n);
		clock = chrono::steady_clock::now();
		partialInsertionSort(ordered, k, n);
		mean += (chrono::steady_clock::now() - clock).count();
	}

	mean /= NUMBER_OF_TESTS;

	cout << setw(10) << mean << " nanoseconds.\n";

	mean = 0ull;

	cout << "Partial quicksort took:      ";
	for (int i = 0; i < NUMBER_OF_TESTS; i++) {
		copyArray(random[i], ordered, n);
		clock = chrono::steady_clock::now();
		partialQuickSort(ordered, k, n);
		mean += (chrono::steady_clock::now() - clock).count();
	}

	mean /= NUMBER_OF_TESTS;

	cout << setw(10) << mean << " nanoseconds.\n";

	mean = 0ull;

	cout << "Partial merge sort took:     ";
	for (int i = 0; i < NUMBER_OF_TESTS; i++) {
		copyArray(random[i], ordered, n);
		clock = chrono::steady_clock::now();
		partialMergeSort(ordered, k, n);
		mean += (chrono::steady_clock::now() - clock).count();
	}

	mean /= NUMBER_OF_TESTS;

	cout << setw(10) << mean << " nanoseconds.\n";

	mean = 0ull;

	cout << "Partial heapsort took:       ";
	for (int i = 0; i < NUMBER_OF_TESTS; i++) {
		copyArray(random[i], ordered, n);
		clock = chrono::steady_clock::now();
		partialHeapSort(ordered, k, n);
		mean += (chrono::steady_clock::now() - clock).count();
	}

	mean /= NUMBER_OF_TESTS;

	cout << setw(10) << mean << " nanoseconds.\n";

	for (int i = 0; i < NUMBER_OF_TESTS; i++)
		delete[] random[i];

	delete[] random;
	delete[] ordered;
}

void sortingBenchmark(int n) {
	// Using two arrays to preserve random elements between sorts
	int** random;
	int* ordered;
	unsigned long long mean;
	chrono::time_point<chrono::steady_clock> clock;

	random = new int*[NUMBER_OF_TESTS];

	for (int i = 0; i < NUMBER_OF_TESTS; i++)
		random[i] = new int[n];

	ordered = new int[n];

	for (int i = 0; i < NUMBER_OF_TESTS; i++)
		for (int j = 0; j < n; j++)
			random[i][j] = rand();

	cout << "Selection sort took: ";

	mean = 0ull;

	for (int i = 0; i < NUMBER_OF_TESTS; i++) {
		copyArray(random[i], ordered, n);
		clock = chrono::steady_clock::now();
		selectionSort(ordered, n);
		mean += (chrono::steady_clock::now() - clock).count();
	}

	mean /= NUMBER_OF_TESTS;

	cout << setw(10) << mean << " nanoseconds.\n";

	cout << "Insertion sort took: ";

	mean = 0ull;

	for (int i = 0; i < NUMBER_OF_TESTS; i++) {
		copyArray(random[i], ordered, n);
		clock = chrono::steady_clock::now();
		insertionSort(ordered, n);
		mean += (chrono::steady_clock::now() - clock).count();
	}

	mean /= NUMBER_OF_TESTS;

	cout << setw(10) << mean << " nanoseconds.\n";

	cout << "Quicksort took:      ";

	mean = 0ull;

	for (int i = 0; i < NUMBER_OF_TESTS; i++) {
		copyArray(random[i], ordered, n);
		clock = chrono::steady_clock::now();
		quickSort(ordered, n);
		mean += (chrono::steady_clock::now() - clock).count();
	}

	mean /= NUMBER_OF_TESTS;

	cout << setw(10) << mean << " nanoseconds.\n";

	cout << "Merge sort took:     ";

	mean = 0ull;

	for (int i = 0; i < NUMBER_OF_TESTS; i++) {
		copyArray(random[i], ordered, n);
		clock = chrono::steady_clock::now();
		mergeSort(ordered, n);
		mean += (chrono::steady_clock::now() - clock).count();
	}

	mean /= NUMBER_OF_TESTS;

	cout << setw(10) << mean << " nanoseconds.\n";

	cout << "Heapsort took:       ";

	mean = 0ull;

	for (int i = 0; i < NUMBER_OF_TESTS; i++) {
		copyArray(random[i], ordered, n);
		clock = chrono::steady_clock::now();
		heapSort(ordered, n);
		mean += (chrono::steady_clock::now() - clock).count();
	}

	mean /= NUMBER_OF_TESTS;

	cout << setw(10) << mean << " nanoseconds.\n";

	for (int i = 0; i < NUMBER_OF_TESTS; i++)
		delete[] random[i];

	delete[] random;
	delete[] ordered;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	srand(time(nullptr));

	cout << "n = 1000, k = 100\n\n";
	partialSortingBenchmark(1000, 100);
	cout << "n = 1000, k = 250\n\n";
	partialSortingBenchmark(1000, 250);
	cout << "\nn = 1000, k = 500\n\n";
	partialSortingBenchmark(1000, 500);
	cout << "\nn = 1000, k = 1000\n\n";
	partialSortingBenchmark(1000, 1000);
	cout << "\nn = 1000\n\n";
	sortingBenchmark(1000);

	cout << "\nn = 10000, k = 100\n\n";
	partialSortingBenchmark(10000, 100);
	cout << "\nn = 10000, k = 1000\n\n";
	partialSortingBenchmark(10000, 1000);
	cout << "\nn = 10000, k = 5000\n\n";
	partialSortingBenchmark(10000, 5000);
	cout << "\nn = 10000, k = 10000\n\n";
	partialSortingBenchmark(10000, 10000);
	cout << "\nn = 10000\n\n";
	sortingBenchmark(10000);

	cout << "\nn = 100000, k = 1000\n\n";
	partialSortingBenchmark(100000, 1000);
	cout << "\nn = 100000, k = 10000\n\n";
	partialSortingBenchmark(100000, 10000);
	cout << "\nn = 100000, k = 25000\n\n";
	partialSortingBenchmark(100000, 25000);
	cout << "\nn = 100000, k = 50000\n\n";
	partialSortingBenchmark(100000, 50000);
	cout << "\nn = 100000, k = 100000\n\n";
	partialSortingBenchmark(100000, 100000);
	cout << "\nn = 100000\n\n";
	sortingBenchmark(100000);
}