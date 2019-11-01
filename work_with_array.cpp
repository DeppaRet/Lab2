#include <iostream>
#include <ctime>
#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>
#include <cstdlib>
#include "work_with_menu.h"
#include "sort.h"
using namespace std;

enum { Yes = 1, No, Shell = 0, Bubble, Selection, Insert, Fast};

string check_file_name(string &file_path, int way) {
	int recreate;
	while (validate(file_path) == false) {
		cout << "Invalid file name. Input new name: ";
		cin >> file_path;
	}
	if (way == No) {
		return (file_path);
	}
	else if (ofstream(file_path, ios::out | ios::_Nocreate)) {
		cout << "File with this name is already created.\nDo you want to rewrite it? \n1 - yes, 2 - no" << endl;
		cin >> recreate;
		check(recreate);
		if (recreate == No) {
			cout << "Input new name for file:" << endl;
			cin >> file_path;
			check_file_name(file_path, Yes);
		}
		else if (recreate == Yes)
			return(file_path);
	}
	return (file_path);
}

bool validate(string file_path) {
	string not_allowed[] = { "<", ">", "/", "|", "?", "*", };
	string not_allowed_names[] = { "con", "prn", "aux", "nul", "com1", "com2", "com3", "com4", "com5", "com6", "com7",
										"com8", "com9", "lpt1", "lpt2", "lpt3", "lpt4", "lpt5", "lpt6", "lpt7", "lpt8", "lpt9" };
	string tmp_file_path = file_path;
	for (int i = 0; i != file_path.length(); i++) {
		tmp_file_path[i] = tolower(file_path[i]);
	}

	int size_not_allowed = sizeof(not_allowed) / sizeof(not_allowed[0]);
	int size_not_allowed_names = sizeof(not_allowed_names) / sizeof(not_allowed_names[0]);
	for (int i = 0; i != size_not_allowed; ++i) {
		if (string::npos != tmp_file_path.find(not_allowed[i]))
			return false;
	}
	for (int i = 0; i != size_not_allowed_names; ++i) {
		if (tmp_file_path == not_allowed_names[i])
			return false;
	}
	return true;
}

int save(int **arr, int rows, int cols) {
	int count = 0, size;
	ofstream out;
	string file_path;
	cout << "Input name of the file: " << endl;
	cin >> file_path;
	check_file_name(file_path, Yes);
	out.open(file_path);
	out << rows << endl;
	out << cols << endl;
	while (true) {
		if (out) {
			size = rows * cols;
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					if (count < size) {
						out << arr[i][j] << " ";
						count += 1;
					}
					else {
						out.close();
						return(0);
					}
				}
				out << endl;
			}
		}
	}
}

int table(int **arr, int rows, int cols, int *count) {
	string file_path;
	cout << "Input name of the file: " << endl;
	cin >> file_path;
	check_file_name(file_path, Yes);
	ofstream out;
	out.open(file_path);
	if (out) {
		out << "Table of comparisons" << endl;
		out << "Sort | Comparisons | Permutations" << endl;
		out << "---------------------------------------------------" << endl;
		out << "Shell               " << count[0] << "                  " << count[1] << endl;
		out << "Bubble              " << count[2] << "                  " << count[3] << endl;
		out << "Selection           " << count[4] << "                  " << count[5] << endl;
		out << "Insert              " << count[6] << "                  " << count[7] << endl;
		out << "Quick               " << count[8] << "                  " << count[9] << endl;
		out << endl;
		out << "Resulted array:" << endl;
		int size = rows * cols;
		int number = 0;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (number < size) {
					out << arr[i][j] << " ";
					number += 1;
				}
			}
			out << endl;
		}
		out.close();
	}
	else {
		out.close();
	}
cout << "File created succesfully" << endl;
return 0;
}

int randomize(int **arr, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			arr[i][j] = rand() % 1000;
		}
	}
	return (0);
}

void console_table(int *count) {
	cout << "Table of comparisons" << endl;
	cout << "Sort     |     Comparisons   |  Permutations" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "Shell               " << count[0] << "              " << count[1] << endl;
	cout << "Bubble              " << count[2] << "              " << count[3] << endl;
	cout << "Selection           " << count[4] << "              " << count[5] << endl;
	cout << "Insert              " << count[6] << "              " << count[7] << endl;
	cout << "Quick               " << count[8] << "              " << count[9] << endl;
	cout << endl;
}

int analyze(int **arr, int rows, int cols) {
	int comparisons = 0, permutations = 0, k = 0, user_choice;
	int **old_array, count[10];
	old_array = new int *[rows];
	for (int i = 0; i < rows; i++)
		old_array[i] = new int[cols];
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++) {
			old_array[i][j] = arr[i][j];
		}
	
	for (int i = Shell; i <= Fast; i++) {
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++) {
				arr[i][j] = old_array[i][j];
			}
		comparisons = 0;
		permutations = 0;
		if (i == Shell) {
			shell_sort(arr, rows, cols, comparisons, permutations);
			cout << "Shell's method:" << endl;
			cout << "Comparisons: " << comparisons << endl;
			cout << "Permutations: " << permutations << endl;
			output(arr, rows, cols);
		}
		else if (i == Bubble) {
			bubble_sort(arr, rows, cols, comparisons, permutations);
			cout << "Bubble sort:" << endl;
			cout << "Comparisons: " << comparisons << endl;
			cout << "Permutations: " << permutations << endl;
			output(arr, rows, cols);
		}
		else if (i == Selection) {
			selection_sort(arr, rows, cols, comparisons, permutations);
			cout << "Selection method:" << endl;
			cout << "Comparisons: " << comparisons << endl;
			cout << "Permutations: " << permutations << endl;
			output(arr, rows, cols);
		}
		else if (i == Insert) {
			insert_sort(arr, cols, rows, comparisons, permutations);
			cout << "Selection method:" << endl;
			cout << "Comparisons: " << comparisons << endl;
			cout << "Permutations: " << permutations << endl;
			output(arr, rows, cols);
		}
		else if (i == Fast) {
			int tmp = rows;
			fast_sort(arr, 0, true, rows - 1, cols, 0, comparisons, permutations);
			cout << "Fast method:" << endl;
			cout << "Comparisons: " << comparisons << endl;
			cout << "Permutations: " << permutations << endl;
			rows = tmp;
			output(arr, rows, cols);
		}
		count[k] = comparisons;
		k++;
		count[k] = permutations;
		k++;
	}
	for (int i = 0; i < rows; i++) {
		delete[] old_array[i];
		old_array[i] = nullptr;
	} 
	delete[] old_array;
	console_table(count);
	cout << "Press 1 if you want to save results: ";
	cin >> user_choice;
	if (user_choice == Yes)
		table(arr, rows, cols, count);
	
	return 0;
}

int output(int **arr, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}
	return(0);
}

