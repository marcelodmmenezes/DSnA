/******************************************************************************
 * INF 610 - Estruturas de Dados e Algoritmos - 2018/2                        *
 *                                                                            *
 * Trabalho prático 2                                                         *
 *                                                                            *
 * Marcelo de Matos Menezes - 75254                                           *
 *                                                                            *
 * Umbalanced K-D Tree implementation.                                        *
 *                                                                            *
 *****************************************************************************/


#ifndef UKD_TREE_HPP
#define UKD_TREE_HPP


#include <cstdlib>

#ifdef UKDT_DEBUG
	#include <iostream>
#endif


template <typename T, size_t K>
struct UKDTNode {
	UKDTNode() : left(nullptr), right(nullptr) {}

	T point[K];

	UKDTNode* left;
	UKDTNode* right;
};


template <typename T, size_t K>
class UKDTree {
public:
	UKDTree();
	~UKDTree();

	//--------------------------------------------------------- Data management
	// Adds a new element to the tree
	void insert(T point[]);

	// Destroys the tree and frees its memory
	void clear();
	//-------------------------------------------------------------------------

	//--------------------------------------------------------------- Depuração
#ifdef UKDT_DEBUG
	void printTree();
#endif
	//-------------------------------------------------------------------------

private:
	//--------------------------------------------------------------- Depuração
#ifdef UKDT_DEBUG
	void printTree(int height, RBTNode<T>* node);
#endif

	void clear(UKDTNode<T, K>* node);

	UKDTNode<T, K>* m_root;
};


template <typename T, size_t K>
UKDTree<T, K>::UKDTree() : m_root(nullptr) {}

template <typename T, size_t K>
UKDTree<T, K>::~UKDTree() {
	clear();
}

template <typename T, size_t K>
void UKDTree<T, K>::insert(T point[]) {
	
}

template <typename T, size_t K>
void UKDTree<T, K>::clear() {
	clear(m_root);
	m_root = nullptr;
}

#ifdef UKDT_DEBUG

template <typename T, size_t K>
void UKDTree<T, K>::printTree() {
	std::cout << std::endl;
	printTree(0, m_root);
	std::cout << std::endl;
}

template <typename T, size_t K>
void UKDTree<T, K>::printTree(int height, UKDTNode<T, K>* node) {
	if (node) {
		printTree(height + 1, node->right);

		for (int i = 0; i < K + 8 * height; i++)
			std::cout << " ";
		std::cout << "|";

		for (int i = 0; i < 6; i++)
			std::cout << "-";

		std::cout << "(" << node->point[0];

		for (int i = 1; i < K; i++)
			std::cout << ", " << node->point[i];

		std::cout << ")" << std::endl;

		printTree(height + 1, node->left);
	}
	else {
		for (int i = 0; i < K + 8 * height; i++)
			std::cout << " ";
		std::cout << "|";

		for (int i = 0; i < 6; i++)
			std::cout << "-";

		std::cout << "()" << std::endl;
	}
}

#endif	// UKDT_DEBUG

template <typename T, size_t K>
void UKDTree<T, K>::clear(UKDTNode<T, K>* node) {
	if (node->left)
		clear(node->left);

	if (node->right)
		clear(node->right);

	delete node;
}


#endif	// KD_TREE_HPP