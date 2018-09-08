/******************************************************************************
 * INF 610 - Estruturas de Dados e Algoritmos - 2018/2                        *
 *                                                                            *
 * Lista de exercícios 3                                                      *
 *                                                                            *
 * Marcelo de Matos Menezes - 75254                                           *
 *                                                                            *
 *****************************************************************************/


// Flag para habilitar as funções de depuração
#define RBT_DEBUG


#ifndef RBT_MULTISET_HPP
#define RBT_MULTISET_HPP


#ifdef RBT_DEBUG
#include <iostream>
#endif	// RBT_DEBUG


//***** DEFINIÇÕES *****//

#define RED true
#define BLACK false

typedef bool Color;


template <typename T>
struct RBTNode {
	RBTNode() : parent(nullptr), left(nullptr), right(nullptr) {}
	RBTNode(T k, Color c) : key(k), color(c), count(1ll),
		parent(nullptr), left(nullptr), right(nullptr) {}

	T key;
	Color color;
	long long count;
	RBTNode<T>* parent;
	RBTNode<T>* left;
	RBTNode<T>* right;
};


template <typename T>
class RBTMultiset {
public:
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
	
	// Verifica se o elemento está contido no multiconjunto.
	bool contains(const T& key);

	// Retorna o número de ocorrências de um elemento.
	long long frequency(const T& key);

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
#ifdef RBT_DEBUG
	void print();
	void print(int height, RBTNode<T>* node);
#endif	// RBT_DEBUG
	//-------------------------------------------------------------------------

private:
	//---------------------------------------------------- Operações auxiliares
	void replaceNode(bool delete_old_node,
		RBTNode<T>* old_node, RBTNode<T>* new_node);
	void clear(RBTNode<T>* node);
	RBTNode<T>* minimum(RBTNode<T>* node);
	RBTNode<T>* maximum(RBTNode<T>* node);
	//-------------------------------------------------------------------------

	//---------------------------------------------- Operações de balanceamento
	void balanceInsertion(RBTNode<T>* node);
	void balanceRemoval(RBTNode<T>* node);
	void leftRotate(RBTNode<T>* node);
	void rightRotate(RBTNode<T>* node);
	//-------------------------------------------------------------------------

	RBTNode<T>* m_root;

	unsigned m_size;
};


//***** IMPLEMENTAÇÕES *****//

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
		RBTNode<T>* itr = m_root;
		RBTNode<T>* parent;

		// Procura o lugar onde o elemento deve ser inserido.
		while (itr && !already_in_tree) {
			parent = itr;

			if (key == itr->key) { // Elemento já está na árvore.
				itr->count++;
				already_in_tree = true;
			}
			else if (key < itr->key) // Deve ser inserido na subárvore esquerda.
				itr = itr->left;
			else // Deve ser inserido na subárvore direita.
				itr = itr->right;
		}

		if (!already_in_tree) { // Se o elemento ainda não está na árvore.
			RBTNode<T>* node = new RBTNode<T>(key, RED);
			node->parent = parent;

			if (node->key < parent->key)
				parent->left = node;
			else
				parent->right = node;

			// Balanceia a árvore.
			balanceInsertion(node);
		}
	}

	m_size++;
}

template <typename T>
bool RBTMultiset<T>::contains(const T& key) {
	bool found = false;
	RBTNode<T>* itr = m_root;

	while (itr && !found) {
		if (key == itr->key)
			found = true;
		else if (key < itr->key)
			itr = itr->left;
		else
			itr = itr->right;
	}

	return found;
}

template <typename T>
long long RBTMultiset<T>::frequency(const T& key) {
	long long freq = 0ll;
	RBTNode<T>* itr = m_root;

	while (itr && freq == 0ll) {
		if (key == itr->key)
			freq = itr->count;
		else if (key < itr->key)
			itr = itr->left;
		else
			itr = itr->right;
	}

	return freq;
}

template <typename T>
bool RBTMultiset<T>::remove(const T& key, bool all_equal) {
	short found = 0;
	RBTNode<T>* itr = m_root;

	while (itr && found == 0) {
		if (key == itr->key) {
			if (!all_equal && itr->count > 1) {
				itr->count--;
				found = 1; // Nó encontrado, mas não é necessário remover
			}
			else
				found = 2; // Nó encontrado e deve ser removido
		}
		else if (key < itr->key)
			itr = itr->left;
		else
			itr = itr->right;
	}

	if (found == 2) {
		RBTNode<T>* aux_node_1;
		RBTNode<T>* aux_node_2;
		RBTNode<T>* aux_node_1_parent = itr;

		Color original_color = itr->color;

 		if (!itr->left) { // Remoção simples
			aux_node_1 = itr->right;
			replaceNode(true, itr, itr->right);
		}
		else if (!itr->right) { // Remoção simples
			aux_node_1 = itr->left;
			replaceNode(true, itr, itr->left);
		}
		else { // Substitui o nó por seu sucessor
			aux_node_2 = minimum(itr->right);
			original_color = aux_node_2->color;
			aux_node_1 = aux_node_2->right;
			aux_node_1_parent = aux_node_2;

			// Se o sucessor não for filho direto do nó a ser removido,
			// o filho do sucessor deve ser colocado em seu lugar e o
			// sucessor se torna o pai da subárvore direita do nó a ser
			// removido
			if (aux_node_2->parent != itr) {
				replaceNode(false, aux_node_2, aux_node_2->right);
				aux_node_2->right = itr->right;
				aux_node_2->right->parent = aux_node_2;
				aux_node_1_parent = aux_node_2->parent;
			}

			// Subárvore esquerda do nó a ser removido se torna subárvore
			// esquerda de seu sucessor
			aux_node_2->left = itr->left;
			aux_node_2->left->parent = aux_node_2;
			aux_node_2->color = itr->color;

			// Sucessor ocupa o lugar do nó a ser removido
			replaceNode(true, itr, aux_node_2);
		}

		if (original_color == BLACK) {
print();
			if (!aux_node_1)
				balanceRemoval(aux_node_1_parent);
			else
				balanceRemoval(aux_node_1);
		}
	}

	return found; // true se o nó foi encontrado, false caso contrário
}

template <typename T>
void RBTMultiset<T>::clear() {
	clear(m_root);
	m_root = nullptr;
	m_size = 0u;
}

//---------------------------------------------- Operações entre multiconjuntos
template <typename T>
RBTMultiset<T> RBTMultiset<T>::_union(const RBTMultiset<T>& ms) {}

template <typename T>
RBTMultiset<T> RBTMultiset<T>::_intersection(const RBTMultiset<T>& ms) {}

template <typename T>
RBTMultiset<T> RBTMultiset<T>::_difference(const RBTMultiset<T>& ms) {}

//------------------------------------------------------------------- Depuração
#ifdef RBT_DEBUG

template <typename T>
void RBTMultiset<T>::print() {
	std::cout << std::endl;
	print(0, m_root);
	std::cout << std::endl;
}

template <typename T>
void RBTMultiset<T>::print(int height, RBTNode<T>* node) {
	if (node) {
		print(height + 1, node->right);

		for (int i = 0; i < 9 * height; i++)
			std::cout << " ";
		std::cout << "|";
		for (int i = 0; i < 6; i++)
			std::cout << "-";

// Nós vermelhos são coloridos no terminal do linux
#ifdef __unix__
		if (node->color == RED)
			std::cout << "\033[31m(" << node->key << ", "
				<< node->count << ")\033[39m" << std::endl;
		else
			std::cout << "(" << node->key << ", "
				<< node->count << ")" << std::endl;
#else
		if (node->color == RED)
			std::cout << "(" << node->key << ", "
				<< node->count << ")" << std::endl;
		else
			std::cout << "(" << node->key << ", "
				<< node->count << ")" << std::endl;
#endif	// Operating System stuff

		print(height + 1, node->left);
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

#endif	// RBT_DEBUG

//-------------------------------------------------------- Operações auxiliares
template <typename T>
void RBTMultiset<T>::replaceNode(bool delete_old_node,
	RBTNode<T>* old_node, RBTNode<T>* new_node) {
	if (!old_node->parent)
		m_root = new_node;
	else if (old_node->parent->left && old_node->parent->left == old_node)
		old_node->parent->left = new_node;
	else
		old_node->parent->right = new_node;

	if (new_node)
		new_node->parent = old_node->parent;

	if (delete_old_node)
		delete old_node;
}

template <typename T>
void RBTMultiset<T>::clear(RBTNode<T>* node) {
	if (node->left)
		clear(node->left);

	if (node->right)
		clear(node->right);

	delete node;
}

template <typename T>
RBTNode<T>* RBTMultiset<T>::minimum(RBTNode<T>* node) {
	RBTNode<T>* itr = node;

	while (itr->left)
		itr = itr->left;

	return itr;
}

template <typename T>
RBTNode<T>* RBTMultiset<T>::maximum(RBTNode<T>* node) {
	RBTNode<T>* itr = node;

	while (itr->right)
		itr = itr->right;

	return itr;
}

//-------------------------------------------------- Operações de balanceamento
template <typename T>
void RBTMultiset<T>::balanceInsertion(RBTNode<T>* node) {
	while (node->parent && node->parent->color == RED) {
		RBTNode<T>* grand_parent = node->parent->parent;

		if (grand_parent->left == node->parent) {
			if (grand_parent->right && grand_parent->right->color == RED) {
				node->parent->color = BLACK;
				grand_parent->right->color = BLACK;
				grand_parent->color = RED;
				node = grand_parent;
			}
			else if (node->parent->right && node->parent->right == node) {
				node = node->parent;
				leftRotate(node);
			}
			else {
				node->parent->color = BLACK;
				grand_parent->color = RED;
				rightRotate(grand_parent);
			}
		}
		else {
			if (grand_parent->left && grand_parent->left->color == RED) {
				node->parent->color = BLACK;
				grand_parent->left->color = BLACK;
				grand_parent->color = RED;
				node = grand_parent;
			}
			else if (node->parent->left && node->parent->left == node) {
				node = node->parent;
				rightRotate(node);
			}
			else {
				node->parent->color = BLACK;
				grand_parent->color = RED;
				leftRotate(grand_parent);
			}
		}
	}

	m_root->color = BLACK;
}

template <typename T>
void RBTMultiset<T>::balanceRemoval(RBTNode<T>* node) {
	RBTNode<T>* aux_node;

	while (node->parent && node->color == BLACK) {
		if (node == node->parent->left) {
			aux_node = node->parent->right;

			if (aux_node && aux_node->color == RED) {
				aux_node->color = BLACK;
				node->parent->color = RED;
				leftRotate(node->parent);
				aux_node = node->parent->right;
std::cout << "0";
print();
			}

			if ((!aux_node->left || aux_node->left->color == BLACK) &&
				(!aux_node->right || aux_node->right->color == BLACK)) {
				aux_node->color = RED;
				node = node->parent;
std::cout << "1";
print();
			}
			else {
				if (!aux_node->right || aux_node->right->color == BLACK) {
					aux_node->left->color = BLACK;
					aux_node->color = RED;
					rightRotate(aux_node);
					aux_node = node->parent->right;
std::cout << "2";
print();
				}

				aux_node->color = node->parent->color;
				node->parent->color = BLACK;
				aux_node->right->color = BLACK;
				leftRotate(node->parent);
std::cout << "3";
print();
				node = m_root;
			}
		}
		else {
			aux_node = node->parent->left;

			if (aux_node && aux_node->color == RED) {
				aux_node->color = BLACK;
				node->parent->color = RED;
				rightRotate(node->parent);
				aux_node = node->parent->left;
std::cout << "4";
print();
			}

			if ((!aux_node->right || aux_node->right->color == BLACK) &&
				(!aux_node->left || aux_node->left->color == BLACK)) {
				aux_node->color = RED;
				node = node->parent;
std::cout << "5";
print();
			}
			else {
				if (!aux_node->left || aux_node->left->color == BLACK) {
					aux_node->right->color = BLACK;
					aux_node->color = RED;
					leftRotate(aux_node);
					aux_node = node->parent->left;
std::cout << "6";
print();
				}

				aux_node->color = node->parent->color;
				node->parent->color = BLACK;
				aux_node->left->color = BLACK;
				rightRotate(node->parent);
std::cout << "7";
print();		
				node = m_root;
			}
		}
	}

	node->color = BLACK;
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

	aux_node->parent = node->parent;

	if (!node->parent)
		m_root = aux_node;
	else if (node == node->parent->left)
		node->parent->left = aux_node;
	else
		node->parent->right = aux_node;

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

	aux_node->parent = node->parent;

	if (!node->parent)
		m_root = aux_node;
	else if (node == node->parent->left)
		node->parent->left = aux_node;
	else
		node->parent->right = aux_node;

	aux_node->right = node;
	node->parent = aux_node;
}


#endif	// MULTISET_HPP