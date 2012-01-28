#include<iostream>
#include"ArrList.h"

using namespace std;

// ensure the minimum capacity
void ArrList ::ensureMinCap(const int cap){
	if(Capacity < cap){
		int *nArr = new int[cap + Capacity];		// new a bigger array space
		for(int i = 0; i < cap; i++)				// set the new space as 0
			nArr[Capacity + i] = 0;
		for(int i = 0; i < Capacity; i++)			// copy the data from the original array
			nArr[i] = Arr[i];
		delete []Arr;								// free the original array space
		Arr = nArr;									// use the new array space
		Capacity += cap;							// update the capacity
	}
}

// get the element at the position k
const int& ArrList::operator [](const int k) const{
	if(k < n) return Arr[k];
}

// attach the value at end
void ArrList::attach(const int d){
	n++;
	ensureMinCap(n);
	Arr[n-1] = d;
}

// insert the value before the position k
void ArrList::insert(const int k, const int d){
	n++;
	ensureMinCap(n);
	for(int i = n - 1; i > k; i--)					// find the place to be inserted
		Arr[i] = Arr[i-1];
	Arr[k] = d;										// insert the data
}

// delete the value at position k
void ArrList::del(const int k){
	n--;
	for(int i = k; i < n; i++)
		Arr[i] = Arr[i+1];
}

// print out all the information in the list
void ArrList::prtAll(){
	cout << "N: " << n << "\tCapacity: " << Capacity << endl;
	for(int i = 0; i < n; i++)
		cout << Arr[i] << '\t';
	cout << endl;
}