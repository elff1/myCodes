#include <iostream>
#include "Increment.h"

using namespace std;

Increment::Increment(int c, int i)
	: count(c), increment(i)
{

}

void Increment::print() const
{
	cout << "count = " << count << ", increment = " << increment << endl;
}
