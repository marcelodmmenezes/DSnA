#include "damultiset.hpp"
#include "rbtmultiset.hpp"

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <set>


#define NUMBER_OF_ELEMENTS 100000


int main(int argc, char* argv[]) {
	std::ios::sync_with_stdio(false);
	srand(time(nullptr));

	int n;
	char c;
	DAMultiset<int> ms1, ms2;

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
	std::cout << std::endl << std::endl;

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