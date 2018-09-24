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
void quickSort(T* arr, int left, int right) {
	int pivot = arr[left], i = left, aux;

	// Elements lower than 'pivot' are put before higher.
	for (int j = left + 1; j <= right; j++) {
		if (arr[j] < pivot) {
			i++;
			aux = arr[i];
			arr[i] = arr[j];
			arr[j] = aux;
		}
	}

	// 'pivot' is assigned to it's location.
	arr[left] = arr[i];
	arr[i] = pivot;

	if (left < i - 1)
		quickSort(arr, left, i - 1);

	if (i + 1 < right)
		quickSort(arr, i + 1, right);
}

template <typename T>
void quickSort(T* arr, int size) {
	if (0 < size - 1)
		quickSort(arr, 0, size - 1);
}
//-----------------------------------------------------------------------------

//------------------------------------------------------------------ Merge sort
template <typename T>
void mergeSort(T* arr, T* merge_array, int left, int right) {
	int mid = (left + right) / 2;

	if (left < mid)
		mergeSort(arr, merge_array, left, mid);

	if (mid + 1 < right)
		mergeSort(arr, merge_array, mid + 1, right);

	// Merge
	int i, j;

	for (i = left; i <= mid; i++)
		merge_array[i] = arr[i];

	// Elements are inserted from higher to lower in second part of
	// auxiliary array, to make easier to add then to result later.
	for (i = mid + 1; i <= right; i++)
		merge_array[i] = arr[right + mid + 1 - i];

	i = left;
	j = right;

	for (int k = left; k <= right; k++) {
		if (merge_array[i] <= merge_array[j]) {
			arr[k] = merge_array[i];
			i++;
		}
		else {
			arr[k] = merge_array[j];
			j--;
		}
	}
}

template <typename T>
void mergeSort(T* arr, int size) {
	if (0 < size - 1) {
		T* merge_array = new T[size];
		mergeSort(arr, merge_array, 0, size - 1);
		delete[] merge_array;
	}
}
//-----------------------------------------------------------------------------

//-------------------------------------------------------------------- Heapsort
template <typename T>
void heapify(T* arr, int left, int right) {
	int root = left, l, r, max, aux;

	while (2 * root + 1 <= right) {
		l = 2 * root + 1;
		r = 2 * root + 2;

		if (r <= right && arr[r] > arr[l])
			max = r;
		else
			max = l;

		if (arr[root] > arr[max])
			return;

		aux = arr[root];
		arr[root] = arr[max];
		arr[max] = aux;

		root = max;
	}
}

template <typename T>
void heapSort(T* arr, int size) {
	int i;
	T aux;

	// Building heap
	for (i = size / 2 - 1; i >= 0; i--)
		heapify(arr, i, size - 1);

	// Sorting the array
	for (i = size - 1; i > 0; i--) {
		aux = arr[0];
		arr[0] = arr[i];
		arr[i] = aux;
		heapify(arr, 0, i - 1);
	}
}
//-----------------------------------------------------------------------------


#endif	// SORTING_HPP