/**
 * getquery.cpp
 * Demonstrates GET method with XHTML form.
 */
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(void) {
	char postString[1024] = "";
	string dataString = "";
	string nameString = "";
	string wordString = "";
	int contentLength = 0;

	if(getenv("CONTENT_LENGTH")) {
		contentLength = atoi(getenv("CONTENT_LENGTH"));
		cin.read(postString, contentLength);
		dataString = postString;
	}

	/* output header*/
	cout << "Content-Type: text/html\n\n";

	// output XML declaration and DOCTYPE
	cout << "<?xml version = \"1.0\"?>"
		<< "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" "
		<< "\"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">";

	// output html element and some of its contents
	cout << "<html xmlns = \"http://www.w3.org/1999/xhtml\">"
		<< "<head><title>Using POST with Forms</title></head><body>";

	// output xhtml form
	cout << "<p>Enter one word:</p>"
		<< "<form method = \"post\" action = \"postquery.cgi\">"
		<< "<input type = \"text\" name = \"word\"/>"
		<< "<input type = \"submit\" value = \"Submit word\"/></form>";

	if(contentLength > 0) {
		int nameLocation = dataString.find_first_of("word=") + 5;
		int endLocation = dataString.find_first_of("&") - 1;

		wordString = dataString.substr(
				nameLocation, endLocation - nameLocation);

		if(wordString == "")
			cout << "<p>Please enter a word.</p>";
		else
			cout << "<p>Your word is: " << wordString << "</p>";
	}
	else
		cout << "<p>Please enter a word.</p>";

	cout << "</body></html>";
	return 0;
}
