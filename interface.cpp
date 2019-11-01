#include <iostream>
#include "work_with_menu.h"
#include "interface.h"
using namespace std;

void about() {
	cout << "Task: Sort cols of matrix from max to min. \nMade by a 1st year student of gr 484: Leviskiy Ilya";
	cout << endl;
}


void interface_of_programm() {
	cout << "___________________________________________\n";
	cout << "********|-----------MENU----------|********\n";
	cout << "*******************************************\n";
	cout << "*******|     What's your choice    |*******";
	cout << "\n*******************************************\n";
	cout << "* 1. About                                *\n";
	cout << "* 2. Random matrix                        *\n";
	cout << "* 3. Matrix from file                     *\n";
	cout << "* 4. Input matrix                         *\n";
	cout << "* 5. Exit                                 *\n"; 
	cout << "*******************************************\n";
}

int check(int user_choice) {
	while (cin.fail()) {
		if (user_choice <= 0) {
			cout << "Enter only a valid choose please. Try again." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			user_choice = 0;
			cin >> user_choice;
		}
	}
	return (user_choice);
}

int what_s_next() {
	int user_choice;
	cout << endl << "What's next?" << endl;
	cout << "1. Menu" << endl;
	cout << "2. Exit" << endl;
	cin >> user_choice;
	user_choice = check(user_choice);
	if (user_choice == 1)
		work_with_menu();
	else if (user_choice == 2)
		return (0);
	else {
		cout << "Wrong choice. Enter only a valid choose" << endl;
		what_s_next();
	}
	return (0);
}