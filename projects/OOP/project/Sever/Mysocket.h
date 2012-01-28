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
	string GetIP();//�õ��ͻ���IP
	void AcceptConnect();//���տͻ�������
	void senddata(char *sendbuf);//��������
	void recvdata(char *recvbuf);//��������
protected:
	WSADATA wsaData; 
	SOCKET Server; 
	sockaddr_in service; 
	SOCKET AcceptSocket;
};