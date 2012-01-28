#include<iostream>
#include<string>
#include"Queue.cpp"
#include"Integer.h"

using namespace std;

int main(void){
	// the int type queue and its data.
	Queue<int> q1;
	int d1;
	// the string type queue and its data.
	Queue<string> q2;
	string d2;
	// the self-defined type queue and its data.
	Queue<Integer> q3;
	Integer d3;

	// test the int type queue
	// Enqueue some numbers, then print out.
	cout << "Enqueue two numbers." << endl;
	q1.inQueue(1);
	q1.inQueue(2);
	q1.printOut();
	cout << endl;

	// Dequeue and print out the data.
	if(q1.outQueue(d1))
		cout << "The dequeue data: " << d1 << endl;
	// Dequeue.
	cout << "Dequeue again." << endl;
	q1.outQueue(d1);
	// test whether the queue is empty.
	if(q1.isEmpty())
		cout << "The queue is empty." << endl;
	// try to dequeue from an empty queue.
	q1.outQueue(d1);
	cout << endl;

	// Enqueue again and test more.
	cout << "Eequeue one more number." << endl;
	q1.inQueue(3);
	if(q1.outQueue(d1))
		cout << "The dequeue data: " << d1 << endl;
	cout << '\n' << endl;


	// test the string type queue
	// Enqueue some strings, then print out.
	cout << "Enqueue two strings." << endl;
	q2.inQueue("ab");
	q2.inQueue("cd");
	q2.printOut();
	cout << endl;

	// Dequeue and print out the data.
	if(q2.outQueue(d2))
		cout << "The dequeue data: " << d2 << endl;
	// Dequeue.
	cout << "Dequeue again." << endl;
	q2.outQueue(d2);
	// test whether the queue is empty.
	if(q2.isEmpty())
		cout << "The queue is empty." << endl;
	// try to dequeue from an empty queue.
	q2.outQueue(d2);
	cout << endl;

	// Enqueue again and test more.
	cout << "Eequeue one more string." << endl;
	q2.inQueue("ef");
	if(q2.outQueue(d2))
		cout << "The dequeue data: " << d2 << endl;
	cout << '\n' << endl;
	

	// test the self-defined Integer type queue
	// Enqueue some Integers, then print out.
	cout << "Enqueue two Integers." << endl;
	q3.inQueue(5);
	q3.inQueue(6);
	q3.printOut();
	cout << endl;

	// Dequeue and print out the data.
	if(q3.outQueue(d3))
		cout << "The dequeue data: " << d3 << endl;
	// Dequeue.
	cout << "Dequeue again." << endl;
	q3.outQueue(d3);
	// test whether the queue is empty.
	if(q3.isEmpty())
		cout << "The queue is empty." << endl;
	// try to dequeue from an empty queue.
	q3.outQueue(d3);
	cout << endl;

	// Enqueue again and test more.
	cout << "Eequeue one more Integer." << endl;
	q3.inQueue(7);
	if(q3.outQueue(d3))
		cout << "The dequeue data: " << d3 << endl;

	getchar();
}