/**
 * login.cpp
 * Program to output an XHTML form, verify the username and
 * password entered, and add members.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

void header();
void writeCookie();

int main(void) {
	char postString[1024] = "";
	string dataString = "";

	string userName = "";
	string passWord = "";

	int contentLength = 0;
	bool newMember = false;

	if(getenv("CONTENT_LENGTH")) {
		contentLength = atoi(getenv("CONTENT_LENGTH"));
		cin.read(postString, contentLength);
		dataString = postString;

		// find username location
		int userLocation = dataString.find("user=") + 5;
		int endUser = dataString.find("&");

		/* find password location*/
		int passwordLocation = dataString.find("password=") + 9;
		int endPassword = dataString.find("&new");

		if(endPassword > 0) {
			newMember = true;
			passWord = dataString.substr(
					passwordLocation, endPassword - passwordLocation);
		}
		else {
			passWord = dataString.substr(passwordLocation);
		}

		userName = dataString.substr(userLocation, endUser - userLocation);

		cout << dataString;
		exit(0);
	}

	if(dataString == "") {
		header();
		cout << "<p>Please login.</p>";

		/* output the login form*/
		cout << "<form method = \"post\" action = \"/cgi-bin/login.cgi\">"
			<< "<p>\nUser Name: <input type = \"text\" name = \"user\"/>"
			<< "<br/>\n"
			<< "Password: <input type=\"password\" name=\"password\"/>"
			<< "<br/>\nNew? <input type = \"checkbox\" name = \"new\""
			<< " value = \"1\"/>\n</p>\n"
			<< "<input type = \"submit\" value = \"login\"/>\n</form>\n";
	}
	else {
		string fileUsername = "";
		string filePassword = "";
		bool userFound = false;

		// open user data file for reading and writing
		fstream userData("userdata.txt", ios::in | ios::out);

		if(!userData) {
			cerr << "Could not open database.";
			exit(1);
		}

		/* add new member*/
		if(newMember) {
			/* read username and password from file*/
			while(!userFound && userData >> fileUsername >> filePassword) {
				if(userName == fileUsername)
					userFound = true;
			}
			if(userFound) {
				header();
				cout << "<p>This name has already been taken.</p>"
					<< "<a href=\"/cgi-bin/login.cgi\">Try Again</a>";
			}
			else {
				writeCookie();
				header();

				/* write usre data to file*/
				userData.clear(); // clear eof, allow write at end of file
				userData << "\n" << userName << "\n" << passWord;

				cout << "<p>Your information has been processed."
					<< "a href=\"/cgi-bin/shop.cgi\">Start To Shop</a></p>";
			}
		}
		else { // search for password if entered
			bool authenticated = false;

			while(!userFound && userData >> fileUsername >> filePassword) {
				if(userName == fileUsername) {
					userFound = true;

					authenticated = (passWord == filePassword);
				}
			}

			if(authenticated) {
				writeCookie();
				header();

				cout << "<p>Welcome returning, " << userName << "!</p>"
					<< "<a href=\"/cgi-bin/shop.cgi\">Start Shopping</a>";
			}
			else {
				header();

				if(userFound)
					cout << "<p>You have entered an incorrect password. "
						<< "Please tyr again.</p>"
						<< "<a href=\"/cgi-bin/login.cgi\">Register</a>";
			}
		}
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
		<< "<head><title>Login Page</title></head><body>";
}

void writeCookie() {
	string expires = "Friday, 14-MAY-10 16:00:00 GMT";
	cout << "Set-Cookie: CART=; expires=" << expires << "; path=\n";
}
