/**
 * shop.cpp
 * Program to display available books.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

void header();

int main(void) {
	char book[50] = "";
	char year[50] = "";
	char isbn[50] = "";
	char price[50] = "";

	string bookString = "";
	string yearString = "";
	string isbnString = "";
	string priceString = "";

	ifstream userData("catalog.txt", ios::in);
	if(!userData) {
		cerr << "Could not open database.";
		exit(1);
	}

	header();

	/* output available books*/
	cout << "<center><br/>Books available for sale<br/><br/>"
		<< "<table border = \"1\" cellpadding = \"7\" >";

	/* file is open*/
	while(userData) {
		userData.getline(book, 50);
		bookString = book;

		userData.getline(year, 50);
		yearString = year;

		userData.getline(isbn, 50);
		isbnString = isbn;

		userData.getline(price, 50);
		priceString = price;

		cout << "<tr><td>" << bookString << "</td><td>" << yearString
			<< "</td><td>" << isbnString << "</td><td>" << priceString
			<< "</td>";

		/* file is still open after reads*/
		if(userData) {
			/* output form with buy button*/
			cout << "<td><form method=\"post\""
				<< "action=\"/cgin-bin/viewcart.cgi\">"
				<< "<input type=\"hidden\" name=\"add\" value=\"true\"/>"
				<< "<input type=\"hidden\" name=\"isbn\" value=\""
				<< isbnString << "\"/>" << "<input type=\"submit\" "
				<< "value=\"Add to Cart\"/>\n</form></td>\n";
		}
		cout << "</tr>\n";
	}

	cout << "</table></center><br/>"
		<< "<a href=\"/cgi-bin/checkout.cgi\">Check Out</a>"
		<< "</body></html>";
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
		<< "<head><title>Shop Page</title></head><body>";
}

