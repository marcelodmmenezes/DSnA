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

	void insert()

	void clear();

private:
	void clear(UKDTNode<T, K>* node);

	UKDTNode<T, K>* m_root;
};


template <typename T, size_t K>
UKDTree::UKDTree() : m_root(nullptr) {}

template <typename T, size_t K>
UKDTree::~UKDTree() {
	clear();
}

template <typename T, size_t K>
void UKDTree::clear() {
	clear(m_root);
	m_root = nullptr;
}

template <typename T, size_t K>
void UKDTree::clear(UKDTNode<T, K>* node) {
	if (node->left)
		clear(node->left);

	if (node->right)
		clear(node->right);

	delete node;
}


#endif	// KD_TREE_HPP