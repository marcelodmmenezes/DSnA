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
	#ifdef _WIN32
		#include <windows.h>
	#endif
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

	// 'value' receives the minimum value in the tree for the 'dim' dimension
	// If the tree is empty returns false. Returns true otherwise
	bool findMinimum(int dim, T& value);

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

	T findMinimum(UKDTNode<T, K>* node, int dim, int height);
	
	void clear(UKDTNode<T, K>* node);

	// Point copy
	inline void copy(T a[], const T b[]);

	// Point comparison
	inline bool equals(const T a[], const T b[]) const;

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

	int height = 0, dim;

	while (itr) {
		parent = itr;
		dim = height % K;

		if (equals(itr->point, point))
			return;
		else if (point[dim] < itr->point[dim])
			itr = itr->left;
		else if (point[dim] >= itr->point[dim])
			itr = itr->right;

		height++;
	}

	dim = (height - 1) % K;

	if (point[dim] < parent->point[dim]) {
		parent->left = new UKDTNode<T, K>;
		copy(parent->left->point, point);
	}
	else {
		parent->right = new UKDTNode<T, K>;
		copy(parent->right->point, point);
	}
}

template <typename T, size_t K>
bool UKDTree<T, K>::findMinimum(int dim, T& value) {
	if (m_root) {
		value = findMinimum(m_root, dim, 0);
		return true;
	}

	return false;
}

template <typename T, size_t K>
bool UKDTree<T, K>::contains(T point[]) {
	UKDTNode<T, K>* itr = m_root;

	int height = 0, dim;

	while (itr) {
		dim = height % K;

		if (equals(itr->point, point))
			return true;
		if (point[dim] < itr->point[dim])
			itr = itr->left;
		else if (point[dim] >= itr->point[dim])
			itr = itr->right;

		height++;
	}

	return false;
}

template <typename T, size_t K>
void UKDTree<T, K>::clear() {
	if (m_root) {
		clear(m_root);
		m_root = nullptr;
	}
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

		for (int i = 0; i < (K + 8) * height; i++)
			std::cout << " ";
		std::cout << "|";

		for (int i = 0; i < 6; i++)
			std::cout << "-";

// The compared coordinate in each level is painted red
#ifdef __unix__

		std::cout << "(";

		if (height % K == 0)
			std::cout << "\033[31m" << node->point[0] << "\033[39m";
		else
			std::cout << node->point[0];

		for (int i = 1; i < K; i++) {
			if (i == height % K)
				std::cout << ", \033[31m" << node->point[i] << "\033[39m";
			else			
				std::cout << ", " << node->point[i];
		}

		std::cout << ")" << std::endl;

#elif defined _WIN32

		auto console = GetStdHandle(STD_OUTPUT_HANDLE);
	    auto *info = new CONSOLE_SCREEN_BUFFER_INFO();
	    GetConsoleScreenBufferInfo(console, info);
	    auto default_color = info->wAttributes;

	    std::cout << "(";

		if (height % K == 0) {
			SetConsoleTextAttribute(console, 4);
			std::cout << node->point[0];
			SetConsoleTextAttribute(console, default_color);
		}
		else
			std::cout << node->point[0];

		for (int i = 1; i < K; i++) {
			if (i == height % K) {
				std::cout << ", ";
				SetConsoleTextAttribute(console, 4);
				std::cout << node->point[i];
				SetConsoleTextAttribute(console, default_color);
			}
			else			
				std::cout << ", " << node->point[i];
		}

		std::cout << ")" << std::endl;

		delete info;

#endif	// Operating system stuff

		printTree(height + 1, node->left);
	}
	else {
		for (int i = 0; i < (K + 8) * height; i++)
			std::cout << " ";
		std::cout << "|";

		for (int i = 0; i < 6; i++)
			std::cout << "-";

		std::cout << "()" << std::endl;
	}
}

#endif	// UKDT_DEBUG

template <typename T, size_t K>
T UKDTree<T, K>::findMinimum(UKDTNode<T, K>* node, int dim, int height) {
	height %= K;

	// If the current height has the 'dimension we are searching for minimum'
	// as comparison key, we can search only on the left subtree.
	if (height == dim) {
		if (node->left)
			findMinimum(node->left, dim, height + 1);
		else
			return node->point[dim];
	}

	// Otherwise, we need to search in both subtrees.
	T minimum = node->point[dim];

	if (node->left) {
		T aux = findMinimum(node->left, dim, height + 1);

		if (aux < minimum)
			minimum = aux;
	}

	if (node->right) {
		T aux = findMinimum(node->right, dim, height + 1);

		if (aux < minimum)
			minimum = aux;
	}

	return minimum;
}

template <typename T, size_t K>
void UKDTree<T, K>::clear(UKDTNode<T, K>* node) {
	if (node->left)
		clear(node->left);

	if (node->right)
		clear(node->right);

	delete node;
}

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


#endif	// KD_TREE_HPP