/******************************************************************************
 * INF 610 - Estruturas de Dados e Algoritmos - 2018/2                        *
 *                                                                            *
 * Trabalho prático 1                                                         *
 *                                                                            *
 * Marcelo de Matos Menezes - 75254                                           *
 *                                                                            *
 * Adaptations of some sorting algorithms for more efficient partial sorting. *
 * That is, given an arbitrary array with n elements,                         *
 * we wish to sort the first k smallest items.                                *
 *                                                                            *
 *****************************************************************************/


#ifndef PARTIAL_SORTING_HPP
#define PARTIAL_SORTING_HPP


//------------------------------------------------------ Partial selection sort
template <typename T>
void partialSelectionSort(T* arr, int k, int size) {
	if (k > size)
		return;

	// We only have to select the first k elements.
	// The rest of the array can remain as it is.
	for (int i = 0; i < k; i++) {
		int min = i;

		// But we still have to search the entire array for the i-th element,
		// because we have to check all elements to find the i-th smallest.
		for (int j = i + 1; j < size; j++)
			if (arr[j] < arr[min])
				min = j;

		// If there's a smaller element, change its positions
		if (i != min) {
			T aux = arr[i];
			arr[i] = arr[min];
			arr[min] = aux;
		}
	}
}
//-----------------------------------------------------------------------------

//------------------------------------------------------ Partial insertion sort
template <typename T>
void partialInsertionSort(T* arr, int k, int size) {
	if (k > size)
		return;

	// Firstly we make a common insertion sort for the first k elements.
	for (int i = 1; i < k; i++) {
		int j = i;

		while (j > 0 && arr[j] < arr[j - 1]) {
			T aux = arr[j];
			arr[j] = arr[j - 1];
			arr[j - 1] = aux;
			j--;
		}
	}

	// Then we need to search the rest of the array for items
	// which are smaller than the k-th element. If found, we replace
	// the k-th with the found element, and use the insertion algorithm
	// to place the new item in it's correct position.
	for (int i = k; i < size; i++) {
		if (arr[i] < arr[k - 1]) {
			T aux = arr[i];
			arr[i] = arr[k - 1];
			arr[k - 1] = aux;

			int j = k - 1;

			while (j > 0 && arr[j] < arr[j - 1]) {
				T aux = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = aux;
				j--;
			}
		}
	}
}
//-----------------------------------------------------------------------------

//----------------------------------------------------------- Partial quicksort
template <typename T>
void partialQuickSort(T* arr, int k, int left, int right) {
	int pivot = arr[left], i = left, aux;

	// Elements smaller than 'pivot' are put before bigger.
	for (int j = left + 1; j <= right; j++) {
		if (arr[j] < pivot) {
			i++;
			aux = arr[i];
			arr[i] = arr[j];
			arr[j] = aux;
		}
	}

	// 'pivot' is assigned to its location.
	arr[left] = arr[i];
	arr[i] = pivot;

	if (left < i - 1)
		partialQuickSort(arr, k, left, i - 1);

	// We only need to call the 'bigger' part of the array if the first
	// part has less than k elements.
	if (i + 1 < right && i - left < k)
		partialQuickSort(arr, k, i + 1, right);
}

template <typename T>
void partialQuickSort(T* arr, int k, int size) {
	if (k <= size && 0 < size - 1)
		partialQuickSort(arr, k, 0, size - 1);
}
//-----------------------------------------------------------------------------

//---------------------------------------------------------- Partial merge sort
template <typename T>
void partialMergeSort(T* arr, T* merge_array, int k, int left, int right) {
	int mid = (left + right) / 2;

	if (left < mid)
		partialMergeSort(arr, merge_array, k, left, mid);

	if (mid + 1 < right)
		partialMergeSort(arr, merge_array, k, mid + 1, right);

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

	// We have to merge at maximum k elements
	for (int it = left; it <= right && it <= left + k; it++) {
		if (merge_array[i] <= merge_array[j]) {
			arr[it] = merge_array[i];
			i++;
		}
		else {
			arr[it] = merge_array[j];
			j--;
		}
	}
}

template <typename T>
void partialMergeSort(T* arr, int k, int size) {
	if (k <= size && 0 < size - 1) {
		T* merge_array = new T[size];
		partialMergeSort(arr, merge_array, k, 0, size - 1);
		delete[] merge_array;
	}
}
//-----------------------------------------------------------------------------

//------------------------------------------------------------ Partial heapsort
template <typename T>
void minHeapify(T* arr, int left, int right) {
	int root = left, l, r, min, aux;

	while (2 * root + 1 <= right) {
		l = 2 * root + 1;
		r = 2 * root + 2;

		if (r <= right && arr[r] < arr[l])
			min = r;
		else
			min = l;

		if (arr[root] < arr[min])
			return;

		aux = arr[root];
		arr[root] = arr[min];
		arr[min] = aux;

		root = min;
	}
}

template <typename T>
void partialHeapSort(T* arr, int k, int size) {
	if (k > size)
		return;

	T aux;

	// Building heap for all elements
	for (int i = size / 2 - 1; i >= 0; i--)
		minHeapify(arr, i, size - 1);

	// Sorting the k smaller elements
	for (int i = size - 1; i >= size - k; i--) {
		aux = arr[0];
		arr[0] = arr[i];
		arr[i] = aux;
		minHeapify(arr, 0, i - 1);
	}

	// Passing them to the start of the array
	for (int i = 0; i < k; i++) {
		aux = arr[i];
		arr[i] = arr[size - i - 1];
		arr[size - i - 1] = aux;
	}
}
//-----------------------------------------------------------------------------


#endif	// PARTIAL_SORTING_HPP