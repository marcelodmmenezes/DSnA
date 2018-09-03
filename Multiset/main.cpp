#include "rbtmultiset.hpp"

int main() {
	RBTMultiset<int> ms;
	ms.insert(1);
	ms.insert(2);
	ms.insert(3);
	ms.insert(4);
	ms.insert(5);
	ms.insert(6);
	ms.insert(7);
	ms.insert(8);
	ms.insert(9);
	ms.insert(10);
	ms.print();
}