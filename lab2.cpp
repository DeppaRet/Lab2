// lab2.cpp
// Лабораторная работа №2.
// Методы сортировки
// Задана квадратная матрица.
// Упорядочить каждый столбец матрицы по убыванию
// Студент группы 484, Левинский Илья Владимирович. 2019 год


#include <iostream>
#include <ctime>
#include "interface.h"
#include "work_with_menu.h"
using namespace std;

int main(){
	srand((unsigned)time(nullptr));
	about();
	work_with_menu();
	cout << "Good bye!";
	return (0);
}
