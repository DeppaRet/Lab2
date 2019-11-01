#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include "Work_with_array.h"
#include "interface.h"
using namespace std;

enum user_choice { About = 1, Random, File, Keyboard, Exit, Yes = 1, No, Work = 0, Die = 6 };


int work_with_menu() {
	int cols, rows, menu, restriction = 1;
	int **arr = nullptr;
	int user_choice;
	string file_path;
	interface_of_programm();
	for (user_choice = Work; user_choice < Die; user_choice++) {
		cin >> user_choice;
		menu = check(user_choice);

		switch (menu) {
		case About: { // ABOUT
			about();
			if (what_s_next() == 0)
				return(0);
		}

		case Random: { // RANDOM
			cout << "Input number of rows and cols:";
			cin >> rows >> cols;
			rows = check(rows);
			cols = check(cols);
			if ((rows < restriction) || (cols < restriction)) {
				cout << "Matrix is too small" << endl;
				if (what_s_next() == 0)
					return(0);
			}
			else {
				arr = new int *[rows];
				for (int i = 0; i < rows; i++) {
					arr[i] = new int[cols];
				}
				randomize(arr, rows, cols);
				cout << endl << "Array on start:" << endl;
				output(arr, rows, cols);
				cout << "Press '1' if you want to save array on start or any key to continue:" << endl;
				cin >> user_choice;
				if (user_choice == Yes) {
					save(arr, rows, cols);
					cout << "File created succesfully" << endl;
				}
				break;
			}
		}

		case File: {
			string file_name;
			cout << "Input name of file (.txt): " << endl;
			cin >> file_name;
			check_file_name(file_name, No);
			ifstream in(file_name);
			if (in.is_open()) {       
				cout << "Input number of rows and cols:";
				
				in >> rows;
				in >> cols;

				if ((rows >= restriction + 1) || (cols >= restriction)) {
					arr = new int *[rows];
					for (int i = 0; i < rows; i++)
						arr[i] = new int[cols];
					for (int i = 0; i < rows; i++)
						for (int j = 0; j < cols; j++)
							in >> arr[i][j];
					cout << endl << "Array on start:" << endl;
					output(arr, rows, cols);
					break;
				}
				else {
					cout << "Matrix is too small" << endl;
					what_s_next();
				}
				in.close();
			}
			else {
				cout << "Can't open this file" << endl;
				user_choice = 0;
				if (what_s_next() == 0)
					return(0);
			}
		}

		case Keyboard: { //FROM KEYBOARD
			cout << "Input number of rows and cols:";
			cin >> rows >> cols;
			rows = check(rows);
			cols = check(cols);
			if ((rows < restriction) || (cols < restriction)) {
				cout << "Matrix is too small" << endl;
				if (what_s_next() == 0)
					return(0);
			}
			else {
				arr = new int *[rows];
				for (int i = 0; i < rows; i++) {
					arr[i] = new int[cols];
				}
				cout << "Input matrix elements:" << endl;
				for (int i = 0; i < rows; i++) {
					for (int j = 0; j < cols; j++) {
						cin >> arr[i][j];
						arr[i][j] = check(arr[i][j]);
					}
				}
				cout << endl << "Array on start:" << endl;
				output(arr, rows, cols);
				cout << "Press '1' if you want to save array on start or any key to continue:" << endl;
				cin >> user_choice;
				if (user_choice == Yes) {
					save(arr, rows, cols);
					cout << "File created succesfully" << endl;
				}
				break;
			}
		}
		case Exit: {	// EXIT
			return (0);
		}
		default: {
			cout << "Not a valid chooice. Please choose again" << endl;
			user_choice = 0;
			continue;
		}
	}
	analyze(arr, rows, cols);
	for (int i = 0; i < rows; i++) {
		delete[] arr[i];
		arr[i] = nullptr;
	} // Освобождение памяти
	delete[] arr;
	if (what_s_next() == 0)
		return 0;
	work_with_menu();
	}
	return 0;
}
