#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "fftw3.h"
#include "dsound.h"
#include "Windows.h" 
#include "math.h"
#include <string>
#include <iostream>
using namespace std;

#pragma comment(lib,"libfftw3-3.lib")
#pragma comment(lib,"libfftw3f-3.lib")
#pragma comment(lib,"libfftw3l-3.lib")

struct sound_sequence{
	float time;
	unsigned int frequance;
	float amplitude;
};

class FastFourier{

public: 

	FastFourier();
	~FastFourier();
	sound_sequence *  transform(string filename,int* size, int* index);
};