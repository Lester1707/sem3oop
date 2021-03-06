#include "pch.h"
#include <iostream>
#include <string>
#include <clocale>
using namespace std;

template <typename T>
void change_values(T &a, T &b) {
	a = a + b;
	b = a - b;
	a = a - b;
}

template <typename T>
class Rectangle {

private:
	T x1, y1;
	T x2, y2;
	bool real;

public:
	Rectangle() {
		real = 0;
	}

	T get_square() {
		if (!real) {
			doesnt_exist();
			return 0;
		}
		return abs(x2 - x1) * abs(y2 - y1);
	}

	double get_square_d() {
		if (!real) {
			doesnt_exist();
			return 0;
		}
		return (double) abs(x2 - x1) * abs(y2 - y1);
	}

	T get_perimetr() {
		if (!real) {
			doesnt_exist();
			return 0;
		}
		return 2 * (abs(x2 - x1) + abs(y2 - y1));
	}

	void get_coordinat() {
		cout << "enter the 4 coordinates (example: (x1 x2 y1 y2))\n";
		cin >> x1 >> x2 >> y1 >> y2;
		if (x2 < x1) {
			change_values(x1, x2);
		}
		if (y2 < y1) {
			change_values(y1, y2);
		}
		if (x1 != x2 && y1 != y2) {
			real = 1;
		}
		cout << "--------------------------------------\n";
	}

	bool go_coordinate(T a, T b, T c, T d) {
		if (a != b && c != d) {
			real = 1;
		}
		else {
			real = 0;
			return 0;
		}
		if (b < a) {
			x1 = b;
			x2 = a;
		}
		else {
			x1 = a;
			x2 = b;
		}
		if (d < c) {
			y1 = d;
			y2 = c;
		}
		else {
			y1 = c;
			y2 = d;
		}
		return 1;
	}

	void doesnt_exist() {
		cout << "The regtangle is doesnt exist.\n";
	}

	void check_info() {
		cout << "Rectangle info: ";
		if (real) {
			cout << "(" << x1 << ", " << x2 << ", " << y1 << ", " << y2 << ") (S = " << get_square() << ", P = " << get_perimetr() << ")\n";
		}
		else {
			doesnt_exist();
		}
		cout << "--------------------------------------\n";
	}

	Rectangle <T> operator ++ () {
		x2 += 1;
		y2 += 1;
		return *this;
	}

	Rectangle <T> operator ++ (int some_value) {
		Rectangle <T> a = *this;
		x2 += 1;
		y2 += 1;
		return a;
	}

};

int cti(char a) {
	return a - '0';
}

int pow(int a, int b) {
	int c = 1;
	for (int i = 1; i <= b; i++) {
		c *= a;
	}
	return c;
}

Rectangle <int> operator "" _rec(const char* a, size_t size) {
	Rectangle <int> c;
	string cord = (string)a;
	int n = cord.size() - 1;
	int i = cord.size() - 1;
	int sumx1 = 0;
	int sumx2 = 0;
	int sumy1 = 0;
	int sumy2 = 0;
	while (cord[i] != ',' && cord[i] != '.') {
		if (cord[i] >= '0' && cord[i] <= '9') {
			sumy2 += cti(cord[i])*pow(10, n - i);
		}
		if (cord[i] == '-') {
			sumy2 = -sumy2;
		}
		i--;
	}
	i--;
	n = i;
	while (cord[i] != ',' && cord[i] != '.') {
		if (cord[i] >= '0' && cord[i] <= '9') {
			sumy1 += cti(cord[i])*pow(10, n - i);
		}
		if (cord[i] == '-') {
			sumy1 = -sumy1;
		}
		i--;
	}
	i--;
	n = i;
	while (cord[i] != ',' && cord[i] != '.') {
		if (cord[i] >= '0' && cord[i] <= '9') {
			sumx2 += cti(cord[i])*pow(10, n - i);
		}
		if (cord[i] == '-') {
			sumx2 = -sumx2;
		}
		i--;
	}
	i--;
	n = i;
	while (i >= 0) {
		if (cord[i] >= '0' && cord[i] <= '9') {
			sumx1 += cti(cord[i])*pow(10, n - i);
		}
		if (cord[i] == '-') {
			sumx1 = -sumx1;
		}
		i--;
	}
	c.go_coordinate(sumx1, sumx2, sumy1, sumy2);
	return c;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Rectangle <int> a;
	Rectangle <double> b;
	Rectangle <int> c;
	cout << "Купцов Илья\nЛабораторная работа №2\nЗадание: Разработать класс Rectangle, представляющий собой прямоугольник со сторонами, параллельными осям координат. Поля – координаты левого нижнего и правого верхнего угла. Требуется реализовать следующие методы: вычисление площади и периметра, перемещения вдоль осей, изменение размеров, сравнение по площади и по периметру. Реализовать метод получения прямоугольника, представляющего общую часть (пересечение) двух прямоугольников. Реализовать метод объединения двух прямоугольников: наименьший прямоугольник, включающего оба заданных прямоугольника.\n Необходимо реализовать :-операцию приведения к типу double, вычисляющую площадь прямоугольника;-операцию префиксного и постфиксного инкремента, увеличивающую одновременно размеры сторон прямоугольника.- операции сравнения(больше, меньше, равно);Необходимо реализовать пользовательский литерал для работы с константами типа Rectangle\nBegining:\n";
	cout << "Input the first rectangle(int):\n";
	a.get_coordinat();
	cout << "Input the second rectangle(double):\n";
	b.get_coordinat();
	a.check_info();
	cout << "double square:\n";
	b.check_info();
	a++;
	cout << "a++ operation:\n";
	a.check_info();
	cout << "Literal operation:\n";
	c = "-5, 8, -3, 7"_rec;
	c.check_info();
	return 0;
}
