/******************************************************************************
 * INF 610 - Estruturas de Dados e Algoritmos - 2018/2                        *
 *                                                                            *
 * Trabalho prático 2                                                         *
 *                                                                            *
 * Marcelo de Matos Menezes - 75254                                           *
 *                                                                            *
 * Just a simple program to test UKDTree implementation.                       *
 *                                                                            *
 *****************************************************************************/


#include "UKDTree.hpp"

#include <array>
#include <cstdlib>
#include <iostream>


using namespace std;


#define DIMENSION 2


void clear() {
#ifdef __unix__
	system("clear");
#elif defined _WIN32
	system("cls");
#endif
}

void printHeader() {
	cout << "*--------------------------------------------------------*\n"
		    "|                                                        |\n"
		    "|       Umbalanced K-D Tree Visualization                |\n"
		    "|                                                        |\n"
		    "|                                                        |\n"
		    "| Enter an option:                                       |\n"
		    "|                                                        |\n"
		    "| 1 - Insert " << DIMENSION << "-dimensional point          "
		    "               |\n"
		    "| 2 - Remove item                                        |\n"
		    "| 3 - Clear tree                                         |\n"
		    "| 4 - Quit                                               |\n"
		    "|                                                        |\n"
		    "*--------------------------------------------------------*\n";
}

int input() {
	int n;
	bool valid_input = false;
	string input;

	while (!valid_input) {
		getline(cin, input);

		try {
			n = stoi(input);
			valid_input = true;
		}
		catch (...) {
			cout << "\nYou must enter an integer." << endl;
		}
	}

	return n;
}

void input(int arr[]) {
	int n;
	bool valid_input = false;
	string input;

	for (int i = 0; i < DIMENSION; i++) {
		while (!valid_input) {
			getline(cin, input);

			try {
				n = stoi(input);
				valid_input = true;
			}
			catch (...) {
				cout << "\nYou must enter an integer." << endl;
			}
		}

		arr[i] = n;
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int menu_option, aux_i;
	bool aux_b;
	UKDTree<int, DIMENSION> tree;
	
	clear();
	printHeader();
	tree.printTree();

	do {
		menu_option = input();

		clear();
		printHeader();
		tree.printTree();

		while (menu_option < 1 || menu_option > 10) {
			cout << "\nYou must enter an integer between 1 and 10,"
					" corresponding to one of the options above." << endl;
			menu_option = input();
		}

		switch (menu_option) {
		case 1:
			cout << "Enter " << DIMENSION
				<< " integer(s) representing a point's coordinates\n";
			
			int aux[DIMENSION];
			input(aux);

			tree.insert(aux);

			clear();
			printHeader();
			tree.printTree();

			break;

		case 2:/*
			cout << "Enter a number to remove from the tree: ";
			aux_i = input();
			aux_b = tree.remove(aux_i);

			if (aux_b) {
				clear();
				printHeader();
				tree.printTree();

				cout << "Item " << aux_i
					 << " removed successfully.\nEnter an option:\n";
			}
			else
				cout << "The tree does not contain " << aux_i << ".\n"
					 << "Enter an option:\n";
*/
			break;

		case 3:
			tree.clear();

			clear();
			printHeader();
			tree.printTree();

			break;
		}
	}
	while (menu_option != 4);
}