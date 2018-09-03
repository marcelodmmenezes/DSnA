/******************************************************************************
 * INF 610 - Estruturas de Dados e Algoritmos - 2018/2                        *
 *                                                                            *
 * Lista de exercícios 3                                                      *
 *                                                                            *
 * Marcelo de Matos Menezes - 75254                                           *
 *                                                                            *
 *****************************************************************************/

//https://www.coders-hub.com/2015/07/red-black-tree-rb-tree-using-c.html#.W41ogXVKi2x
//https://www.cs.usfca.edu/~galles/visualization/RedBlack.html


#define RBT_DEBUG


#ifndef RBT_MULTISET_HPP
#define RBT_MULTISET_HPP


#ifdef RBT_DEBUG
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
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


template<typename T>
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
#ifdef RBT_DEBUG
	void print();
#endif	// RBT_DEBUG
	//-------------------------------------------------------------------------

private:
	//---------------------------------------------- Operações de balanceamento
	void balance(RBTNode<T>* node);
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
				itr->key++;
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
			balance(node);
		}
	}

	m_size++;
}

template <typename T>
bool RBTMultiset<T>::contains(const T& key) {}

template <typename T>
int RBTMultiset<T>::frequency(const T& key) {}

template <typename T>
bool RBTMultiset<T>::remove(const T& key, bool all_equal) {}

template <typename T>
void RBTMultiset<T>::clear() {}


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
	int height = 1;

	std::queue<RBTNode<T>*> output;

	output.push(m_root);

	// Flag (nó com count == -1) para contar os níveis da árvore
	RBTNode<T>* flag = new RBTNode<T>;
	flag->count = -1ll;
	output.push(flag);

	while (!output.empty()) {
		auto node = output.front();
		output.pop();

		if (!node) { // Filho nulo imprime espaços
			for (int i = 0; i < 200 / pow(2, height); i++)
				std::cout << " ";
			std::cout << "         ";

			if (height < log(m_size)) { // Simula árvore cheia
				output.push(nullptr);
				output.push(nullptr);
			}
		}
		else if (node->count == -1ll) { // Se for flag a busca passou um nível
			std::cout << std::endl;
			output.push(flag);

			height++;

			// Duas flags seguidas indicam que a fila está vazia.
			if (output.front() && output.front()->count == -1ll)
				break;
		}
		else {
			for (int i = 0; i < 100 / pow(2, height); i++)
				std::cout << " ";

			std::cout << "(" << std::setw(1) << node->key << ", "
				<< std::setw(1) << node->count << ") ";

			for (int i = 0; i < 100 / pow(2, height); i++)
				std::cout << " ";
			
			output.push(node->left);
			output.push(node->right);
		}
	}

	delete flag;
}

#endif	// RBT_DEBUG


//-------------------------------------------------- Operações de balanceamento
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

		m_root->color = BLACK;
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