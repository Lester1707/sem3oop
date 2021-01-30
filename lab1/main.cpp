//#include "pch.h"
#include <iostream>
using namespace std;

void change_values(int &a, int &b) {
	a = a + b;
	b = a - b;
	a = a - b;
}

class Rectangle {

private:
	int x1, y1;
	int x2, y2;
	bool real;

public:
	Rectangle() {  
		real = 0;
	}

	int get_square() {
		if (!real) {
			doesnt_exist();
			return 0;
		}
		return abs(x2 - x1) * abs(y2 - y1);
	}

	int get_perimetr() {
		if (!real) {
			doesnt_exist();
			return 0;
		}
		return 2 * (abs(x2 - x1) + abs(y2 - y1));
	}

	void get_coordinat() {
		cout << "input the first x coordinate\n"; cin >> x1;
		cout << "input the second x coordinate\n"; cin >> x2;
		if (x2 < x1) {
			change_values(x1, x2);
		}
		cout << "input the first y coordinate\n"; cin >> y1;
		cout << "input the second y coordinate\n"; cin >> y2;
		if (y2 < y1) {
			change_values(y1, y2);
		}
		if (!(x1 == x2 || y1 == y2)) {
			real = 1;
		}
	}

	bool move_on_x(int dx) {
		cout << "the rectangle change x plays on " << dx << "\n";
		if (!real) {
			doesnt_exist();
			return 0;
		} 
		x1 += dx;
		x2 += dx;
		return 1;
	}

	bool move_on_y(int dy) {
		cout << "the rectangle change y plays on " << dy << "\n";
		if (!real) {
			doesnt_exist();
			return 0;
		}
		y1 += dy;
		y2 += dy;
		return 1;
	}

	bool change_size_x_right(int dx) {
		cout << "the rectangle change (right) x size on " << dx << "\n";
		if (!real) {
			doesnt_exist();
			return 0;
		}
		if (dx <= -(x2 - x1)) {
			real = 0;
			return 1;
		}
		x2 += dx;
		return 1;
	}

	bool change_size_x_left(int dx) {
		cout << "the rectangle change (left) x size on " << dx << "\n";
		dx = -dx;
		if (!real) {
			doesnt_exist();
			return 0;
		}
		if (dx <= -(x2 - x1)) {
			real = 0;
			return 1;
		}
		x1 += dx;
		return 1;
	}

	bool change_size_y_up(int dy) {
		cout << "the rectangle change (up) y size on " << dy << "\n";
		if (!real) {
			doesnt_exist();
			return 0;
		}
		if (dy <= -(y2 - y1)) {
			real = 0;
			return 1;
		}
		y2 += dy;
		return 1;
	}

	bool change_size_y_down(int dy) {
		cout << "the rectangle change (down) y size on " << dy << "\n";
		dy = -dy;
		if (!real) {
			doesnt_exist();
			return 0;
		}
		if (dy <= -(y2 - y1)) {
			real = 0;
			return 1;
		}
		y1 += dy;
		return 1;
	}

	void doesnt_exist() {
		cout << "The regtangle is doesnt exist.\n";
	}

	void check_info() {
		cout << "Rectangle info:\n";
		cout << "exist - " << real << "\n";
		if (real) {
			cout << "x1 = " << x1 << " x2 = " << x2 << "\n";
			cout << "y1 = " << y1 << " y2 = " << y2 << "\n";
			cout << "The square = " << get_square() << "\n";
			cout << "The perimetr = " << get_perimetr() << "\n";
		}
		else {
			doesnt_exist();
		}
		cout << "--------------------------------------\n";
	}

	Rectangle operator && (Rectangle b) {
		cout << "a && b:\n";
		Rectangle c;
		if (real == 0 || b.real == 0) {
			c.real = 0;
			return c;
		}
		if (b.x2 <= x1 || b.x1 >= x2 || b.y1 >= y2 || b.y2 <= y1) {
			c.real = 0;
			return c;
		}
		c.real = 1;
		if (b.x1 < x1) {
			c.x1 = x1;
		}
		else {
			c.x1 = b.x1;
		}
		if (x2 < b.x2) {
			c.x2 = x2;
		}
		else {
			c.x2 = b.x2;
		}
		if (b.y1 < y1) {
			c.y1 = y1;
		}
		else {
			c.y1 = b.y1;
		}
		if (y2 < b.y2) {
			c.y2 = y2;
		}
		else {
			c.y2 = b.y2;
		}
		return c;
	}

	Rectangle operator || (Rectangle b) {
		cout << "a || b:\n";
		Rectangle r;
		if (real + b.real == 0) {
			r.real = 0;
			return r;
		}
		if (real == 0) {
			return b;
		}
		if (b.real == 0) {
			return *this;
		}
		r.real = 1;
		int c[4];
		c[0] = y1;
		c[1] = y2;
		c[2] = b.y1;
		c[3] = b.y2;
		int max_y = c[0];
		for (int i = 0; i < 4; i++) {
			if (c[i] > max_y) {
				max_y = c[i];
			}
		}
		int min_y = c[0];
		for (int i = 0; i < 4; i++) {
			if (c[i] < min_y) {
				min_y = c[i];
			}
		}
		c[0] = x1;
		c[1] = x2;
		c[2] = b.x1;
		c[3] = b.x2;
		int max_x = c[0];
		for (int i = 0; i < 4; i++) {
			if (c[i] > max_x) {
				max_x = c[i];
			}
		}
		int min_x = c[0];
		for (int i = 0; i < 4; i++) {
			if (c[i] < min_x) {
				min_x = c[i];
			}
		}
		r.x1 = min_x;
		r.x2 = max_x;
		r.y1 = min_y;
		r.y2 = max_y;
		return r;
	}

	bool square_bigger (Rectangle b) {
		cout << "Sa > Sb? :\n";
		if (get_square() > b.get_square()) {
			return 1;
		}
		else {
			return 0;
		}
	}

	bool perimetr_bigger (Rectangle b) {
		cout << "Pa > Pb? :\n";
		if (get_perimetr() > b.get_perimetr()) {
			return 1;
		}
		else {
			return 0;
		}
	}
	
};

int main()
{
	Rectangle a;
	Rectangle b;
	Rectangle c;
	cout << "the first rectangle:\n"; 
	a.get_coordinat();
	cout << "the second rectangle:\n";
	b.get_coordinat();
	a.check_info();
	b.check_info();
	cout << a.square_bigger(b) << '\n';
	cout << a.perimetr_bigger(b) << '\n';
	c = a && b;
	c.check_info();
	c = a || b;
	c.check_info();
	c.move_on_x(3);
	c.check_info();
	c.change_size_x_right(2);
	c.check_info();
	c.change_size_y_down(3);
	c.check_info();
	return 0;
}
