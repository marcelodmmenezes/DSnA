#include "rbtmultiset.hpp"
#include <iostream>

int main() {
	int n;
	char c;
	RBTMultiset<int> ms;

	while (std::cin >> c >> n) {
		if (c == 'i')
			ms.insert(n);
		else if (c == 'd')
			ms.remove(n);
		else if (c == 'q')
			break;
		else
			ms.clear();

		ms.print();
		std::cout << std::endl;
	}
}