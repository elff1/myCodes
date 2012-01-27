#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <iomanip>
using std::setw;

#include <csignal>
using std::raise;
using std::signal;

#include <cstdlib>
using std::exit;
using std::rand;
using std::srand;

#include <ctime>
using std::time;

void signalHandler(int);

int main(void) {
	signal(SIGINT, signalHandler);
	srand(time(0));

	for(int i = 1; i <= 100; i++) {
		int x = 1 + rand() % 50;

		if(x == 25)
			raise(SIGINT);

		cout << setw(4) << i;

		if(i % 10 == 0)
			cout << endl;
	}

	return 0;
}

void signalHandler(int signalValue) {
	cout << "\nInterrupt signal (" << signalValue
		<< ") received.\n"
		<< "Do you wish to continue (1 = yes or 2 = no)? ";
	
	int response;

	cin >> response;

	while(response != 1 && response != 2) {
		cout << "(1 = yes or 2 = no)? ";
		cin >> response;
	}

	if(response != 1)
		exit( EXIT_SUCCESS);

	signal(SIGINT, signalHandler);
}
