/**
 * checkout.cpp
 * program to log out of the system.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

void header();
void writeCookie();

int main(void) {
	writeCookie();
	header();

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
		<< "<head><title>Checked Out</title></head><body><center>"
		<< "<p>You have checked out<br/>"
		<< "You will be billed accordingly<br/>To login again. "
		<< "<a href=\"/cgi-bin/login.cgi\">click here</a>"
		<< "</center></body></html>\n";
}

void writeCookie() {
	string expires = "elf";

	cout << "Set-Cookie: CART=; expires=" << expires << "; path=\n";
}
