#include <iostream>
#include <string>
#include "base64.h"
using namespace std;

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#pragma once
#define Max_buf 10240

class client
{
public:
	client(void);
	~client(void);
	void ConnectToServer();	//连接到服务器
	void senddata(char sendbuf[Max_buf]);//将sendbuf中的内容发送到服务器
	void recvdata(char recvbuf[Max_buf]);//接收服务器发送过来的内容，客户端以senddata(),recvdata()作为一次反应。
protected:                               //而服务器以recvdata(),senddata()作为一次反应。
	WSADATA wsaData;
	SOCKET Client;
	sockaddr_in clientService;
	char reg_name[30], reg_password[30];
};

class mail
{
public:
	mail();
	~mail();
	char user_name[30], password[30], sender[30], receiver[30], topic[80], text[Max_buf], attachment[30], datatime[30], mark[1], num[9];
};