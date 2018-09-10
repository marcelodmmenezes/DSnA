/******************************************************************************
 * INF 610 - Estruturas de Dados e Algoritmos - 2018/2                        *
 *                                                                            *
 * Lista de exercícios 3                                                      *
 *                                                                            *
 * Marcelo de Matos Menezes - 75254                                           *
 *                                                                            *
 *****************************************************************************/


#include "damultiset.hpp"
#include "rbtmultiset.hpp"

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <set>


enum BenchmarkType {
	INSERT_CRESCENT_DATA,
	INSERT_DECRESCENT_DATA,
	INSERT_RANDOM_DATA,
	RANDOM_QUERIES
};


template <typename T>
void insertCrescentData(int n, T& ms);

template <typename T>
void insertDecrescentData(int n, T& ms);

template <typename T>
void insertRandomData(int n, T& ms);

template <typename T>
void randomQueries(int n, T& ms);

void benchmark(int n, BenchmarkType type,
	DAMultiset<int>& dams, RBTMultiset<int>& rbtms, std::multiset<int>& stdms, 
	std::ostream& output = std::cout);


int main() {
	srand(time(nullptr));
	std::ios_base::sync_with_stdio(false);

	DAMultiset<int> dams;
	RBTMultiset<int> rbtms;
	std::multiset<int> stdms;

	std::ostream& output = std::cout;

	for (int i = 1000; i <= 100000; i *= 10) {
		output << i << ":" << std::endl;

		benchmark(i, INSERT_CRESCENT_DATA, dams, rbtms, stdms);

		dams.reset();
		rbtms.clear();
		stdms.clear();

		benchmark(i, INSERT_DECRESCENT_DATA, dams, rbtms, stdms);

		dams.reset();
		rbtms.clear();
		stdms.clear();

		benchmark(i, INSERT_RANDOM_DATA, dams, rbtms, stdms);
		benchmark(i, RANDOM_QUERIES, dams, rbtms, stdms);
	}
}


template <typename T>
void insertCrescentData(int n, T& ms) {
	for (int i = 0; i < n; i++)
		ms.insert(i);
}

template <typename T>
void insertDecrescentData(int n, T& ms) {
	for (int i = n - 1; i >= 0; i--)
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

void benchmark(int n, BenchmarkType type,
	DAMultiset<int>& dams, RBTMultiset<int>& rbtms, std::multiset<int>& stdms, 
	std::ostream& output) {
	auto clock = std::chrono::high_resolution_clock::now();

	switch (type) {
		case INSERT_CRESCENT_DATA:
			insertCrescentData(n, dams);
			break;
		case INSERT_DECRESCENT_DATA:
			insertDecrescentData(n, dams);
			break;
		case INSERT_RANDOM_DATA:
			insertRandomData(n, dams);
			break;
		case RANDOM_QUERIES:
			randomQueries(n, dams);
			break;
	}

	output << "\tda  : " <<
		(std::chrono::high_resolution_clock::now() - clock).count()
		<< std::endl;

	clock = std::chrono::high_resolution_clock::now();


	switch (type) {
		case INSERT_CRESCENT_DATA:
			insertCrescentData(n, rbtms);
			break;
		case INSERT_DECRESCENT_DATA:
			insertDecrescentData(n, rbtms);
			break;
		case INSERT_RANDOM_DATA:
			insertRandomData(n, rbtms);
			break;
		case RANDOM_QUERIES:
			randomQueries(n, rbtms);
			break;
	}

	output << "\trbt : " <<
		(std::chrono::high_resolution_clock::now() - clock).count()
		<< std::endl;

	clock = std::chrono::high_resolution_clock::now();


	switch (type) {
		case INSERT_CRESCENT_DATA:
			insertCrescentData(n, stdms);
			break;
		case INSERT_DECRESCENT_DATA:
			insertDecrescentData(n, stdms);
			break;
		case INSERT_RANDOM_DATA:
			insertRandomData(n, stdms);
			break;
		case RANDOM_QUERIES:
			randomQueries(n, stdms);
			break;
	}

	output << "\tstd : " <<
		(std::chrono::high_resolution_clock::now() - clock).count()
		<< std::endl << std::endl;
}