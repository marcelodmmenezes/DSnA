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


//-------------------------------------------------------------- Selection sort
template <typename T>
void partialSelectionSort(T* arr, int k, int size) {
}
//-----------------------------------------------------------------------------

//-------------------------------------------------------------- Insertion sort
template <typename T>
void partialInsertionSort(T* arr, int k, int size) {}
//-----------------------------------------------------------------------------

//------------------------------------------------------------------- Quicksort
template <typename T>
void partialQuickSort(T* arr, int left, int right) {}

template <typename T>
void partialQuickSort(T* arr, int k, int size) {}
//-----------------------------------------------------------------------------

//------------------------------------------------------------------ Merge sort
template <typename T>
void partialMergeSort(T* arr, T* merge_array, int left, int right) {}

template <typename T>
void partialMergeSort(T* arr, int k, int size) {}
//-----------------------------------------------------------------------------

//-------------------------------------------------------------------- Heapsort
template <typename T>
void partialHeapify(T* arr, int left, int right) {}

template <typename T>
void partialHeapSort(T* arr, int k, int size) {}
//-----------------------------------------------------------------------------


#endif	// PARTIAL_SORTING_HPP