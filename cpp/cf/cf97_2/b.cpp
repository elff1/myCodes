#include <iostream>
using namespace std;

class Ternary{
	friend ostream &operator<<(ostream &, const Ternary &);
	friend istream &operator>>(istream &, Ternary &);
private:
	int len;
	int d;
	char t[20];
public:
	Ternary(){};
//	Ternary(int dd);
//	Ternary(char *tt);
	~Ternary(){};
//	void tor(Ternary &b);
	void getT();
	void getD();
	Ternary getB(Ternary &a);
};

void Ternary::getT() {
	int i;
	int dd = d;

	len = 0;
	while(dd > 0) {
		t[len] = dd % 3;
		dd /= 3;
		len++;
	}
	for(i = len; i < 20; i++)
		t[i] = 0;
}

void Ternary::getD() {
	int c = 1;

	d = 0;
	for(int i = 0; i < len; i++) {
		d += t[i] * c;
		c *= 3;
	}
}

Ternary Ternary::getB(Ternary &a) {
	Ternary b;

	b.len = ((a.len > len) ? a.len : len);
	for(int i = 0; i < 20; i++) {
		b.t[i] = (t[i] - a.t[i] + 3) % 3;
	}
	b.getD();

	return b;
}

ostream &operator<<(ostream &out, const Ternary &t) {
	out << t.d;

	return out;
}

istream &operator>>(istream &in, Ternary &t) {
	in >> t.d;
	t.getT();

	return in;
}

int main(void) {
	Ternary a, c;
	
	cin >> a >> c;
//	cout << a << " " << c << endl;
	cout << c.getB(a) << endl;

	return 0;
}
