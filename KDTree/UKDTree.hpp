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

	// Returns true if the tree contains the element 'point', false otherwise
	bool contains(T point[]);

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
	void printTree(int height, UKDTNode<T, K>* node);
#endif
	// Point copy
	inline void copy(T a[], const T b[]);

	// Point comparison
	inline bool equals(const T a[], const T b[]) const;

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
	if (!m_root) {
		m_root = new UKDTNode<T, K>;
		copy(m_root->point, point);
		return;
	}

	UKDTNode<T, K>* itr = m_root;
	UKDTNode<T, K>* parent = m_root;

	int height = 0;

	while (itr) {
		parent = itr;

		if (equals(itr->point, point))
			return;
		else if (point[height % K] < itr->point[height % K])
			itr = itr->left;
		else if (point[height % K] >= itr->point[height % K])
			itr = itr->right;

		height++;
	}

	if (point[(height - 1) % K] < parent->point[(height - 1) % K]) {
		parent->left = new UKDTNode<T, K>;
		copy(parent->left->point, point);
	}
	else {
		parent->right = new UKDTNode<T, K>;
		copy(parent->right->point, point);
	}
}

template <typename T, size_t K>
bool UKDTree<T, K>::contains(T point[]) {
	UKDTNode<T, K>* itr = m_root;

	int height = 0;

	while (itr) {
		if (equals(itr->point, point))
			return true;
		if (itr->point[height % K] < point[height % K])
			itr = itr->left;
		else if (itr->point[height % K] >= point[height % K])
			itr = itr->right;

		height++;
	}

	return false;
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
inline void UKDTree<T, K>::copy(T a[], const T b[]) {
	for (int i = 0; i < K; i++)
		a[i] = b[i];	
}

template <typename T, size_t K>
inline bool UKDTree<T, K>::equals(const T a[], const T b[]) const {
	for (int i = 0; i < K; i++)
		if (a[i] != b[i])
			return false;

	return true;
}

template <typename T, size_t K>
void UKDTree<T, K>::clear(UKDTNode<T, K>* node) {
	if (node->left)
		clear(node->left);

	if (node->right)
		clear(node->right);

	delete node;
}


#endif	// KD_TREE_HPP