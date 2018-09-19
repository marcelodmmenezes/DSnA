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

int main() {
	std::ios_base::sync_with_stdio(false);

	int menu_option;
	string input;
	UBST<int> tree;
	
	do {
		clear();

		cout << "*--------------------------------------------------------*\n"
			    "|                                                        |\n"
			    "|       Umbalanced Binary Search Tree Visualization      |\n"
			    "|                                                        |\n"
			    "|                                                        |\n"
			    "| Enter a number:                                        |\n"
			    "|                                                        |\n"
			    "| 1 - Insert item (integer)                              |\n"
			    "| 2 - Remove item                                        |\n"
			    "| 3 - Get highest item                                   |\n"
			    "| 4 - Get number of itens                                |\n"
			    "| 5 - Get tree height                                    |\n"
			    "| 6 - Get number of leaves                               |\n"
			    "| 7 - Get number of inner nodes                          |\n"
			    "| 8 - Clear tree                                         |\n"
			    "| 9 - Quit                                               |\n"
			    "|                                                        |\n"
			    "*--------------------------------------------------------*\n";

		tree.printTree();

		bool valid_input = false;

		while (!valid_input) {
			getline(cin, input);

			try {
				menu_option = stoi(input);

				if (menu_option < 1 || menu_option > 9)
					throw 0;

				valid_input = true;
			}
			catch (...) {
				cout << "Enter a number between 1 and 9 to select"
						"the corresponding option." << endl;
			}
		}

		switch (menu_option) {

		}
	}
	while (menu_option != 9);

}