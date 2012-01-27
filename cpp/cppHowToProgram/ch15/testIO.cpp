#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
	const int SIZE = 80;
	char buffer[SIZE];

//	cin.read(buffer, 20);

	cout << cin.gcount() << endl;
	cout.write(buffer, cin.gcount());

	int n = 29;
	cout << n << '\t'
		<< oct << n << '\t'
		<< hex << n << '\t'
		<< setbase(2) << n << '\t' << endl;
}
