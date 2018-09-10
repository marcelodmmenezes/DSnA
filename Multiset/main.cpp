#include "rbtmultiset.hpp"

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
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
	for (int i = 0; i < NUMBER_OF_ELEMENTS / 2; i++)
		ms.remove(i);

	for (int i = 0; i < NUMBER_OF_ELEMENTS / 2; i++)
		ms.remove(i);
}

void removeSequentialData(std::multiset<int>& ms) {
	for (int i = 0; i < NUMBER_OF_ELEMENTS / 2; i++)
		ms.erase(i);

	for (int i = 0; i < NUMBER_OF_ELEMENTS / 2; i++)
		ms.erase(i);
}

void insertRandomData(RBTMultiset<int>& ms) {
	for (int i = 0; i < NUMBER_OF_ELEMENTS; i++)
		ms.insert(rand());
}

void insertRandomData(std::multiset<int>& ms) {
	for (int i = 0; i < NUMBER_OF_ELEMENTS; i++)
		ms.insert(rand());
}

int main(int argc, char* argv[]) {
	std::ios::sync_with_stdio(false);
	srand(time(nullptr));
/*
	RBTMultiset<int> rbtmsi;

	std::multiset<int> stdmsi;

	//-------------------------------------------------- Insert sequential data
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

	std::cout << std::endl;
	//-------------------------------------------------------------------------

	//-------------------------------------------------- Remove sequential data
	std::cout << rbtmsi.size() << " " << stdmsi.size() << std::endl;

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

	std::cout << rbtmsi.size() << " " << stdmsi.size() << std::endl;

	std::cout << std::endl;
	//-------------------------------------------------------------------------
rbtmsi.print();
	//------------------------------------------------------ Insert random data
	clock = std::chrono::high_resolution_clock::now();

	insertRandomData(rbtmsi);

	std::cout << "rbtmsi insertRandomData: " <<
		(std::chrono::high_resolution_clock::now() - clock).count()
		<< std::endl;

	clock = std::chrono::high_resolution_clock::now();

	insertRandomData(stdmsi);

	std::cout << "stdmsi insertRandomData: " <<
		(std::chrono::high_resolution_clock::now() - clock).count()
		<< std::endl;

	std::cout << rbtmsi.size() << " " << stdmsi.size() << std::endl;

	std::cout << std::endl;
	//-------------------------------------------------------------------------
*/

	int n;
	char c;
	RBTMultiset<int> ms1, ms2;

	while (std::cin >> c >> n) {
		if (c == 'i')
			ms1.insert(n);
		else if (c == 'd')
			ms1.remove(n);
		else if (c == 'q')
			break;
	}

	while (std::cin >> c >> n) {
		if (c == 'i')
			ms2.insert(n);
		else if (c == 'd')
			ms2.remove(n);
		else if (c == 'q')
			break;
	}

	std::cout << std::endl;
	ms1.printElements();
	std::cout << std::endl;
	ms2.printElements();
	std::cout << std::endl;

	std::cout << "Union: ";
	ms1._union(ms2).printElements();
	std::cout << std::endl;
	std::cout << "Intersection: ";
	ms1._intersection(ms2).printElements();
	std::cout << std::endl;
	std::cout << "Difference: ";
	ms1._difference(ms2).printElements();
	std::cout << std::endl;
}