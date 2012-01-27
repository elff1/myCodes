/**
 * localtime.cpp
 * Displays the current date and time in a web browser.
 */
#include <iostream>
#include <ctime>

using namespace std;

int main(void) {
	time_t currentTime;

	cout << "Content-Type: text/html\n\n";

	// output XML declaration and DOCTYPE
	cout << "<?xml version = \"1.0\"?>"
		<< "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" "
		<< "\"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">";

	time(&currentTime);

	// output html element and some of its contents
	cout << "<html xmlns = \"http://www.w3.org/1999/xhtml\">"
		<< "<head><title>Current Time</title></head>"
		<< "<body><p>" << asctime(localtime(&currentTime))
		<< "</p></body></html>";
	return 0;
}
