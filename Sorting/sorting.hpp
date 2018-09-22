/******************************************************************************
 * INF 610 - Estruturas de Dados e Algoritmos - 2018/2                        *
 *                                                                            *
 * Trabalho prático 1                                                         *
 *                                                                            *
 * Marcelo de Matos Menezes - 75254                                           *
 *                                                                            *
 * Sorting algorithms.                                                        *
 *                                                                            *
 *****************************************************************************/


#ifndef SORTING_HPP
#define SORTING_HPP


//-------------------------------------------------------------- Selection sort
template <typename T>
void selectionSort(T* arr, int size) {
	for (int i = 0; i < size - 1; i++) {
		int min = i;

		// Searching for i-th minimum value
		for (int j = i + 1; j < size; j++)
			if (arr[j] < arr[min])
				min = j;

		// If there's a minor element, change its positions
		if (i != min) {
			T aux = arr[i];
			arr[i] = arr[min];
			arr[min] = aux;
		}
	}
}
//-----------------------------------------------------------------------------

//-------------------------------------------------------------- Insertion sort
template <typename T>
void insertionSort(T* arr, int size) {
	for (int i = 1; i < size; i++) {
		int j = i;

		// Moves the i-th element to its position in the sorted array
		while (j > 0 && arr[j] < arr[j - 1]) {
			T aux = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = aux;
			j--;
		}
	}
}
//-----------------------------------------------------------------------------

//------------------------------------------------------------------- Quicksort
template <typename T>
void quickSort(T* arr, int size) {}
//-----------------------------------------------------------------------------

//------------------------------------------------------------------ Merge sort
template <typename T>
void mergeSort(T* arr, int size) {}
//-----------------------------------------------------------------------------

//-------------------------------------------------------------------- Heapsort
template <typename T>
void heapSort(T* arr, int size) {}
//-----------------------------------------------------------------------------


#endif	// SORTING_HPP