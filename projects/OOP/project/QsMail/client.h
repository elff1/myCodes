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
	void ConnectToServer();	//���ӵ�������
	void senddata(char sendbuf[Max_buf]);//��sendbuf�е����ݷ��͵�������
	void recvdata(char recvbuf[Max_buf]);//���շ��������͹��������ݣ��ͻ�����senddata(),recvdata()��Ϊһ�η�Ӧ��
protected:                               //����������recvdata(),senddata()��Ϊһ�η�Ӧ��
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