/******************************************************************************
 * INF 610 - Estruturas de Dados e Algoritmos - 2018/2                        *
 *                                                                            *
 * Lista de exercícios 3                                                      *
 *                                                                            *
 * Marcelo de Matos Menezes - 75254                                           *
 *                                                                            *
 *****************************************************************************/


#include "odamultiset.hpp"
#include "rbtmultiset.hpp"

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>


#define WRITE_TO_FILE


enum BenchmarkType {
	INSERT_CRESCENT_DATA,
	INSERT_DECRESCENT_DATA,
	INSERT_RANDOM_DATA,
	RANDOM_QUERIES,
	RANDOM_REMOVAL,

	UNION,
	INTERSECTION,
	DIFF
};


template <typename T>
void insertCrescentData(int l, int u, T& ms) {
	for (int i = l; i < u; i++)
		ms.insert(i);
}

template <typename T>
void insertDecrescentData(int l, int u, T& ms) {
	for (int i = u - 1; i >= l; i--)
		ms.insert(i);
}

template <typename T>
void insertRandomData(int n, T& ms) {
	for (int i = 0; i < n; i++)
		ms.insert(rand());
}

template <typename T>
void randomQueries(int n, T& ms) {
	for (int i = 0; i < n; i++)
		ms.contains(rand());
}

template <>
void randomQueries<std::multiset<int>>(int n, std::multiset<int>& ms) {
	for (int i = 0; i < n; i++)
		ms.find(rand());
}

template <typename T>
void randomRemoval(int n, T& ms) {
	for (int i = 0; i < n; i++)
		ms.remove(rand());
}

template <>
void randomRemoval<std::multiset<int>>(int n, std::multiset<int>& ms) {
	for (int i = 0; i < n; i++)
		ms.erase(rand());
}

void benchmarkDataManipulation(int n, BenchmarkType type,
	ODAMultiset<int>& dams, RBTMultiset<int>& rbtms, std::multiset<int>& stdms, 
	std::ostream& output = std::cout) {
	auto clock = std::chrono::high_resolution_clock::now();

	switch (type) {
		case INSERT_CRESCENT_DATA:
			insertCrescentData(0, n, dams);
			break;
		case INSERT_DECRESCENT_DATA:
			insertDecrescentData(0, n, dams);
			break;
		case INSERT_RANDOM_DATA:
			insertRandomData(n, dams);
			break;
		case RANDOM_QUERIES:
			randomQueries(n, dams);
			break;
		case RANDOM_REMOVAL:
			randomRemoval(n, dams);
			break;
	}

	output << "\tda  : " <<
		(std::chrono::high_resolution_clock::now() - clock).count()
		<< std::endl;

	clock = std::chrono::high_resolution_clock::now();

	switch (type) {
		case INSERT_CRESCENT_DATA:
			insertCrescentData(0, n, rbtms);
			break;
		case INSERT_DECRESCENT_DATA:
			insertDecrescentData(0, n, rbtms);
			break;
		case INSERT_RANDOM_DATA:
			insertRandomData(n, rbtms);
			break;
		case RANDOM_QUERIES:
			randomQueries(n, rbtms);
			break;
		case RANDOM_REMOVAL:
			randomRemoval(n, rbtms);
			break;
	}

	output << "\trbt : " <<
		(std::chrono::high_resolution_clock::now() - clock).count()
		<< std::endl;

	clock = std::chrono::high_resolution_clock::now();

	switch (type) {
		case INSERT_CRESCENT_DATA:
			insertCrescentData(0, n, stdms);
			break;
		case INSERT_DECRESCENT_DATA:
			insertDecrescentData(0, n, stdms);
			break;
		case INSERT_RANDOM_DATA:
			insertRandomData(n, stdms);
			break;
		case RANDOM_QUERIES:
			randomQueries(n, stdms);
			break;
		case RANDOM_REMOVAL:
			randomRemoval(n, stdms);
			break;
	}

	output << "\tstd : " <<
		(std::chrono::high_resolution_clock::now() - clock).count()
		<< std::endl << std::endl;
}


void benchmarkSetOperations(BenchmarkType type,
	ODAMultiset<int>& dams_1, ODAMultiset<int>& dams_2,
	RBTMultiset<int>& rbtms_1, RBTMultiset<int>& rbtms_2,
	std::multiset<int>& stdms_1, std::multiset<int>& stdms_2, 
	std::ostream& output = std::cout) {
	auto clock = std::chrono::high_resolution_clock::now();

	switch (type) {
		case UNION:
			dams_1._union(dams_2);
			break;
		case INTERSECTION:
			dams_1._intersection(dams_2);
			break;
		case DIFF:
			dams_1._difference(dams_2);
			break;
	}

	output << "\t\tda  : " <<
		(std::chrono::high_resolution_clock::now() - clock).count()
		<< std::endl;

	clock = std::chrono::high_resolution_clock::now();

	switch (type) {
		case UNION:
			rbtms_1._union(rbtms_2);
			break;
		case INTERSECTION:
			rbtms_1._intersection(rbtms_2);
			break;
		case DIFF:
			rbtms_1._difference(rbtms_2);
			break;
	}

	output << "\t\trbt : " <<
		(std::chrono::high_resolution_clock::now() - clock).count()
		<< std::endl;

	clock = std::chrono::high_resolution_clock::now();

	// As operações entre conjuntos da algorithm requerem
	// um novo conjunto para se armazenar os dados
	// A criação do conjunto auxiliar entra na contagem do tempo pois as
	// implementações anteriores criam o conjunto nas operações
	// std::back_inserter para melhorar a eficiência de inserção

	std::vector<int> aux;

	switch (type) {
		case UNION:
			std::set_union(stdms_1.begin(), stdms_1.end(),
				stdms_2.begin(), stdms_2.end(), std::back_inserter(aux));
			break;
		case INTERSECTION:
			std::set_intersection(stdms_1.begin(), stdms_1.end(),
				stdms_2.begin(), stdms_2.end(), std::back_inserter(aux));
			break;
		case DIFF:
			std::set_difference(stdms_1.begin(), stdms_1.end(),
				stdms_2.begin(), stdms_2.end(), std::back_inserter(aux));
			break;
	}

	output << "\t\tstd : " <<
		(std::chrono::high_resolution_clock::now() - clock).count()
		<< std::endl << std::endl;
}



int main() {
	srand(time(nullptr));
	std::ios_base::sync_with_stdio(false);

	ODAMultiset<int> dams_1, dams_2;
	RBTMultiset<int> rbtms_1, rbtms_2;
	std::multiset<int> stdms_1, stdms_2;

	// Para ficar fácil de redirecionar a saída caso necessário

#ifdef WRITE_TO_FILE
	std::ofstream output;
	output.open("output.txt", std::ios::out);
#else
	std::ostream& output = std::cout;
#endif

	output << "Benchmarking data manipulation:\n" << std::endl;

	for (int i = 1000; i <= 100000; i *= 10) {
		output << i << ":" << std::endl;

		benchmarkDataManipulation(i, INSERT_CRESCENT_DATA,
			dams_1, rbtms_1, stdms_1, output);

		dams_1.reset();
		rbtms_1.clear();
		stdms_1.clear();

		benchmarkDataManipulation(i, INSERT_DECRESCENT_DATA,
			dams_1, rbtms_1, stdms_1, output);

		dams_1.reset();
		rbtms_1.clear();
		stdms_1.clear();

		benchmarkDataManipulation(i, INSERT_RANDOM_DATA,
			dams_1, rbtms_1, stdms_1, output);
		
		benchmarkDataManipulation(i, RANDOM_QUERIES,
			dams_1, rbtms_1, stdms_1, output);

		benchmarkDataManipulation(i, RANDOM_REMOVAL,
			dams_1, rbtms_1, stdms_1, output);

		dams_1.reset();
		rbtms_1.clear();
		stdms_1.clear();
	}

	output << "Benchmarking set operations:\n" << std::endl;

	for (int i = 1000; i <= 1000000; i *= 10) {
		output << i << ":" << std::endl;

		output << "\n\tElementos distintos:" << std::endl;

		// Todas as estruturas são ordenadas, portanto para esse teste
		// não importa a ordem de inserção dos elementos
		insertCrescentData(0, i, dams_1);
		insertCrescentData(i + 1, 2 * (i + 1), dams_2);
		insertCrescentData(0, i, rbtms_1);
		insertCrescentData(i + 1, 2 * (i + 1), rbtms_2);
		insertCrescentData(0, i, stdms_1);
		insertCrescentData(i + 1, 2 * (i + 1), stdms_2);

		benchmarkSetOperations(UNION, dams_1, dams_2,
			rbtms_1, rbtms_2, stdms_1, stdms_2, output);

		benchmarkSetOperations(INTERSECTION, dams_1, dams_2,
			rbtms_1, rbtms_2, stdms_1, stdms_2, output);

		benchmarkSetOperations(DIFF, dams_1, dams_2,
			rbtms_1, rbtms_2, stdms_1, stdms_2, output);

		dams_1.reset();
		dams_2.reset();
		rbtms_1.clear();
		rbtms_2.clear();
		stdms_1.clear();
		stdms_2.clear();

		output << "\n\tElementos iguais:" << std::endl;

		// Todas as estruturas são ordenadas, portanto para esse teste
		// não importa a ordem de inserção dos elementos
		insertCrescentData(0, i, dams_1);
		insertCrescentData(0, i, dams_2);
		insertCrescentData(0, i, rbtms_1);
		insertCrescentData(0, i, rbtms_2);
		insertCrescentData(0, i, stdms_1);
		insertCrescentData(0, i, stdms_2);

		benchmarkSetOperations(UNION, dams_1, dams_2,
			rbtms_1, rbtms_2, stdms_1, stdms_2, output);

		benchmarkSetOperations(INTERSECTION, dams_1, dams_2,
			rbtms_1, rbtms_2, stdms_1, stdms_2, output);

		benchmarkSetOperations(DIFF, dams_1, dams_2,
			rbtms_1, rbtms_2, stdms_1, stdms_2, output);

		dams_1.reset();
		dams_2.reset();
		rbtms_1.clear();
		rbtms_2.clear();
		stdms_1.clear();
		stdms_2.clear();

		output << "\n\tElementos aleatórios:" << std::endl;

		insertRandomData(i, dams_1);
		insertRandomData(i, dams_2);
		insertRandomData(i, rbtms_1);
		insertRandomData(i, rbtms_2);
		insertRandomData(i, stdms_1);
		insertRandomData(i, stdms_2);

		benchmarkSetOperations(UNION, dams_1, dams_2,
			rbtms_1, rbtms_2, stdms_1, stdms_2, output);

		benchmarkSetOperations(INTERSECTION, dams_1, dams_2,
			rbtms_1, rbtms_2, stdms_1, stdms_2, output);

		benchmarkSetOperations(DIFF, dams_1, dams_2,
			rbtms_1, rbtms_2, stdms_1, stdms_2, output);

		dams_1.reset();
		dams_2.reset();
		rbtms_1.clear();
		rbtms_2.clear();
		stdms_1.clear();
		stdms_2.clear();
	}

#ifdef WRITE_TO_FILE
	output.close();
#endif
}