#include <iostream>
#include <string>
#include "UI.h"

int main(void) {
	UI ui;
	string cmd;
	cout << "This is the client of the Socket Lab of Computer Network." << endl;
	while(!ui.finished()) {
		cout << "# ";
		getline(cin, cmd);
		ui.handle(cmd);
	}
	
	return 0;
}