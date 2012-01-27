/**
 * getquery.cpp
 * Demonstrates GET method with XHTML form.
 */
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(void) {
	string nameString = "";
	string wordString = "";
	string query = "";

	if(getenv("QUERY_STRING"))
		query = getenv("QUERY_STRING");

	cout << "Content-Type: text/html\n\n";

	// output XML declaration and DOCTYPE
	cout << "<?xml version = \"1.0\"?>"
		<< "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" "
		<< "\"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">";

	// output html element and some of its contents
	cout << "<html xmlns = \"http://www.w3.org/1999/xhtml\">"
		<< "<head><title>Using GET with Forms</title></head><body>";

	// output xhtml form
	cout << "<p>Enter one word:</p>"
		<< "<form method = \"get\" action = \"getquery.cgi\">"
		<< "<input type = \"text\" name = \"word\"/>"
		<< "<input type = \"submit\" value = \"Submit word\"/></form>";

	if(query == "")
		cout << "<p>Please enter a word.</p>";
	else {
		int wordLocation = query.find_first_of("word=") + 5;
		wordString = query.substr(wordLocation);

		if(wordString == "")
			cout << "<p>Please enter a word.</p>";
		else
			cout << "<p>Your word is: " << wordString << "</p>";
	}

	cout << "</body></html>";
	return 0;
}
