/******************************************************************************
 * INF 610 - Estruturas de Dados e Algoritmos - 2018/2                        *
 *                                                                            *
 * Lista de exercícios 3                                                      *
 *                                                                            *
 * Marcelo de Matos Menezes - 75254                                           *
 *                                                                            *
 *****************************************************************************/


#ifndef RBT_MULTISET_HPP
#define RBT_MULTISET_HPP


#ifdef RBT_DEBUG
	#include <iostream>
	#ifdef _WIN32
		#include <windows.h>
	#endif
#endif

#include <utility>


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
	RBTMultiset(RBTMultiset<T>&& ms);
	~RBTMultiset();
	
	//-------------------------------------------------------------------- Info
	// Testa se o multiconjunto está vazio.
	bool empty();

	// Retorna o tamanho do multiconjunto.
	long long size();
	//-------------------------------------------------------------------------

	//-------------------------------------------------- Gerenciamento de dados
	// Insere um ou mais elementos.
	void insert(const T& key, long long qnt = 1ll);
	
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
	RBTMultiset<T> _union(RBTMultiset<T>& ms);

	// Interseção
	RBTMultiset<T> _intersection(RBTMultiset<T>& ms);

	// Diferença
	RBTMultiset<T> _difference(RBTMultiset<T>& ms);
	//-------------------------------------------------------------------------

	//--------------------------------------------------------------- Depuração
#ifdef RBT_DEBUG
	void printElements();
	void printTree();
#endif
	//-------------------------------------------------------------------------

private:
	//--------------------------------------------------------------- Depuração
#ifdef RBT_DEBUG
	void printElements(RBTNode<T>* node);
	void printTree(int height, RBTNode<T>* node);
#endif
	//-------------------------------------------------------------------------

	//---------------------------------------------------- Operações auxiliares
	void replaceNode(bool delete_old_node,
		RBTNode<T>* old_node, RBTNode<T>* new_node);

	void clear(RBTNode<T>* node);
	RBTNode<T>* minimum(RBTNode<T>* node);
	RBTNode<T>* maximum(RBTNode<T>* node);
	RBTNode<T>* successor(RBTNode<T>* node);
	//-------------------------------------------------------------------------

	//---------------------------------------------- Operações de balanceamento
	void balanceInsertion(RBTNode<T>* node);
	void balanceRemoval(RBTNode<T>* node);
	void leftRotate(RBTNode<T>* node);
	void rightRotate(RBTNode<T>* node);
	//-------------------------------------------------------------------------

	RBTNode<T>* m_root;

	long long m_size;
};


//***** IMPLEMENTAÇÕES *****//

template <typename T>
RBTMultiset<T>::RBTMultiset() : m_root(nullptr), m_size(0ll) {}

template <typename T>
RBTMultiset<T>::RBTMultiset(RBTMultiset<T>&& ms) :
	m_root(ms.m_root), m_size(ms.m_size) {
	ms.m_size = 0ll;
	ms.m_root = nullptr;
}

template <typename T>
RBTMultiset<T>::~RBTMultiset() {
	clear();
}

template <typename T>
bool RBTMultiset<T>::empty() {
	return m_size == 0ll;
}

template <typename T>
long long RBTMultiset<T>::size() {
	return m_size;
}

//------------------------------------------------------ Gerenciamento de dados
template <typename T>
void RBTMultiset<T>::insert(const T& key, long long qnt) {
	// Se a árvore estiver vazia constrói a raiz
	if (m_root == nullptr)
		m_root = new RBTNode<T>(key, BLACK);
	else {
		bool already_in_tree = false;
		RBTNode<T>* itr = m_root;
		RBTNode<T>* parent;

		// Procura o lugar onde o elemento deve ser inserido
		while (itr && !already_in_tree) {
			parent = itr;

			if (key == itr->key) { // Elemento já está na árvore
				itr->count += qnt;
				already_in_tree = true;
			}
			else if (key < itr->key) // Deve ser inserido na subárvore esquerda
				itr = itr->left;
			else // Deve ser inserido na subárvore direita
				itr = itr->right;
		}

		if (!already_in_tree) { // Se o elemento ainda não está na árvore
			RBTNode<T>* node = new RBTNode<T>(key, RED);
			node->count = qnt;
			node->parent = parent;

			if (node->key < parent->key)
				parent->left = node;
			else
				parent->right = node;

			// Balanceia a árvore
			balanceInsertion(node);
		}
	}

	m_size += qnt;
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
				m_size--;
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
		m_size -= itr->count;

		RBTNode<T>* placeholder;
		RBTNode<T>* replacement;
		bool del_placeholder = false;

		Color original_color = itr->color;

 		if (!itr->left) { // Remoção simples
			// Se ambos os filhos são nulos
			if (!itr->right && itr->parent) {
				// Substituto do nó nulo para balanceamento
				itr->right = new RBTNode<T>;
				itr->right->color = BLACK;
				del_placeholder = true;
			}
			//else
			//	original_color = RED; // Evita o balanceamento

			placeholder = itr->right;
			replaceNode(true, itr, itr->right);
		}
		else if (!itr->right) { // Remoção simples
			// Se ambos os filhos são nulos
			if (!itr->left && itr->parent) {
				// Substituto do nó nulo para balanceamento
				itr->left = new RBTNode<T>;
				itr->left->color = BLACK;
				del_placeholder = true;
			}
			//else
			//	original_color = RED; // Evita o balanceamento

			placeholder = itr->left;
			replaceNode(true, itr, itr->left);
		}
		else { // Substitui o nó por seu sucessor
			replacement = minimum(itr->right);
			original_color = replacement->color;
			
			// Substituto do nó nulo para balanceamento
			if (!replacement->right) {
				replacement->right = new RBTNode<T>;
				replacement->right->color = BLACK;
				replacement->right->parent = replacement;
				del_placeholder = true;
			}

			placeholder = replacement->right;

			// Se o sucessor não for filho direto do nó a ser removido,
			// o filho do sucessor deve ser colocado em seu lugar e o
			// sucessor se torna o pai da subárvore direita do nó a ser
			// removido
			if (replacement->parent != itr) {
				replaceNode(false, replacement, replacement->right);
				replacement->right = itr->right;
				replacement->right->parent = replacement;
			}

			// Subárvore esquerda do nó a ser removido se torna subárvore
			// esquerda de seu sucessor
			replacement->left = itr->left;
			replacement->left->parent = replacement;
			replacement->color = itr->color;

			// Sucessor ocupa o lugar do nó a ser removido
			replaceNode(true, itr, replacement);
		}

		if (original_color == BLACK)
			balanceRemoval(placeholder);

		// Limpando a memória auxiliar
		if (del_placeholder) {
			if (placeholder->parent) {
				if (placeholder->parent->left == placeholder)
					placeholder->parent->left = nullptr;
				else
					placeholder->parent->right = nullptr;
			}

			delete placeholder;
		}
	}

	return found; // true se o nó foi encontrado, false caso contrário
}

template <typename T>
void RBTMultiset<T>::clear() {
	if (m_root) {
		clear(m_root);
		m_root = nullptr;
	}
	
	m_size = 0ll;
}

//---------------------------------------------- Operações entre multiconjuntos
template <typename T>
RBTMultiset<T> RBTMultiset<T>::_union(RBTMultiset<T>& ms) {
	RBTMultiset<T> result;

	RBTNode<T>* itr_1 = minimum(m_root);
	RBTNode<T>* itr_2 = minimum(ms.m_root);

	while (itr_1 && itr_2) {
		if (itr_1->key < itr_2->key) {
			result.insert(itr_1->key, itr_1->count);
			itr_1 = successor(itr_1);
		}
		else if (itr_1->key > itr_2->key) {
			result.insert(itr_2->key, itr_2->count);
			itr_2 = successor(itr_2);
		}
		else {
			result.insert(itr_1->key,
				itr_1->count > itr_2->count ?
				itr_1->count : itr_2->count);

			itr_1 = successor(itr_1);
			itr_2 = successor(itr_2);
		}
	}

	while (itr_1) {
		result.insert(itr_1->key, itr_1->count);
		itr_1 = successor(itr_1);
	}

	while (itr_2) {
		result.insert(itr_2->key, itr_2->count);
		itr_2 = successor(itr_2);
	}

	return std::move(result);
}

template <typename T>
RBTMultiset<T> RBTMultiset<T>::_intersection(RBTMultiset<T>& ms) {
	RBTMultiset<T> result;

	RBTNode<T>* itr_1 = minimum(m_root);
	RBTNode<T>* itr_2 = minimum(ms.m_root);

	while (itr_1 && itr_2) {
		if (itr_1->key < itr_2->key)
			itr_1 = successor(itr_1);
		else if (itr_1->key > itr_2->key)
			itr_2 = successor(itr_2);
		else {
			result.insert(itr_1->key,
				itr_1->count < itr_2->count ?
				itr_1->count : itr_2->count);

			itr_1 = successor(itr_1);
			itr_2 = successor(itr_2);
		}
	}

	return std::move(result);
}

template <typename T>
RBTMultiset<T> RBTMultiset<T>::_difference(RBTMultiset<T>& ms) {
	RBTMultiset<T> result;

	RBTNode<T>* itr_1 = minimum(m_root);
	RBTNode<T>* itr_2 = minimum(ms.m_root);

	while (itr_1 && itr_2) {
		if (itr_1->key < itr_2->key) {
			result.insert(itr_1->key, itr_1->count);
			itr_1 = successor(itr_1);
		}
		else if (itr_1->key > itr_2->key) {
			itr_2 = successor(itr_2);
		}
		else {
			long long dif = itr_1->count > itr_2->count ?
				itr_1->count - itr_2->count : 0ll;

			if (dif > 0ll)
				result.insert(itr_1->key, dif);

			itr_1 = successor(itr_1);
			itr_2 = successor(itr_2);
		}
	}

	while (itr_1) {
		result.insert(itr_1->key, itr_1->count);
		itr_1 = successor(itr_1);
	}

	return std::move(result);
}

//------------------------------------------------------------------- Depuração
#ifdef RBT_DEBUG

template <typename T>
void RBTMultiset<T>::printElements() {
	if (m_root)
		printElements(m_root);
}

template <typename T>
void RBTMultiset<T>::printTree() {
	std::cout << std::endl;
	printTree(0, m_root);
	std::cout << std::endl;
}

template <typename T>
void RBTMultiset<T>::printElements(RBTNode<T>* node) {
	if (node->left)
		printElements(node->left);

	for (long long i = 0; i < node->count; i++)
		std::cout << node->key << " ";

	if (node->right)
		printElements(node->right);
}

template <typename T>
void RBTMultiset<T>::printTree(int height, RBTNode<T>* node) {
	if (node) {
		printTree(height + 1, node->right);

		for (int i = 0; i < 9 * height; i++)
			std::cout << " ";
		std::cout << "|";
		for (int i = 0; i < 6; i++)
			std::cout << "-";

// Nós são coloridos de acordo com o sistema operacional
#ifdef __unix__

		if (node->color == RED)
			std::cout << "\033[31m(" << node->key << ", "
				<< node->count << ")\033[39m" << std::endl;
		else
			std::cout << "(" << node->key << ", "
				<< node->count << ")" << std::endl;

#elif defined _WIN32

		auto console = GetStdHandle(STD_OUTPUT_HANDLE);
	    auto *info = new CONSOLE_SCREEN_BUFFER_INFO();
	    GetConsoleScreenBufferInfo(console, info);
	    auto default_color = info->wAttributes;

		if (node->color == RED) {
			SetConsoleTextAttribute(console, 4);
			std::cout << "(" << node->key << ", "
				<< node->count << ")" << std::endl;
		}
		else {
			SetConsoleTextAttribute(console, 2);
			std::cout << "(" << node->key << ", "
				<< node->count << ")" << std::endl;
		}

		SetConsoleTextAttribute(console, default_color);

		delete info;

#endif	// Coisas do sistema operacional

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

	while (itr && itr->left)
		itr = itr->left;

	return itr;
}

template <typename T>
RBTNode<T>* RBTMultiset<T>::maximum(RBTNode<T>* node) {
	RBTNode<T>* itr = node;

	while (itr && itr->right)
		itr = itr->right;

	return itr;
}

template <typename T>
RBTNode<T>* RBTMultiset<T>::successor(RBTNode<T>* node) {
	if (node && node->right)
		return minimum(node->right);

	RBTNode<T>* itr = node->parent;

	while (itr && node == itr->right) {
		node = itr;
		itr = node->parent;
	}

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

	while (node && node->parent && node->color == BLACK) {
		if (node == node->parent->left) {
			aux_node = node->parent->right;

			if (aux_node && aux_node->color == RED) {
				aux_node->color = BLACK;
				node->parent->color = RED;
				leftRotate(node->parent);
				aux_node = node->parent->right;
			}

			if (aux_node &&
				(!aux_node->left || aux_node->left->color == BLACK) &&
				(!aux_node->right || aux_node->right->color == BLACK)) {
				aux_node->color = RED;
				node = node->parent;
			}
			else if (aux_node) {
				if (!aux_node->right || aux_node->right->color == BLACK) {
					aux_node->left->color = BLACK;
					aux_node->color = RED;
					rightRotate(aux_node);
					aux_node = node->parent->right;
				}

				aux_node->color = node->parent->color;
				node->parent->color = BLACK;
				aux_node->right->color = BLACK;
				leftRotate(node->parent);
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
			}

			if (aux_node &&
				(!aux_node->right || aux_node->right->color == BLACK) &&
				(!aux_node->left || aux_node->left->color == BLACK)) {
				aux_node->color = RED;
				node = node->parent;
			}
			else if (aux_node) {
				if (!aux_node->left || aux_node->left->color == BLACK) {
					aux_node->right->color = BLACK;
					aux_node->color = RED;
					leftRotate(aux_node);
					aux_node = node->parent->left;
				}

				aux_node->color = node->parent->color;
				node->parent->color = BLACK;
				aux_node->left->color = BLACK;
				rightRotate(node->parent);
				node = m_root;
			}
		}
	}

	if (node)
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