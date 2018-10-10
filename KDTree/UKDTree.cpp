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

#include <cstdlib>
#include <iostream>


using namespace std;


#define DIMENSION 3


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
		    "|           Umbalanced K-D Tree Visualization            |\n"
		    "|                                                        |\n"
		    "|                                                        |\n"
		    "| Enter an option:                                       |\n"
		    "|                                                        |\n"
		    "| 1 - Insert " << DIMENSION << "-dimensional point          "
		    "               |\n"
		    "| 2 - Remove point                                       |\n"
		    "| 3 - Check if point is in tree                          |\n"
		    "| 4 - Find minimum of a dimension                        |\n"
		    "| 5 - Clear tree                                         |\n"
		    "| 6 - Quit                                               |\n"
		    "|                                                        |\n"
		    "*--------------------------------------------------------*\n";
}

int input() {
	int n;
	bool valid_input = false;
	string input;

	while (!valid_input) {
		cin >> input;

		try {
			n = stoi(input);
			valid_input = true;
		}
		catch (...) {
			cout << "You must enter an integer." << endl;
		}
	}

	return n;
}

void input(int& dim) {
	bool valid_input = false;
	string input;

	while (!valid_input) {
		cin >> input;

		try {
			dim = stoi(input);

			if (dim < 0 || dim >= DIMENSION)
				throw 0;

			valid_input = true;
		}
		catch (...) {
			cout << "You must enter an integer between 0 and "
				<< DIMENSION - 1 << "." << endl;
		}
	}
}

void input(int arr[]) {
	int n;
	bool valid_input;
	string input;

	for (int i = 0; i < DIMENSION; i++) {
		valid_input = false;

		while (!valid_input) {
			cin >> input;

			try {
				n = stoi(input);
				valid_input = true;
			}
			catch (...) {
				cout << "You must enter an integer." << endl;
			}
		}

		arr[i] = n;
	}
}

int main() {
	ios_base::sync_with_stdio(false);

	int menu_option, aux_i_1, aux_i_2;
	int aux_point[DIMENSION];
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
				<< " integer(s) representing a point's coordinates:\n";
			
			input(aux_point);
			tree.insert(aux_point);

			clear();
			printHeader();
			tree.printTree();

			break;

		case 2:/*
			cout << "Enter a number to remove from the tree: ";
			aux_i_1 = input();
			aux_b = tree.remove(aux_i_1);

			if (aux_b) {
				clear();
				printHeader();
				tree.printTree();

				cout << "Item " << aux_i_1
					 << " removed successfully.\nEnter an option:\n";
			}
			else
				cout << "The tree does not contain " << aux_i_1 << ".\n"
					 << "Enter an option:\n";
*/
			break;

		case 3:
			cout << "Enter " << DIMENSION
				<< " integer(s) representing a point's coordinates:\n";
			
			input(aux_point);

			if (tree.contains(aux_point))
				cout << "\nThe tree contains the point (" << aux_point[0];
			else
				cout << "\nThe tree does not contain the point (" << aux_point[0];

			for (int i = 1; i < DIMENSION; i++)
				cout << ", " << aux_point[i];

			cout << ")\nPress enter to continue..." << endl;
			getchar();

			clear();
			printHeader();
			tree.printTree();

			break;

		case 4:
			cout << "Which dimension (0..." << DIMENSION - 1 << ")?:\n";

			input(aux_i_1);

			if (tree.findMinimum(aux_i_1, aux_i_2))
				cout << "\nThe minimum at " << aux_i_1
					<< "-th dimension is " << aux_i_2;
			else
				cout << "The tree is empty";

			cout << "\nPress enter to continue..." << endl;
			getchar();

			clear();
			printHeader();
			tree.printTree();	

			break;

		case 5:
			tree.clear();

			clear();
			printHeader();
			tree.printTree();

			break;
		}
	}
	while (menu_option != 6);
}