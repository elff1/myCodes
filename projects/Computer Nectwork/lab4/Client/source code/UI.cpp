#include "UI.h"

bool UI::daemonUp = false;
HANDLE recvThread;

UI::UI(void) {
	_isFinished = false;
	_isConnected = false;
	_address.host = "";
	_address.port = 0;
	daemonUp = true;
	recvThread = CreateThread(NULL, 0, UI::daemon, NULL, 0, NULL);
	CloseHandle(recvThread);
}

UI::~UI(void) {

}

void UI::handle(string cmd) {
	stringstream ss;
	string cmdHeader;

	ss << cmd;
	ss >> cmdHeader;
	if(cmdHeader == "conn") {
		TcpAddress tmp;
		
		ss >> tmp.host >> tmp.port;
		handleConnect(tmp);
	} else if(cmdHeader == "name") {
		if(!checkCmd(ss)) {
			cmdError();
			return;
		}
		handleName();
	} else if(cmdHeader == "time") {
		if(!checkCmd(ss)) {
			cmdError();
			return;
		}
		handleTime();
	} else if(cmdHeader == "list") {
		if(!checkCmd(ss)) {
			cmdError();
			return;
		}
		handleList();
	} else if(cmdHeader == "send") {
		int id;
		
		ss >> id;
		if(!checkCmd(ss)) {
			cmdError();
			return;
		}
		handleSend(id);
	} else if(cmdHeader == "disconn") {
		if(!checkCmd(ss)) {
			cmdError();
			return;
		}
		handleDisConnect();
	} else if(cmdHeader == "quit") {
		if(!checkCmd(ss)) {
			cmdError();
			return;
		}
		handleQuit();
	} else if(cmdHeader != "") {
		cmdError();
	}
}

bool UI::finished(void) {
	WaitForSingleObject(recvThread, INFINITE);
	return _isFinished; 
}

void UI::handleConnect(TcpAddress address) {
	//cout << "connected\n" << endl;
	cout << "Connecting to " << address.port << "@" << address.host << " ..." << endl;
	if(TcpClient::getInstance()->connectServer(address) && sendData("LOGON")) {
		cout << "Connected.\n" << endl;
		_address = address;
		_isConnected = true;
		daemonUp = true;
	} else {
		cout << "Connect failed.\n" << endl;
		_isConnected = false;
	}
}

void UI::handleDisConnect(void) {
	//cout << "disconnected\n" << endl;
	if(!_isConnected)
		return;

	sendData("LOGOUT");
	TcpClient::getInstance()->disConnect();
	cout << "Disconnected from " << _address.port << "@" << _address.host << ".\n" << endl;
	_isConnected = false;
	daemonUp = false;
}

void UI::handleName(void) {
	if(!_isConnected) {
		cout << "Please connected to the server first.\n" << endl;
		return;
	}
	//cout << "name\n" << endl;
	cout << "The host name is:" << endl;
	sendData("N\n");
}

void UI::handleTime(void) {
	if(!_isConnected) {
		cout << "Please connected to the server first.\n" << endl;
		return;
	}
	//cout << "time\n" << endl;
	cout << "The server's time is:" << endl;
	sendData("T\n");
}

void UI::handleList(void) {
	if(!_isConnected) {
		cout << "Please connected to the server first.\n" << endl;
		return;
	}
	//cout << "list\n" << endl;
	cout << "The clients list:" << endl;
	sendData("L\n");
}

void UI::handleSend(int id) {
	if(!_isConnected) {
		cout << "Please connected to the server first.\n" << endl;
		return;
	}
	//cout << "send to " << id << "\n" << endl;
	cout << "Enter the message to be send:" << endl;
	string tmp;
	getline(cin, tmp);

	stringstream dataStream;
	dataStream << "S " << id << " " << tmp << endl;
	sendData(dataStream.str());
}

void UI::handleQuit(void) {
	handleDisConnect();
	cout << "quit\n" << endl;
	_isFinished = true;
}

bool UI::sendData(string data) {
	if(TcpClient::getInstance()->sendData(data))
		return true;

	cout << "Send data failed.\n" << endl;
	return false;
}

DWORD WINAPI UI::daemon(LPVOID param) {
	while(daemonUp) {
		string data;
		if(TcpClient::getInstance()->recvData(data)) {
			cout << data;
		}
	}
	return 0;
}

bool UI::checkCmd(stringstream &ss) {
	string tmp;
	ss >> tmp;
	if(tmp == "")
		return true;
	else
		return false;
}

void UI::cmdError(void) {
	cout << "Syntax error.\n" << endl;
}