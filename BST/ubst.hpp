/******************************************************************************
 * INF 610 - Estruturas de Dados e Algoritmos - 2018/2                        *
 *                                                                            *
 * Lista de exercícios 6                                                      *
 *                                                                            *
 * Marcelo de Matos Menezes - 75254                                           *
 *                                                                            *
 * Simple, umbalanced, binary search tree implementation.                     *
 * UBST stands for Unbalanced Binary Search Tree.                             *
 *                                                                            *
 *****************************************************************************/


#ifndef UBST_HPP
#define UBST_HPP


#ifdef UBST_DEBUG
	#include <iostream>
#endif


// The node contains an item and a pointer to both children

template <typename T>
struct UBSTNode {
	UBSTNode() : left(nullptr), right(nullptr) {}

	T item;
	UBSTNode* left;
	UBSTNode* right;
};


template <typename T>
class UBST {
public:	
	UBST();
	~UBST();

	//-------------------------------------------------------------------- Info
	// Returns the number of elements in the tree
	unsigned size() const;

	// Returns the height of the tree
	unsigned height() const;

	// Returns the number of leaves in the tree
	unsigned countLeaves() const;

	// Returns the number of inner nodes
	unsigned countInnerNodes() const;
	//-------------------------------------------------------------------------

	//--------------------------------------------------------- Data management
	// Adds a new element to the tree
	void insert(const T& item);

	// Removes the specified item from the tree.
	// Returns true if the item was in the tree, false otherwise.
	bool remove(const T& item);

	// Returns the highest element in the tree (rightmost node).
	T getHighest();

	// Destroy the tree and free its memory
	void clear();
	//-------------------------------------------------------------------------

	//--------------------------------------------------------------- Debugging
#ifdef UBST_DEBUG
	void printTree();
#endif
	//-------------------------------------------------------------------------

private:
	//--------------------------------------------------------------- Debugging
#ifdef UBST_DEBUG
	void printTree(int height, UBSTNode<T>* node);
#endif
	//-------------------------------------------------------------------------

	//------------------------------------------------------- Auxiliary Methods
	void clear(UBSTNode<T>* node);
	//-------------------------------------------------------------------------

	UBSTNode<T>* m_root;
	unsigned m_size;
	unsigned m_height;
	unsigned m_num_leaves;
};


template <typename T>
UBST<T>::UBST() : m_root(nullptr), m_size(0u),
	m_height(0u), m_num_leaves(0u) {}

template <typename T>
UBST<T>::~UBST() {
	clear();
}


//------------------------------------------------------------------------ Info
template <typename T>
unsigned UBST<T>::size() const {
	return m_size;
}

template <typename T>
unsigned UBST<T>::height() const {
	return m_height;
}

template <typename T>
unsigned UBST<T>::countLeaves() const {
	return m_num_leaves;
}

template <typename T>
unsigned UBST<T>::countInnerNodes() const {
	return m_size - m_num_leaves;
}


//------------------------------------------------------------- Data management
template <typename T>
void UBST<T>::insert(const T& item) {
	if (!m_root) {
		m_root = new UBSTNode<T>;
		m_root->item = item;
		m_num_leaves++;
	}
	else {
		UBSTNode<T>* itr = m_root;
		UBSTNode<T>* parent;

		// Searching for the position to add the new item
		while (itr) {
			parent = itr;

			if (item < itr->item) // Lower children to the left
				itr = itr->left;
			else // Higher or equal to the right
				itr = itr->right;
		}

		if (item < parent->item) {
			parent->left = new UBSTNode<T>;
			parent->left->item = item;
		}
		else {
			parent->left = new UBSTNode<T>;
			parent->left->item = item;
		}

		// If the parent wasn't a leaf the number of leaves is incremented
		if (parent->left && parent->right)
			m_num_leaves++;
	}

	// Size is always incremented on insertion
	m_size++;
}

template <typename T>
bool UBST<T>::remove(const T& item) {

}

template <typename T>
T UBST<T>::getHighest() {
	UBSTNode<T>* itr = m_root;

	while (itr->right)
		itr = itr->right;

	return itr->item;
}

template <typename T>
void UBST<T>::clear() {
	if (m_root) {
		clear(m_root);
		m_size = m_height = m_num_leaves = 0u;
	}
}

//------------------------------------------------------------------- Debugging
#ifdef UBST_DEBUG

template <typename T>
void UBST<T>::printTree() {
	std::cout << std::endl;
	printTree(0, m_root);
	std::cout << std::endl;
}

template <typename T>
void UBST<T>::printTree(int height, UBSTNode<T>* node) {
	if (node) {
		printTree(height + 1, node->right);

		for (int i = 0; i < 9 * height; i++)
			std::cout << " ";
		std::cout << "|";
		for (int i = 0; i < 6; i++)
			std::cout << "-";

		std::cout << "(" << node->item << ")" << std::endl;

		printTree(height + 1, node->left);
	}
	else {
		for (int i = 0; i < 9 * height; i++)
			std::cout << " ";
		std::cout << "|";
		for (int i = 0; i < 6; i++)
			std::cout << "-";

		std::cout << "()" << std::endl;
	}
}

#endif	// UBST_DEBUG

//----------------------------------------------------------- Auxiliary Methods
template <typename T>
void UBST<T>::clear(UBSTNode<T>* node) {
	if (node->left)
		clear(node->left);

	if (node->right)
		clear(node->right);

	delete node;
}


#endif	// UBST_HPP