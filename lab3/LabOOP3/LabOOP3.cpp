#include "pch.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
const double PI = 3.1415926535;

void wrong() {
	cout << "Wrong format!!\n";
}

template <class T>
class Figure {
protected:
	vector <T> c_x;
	vector <T> c_y;
	int n_size;
	bool exist;
public:
	Figure() {
		n_size = 0;
		exist = 0;
	}
	void d_exist() {
		cout << "'Figure dosent exist'\n";
	}
	void add_point(T x1, T y1) {
		c_x.push_back(x1);
		c_y.push_back(y1);
		n_size++;
	}
	virtual T get_square() = 0;
	void get_info() {
		if (!exist) {
			d_exist();
			return;
		}
		vector <T> out = center();
		cout << "{ ";
		for (int i = 0; i < n_size; i++) {
			cout << "(" << c_x[i] << ", " << c_y[i] << ") ";
		}
		cout << "}; ";
		cout << "S = " << get_square();
		cout << "; Geom Center: (" << out[0] << ", " << out[1] << ")\n";
	}
	vector <T> center() {
		vector <T> out(2);
		T S1, S2;
		S1 = 0;
		S2 = 0;
		for (int i = 0; i < n_size; i++) {
			S1 += c_x[i];
			S2 += c_y[i];
		}
		out[0] = S1 / n_size;
		out[1] = S2 / n_size;
		return out;
	}
};

template <class T>
class Trap : public Figure <T> {
protected:
	T b;
	T a;
	T l;
	T h;
public:
	Trap(T c, T x1, T y1, T x2, T y2)
	{
		if (c == 0 || (x1 == x2 && y1 == y2)) {
			return;
		}
		if (x2 - x1 <= -c) {
			return;
		}
		a = c;
		b = c + 2 * (x2 - x1);
		h = abs(y2 - y1);
		l = sqrt(pow(x2 - x1, 2) + pow(h, 2));
		if (h == 0 || l == 0 || a == 0 || b == 0) {
			return;
		}
		this->exist = 1;
		this->add_point(x1, y1);
		this->add_point(x2, y2);
		this->add_point(x1 + b, y1);
		this->add_point(x2 + a, y2);
	}
	T get_square() {
		return (a + b) / 2 * h;
	}
};

template <class T>
class Romb : public Figure <T> {
protected:
	T a;
	T h;
public:
	Romb(T x1, T y1, T x2, T y2) {
		if (x1 == x2 && y1 == y2) {
			return;
		}
		a = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
		h = abs(y2 - y1);
		if (a == 0 || h == 0) {
			return;
		}
		this->exist = 1;
		this->add_point(x1, y1);
		this->add_point(x2, y2);
		this->add_point(x2 + a, y2);
		this->add_point(x1 + a, y1);
	}
	T get_square() {
		return a * h;
	}
};

template <class T>
class Pentagon : public Trap <T> {
protected:
	T a;
public:
	Pentagon(T c, T x1, T y1) : Trap <T>(c, x1 - c * cos(2 * PI / 5), y1 + c * sin(2 * PI / 5), x1, y1)
	{
		if (!this->exist) {
			return;
		}
		a = c;
		this->add_point(this->c_x[0] + c * cos(PI / 5), this->c_y[2] + c * sin(PI / 5));
	}
	T get_square() {
		return 5 / 4 * pow(a, 2) / tan(PI / 5);
	}
};

template <class T>
void add_figure(vector <Figure <T>*> &a, T c, T x1, T y1, T x2, T y2) {
	Trap <T>* b = new Trap <T>(c, x1, y1, x2, y2);
	a.push_back(b);
}

template <class T>
void add_figure(vector <Figure <T>*> &a, T x1, T y1, T x2, T y2) {
	Romb <T>* b = new Romb <T>(x1, y1, x2, y2);
	a.push_back(b);
}

template <class T>
void add_figure(vector <Figure <T>*> &a, T c, T x1, T y1) {
	Pentagon <T>* b = new Pentagon <T>(c, x1, y1);
	a.push_back(b);
}

template <class T>
void show_info(vector <Figure <T>*> &a) {
	for (unsigned int i = 0; i < a.size(); i++) {
		a[i]->get_info();
	}
}

template <class T>
T median_square(vector <Figure <T>*> &a) {
	T S = 0;
	for (unsigned int i = 0; i < a.size(); i++) {
		S += a[i]->get_square();
	}
	return S;
}

template <class T>
void delete_fig(vector <Figure <T>*> &a, unsigned int j) {
	delete a[j];
	for (unsigned int i = j; i < a.size() - 1; i++) {
		a[i] = a[i + 1];
	}
	a[a.size() - 1] = nullptr;
	a.pop_back();
}

typedef double use_type;
int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Студент Купцов Илья.\nЛабораторная работа №3\nОснованя задача:\n";
	cout << "Разработать классы согласно варианту задания, классы должны наследоваться от базового класса Figure. Фигуры являются фигурами вращения. Все классы должны поддерживать набор общих методов:\n1.   	Вычисление геометрического центра фигуры;\n2.   	Вывод в стандартный поток вывода std::cout координат вершин фигуры;\n3.	Вычисление площади фигуры;\n\nСоздать программу, которая позволяет :\n	-Вводить из стандартного ввода std::cin фигуры, согласно варианту задания.Сохранять созданные фигуры в динамический массив std::vector<Figure*>\n	-Вызывать для всего массива общие функции(1 - 3 см.выше).Т.е.распечатывать для каждой фигуры в массиве геометрический центр, координаты вершин и площадь.\n	-Необходимо уметь вычислять общую площадь фигур в массиве.\n	-Удалять из массива фигуру по индексу;\n";
	cout << "\nПрограмма:\n	't' + arguments (длина основания и вектор боковой стороны соотвественно) - создать фигуру 'трапеция';\n	'r' + arguments (вектор одной стороны) - создать фигуру 'ромб';\n	'p' + arguments (длина основания и его единственная точка) - создать фигуру 'пятиугольник';\n	'i' - вывести все добавление фигуры;\n	'd' + arguments (номер элемента) - удалить ранее созданную фигуру;\n	'm' - вывести суммарную площадь всех фигур;\n	's' - завершить программу;\n";
	vector <Figure <use_type>*> vec;
	use_type x1, x2, y1, y2, c;
	unsigned int j;
	char ch;
	while (true) {
		cin >> ch;
		if (ch == 't') {
			cin >> c >> x1 >> y1 >> x2 >> y2;
			add_figure(vec, c, x1, y1, x2, y2);
		}
		else if (ch == 'r') {
			cin >> x1 >> y1 >> x2 >> y2;
			add_figure(vec, x1, y1, x2, y2);
		}
		else if (ch == 'p') {
			cin >> c >> x1 >> y1;
			add_figure(vec, c, x1, y1);
		}
		else if (ch == 'd') {
			cin >> j;
			j--;
			if (j >= 0 && j < vec.size()) {
				delete_fig(vec, j);
			}
			else {
				wrong();
			}
		}
		else if (ch == 'i') {
			show_info(vec);
		}
		else if (ch == 'm') {
			cout << "S_all = " << median_square(vec) << ";\n";
		}
		else if (ch == 's') {
			while (vec.size() > 0) {
				delete_fig(vec, 0);
			}
			break;
		}
		else {
			wrong();
		}
	}
	return 0;
}
