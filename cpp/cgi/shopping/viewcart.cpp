/**
 * viewcart.cpp
 * program to view books in the shopping cart
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

void header();
void displayShoppingCart(const string &);

int main(void) {
	char postString[1024] = "";
	string dataString = "";
	string cookieString = "";
	string isbnEntered = "";

	string cartData;

	int contentLength = 0;

	if(getenv("HTTP_COOKIE")) {
		cartData = getenv("HTTP_COOKIE");
		cookieString = cartData;
	}

	if(getenv("CONTENT_LENGTH")) {
		contentLength = atoi(getenv("CONTENT_LENGTH"));
		cin.read(postString, contentLength);
		dataString = postString;

		/* find location of isbn value*/
		int addLocation = dataString.find("add=") + 4;
		int endAdd = dataString.find("&isbn");
		int isbnLocation = dataString.find("isbn=") + 5;

		/* retrieve isbn number to add to cart*/
		isbnEntered = dataString.substr(isbnLocation);

		/* write cookie*/
		string expires = "elf";
		int cartLocation = cookieString.find("CART=") + 5;

		if(cartLocation > 4)
			cookieString= cookieString.substr(cartLocation);

		if(cookieString == "")
			cookieString = isbnEntered;
		else
			cookieString += "," + isbnEntered;

		/* set cookie*/
		cout << "Set-Cookie: CART=" << cookieString << "; expires="
			<< expires << "; path=\n";
	}

	header();

	if(cookieString != "")
		displayShoppingCart(cookieString);
	else
		cout << "The shopping cart is empty.";

	/* output links back to book list and to check out*/
	cout << "</center><br/>";
	cout << "<a href=\"cgi-bin/shop.cgi\">Back to book list</a><br/>";
	cout << "<a href=\"cgi-bin/checkout.cgi\">Check Out</a>";
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
		<< "<head><title>Shopping Cart</title></head>"
		<< "<body><center><p>Here is your current order:</p>";
}

void displayShoppingCart(const string &cookieRef) {
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
	cout << "<table border = \"1\" cellpadding = \"7\" >";
	cout << "<tr><td>Title</td><td>Copyright</td><td>ISBN</td>"
		<< "<td>Price</td><td>Count</td></tr>";

	/* file is open*/
	while(!userData.eof()) {
		userData.getline(book, 50);
		bookString = book;

		userData.getline(year, 50);
		yearString = year;

		userData.getline(isbn, 50);
		isbnString = isbn;

		userData.getline(price, 50);
		priceString = price;

		int match = cookieRef.find(isbnString, 0);
		int count = 0;

		while(match >= 0 && isbnString != "") {
			count++;
			match = cookieRef.find(isbnString, match + 13);
		}

		if(count != 0)
			cout << "<tr><td>" << bookString << "</td><td>" << yearString
				<< "</td><td>" << isbnString << "</td><td>" << priceString
				<< "</td><td>" << count << "</td></tr>";
	}

	cout << "</table>";
}
