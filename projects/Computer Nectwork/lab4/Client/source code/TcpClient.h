#ifndef __TCPCLIENT_H
#define __TCPCLIENT_H

#include <iostream>
#include <string>
#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

typedef struct _TcpAddress TcpAddress;
struct _TcpAddress {
	string host;
	int port;
};

class TcpClient{
public:
	TcpClient(void);
	~TcpClient(void);
	
	static TcpClient *getInstance();
	bool connectServer(TcpAddress tcpAddress);
	bool recvData(string &data);
	bool sendData(string data);
	void disConnect(void);
	bool isConnected;

private:
	static TcpClient *instance;
	SOCKET _socketClient;
	SOCKADDR_IN _addrClient;
	WSADATA wsaData;
	char _recvBuf[1000];
};

#endif