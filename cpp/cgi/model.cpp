/**
 * .cpp
 *
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

void header();

int main(void) {
	char postString[1024] = "";
	string dataString = "";

	int contentLength = 0;

	if(getenv("CONTENT_LENGTH")) {
		contentLength = atoi(getenv("CONTENT_LENGTH"));
		cin.read(postString, contentLength);
		dataString = postString;
	}

	cout << "</body>\n</html>\n";
	return 0;
}

void header() {
	/* output header*/
	cout << "Content-Type: text/html\n\n";

	// output XML declaration and DOCTYPE
	cout << "<?xml version = \"1.0\"?>"
		<< "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" "
		<< "\"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">";

	// output html element and some of its contents
	cout << "<html xmlns = \"http://www.w3.org/1999/xhtml\">"
		<< "<head><title>Using POST with Forms</title></head><body>";
}

