/******************************************************************************
 * INF 610 - Estruturas de Dados e Algoritmos - 2018/2                        *
 *                                                                            *
 * Lista de exercícios 3                                                      *
 *                                                                            *
 * Marcelo de Matos Menezes - 75254                                           *
 *                                                                            *
 *****************************************************************************/
https://www.coders-hub.com/2015/07/red-black-tree-rb-tree-using-c.html#.W37zQuhKjIU

#ifndef RBT_MULTISET_HPP
#define RBT_MULTISET_HPP


//------------------------------------------------------------------ Definições

#define RED true
#define BLACK false
typedef bool Color;


template <typename T>
struct RBTNode {
	RBTNode(T k, Color c) : key(k), color(c), count(1ll),
		parent(nullptr), left(nullptr), right(nullptr) {}

	T key;
	Color color;
	long long count;
	RBTNode<T>* parent;
	RBTNode<T>* left;
	RBTNode<T>* right;
};


template<typename T>
class RBTMultiset {
public:
	//-------------------------------------------------- Construtores/Destrutor
	RBTMultiset();
	~RBTMultiset();
	
	//------------------------------------------------------ Capacidade/Tamanho
	// Testa se o multiconjunto está vazio.
	bool empty();

	// Retorna o tamanho do multiconjunto.
	unsigned size();
	//-------------------------------------------------------------------------

	//-------------------------------------------------- Gerenciamento de dados
	// Insere um elemento.
	void insert(const T& key);
	
	// Verifica se o elemento pertence ao multiconjunto.
	bool contains(const T& key);

	// Retorna o número de ocorrências de um elemento.
	int frequency(const T& key);

	// Remove um dado elemento do multiconjunto.
	// Caso o segundo parâmetro seja passado com o valor "true",
	// todos os elementos iguais são removidos.
	bool remove(const T& key, bool all_equal = false);

	// Remove todos os elementos do multiconjunto.
	void clear();
	//-------------------------------------------------------------------------

	//------------------------------------------ Operações entre multiconjuntos
	// A partir do C++ 11, retorno de objeto local
	// usa "move semantics" (não há cópia).

	// União (union é palavra reservada ¬¬)
	RBTMultiset<T> _union(const RBTMultiset<T>& ms);

	// Interseção
	RBTMultiset<T> _intersection(const RBTMultiset<T>& ms);

	// Diferença
	RBTMultiset<T> _difference(const RBTMultiset<T>& ms);
	//-------------------------------------------------------------------------

	//--------------------------------------------------------------- Depuração
	//-------------------------------------------------------------------------

private:
	//---------------------------------------------- Operações de balanceamento
	void balance(RBTNode<T>* node);
	void leftRotate(RBTNode<T>* node);
	void rightRotate(RBTNode<T>* node);

	RBTNode<T>* m_root;

	unsigned m_size;
};


//-------------------------------------------------------------- Implementações

template <typename T>
RBTMultiset<T>::RBTMultiset() : m_root(nullptr), m_size(0u) {}

template <typename T>
RBTMultiset<T>::~RBTMultiset() {
	clear();
}

template <typename T>
bool RBTMultiset<T>::empty() {
	return m_size == 0;
}

template <typename T>
unsigned RBTMultiset<T>::size() {
	return m_size;
}

template <typename T>
void RBTMultiset<T>::insert(const T& key) {
	// Se a árvore estiver vazia constrói a raiz.
	if (m_root == nullptr)
		m_root = new RBTNode<T>(key, BLACK);
	else {
		bool already_in_tree = false;
		RBTNode<T>* itr = m_root, parent;

		// Procura o lugar onde o elemento deve ser inserido.
		while (itr && !already_in_tree) {
			parent = itr;

			if (key == itr.key) { // Elemento já está na árvore.
				itr.key++;
				already_in_tree = true;
			}
			else if (key < itr.key) // Deve ser inserido na subárvore esquerda.
				itr = itr->left;
			else // Deve ser inserido na subárvore direita.
				itr = itr->right;
		}

		if (!already_in_tree) { // Se o elemento ainda não está na árvore.
			RBTNode<T>* node = new RBTNode<T>(key, RED);
			node.parent = parent;

			if (node.key < parent.key)
				parent.left = node;
			else
				parent.right = node;

			// Balanceia a árvore.
			balance(node);
		}
	}
}

template <typename T>
bool RBTMultiset<T>::contains(const T& key) {}

template <typename T>
int RBTMultiset<T>::frequency(const T& key) {}

template <typename T>
bool RBTMultiset<T>::remove(const T& key, bool all_equal) {}

template <typename T>
void RBTMultiset<T>::clear() {}

template <typename T>
RBTMultiset<T> RBTMultiset<T>::_union(const RBTMultiset<T>& ms) {}

template <typename T>
RBTMultiset<T> RBTMultiset<T>::_intersection(const RBTMultiset<T>& ms) {}

template <typename T>
RBTMultiset<T> RBTMultiset<T>::_difference(const RBTMultiset<T>& ms) {}

template <typename T>
void RBTMultiset<T>::balance(RBTNode<T>* node) {
	while (node->parent && node->parent->color == RED) {
		RBTNode<T>* grand_parent = node->parent->parent;

		if (grand_parent->left == node->parent) {
			if (grand_parent->right) {
				if (grand_parent->right->color = RED) {
					node->parent->color = BLACK;
					grand_parent->right->color = BLACK;
					grand_parent->color = RED;
					node = grand_parent;
				}
			}
			else {
				if (node->parent->right == node) {
					node = node->parent;
					leftRotate(node);
				}

				node->parent->color = BLACK;
				grand_parent->color = RED;
				rightRotate(grand_parent);
			}
		}
		else {
			if (grand_parent->left) {
				if (grand_parent->left->color = RED) {
					node->parent->color = BLACK;
					grand_parent->left->color = BLACK;
					grand_parent->color = RED;
					node = grand_parent;
				}
			}
			else {
				if (node->parent->left == node) {
					node = node->parent;
					rightRotate(node);
				}

				node->parent->color = BLACK;
				grand_parent->color = RED;
				leftRotate(grand_parent);
			}
		}

		m_root.color = BLACK;
	}
}

template <typename T>
void RBTMultiset<T>::leftRotate(RBTNode<T>* node) {
	if (!node->right)
		return;

	RBTNode<T>* aux_node = node->right;

	if (aux_node->left) {
		node->right = aux_node->left;
		aux_node->left->parent = node;
	}
	else
		node->right = nullptr;

	if (!node->parent)
		m_root = aux_node;
	else {
		aux_node->parent = node->parent;

		if (node == node->parent->left)
			node->parent->left = aux_node;
		else
			node->parent->right = aux_node;
	}

	aux_node->left = node;
	node->parent = aux_node;
}

template <typename T>
void RBTMultiset<T>::rightRotate(RBTNode<T>* node) {
	if (!node->left)
		return;

	RBTNode<T>* aux_node = node->left;

	if (aux_node->right) {
		node->left = aux_node->right;
		aux_node->right->parent = node;
	}
	else
		node->left = nullptr;

	if (!node->parent)
		m_root = aux_node;
	else {
		aux_node->parent = node->parent;

		if (node == node->parent->left)
			node->parent->left = aux_node;
		else
			node->parent->right = aux_node;
	}

	aux_node->right = node;
	node->parent = aux_node;
}


#endif	// MULTISET_HPP