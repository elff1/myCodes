#include<iostream>
#include<time.h>
#include"ArrStack.h"
#include"LinkStack.h"

#define MaxN 1000000									// the push and pop times

using namespace std;

int main(void){
	int i;

	clock_t start, stop;								// the  clock time
	double duration1, duration2;						// the running time

	// test the stack using array list
	start = clock();									// record the start time
	{
		ArrStack s1;
		for(i = 0; i < MaxN; i++)						// push element into the stack MaxN times
			s1.Push(i);
		for(i = 0; i < MaxN; i++)						// pop all the elements out
			s1.Pop();
	}
	stop = clock();										// record the stop time
	duration1 = ((double)(stop - start))/CLK_TCK;		// calculate the running time

	// test the stack using link list
	start = clock();									// record the start time
	{
		LinkStack s2;
		for(i = 0; i < MaxN; i++)						// push element into the stack MaxN times
			s2.Push(i);
		for(i = 0; i < MaxN; i++)						// pop all the elements out
			s2.Pop();
	}
	stop = clock();										// record the stop time
	duration2 = ((double)(stop - start))/CLK_TCK;		// calculate the running time

	// print out the testing results
	cout << "The time of " << MaxN << " times push and pop on a array stack is "
		<< duration1 << endl;
	cout << "The time of " << MaxN << " times push and pop on a link list stack is "
		<< duration2 << endl;
}