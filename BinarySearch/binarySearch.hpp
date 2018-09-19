/******************************************************************************
 * INF 610 - Estruturas de Dados e Algoritmos - 2018/2                        *
 *                                                                            *
 * Lista de exercícios 6                                                      *
 *                                                                            *
 * Marcelo de Matos Menezes - 75254                                           *
 *                                                                            *
 * Iterative and recursive binary search implementations.                     *
 *                                                                            *
 *****************************************************************************/


#ifndef BINARY_SEARCH_HPP
#define BINARY_SEARCH_HPP


// Both implementations return the index of the key in the array.
// If the array doesn't contain the key, the returned value is -1.

// k = key
// l = lower limit
// u = upper limit

template <typename T>
int iterativeBinarySearch(const T* arr, T k, int l, int u) {
	int m;

	while (l <= u) {
		m = (l + u) / 2;

		if (arr[m] == k)
			return m;
		else if (arr[m] > k)
			u = m - 1;
		else
			l = m + 1;
	}

	return -1;
}

template <typename T>
int recursiveBinarySearch(const T* arr, T k, int l, int u) {
	if (l <= u) {
		int m = (l + u) / 2;

		if (arr[m] == k)
			return m;

		if (arr[m] > k)
			return recursiveBinarySearch(arr, k, l, m - 1); 

		return recursiveBinarySearch(arr, k, m + 1, u); 
	}

	return -1;
}


#endif	// BINARY_SEARCH_HPP