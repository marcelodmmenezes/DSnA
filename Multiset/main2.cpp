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

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <set>


using namespace std;


int main() {
	srand(time(nullptr));
	std::ios_base::sync_with_stdio(false);

	int n;
	DAMultiset<int> da1, da2;
	RBTMultiset<int> ms1, ms2;

	while (cin >> n, n != 0)
		ms1.insert(n), da1.insert(n);

	while (cin >> n, n != 0)
		ms2.insert(n), da2.insert(n);

	cout << "\nDA:\n" << endl;
	
	da1.printElements();
	cout << endl;
	da2.printElements();
	cout << endl << endl;

	cout << "Union:" << endl;
	
	da1._union(da2).printElements();
	cout << endl;
	da2._union(da1).printElements();
	cout << endl;

	cout << "Intersection:" << endl;
	
	da1._intersection(da2).printElements();
	cout << endl;
	da2._intersection(da1).printElements();
	cout << endl;

	cout << "Difference:" << endl;
	
	da1._difference(da2).printElements();
	cout << endl;
	da2._difference(da1).printElements();
	cout << endl << endl;

	cout << "\nRBT:\n" << endl;
	
	ms1.printElements();
	cout << endl;
	ms2.printElements();
	cout << endl;

	cout << "Union:" << endl;
	
	ms1._union(ms2).printElements();
	cout << endl;
	ms2._union(ms1).printElements();
	cout << endl;

	cout << "Intersection:" << endl;
	
	ms1._intersection(ms2).printElements();
	cout << endl;
	ms2._intersection(ms1).printElements();
	cout << endl;

	cout << "Difference:" << endl;
	
	ms1._difference(ms2).printElements();
	cout << endl;
	ms2._difference(ms1).printElements();
	cout << endl;
}