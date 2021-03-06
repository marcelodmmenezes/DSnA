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

	// If tree is empty, returns false.
	// Otherwise, item receives the highest element
	// in the tree (rightmost node) and the method returns true.
	// The element is removed from the tree if del is true.
	bool getHighest(T& item, bool del = false);

	// Destroys the tree and frees its memory
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
	unsigned height(UBSTNode<T>* node) const;
	void clear(UBSTNode<T>* node);
	//-------------------------------------------------------------------------

	UBSTNode<T>* m_root;

	// Information stored to make some queries O(1).
	unsigned m_size;
	unsigned m_num_leaves;
};


template <typename T>
UBST<T>::UBST() : m_root(nullptr), m_size(0u), m_num_leaves(0u) {}

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
	return height(m_root);
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

			if (item == itr->item) // Already in tree
				return;
			else if (item < itr->item) // Lower children to the left
				itr = itr->left;
			else // Higher to the right
				itr = itr->right;
		}

		if (item < parent->item) {
			parent->left = new UBSTNode<T>;
			parent->left->item = item;
		}
		else {
			parent->right = new UBSTNode<T>;
			parent->right->item = item;
		}

		// If the parent wasn't a leaf, the number of leaves is incremented
		if (parent->left && parent->right)
			m_num_leaves++;
	}

	m_size++;
}

template <typename T>
bool UBST<T>::remove(const T& item) {
	if (!m_root)
		return false;

	UBSTNode<T>* itr = m_root;
	UBSTNode<T>* parent = nullptr;

	// Searching for the item
	while (itr) {
		if (item == itr->item)
			break;
		else if (item < itr->item) {
			parent = itr;
			itr = itr->left;
		}
		else {
			parent = itr;
			itr = itr->right;
		}
	}

	if (!itr) // Item not in tree
		return false;

	if (itr->left && itr->right) {
		UBSTNode<T>* replacement = itr->right;
		// Aux node to keep reference to replacement's parent
		UBSTNode<T>* aux = nullptr;

		while (replacement && replacement->left) {
			aux = replacement;
			replacement = replacement->left;
		}

		if (aux) { // Replacement is not itr's right child
			aux->left = replacement->right;

			// If replacement is leaf and it's father was not
			if (!replacement->left && !replacement->right &&
				aux->right)
				m_num_leaves--;
		}
		else {
			itr->right = replacement->right;

			// If replacement is leaf
			if (!replacement->left && !replacement->right)
				m_num_leaves--;
		}

		itr->item = replacement->item;

		delete replacement;
	}
	else {
		if (itr->right) { // If the node has only the right child
			if (parent) {
				if (itr == parent->left)
					parent->left = itr->right;
				else
					parent->right = itr->right;
			}
			else
				m_root = itr->right;
		}
		else if (itr->left) { // If the node has only the left child
			if (parent) {
				if (itr == parent->left)
					parent->left = itr->left;
				else
					parent->right = itr->left;
			}
			else
				m_root = itr->left;
		}
		else { // Node to be removed is leaf
			if (parent) {
				if (itr == parent->left)
					parent->left = nullptr;
				else
					parent->right = nullptr;
			}
			else
				m_root = nullptr;

			// Parent is not a leaf
			if (!parent || parent->left || parent->right)
				m_num_leaves--;
		}

		delete itr;
	}

	m_size--;

	return true;
}

template <typename T>
bool UBST<T>::getHighest(T& item, bool del) {
	if (!m_root)
		return false;

	UBSTNode<T>* itr = m_root;

	while (itr->right)
		itr = itr->right;

	item = itr->item;

	if (del)
		remove(item);

	return true;
}

template <typename T>
void UBST<T>::clear() {
	if (m_root) {
		clear(m_root);
		m_size = m_num_leaves = 0u;
		m_root = nullptr;
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

		for (int i = 0; i < 8 * height; i++)
			std::cout << " ";
		std::cout << "|";

		for (int i = 0; i < 6; i++)
			std::cout << "-";

		std::cout << "(" << node->item << ")" << std::endl;

		printTree(height + 1, node->left);
	}
	else {
		for (int i = 0; i < 8 * height; i++)
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
unsigned UBST<T>::height(UBSTNode<T>* node) const {
	unsigned h = 0;

	if (node) {
		if (node->left)
			h = height(node->left);

		if (node->right)
			h = std::max(h, height(node->right));

		h++;
	}

	return h;
}

template <typename T>
void UBST<T>::clear(UBSTNode<T>* node) {
	if (node->left)
		clear(node->left);

	if (node->right)
		clear(node->right);

	delete node;
}


#endif	// UBST_HPP