/******************************************************************************
 * INF 610 - Estruturas de Dados e Algoritmos - 2018/2                        *
 *                                                                            *
 * Lista de exercícios 6                                                      *
 *                                                                            *
 * Marcelo de Matos Menezes - 75254                                           *
 *                                                                            *
 * Just a simple program to test the implementations.                         *
 *                                                                            *
 *****************************************************************************/


#ifdef _WIN32
	#define high_resolution_clock steady_clock
#endif


#include "binarySearch.hpp"

#include <chrono>
#include <iostream>


using namespace std;


const int SIZE = 1000;  // 1 million


template <typename T, typename F>
void benchmark(const T* arr, int l, int u, F binarySearch) {
	int pos;
	unsigned time;
	chrono::time_point<chrono::high_resolution_clock> clock;

	cout << "Element 0 found at: ";

	clock = chrono::high_resolution_clock::now();
	pos = binarySearch(arr, 0, l, u);
	time = (chrono::high_resolution_clock::now() - clock).count();

	cout << pos << " - Took " << time << " nanoseconds\n";

	cout << "Element " << SIZE - 1 << " found at: ";

	clock = chrono::high_resolution_clock::now();
	pos = binarySearch(arr, SIZE - 1, l, u);
	time = (chrono::high_resolution_clock::now() - clock).count();

	cout << pos << " - Took " << time << " nanoseconds\n";

	cout << "Element " << (SIZE - 1) / 2 << " found at: ";

	clock = chrono::high_resolution_clock::now();
	pos = binarySearch(arr, (SIZE - 1) / 2, l, u);
	time = (chrono::high_resolution_clock::now() - clock).count();

	cout << pos << " - Took " << time << " nanoseconds\n";

	// Testing when element is not in array

	cout << "Element " << 2 * SIZE << " found at: ";

	clock = chrono::high_resolution_clock::now();
	pos = binarySearch(arr, 2 * SIZE, l, u);
	time = (chrono::high_resolution_clock::now() - clock).count();

	cout << pos << " - Took " << time << " nanoseconds\n";
}


int main() {
	int* arr;

	arr = new int[SIZE]; // Dynamic allocation for large sizes

	for (int i = 0; i < SIZE; i++)
		arr[i] = i;

	cout << "Measuring iterative binary search:\n\n";
	benchmark(arr, 0, SIZE - 1, iterativeBinarySearch<int>);
	cout << endl;

	cout << "Measuring recursive binary search:\n\n";
	benchmark(arr, 0, SIZE - 1, recursiveBinarySearch<int>);
	cout << endl;

	delete arr;
}