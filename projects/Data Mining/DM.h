#ifndef _DM_H
#define _DM_H

#define MaxM 1000
#define MaxN 3000
class Data{
private:
	int m, n, k;
	int b, r;
	float t;
	int SIM, FP, FN;
	bool **rate;
	float **JacSim;
	int **a, **abc;
	bool **similar;

public:
	Data(){}
	~Data();	
	void InitRate();
	void InitParameters();
	void CalculateJacSim();
	void CalculateSimilar();
	void PrintAns();
};

#endif // _DM_H