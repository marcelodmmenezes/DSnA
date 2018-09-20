/******************************************************************************
 * INF 610 - Estruturas de Dados e Algoritmos - 2018/2                        *
 *                                                                            *
 * Lista de exercícios 6                                                      *
 *                                                                            *
 * Marcelo de Matos Menezes - 75254                                           *
 *                                                                            *
 * Just a simple program to test UBTS implementation.                         *
 *                                                                            *
 *****************************************************************************/


#include "ubst.hpp"

#include <cstdlib>
#include <iostream>


using namespace std;


void clear() {
#ifdef __unix__
	system("reset");
#elif defined _WIN32
	system("cls");
#endif
}

void printHeader() {
	cout << "*--------------------------------------------------------*\n"
		    "|                                                        |\n"
		    "|       Umbalanced Binary Search Tree Visualization      |\n"
		    "|                                                        |\n"
		    "|                                                        |\n"
		    "| Enter an option:                                       |\n"
		    "|                                                        |\n"
		    "| 1 - Insert item (integer)                              |\n"
		    "| 2 - Remove item                                        |\n"
		    "| 3 - Get highest item                                   |\n"
		    "| 4 - Get number of itens                                |\n"
		    "| 5 - Get tree height                                    |\n"
		    "| 6 - Count leaves                                       |\n"
		    "| 7 - Count inner nodes                                  |\n"
		    "| 8 - Clear tree                                         |\n"
		    "| 9 - Quit                                               |\n"
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

int main() {
	std::ios_base::sync_with_stdio(false);

	int menu_option, aux_i;
	bool aux_b;
	UBST<int> tree;
	
	clear();
	printHeader();
	tree.printTree();

	do {
		menu_option = input();

		clear();
		printHeader();
		tree.printTree();

		while (menu_option < 1 || menu_option > 9) {
			cout << "\nYou must enter an integer between 1 and 9,"
					" corresponding to one of the options above." << endl;
			menu_option = input();
		}

		switch (menu_option) {
		case 1:
			cout << "Enter a number to insert in the tree: ";
			tree.insert(input());

			clear();
			printHeader();
			tree.printTree();

			break;

		case 2:
			cout << "Enter a number to remove from the tree: ";
			aux_i = input();
			aux_b = tree.remove(aux_i);

			if (aux_b) {
				cout << "Item " << aux_i << " removed successfully.";
				clear();
				printHeader();
				tree.printTree();
			}
			else
				cout << "The tree does not contain " << aux_i << ".\n"
					 << "Enter an option:\n";

			break;

		case 3:
			aux_b = tree.getHighest(aux_i);

			if (aux_b)
				cout << "The highest item in the tree is " << aux_i << ".\n";
			else
				cout << "The tree is empty.\n";

			break;
		
		case 4:
			cout << "The number of items in the tree is "
				 << tree.size() << "\n";
			break;

		case 5:
			cout << "The height of the tree is " << tree.height() << "\n";
			break;

		case 6:
			cout << "The tree contains " << tree.countLeaves() << " leaves.\n";
			break;

		case 7:
			cout << "The tree contains " << tree.countInnerNodes()
				 << " inner nodes.\n";
			break;

		case 8:
			tree.clear();

			clear();
			printHeader();
			tree.printTree();

			break;
		}
	}
	while (menu_option != 9);

}