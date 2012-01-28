#include<iostream>
#include<fstream>
#include"DM.h"
using namespace std;

int main(){
	Data DM;
	int t;

	DM.InitRate();
	//DM.CalculateJacSim();
	cout << "Triples: ";
	cin >> t;
	cout << endl;
	for(int i = 0; i < t; i++){
		DM.InitParameters();
		DM.CalculateSimilar();
		DM.PrintAns();
	}

	system("pause");
}

Data::~Data(){
	int i;

	if(rate){
		for(i = 0; i < m; i++)
			if(rate[i])
				delete [] rate[i];
		delete [] rate;
	}
	if(JacSim){
		for(i = 0; i < n - 1; i++)
			if(JacSim[i])
				delete [] JacSim[i];
		delete [] JacSim;
	}
	if(a){
		for(i = 0; i < n - 1; i++)
			if(a[i])
				delete [] a[i];
		delete [] a;
	}
	if(abc){
		for(i = 0; i < n - 1; i++)
			if(abc[i])
				delete [] abc[i];
		delete [] abc;
	}
	if(similar){
		for(i = 0; i < n - 1; i++)
			if(similar[i])
				delete [] similar[i];
		delete [] similar;
	}
}

void Data::InitRate(){
	int i, j, k;
	int t;
	ifstream fin("matrix.txt");

	fin >> n >> m;

	a = new int *[n];
	abc = new int *[n];
	for(i = 0; i < n - 1; i++){
		a[i] = new int[n];
		abc[i] = new int[n];
		for(j = 0; j < n; j++)
			a[i][j] = abc[i][j] = 0;
	}

	rate = new bool *[m];
	for(i = 0; i < m; i++){
		rate[i] = new bool[n];
		for(j = 0; j < n; j++){
			fin >> t;
			if(t)
				rate[i][j] = true;
			else
				rate[i][j] = false;

			for(k = 0; k < j - 1; k++){
				if(rate[i][j] || rate[i][k])
					abc[k][j]++;
				if(rate[i][j] && rate[i][k])
					a[k][j]++;
			}
		}
	}
	JacSim = new float *[n];
	similar = new bool *[n];
	for(int i = 0; i < n - 1; i++){
		similar[i] = new bool[n];
		JacSim[i] = new float[n];
		for(int j = i + 1; j < n; j++){
			JacSim[i][j] = 1.0 * a[i][j] / abc[i][j];
		}
	}
}

void Data::InitParameters(){
	cout << "Input a threshold: ";
	cin >> t;
}

void Data::CalculateJacSim(){
	int a, abc;
	JacSim = new float *[n];
	for(int i = 0; i < n - 1; i++){
		JacSim[i] = new float[n];
		for(int j = i + 1; j < n; j++){
			a = abc = 0;
			for(int k = 0; k < m; k++){
				if(rate[k][i] || rate[k][j])
					abc++;
				if(rate[k][i] && rate[k][j])
					a++;
			}
			JacSim[i][j] = 1.0 * a / abc;
		}
	}
}

void Data::CalculateSimilar(){
	SIM = 0;

	for(int i = 0; i < n - 1; i++){
		for(int j = i + 1; j < n; j++)
			if(JacSim[i][j] >= t){
				similar[i][j] = true;
				SIM++;
			}
			else
				similar[i][j] = false;
	}
}

void Data::PrintAns(){
	int i, j;

	cout << "For threshold " << t << ":" << endl;
	cout << "\tSIM: " << SIM << endl;
}