#include <iostream>
using namespace std;

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include "base64.h"

#pragma once

#define Max_buf 10240

class Mysocket
{
public:
	Mysocket();
	~Mysocket();
	string GetIP();//得到客户端IP
	void AcceptConnect();//接收客户端连接
	void senddata(char *sendbuf);//发送数据
	void recvdata(char *recvbuf);//接收数据
protected:
	WSADATA wsaData; 
	SOCKET Server; 
	sockaddr_in service; 
	SOCKET AcceptSocket;
};