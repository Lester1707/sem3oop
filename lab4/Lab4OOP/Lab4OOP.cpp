/*
Купцов Илья. Лабораторная работа№4
Разработать шаблоны классов согласно варианту задания.  Параметром шаблона должен являться скалярный тип данных 
задающий тип данных для оси координат. Классы должны иметь публичные поля. Фигуры являются фигурами вращения. 
Для хранения координат фигур необходимо использовать шаблон  std::pair.

Создать набор шаблонов, создающих функции, реализующие:
1.   	Вычисление геометрического центра фигуры;
2.   	Вывод в стандартный поток вывода std::cout координат вершин фигуры;
3.   	Вычисление площади фигуры;
Параметром шаблона должен являться тип класса фигуры ( например Square<int>). Помимо самого класса фигуры, шаблонная функция должна уметь работать с tuple. 
Например, std::tuple<std::pair<int,int>, std::pair<int,int>, std::pair<int,int>> должен интерпретироваться как треугольник. 
std::tuple<std::pair<int,int>, std::pair<int,int>, std::pair<int,int>, std::pair<int,int>> - как квадрат. 
Каждый std::pair<int,int> - соответствует координатам вершины фигуры вращения.

Создать программу, которая позволяет:
•  Вводить из стандартного ввода std::cin фигуры, согласно варианту задания (как в виде класса, так и в виде std::tuple).
•  Вызывать для нее шаблонные функции (1-3).
*/

#include "pch.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
using namespace std;
const double PI = 3.141592;

void wrong() {
    cout << "Wrong format!!\n";
}

template <class T>
class Figure {
protected:
    int n_size;
public:
    bool exist;
    vector <pair <T, T>> cord;
    Figure() {
        n_size = 0;
        exist = 0;
    }
    void d_exist() {
        cout << "'Figure dosent exist'\n";
    }
    void add_point(T x1, T y1) {
        cord.push_back(make_pair(x1, y1));
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
            cout << "(" << cord[i].first << ", " << cord[i].second << ") ";
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
            S1 += cord[i].first;
            S2 += cord[i].second;
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
        if (h == 0 || a == 0 || b == 0 || a == b) {
            return;
        }
        this->exist = 1;
        this->add_point(x1, y1);
        this->add_point(x2, y2);
        this->add_point(x1 + b, y1);
        this->add_point(x2 + a, y2);
    }
    Trap(tuple <pair <T, T>, pair <T, T>, pair <T, T>> t)
    {
        T c = get<2>(t).first - get<1>(t).first;
        T x1 = get<0>(t).first;
        T x2 = get<1>(t).first;
        T y1 = get<0>(t).second;
        T y2 = get<1>(t).second;
        T x3 = get<2>(t).first;
        T y3 = get<2>(t).second;
        if (c == 0 || (x1 == x2 && y1 == y2) || (x3 == x2 && y3 == y2) || (x3 == x1 && y3 == y1) || y3 - y2 != 0) {
            return;
        }
        if (x2 - x1 <= -c) {
            return;
        }
        a = c;
        b = c + 2 * (x2 - x1);
        h = abs(y2 - y1);
        if (h == 0 || a == 0 || b == 0 || a == b) {
            return;
        }
        this->exist = 1;
        this->add_point(x1, y1);
        this->add_point(x2, y2);
        this->add_point(x3, y3);
        this->add_point(x1 + b, y1);
    }
    T get_square() {
        return (a + b) / 2 * h;
    }
};

template <class T>
class Romb : public Figure <T> {
protected:
    T a;
    T S;
public:
    Romb(T x1, T y1, T x2, T y2) {
        T h;
        if (x1 == x2 && y1 == y2) {
            return;
        }
        a = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
        h = abs(y2 - y1);
        S = a * h;
        if (a == 0 || h == 0) {
            return;
        }
        this->exist = 1;
        this->add_point(x1, y1);
        this->add_point(x2, y2);
        this->add_point(x2 + a, y2);
        this->add_point(x1 + a, y1);
    }
    Romb(tuple <pair <T, T>, pair <T, T>> t) {
        T h;
        T x1 = get<0>(t).first;
        T x2 = get<1>(t).first;
        T y1 = get<0>(t).second;
        T y2 = get<1>(t).second;
        if (x1 == x2 && y1 == y2) {
            return;
        }
        a = (T) sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
        h = abs(y2 - y1);
        S = a * h;
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
        return S;
    }
};

template <class T>
class Pentagon : public Trap <T> {
protected:
    T l;
public:
    Pentagon(T c, T x1, T y1) : Trap <T>(c, x1 - c * cos(2 * PI / 5), y1 + c * sin(2 * PI / 5), x1, y1)
    {
        if (!this->exist) {
            return;
        }
        l = c;
        this->add_point(this->cord[0].first + c * cos(PI / 5), this->cord[2].second + c * sin(PI / 5));
    }
    Pentagon(tuple <pair <T, T>, pair <T, T>> t) : Trap <T>((get<1>(t).first - get<0>(t).first), get<0>(t).first - (get<1>(t).first - get<0>(t).first) * (T) cos(2 * (T) PI / 5), get<0>(t).second + (get<1>(t).first - get<0>(t).first) * (T) sin(2 * (T) PI / 5), get<0>(t).first, get<0>(t).second)
    {
        if (!this->exist) {
            return;
        }
        if ((get<1>(t).second - get<0>(t).second) != 0) {
            this->exist = 0;
            return;
        }
        T c = (get<1>(t).first - get<0>(t).first);
        l = c;
        this->add_point(this->cord[0].first + c * (T) cos((T)PI / 5), this->cord[2].second + c * (T) sin((T)PI / 5));
    }
    T get_square() {
        return (T) 5 / 4 * (T) pow(l, 2) / (T) tan((T)PI / 5);
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
void delete_fig(vector <Figure <T>*> &a, unsigned int j) {
    delete a[j];
    for (unsigned int i = j; i < a.size() - 1; i++) {
        a[i] = a[i + 1];
    }
    a[a.size() - 1] = nullptr;
    a.pop_back();
}

template <class T>
void clear_all(vector <Figure <T>*> &a) {
    while (a.size() > 0) {
        delete_fig(a, 0);
    }
}

template <class T>
void add_figure(vector <Figure <T>*> &a, tuple <pair <T, T>, pair<T, T>, pair <T, T>> t) {
    Trap <T>* b = new Trap <T>(t);
    a.push_back(b);
}

template <class T>
void add_figure_p(vector <Figure <T>*> &a, tuple <pair <T, T>, pair<T, T>> t) {
    Pentagon <T>* b = new Pentagon <T>(t);  
    a.push_back(b);
}

template <class T>
void add_figure(vector <Figure <T>*> &a, tuple <pair <T, T>, pair<T, T>> t) {
    Romb <T>* b = new Romb <T>(t);
    a.push_back(b);
}

template <class T>
T square_func(Figure <T>* a) {
    return a->get_square();
}

template <class T>
pair <T, T> center_func(Figure <T>* a) {
    vector <T> b = a->center();
    return make_pair(b[0], b[1]);
}

template <class T>
void out_info(Figure <T>* a) {
    if (!a->exist) {
        cout << "Figure doesnt exist\n";
        return;
    }
    pair <T, T> out = center_func(a);
    cout << "{ ";
    for (unsigned int i = 0; i < a->cord.size(); i++) {
        cout << "(" << a->cord[i].first << ", " << a->cord[i].second << ") ";
    }
    cout << "}; ";
    cout << "S = " << square_func(a);
    cout << "; Geom Center: (" << out.first << ", " << out.second << ")\n";
}

template <class T>
void print_info(vector <Figure <T>*> &a) {
    for (unsigned int i = 0; i < a.size(); i++) {
        out_info(a[i]);
    }
}

template <class T>
T square_func(tuple <pair <T, T>, pair<T, T>, pair <T, T>> t) {
    Trap <T> a(get<1>(t).first - get<0>(t).first, get<0>(t).first, get<0>(t).second, get<1>(t).first, get<1>(t).second);
    return a.get_square();
}

template <class T>
pair <T, T> center_func(tuple <pair <T, T>, pair<T, T>, pair <T, T>> t) {
    Trap <T> a(get<1>(t).first - get<0>(t).first, get<0>(t).first, get<0>(t).second, get<1>(t).first, get<1>(t).second);
    return center_func(&a);
}

template <class T>
pair <T, T> center_func(tuple <pair <T, T>, pair<T, T>> t) {
    if (get<1>(t).second - get<0>(t).second == 0) {
        Pentagon <T> a(t);
        return center_func(&a);
    }
    Romb <T> a(get<0>(t).first, get<0>(t).second, get<1>(t).first, get<1>(t).second);
    return center_func(&a);
}

template <class T>
pair <T, T> square_func(tuple <pair <T, T>, pair<T, T>> t) {
    if (get<1>(t).second - get<0>(t).second == 0) {
        Pentagon <T> a(t);
        return a.get_square();
    }
    Romb <T> a(get<0>(t).first, get<0>(t).second, get<1>(t).first, get<1>(t).second);
    return a.get_square();
}

typedef double use_type;
int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Студент Купцов Илья.\nЛабораторная работа №4\n";
    cout << "Разработать шаблоны классов согласно варианту задания.  Параметром шаблона должен являться скалярный тип данных задающий тип данных для оси координат. Классы должны иметь публичные поля. Фигуры являются фигурами вращения. Для хранения координат фигур необходимо использовать шаблон  std::pair.\n";
    cout << "Создать набор шаблонов, создающих функции, реализующие:\n  1. Вычисление геометрического центра фигуры;\n  2. Вывод в стандартный поток вывода std::cout координат вершин фигуры;\n  3. Вычисление площади фигуры;\nПараметром шаблона должен являться тип класса фигуры(например Square<int>).\nПомимо самого класса фигуры, шаблонная функция должна уметь работать с tuple.Например, std::tuple<std::pair<int, int>, std::pair<int, int>, std::pair<int, int>> должен интерпретироваться как треугольник.std::tuple<std::pair<int, int>, std::pair<int, int>, std::pair<int, int>, std::pair<int, int>> -как квадрат.Каждый std::pair<int, int> -соответствует координатам вершины фигуры вращения. Создать программу, которая позволяет:\n 1. Вводить из стандартного ввода std::cin фигуры, согласно варианту задания(как в виде класса, так и в виде std::tuple)\n 2. Вызывать для нее шаблонные функции(1 - 3).\n\n";
    cout << "Необходимая информация для работы с программой:\n\t't' + arguments (последовательно точки двух направляющих векторов) - создать фигуру 'трапеция';\n\t'r' + arguments (последовательно точки одного направляющего вектора) - создать фигуру 'ромб';\n\t'p' + arguments (последовательно точки одного направляющего вектора) - создать фигуру 'пятиугольник';\n\t'i' - вывести все добавление фигуры;\n\t'd' + arguments (номер элемента) - удалить ранее созданную фигуру;\n	's' - завершить программу;\n";
    vector <Figure <use_type>*> vec;
    use_type x1, x2, y1, y2, x3, y3;
    unsigned int j;
    char ch;
    while (true) {
        cin >> ch;
        if (ch == 't') {
            cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
            add_figure(vec, make_tuple(make_pair(x1, y1), make_pair(x2, y2), make_pair(x3, y3)));
        }
        else if (ch == 'r') {
            cin >> x1 >> y1 >> x2 >> y2;
            add_figure(vec, make_tuple(make_pair(x1, y1), make_pair(x2, y2)));
        }
        else if (ch == 'p') {
            cin >> x1 >> y1 >> x2 >> y2;
            add_figure_p(vec, make_tuple(make_pair(x1, y1), make_pair(x2, y2)));
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
            print_info(vec);
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
