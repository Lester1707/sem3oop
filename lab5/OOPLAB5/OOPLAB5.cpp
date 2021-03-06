/*
Студент Купцов Илья. Группа 207-Б. Лабораторная номер 6.

Задание:
Разработать шаблоны классов согласно варианту задания.  Параметром шаблона должен являться скалярный тип данных задающий тип данных
для оси координат. Классы должны иметь публичные поля. Фигуры являются фигурами вращения. Для хранения координат фигур необходимо
использовать шаблон  std::pair.

Создать шаблон динамической коллекцию, согласно варианту задания:
1. Коллекция должна быть реализована с помощью умных указателей (std::shared_ptr, std::weak_ptr).
Опционально использование std::unique_ptr;
2. В качестве параметра шаблона коллекция должна принимать тип данных;
3. Коллекция должна содержать метод доступа:
    oСтек – pop, push, top;
    oОчередь – pop, push, top;
    oСписок, Динамический массив – доступ к элементу по оператору [];
4. Реализовать аллокатор, который выделяет фиксированный размер памяти (количество блоков памяти –
является параметром шаблона аллокатора). Внутри аллокатор должен хранить указатель на
используемый блок памяти и динамическую коллекцию указателей на свободные блоки. Динамическая
коллекция должна соответствовать варианту задания (Динамический массив, Список, Стек, Очередь);
5. Коллекция должна использовать аллокатор для выделеления и освобождения памяти для своих
элементов.
6. Аллокатор должен быть совместим с контейнерами std::map и std::list (опционально – vector).
7. Реализовать программу, которая:
    oПозволяет вводить с клавиатуры фигуры (с типом int в качестве параметра шаблона фигуры) и добавлять в коллекцию использующую 
    аллокатор;
    oПозволяет удалять элемент из коллекции по номеру элемента;
    oВыводит на экран введенные фигуры c помощью std::for_each;
*/
#include "pch.h"
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>

using namespace std;

void wrong() {
    cout << "Wrong format!!\n";
}

template <class T>
class Figure {
protected:
    int n_size;

    void d_exist() {
        cout << "'Figure dosent exist'\n";
    }
public:
    bool exist;
    vector <pair <T, T>> cord;
    Figure() {
        n_size = 0;
        exist = 0;
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
    T get_square() {
        return (a + b) / 2 * h;
    }
};

template <class T>
struct Node {
    T value;
    shared_ptr <Node> left;
    shared_ptr <Node> right;
};

template <class T>
class Iterator {
private:
    shared_ptr <Node <T>> iterator;
public:
    Iterator() {
        iterator = nullptr;
    }
    void operator = (shared_ptr <Node <T>> &new_node) {
        iterator = new_node;
    }
    Iterator operator ++ () {
        iterator = iterator->right;
        return *this;
    }
    shared_ptr <Node <T>> get_ptr() {
        return iterator;
    }
    bool operator == (shared_ptr <Node <T>> iter) {
        if (iterator == iter)
            return 1;
        return 0;
    }
    bool operator != (Iterator <T> iter) {
        if (iterator != iter.get_ptr())
            return 1;
        return 0;
    }
    shared_ptr <Node <T>> operator * () {
        return iterator;
    }
    Iterator forward_iter() {
        return ++*this;
    }
};

template <class T>
class List : public Iterator <T> {
protected:
    shared_ptr <Node <T>> node;
    shared_ptr <Node <T>> empety;
    int size;
    Iterator <T> iterator;
    queue <shared_ptr <Node <T>>> alloc;

    shared_ptr <Node <T>> create_ptr() {
        Node <T>* ptr = new Node <T>;
        shared_ptr <Node <T>> new_node(ptr);
        new_node->left = nullptr;
        new_node->right = nullptr;
        alloc.push(new_node);
        return new_node;
    }
public:
    List() {
        size = 0;
        empety = create_ptr();
        iterator = node;
        node = nullptr;
        alloc_size(1);
    } 
    Iterator <T> begin() {
        return iterator;
    }
    Iterator <T> end() {
        Iterator <T> iter_p;
        iter_p = empety;
        return iter_p;
    }
    void alloc_size(int mem) {
        for (int i = 0; i < mem; i++)
            create_ptr();
    } 
    T & operator [] (const int &j) {
        if (j < 0 || j > size)
            throw std::out_of_range("Out of range!!!");
        shared_ptr <Node <T>> iter = node;
        for (int i = 0; i < j; i++)
            iter = iter->right;
        return iter->value;
    }
    T & operator [] (Iterator <T> iter) {
        return *iter->value;
    }
    int len() {
        return size;
    }

    shared_ptr <Node <T>> next_iter(int count) {
        if (count < 0 || count > size)
            throw std::out_of_range("Out of range!!!");
        shared_ptr <Node <T>> iter = node;
        for (int i = 0; i < count; i++) 
            iter = iter->right;
        return iter;
    }

    void push_back(const T em) {
        if (size == 0) {
            node = empety;
            if (size + 1 != alloc.size()) {
                for (int i = 1; i <= size + 1; i++) {
                    alloc.push(alloc.front());
                    alloc.pop();
                }
                empety = alloc.front();
                for (unsigned int i = size + 1; i < alloc.size(); i++) {
                    alloc.push(alloc.front());
                    alloc.pop();
                }
            }
            else {
                empety = create_ptr();
            }
            node->value = em;
            node->right = empety;
            node->left = empety;
            empety->left = node;
            empety->right = node;
            size++;
            iterator = node;
            return;
        }
        shared_ptr <Node <T>> new_node = empety;
        if (size + 1 != alloc.size()) {
            for (int i = 1; i <= size + 1; i++) {
                alloc.push(alloc.front());
                alloc.pop();
            }
            empety = alloc.front();
            for (unsigned int i = size + 1; i < alloc.size(); i++) {
                alloc.push(alloc.front());
                alloc.pop();
            }
        }
        else {
            empety = create_ptr();
        }
        new_node->value = em;
        new_node->right = empety;
        node->left = empety;
        empety->left = new_node;
        empety->right = node;
        size++;
    }
    void push_front(const T em) {
        insert(em, 0);
    }
    void insert(const T em, const int &j) {
        if (j < 0 || j > size)
            throw std::out_of_range("Out of range!!!");
        if (size == 0) {
            node = empety;
            empety = create_ptr();
            node->value = em;
            node->right = empety;
            node->left = empety;
            empety->left = node;
            empety->right = node;
            size++;
            iterator = node;
            return;
        }
        shared_ptr <Node <T>> iter = next_iter(j);
        shared_ptr <Node <T>> new_node = create_ptr();
        new_node->value = em;
        new_node->right = iter;
        new_node->left = iter->left;
        iter->left = new_node;
        new_node->left->right = new_node;
        if (iter == node)
            node = new_node;
        size++;
    }
    T erase(const int &j) {
        if (j < 0 || j >= size)
            throw std::out_of_range("Out of range!!!");
        T obj;
        shared_ptr <Node <T>> iter = next_iter(j);
        if (j == 0) {
            node = iter->right;
            iterator = node;
            if (alloc.size() != 1)
                alloc.pop();
            iter->left->right = iter->right;
            iter->right->left = iter->left;
            iter->left = nullptr;
            iter->right = nullptr;
            obj = iter->value;
            size--;
            return obj;
        }
        iter->left->right = iter->right;
        iter->right->left = iter->left;
        iter->left = nullptr;
        iter->right = nullptr;
        obj = iter->value;
        size--;
        for (int i = 1; i < j + 1; i++) {
            alloc.push(alloc.front());
            alloc.pop();
        }
        alloc.pop();
        for (unsigned int i = j + 1; i < alloc.size(); i++) {
            alloc.push(alloc.front());
            alloc.pop();
        }
        return obj;
    }

    T erase(Iterator <T> iter_P) {
        shared_ptr <Node<T>> iter = *iter_P;
        T obj;
        if (iter == node) {
            node = iter->right;
            iterator = node;
        }
        iter->left->right = iter->right;
        iter->right->left = iter->left;
        iter->left = nullptr;
        iter->right = nullptr;
        obj = iter->value;
        size--;
        return obj;
    }
    void insert(Iterator <T> iter_P, const T em) {
        shared_ptr <Node<T>> iter = *iter_P;
        if (end() == iter) {
            push_back(em);
            return;
        }
        if (size == 0) {
            node = empety;
            empety = create_ptr();
            node->value = em;
            node->right = empety;
            node->left = empety;
            empety->left = node;
            empety->right = node;
            size++;
            iterator = node;
            return;
        }
        shared_ptr <Node <T>> new_node = create_ptr();
        new_node->value = em;
        new_node->right = iter;
        new_node->left = iter->left;
        iter->left = new_node;
        new_node->left->right = new_node;
        if (iter == node)
            node = new_node;
        size++;
    }
};

void show(shared_ptr <Node <Trap <int>*>> a) {
    a->value->get_info();
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Студент Купцов Илья.\nЛабораторная работа №5\n";
    cout << "\nИнформация для работы с программой:\nВведите\n:	't' + arguments (длина основания и вектор боковой стороны соотвественно) - создать фигуру 'трапеция';\n	'i' - вывести все добавление фигуры;\n	'd' + arguments (номер элемента) - удалить ранее созданную фигуру;\n	's' + arguments (размер площади относительно которой идет счет) - найти количество фигур, площадью меньше заданной;\n	'e' - завершить программу;\n";
    List <Trap <int>*> list;
    Trap <int>* a;
    int x1, x2, y1, y2, c;
    int j;
    char ch;
    int square;
    while (true) {
        cin >> ch;
        if (ch == 't') {
            cin >> c >> x1 >> y1 >> x2 >> y2;
            a = new Trap <int>(c, x1, y1, x2, y2);
            list.push_back(a);
        }
        else if (ch == 'd') {
            cin >> j;
            j--;
            if (j < 0 || j >= list.len()) {
                wrong();
                continue;
            }
            list.erase(j);
        }
        else if (ch == 'i') {
            for_each(list.begin(), list.end(), show);
        }
        else if (ch == 's') {
            j = 0;
            cin >> square;
            for (int i = 0; i < list.len(); i++)
                if (list[i]->get_square() < square)
                    j++;
            cout << "Count traps square bigger then input: " << j << endl;
        }
        else if (ch == 'e') {
            for (int i = 0; i < list.len(); i++)
                delete list[i];
            break;
        }
        else {
            wrong();
        }
    }
    return 0;
}

