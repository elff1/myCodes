#include<iostream>
#include<iomanip>
#include<cstdio>
using namespace std;

const char name[3] = {'W', 'T', 'L'};

class Game{
private:
	double game[3][3];
public:
	Game(){}
	~Game(){}
	void init();
	void bestResult(double base);
};

void Game::init(){
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			cin >> game[i][j];
}

void Game::bestResult(double base){
	double best = 0.65;
	for(int i = 0; i < 3; i++){
		double tmp = game[i][0];
		int k = 0;
		for(int j = 1; j < 3; j++)
			if(game[i][j] > tmp){
				tmp = game[i][j];
				k = j;
			}
		best *= tmp;
		cout << name[k] << ' ';
	}
	//cout.precision(2);
	//cout << setprecision(2) << fixed << (best - 1) * base << endl;
	printf("%0.2f\n", (best - 1) * base);
}

int main(){
	Game g;
	
	g.init();
	g.bestResult(2);

	return 0;
}
