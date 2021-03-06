/******************************************************************************
 * INF 610 - Estruturas de Dados e Algoritmos - 2018/2                        *
 *                                                                            *
 * Lista de exercícios 3                                                      *
 *                                                                            *
 * Marcelo de Matos Menezes - 75254                                           *
 *                                                                            *
 * Multiset implementation using an Ordered Dynamic Array as data strutcture. *
 *                                                                            *
 *****************************************************************************/


#ifndef ODA_MULTISET_HPP
#define ODA_MULTISET_HPP


#ifdef ODA_DEBUG
	#include <iostream>
#endif

#include <utility>


//***** DEFINIÇÕES *****//

template <typename T>
struct ODANode {
	ODANode() : count(1ll) {}
	ODANode(T k, long long c) : key(k), count(c) {}

	T key;
	long long count;
};


template <typename T>
class ODAMultiset {
public:
	ODAMultiset();
	ODAMultiset(ODAMultiset<T>&& ms);
	ODAMultiset(long long capacity);
	~ODAMultiset();

	//-------------------------------------------------------------------- Info
	// Testa se o multiconjunto está vazio.
	bool empty();

	// Retorna o tamanho do multiconjunto.
	long long size();

	// Retorna o número de elementos distintos do multiconjunto.
	long long unique();

	// Retorna o tamanho em memória ocupado pelo multiconjunto.
	long long capacity();
	//-------------------------------------------------------------------------

	//-------------------------------------------------- Gerenciamento de dados
	// Insere um ou mais elementos.
	bool insert(const T& key, long long qnt = 1ll);
	
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

	// Mesmo que o clear, mas libera a memória, com exceção de uma posição
	void reset();
	//-------------------------------------------------------------------------	

	//------------------------------------------ Operações entre multiconjuntos
	// A partir do C++ 11, retorno de objeto local
	// usa "move semantics" (não há cópia).

	// União (union é palavra reservada ¬¬)
	ODAMultiset<T> _union(ODAMultiset<T>& ms);

	// Interseção
	ODAMultiset<T> _intersection(ODAMultiset<T>& ms);

	// Diferença
	ODAMultiset<T> _difference(ODAMultiset<T>& ms);
	//-------------------------------------------------------------------------

	//--------------------------------------------------------------- Depuração
#ifdef ODA_DEBUG
	void printElements();
#endif
	//-------------------------------------------------------------------------

private:
	//---------------------------------------------------- Operações auxiliares
	// Retorna o índice do elemento. -1 caso não exista.
	long long getElementPosition(const T& key);
	//-------------------------------------------------------------------------

	ODANode<T>* m_array;
	long long m_size; // Quantidade de elemenos
	long long m_occupied; // Memória ocupada
	long long m_capacity; // Memória alocada
};


//***** IMPLEMENTAÇÕES *****//

template <typename T>
ODAMultiset<T>::ODAMultiset() : m_size(0ll), m_occupied(0ll), m_capacity(1ll) {
	m_array = new ODANode<T>;
}

template <typename T>
ODAMultiset<T>::ODAMultiset(ODAMultiset<T>&& ms) : m_size(ms.m_size),
	m_occupied(ms.m_occupied), m_capacity(ms.m_capacity), m_array(ms.m_array) {
	ms.m_size = ms.m_occupied = ms.m_capacity = 0ll;
	ms.m_array = nullptr;
}

template <typename T>
ODAMultiset<T>::ODAMultiset(long long capacity) :
	m_size(0ll), m_occupied(0ll), m_capacity(capacity) {
	if (m_capacity <= 0ll)
		m_capacity = 1ll;

	m_array = new ODANode<T>[m_capacity];
}

template <typename T>
ODAMultiset<T>::~ODAMultiset() {
	clear();
	delete[] m_array;
}

template <typename T>
bool ODAMultiset<T>::empty() {
	return m_size == 0ll;
}

template <typename T>
long long ODAMultiset<T>::size() {
	return m_size;
}

template <typename T>
long long ODAMultiset<T>::unique() {
	return m_occupied;
}

template <typename T>
long long ODAMultiset<T>::capacity() {
	return m_capacity;
}

//------------------------------------------------------ Gerenciamento de dados
template <typename T>
bool ODAMultiset<T>::insert(const T& key, long long qnt) {
	long long pos = getElementPosition(key);

	// Se o elemento já estiver no array basta incrementar seu contador
	if (pos >= 0ll) {
		m_array[pos].count += qnt;
		m_size += qnt;
		return true;
	}

	// Se a capacidade foi preenchida aloca um novo vetor
	if (m_occupied == m_capacity) {
		m_capacity *= 2ll;

		ODANode<T>* aux = new ODANode<T>[m_capacity];
		
		// Se conseguiu alocar o array, copia o array antigo
		//acrescentando o novo elemento
		if (aux) {
			long long i = 0ll;

			while (i < m_occupied && m_array[i].key < key) {
				aux[i] = m_array[i];
				i++;
			}

			aux[i] = ODANode<T>(key, qnt);

			while (i < m_occupied) {
				aux[i + 1ll] = m_array[i];
				i++;
			}

			m_size += qnt;
			m_occupied++;

			delete[] m_array;
			m_array = aux;

			return true;
		}
	}
	else {
		long long i = m_occupied;

		while (i > 0ll && m_array[i - 1ll].key > key) {
			m_array[i] = m_array[i - 1ll];
			i--;
		}

		m_array[i] = ODANode<T>(key, qnt);

		m_size += qnt;
		m_occupied++;

		return true;
	}

	return false;
}

template <typename T>
bool ODAMultiset<T>::contains(const T& key) {
	return getElementPosition(key) >= 0;
}

template <typename T>
long long ODAMultiset<T>::frequency(const T& key) {
	long long pos = getElementPosition(key);

	if (pos >= 0ll)
		return m_array[pos].count;
	else
		return 0ll;
}

template <typename T>
bool ODAMultiset<T>::remove(const T& key, bool all_equal) {
	long long pos = getElementPosition(key);

	if (pos < 0ll)
		return false;

	if (all_equal || m_array[pos].count == 1ll) {
		for (long long i = pos; i < m_occupied; i++)
			m_array[i] = m_array[i + 1ll];

		m_size -= m_array[pos].count;
		m_occupied--;
	}
	else {
		m_size--;
		m_array[pos].count--;
	}

	return true;
}

template <typename T>
void ODAMultiset<T>::clear() {
	m_size = m_occupied = 0ll;
}

template <typename T>
void ODAMultiset<T>::reset() {
	delete[] m_array;
	m_array = new ODANode<T>;

	m_size = m_occupied = 0ll;
	m_capacity = 1ll;
}

template <typename T>
ODAMultiset<T> ODAMultiset<T>::_union(ODAMultiset<T>& ms) {
	ODAMultiset<T> result;
	long long itr_1 = 0ll, itr_2 = 0ll;

	while (itr_1 < m_occupied && itr_2 < ms.m_occupied) {
		if (m_array[itr_1].key < ms.m_array[itr_2].key) {
			result.insert(m_array[itr_1].key, m_array[itr_1].count);
			itr_1++;
		}
		else if (m_array[itr_1].key > ms.m_array[itr_2].key) {
			result.insert(ms.m_array[itr_2].key, ms.m_array[itr_2].count);
			itr_2++;
		}
		else {
			result.insert(m_array[itr_1].key,
				m_array[itr_1].count > ms.m_array[itr_2].count ?
				m_array[itr_1].count : ms.m_array[itr_2].count);

			itr_1++;
			itr_2++;
		}
	}

	while (itr_1 < m_occupied) {
		result.insert(m_array[itr_1].key, m_array[itr_1].count);
		itr_1++;
	}

	while (itr_2 < ms.m_occupied) {
		result.insert(ms.m_array[itr_2].key, ms.m_array[itr_2].count);
		itr_2++;
	}

	return std::move(result);
}

template <typename T>
ODAMultiset<T> ODAMultiset<T>::_intersection(ODAMultiset<T>& ms) {
	ODAMultiset<T> result;
	long long itr_1 = 0ll, itr_2 = 0ll;

	while (itr_1 < m_occupied && itr_2 < ms.m_occupied) {
		if (m_array[itr_1].key < ms.m_array[itr_2].key)
			itr_1++;
		else if (m_array[itr_1].key > ms.m_array[itr_2].key)
			itr_2++;
		else {
			result.insert(m_array[itr_1].key,
				m_array[itr_1].count < ms.m_array[itr_2].count ?
				m_array[itr_1].count : ms.m_array[itr_2].count);

			itr_1++;
			itr_2++;
		}
	}

	return std::move(result);
}

template <typename T>
ODAMultiset<T> ODAMultiset<T>::_difference(ODAMultiset<T>& ms) {
	ODAMultiset<T> result;

	long long itr_1 = 0ll, itr_2 = 0ll;

	while (itr_1 < m_occupied && itr_2 < ms.m_occupied) {
		if (m_array[itr_1].key < ms.m_array[itr_2].key) {
			result.insert(m_array[itr_1].key, m_array[itr_1].count);
			itr_1++;
		}
		else if (m_array[itr_1].key > ms.m_array[itr_2].key)
			itr_2++;
		else {
			long long dif = m_array[itr_1].count > ms.m_array[itr_2].count ?
				m_array[itr_1].count - ms.m_array[itr_2].count : 0ll;

			if (dif > 0ll)
				result.insert(m_array[itr_1].key, dif);

			itr_1++;
			itr_2++;
		}
	}

	while (itr_1 < m_occupied) {
		result.insert(m_array[itr_1].key, m_array[itr_1].count);
		itr_1++;
	}

	return std::move(result);
}

//------------------------------------------------------------------- Depuração
#ifdef ODA_DEBUG

template <typename T>
void ODAMultiset<T>::printElements() {
	for (long long i = 0ll; i < m_occupied; i++)
		for (long long j = 0ll; j < m_array[i].count; j++)
			std::cout << m_array[i].key << " ";
}

#endif	// ODA_DEBUG

//-------------------------------------------------------- Operações auxiliares
template <typename T>
long long ODAMultiset<T>::getElementPosition(const T& key) {
	long long left = 0ll, right = m_occupied - 1, middle;

    while (left <= right) {
        middle = (right + left) / 2;

		// Se encontrar a chave retorna
        if (m_array[middle].key == key)
            return middle;

        if (m_array[middle].key < key)
            left = middle + 1;
        else
            right = middle - 1;
    }

    return -1ll;
}


#endif	// ODA_MULTISET_HPP