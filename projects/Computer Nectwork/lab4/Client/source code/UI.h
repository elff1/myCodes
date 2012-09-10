#ifndef __UI_H
#define __UI_H

#include <iostream>
#include <string>
#include <sstream>
#include "TcpClient.h"
#include <Windows.h>

using namespace std;

class UI {
public:
	UI(void);
	~UI(void);
	void handle(string cmd);
	bool finished(void);
private:
	bool _isFinished;
	bool _isConnected;
	TcpAddress _address;
	static bool daemonUp;

	void handleConnect(TcpAddress address);
	void handleDisConnect(void);
	void handleName(void);
	void handleTime(void);
	void handleList(void);
	void handleSend(int id);
	void handleQuit(void);
	bool sendData(string data);
	static DWORD WINAPI daemon(LPVOID param);

	bool checkCmd(stringstream &ss);
	void cmdError(void);
};

#endif