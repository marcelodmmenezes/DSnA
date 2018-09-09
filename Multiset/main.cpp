#include "rbtmultiset.hpp"
#include <chrono>
#include <iostream>
#include <random>
#include <set>


#define NUMBER_OF_ELEMENTS 10000000


void insertSequentialData(RBTMultiset<int>& ms) {
	for (int i = 0; i < NUMBER_OF_ELEMENTS / 2; i++)
		ms.insert(i);

	for (int i = 0; i < NUMBER_OF_ELEMENTS / 2; i++)
		ms.insert(i);
}

void insertSequentialData(std::multiset<int>& ms) {
	for (int i = 0; i < NUMBER_OF_ELEMENTS / 2; i++)
		ms.insert(i);

	for (int i = 0; i < NUMBER_OF_ELEMENTS / 2; i++)
		ms.insert(i);
}

void removeSequentialData(RBTMultiset<int>& ms) {
	for (int i = 1; i < NUMBER_OF_ELEMENTS / 2; i++)
		ms.remove(i);

	for (int i = 1; i < NUMBER_OF_ELEMENTS / 2; i++)
		ms.remove(i);
}

void removeSequentialData(std::multiset<int>& ms) {
	for (int i = 0; i < NUMBER_OF_ELEMENTS / 2; i++)
		ms.erase(i);

	for (int i = 0; i < NUMBER_OF_ELEMENTS / 2; i++)
		ms.erase(i);
}

int main(int argc, char* argv[]) {
	std::ios::sync_with_stdio(false);

	RBTMultiset<int> rbtmsi;

	std::multiset<int> stdmsi;

	auto clock = std::chrono::high_resolution_clock::now();

	insertSequentialData(rbtmsi);

	std::cout << "rbtmsi insertSequentialData: " <<
		(std::chrono::high_resolution_clock::now() - clock).count()
		<< std::endl;

	clock = std::chrono::high_resolution_clock::now();

	insertSequentialData(stdmsi);

	std::cout << "stdmsi insertSequentialData: " <<
		(std::chrono::high_resolution_clock::now() - clock).count()
		<< std::endl;

	clock = std::chrono::high_resolution_clock::now();

	removeSequentialData(rbtmsi);

	std::cout << "rbtmsi removeSequentialData: " <<
		(std::chrono::high_resolution_clock::now() - clock).count()
		<< std::endl;

	clock = std::chrono::high_resolution_clock::now();

	removeSequentialData(stdmsi);

	std::cout << "stdmsi removeSequentialData: " <<
		(std::chrono::high_resolution_clock::now() - clock).count()
		<< std::endl;

/*
	int n;
	char c;

	while (std::cin >> c >> n) {
		if (c == 'i')
			rbtmsi.insert(n);
		else if (c == 'd')
			rbtmsi.remove(n);
		else if (c == 'q')
			break;
		else
			rbtmsi.clear();

		rbtmsi.print();
		std::cout << std::endl;
	}*/

}