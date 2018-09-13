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

#include <cstdlib>
#include <iostream>


using namespace std;


void getData(int ms, ODAMultiset<int>& oda, RBTMultiset<int>& rbt) {
	long long n;
	string input;

#ifdef __unix__
		system("reset");
#elif defined _WIN32
		system("cls");
#endif

	cout << "Insert multiset" << (ms == 1 ? " A " : " B ")
		<< "elements (integers (0 to finish)):\n" << endl;

	rbt.printTree();

	while (getline(cin, input)) {
		try {
			n = stoi(input);
			
			if (!n)
				break;
		}
		catch (...) {
			cout << "Only integer input accepted. Please enter an integer.\n";
			continue;
		}

		oda.insert(n);
		rbt.insert(n);

#ifdef __unix__
		system("reset");
#elif defined _WIN32
		system("cls");
#endif

		cout << "Insert multiset" << (ms == 1 ? " A " : " B ")
			<< "elements (integers (0 to finish)):\n" << endl;

		rbt.printTree();
	}

#ifdef __unix__
		system("reset");
#elif defined _WIN32
		system("cls");
#endif
}


int main() {
	std::ios_base::sync_with_stdio(false);

	ODAMultiset<int> oda1, oda2;
	RBTMultiset<int> rbt1, rbt2;

	getData(1, oda1, rbt1);
	getData(2, oda2, rbt2);

	cout << "----------------------------- Ordered Dynamic Array:\n" << endl;
	
	cout << "Multiset A:         ";
	oda1.printElements();
	cout << endl;
	cout << "Multiset B:         ";
	oda2.printElements();
	cout << endl;
	
	cout << "\nA union B:          ";
	oda1._union(oda2).printElements();
	cout << "\nB union A:          ";
	oda2._union(oda1).printElements();
	cout << endl;
	
	cout << "\nA intersection B:   ";
	oda1._intersection(oda2).printElements();
	cout << "\nB intersection A:   ";
	oda2._intersection(oda1).printElements();
	cout << endl;
	
	cout << "\nA difference B:     ";
	oda1._difference(oda2).printElements();
	cout << "\nB difference A:     ";
	oda2._difference(oda1).printElements();
	cout << endl;

	cout << "\n------------------------------------ Red-Black Tree:\n" << endl;
	
	cout << "Multiset A:         ";
	rbt1.printElements();
	cout << endl;
	cout << "Multiset B:         ";
	rbt2.printElements();
	cout << endl;
	
	cout << "\nA union B:          ";
	rbt1._union(rbt2).printElements();
	cout << "\nB union A:          ";
	rbt2._union(rbt1).printElements();
	cout << endl;
	
	cout << "\nA intersection B:   ";
	rbt1._intersection(rbt2).printElements();
	cout << "\nB intersection A:   ";
	rbt2._intersection(rbt1).printElements();
	cout << endl;
	
	cout << "\nA difference B:     ";
	rbt1._difference(rbt2).printElements();
	cout << "\nB difference A:     ";
	rbt2._difference(rbt1).printElements();
	cout << endl;
}