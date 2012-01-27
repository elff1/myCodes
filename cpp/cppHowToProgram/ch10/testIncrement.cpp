#include <iostream>
#include "Increment.h"

using namespace std;

int main()
{
	Increment value(10, 5);

	value.print();

	for(int i = 1; i <= 3; i++) {
		value.addIncrement();
		cout << i << ": ";
		value.print();
	}

	return 0;
}
