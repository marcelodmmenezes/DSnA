#include "rbtmultiset.hpp"
#include <iostream>

int main() {
	int n;
	RBTMultiset<int> ms;

	while (std::cin >> n) {
		ms.insert(n);
		ms.print();
		std::cout << std::endl;
	}
}