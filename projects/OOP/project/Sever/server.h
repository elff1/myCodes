#include <iostream>
using namespace std;

#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#include <string>

#include "Mysocket.h"

#define Max_buf 10240
#pragma once

class server:public Mysocket
{
public:
	int login(char *buf);//�����¼����
	int check(char *buf);//����鿴�ʼ�����
	int mail(char *buf);//�������ʼ�����
	int sign_in(char *buf);//����ע������
	int delete_mail(char *buf);//����ɾ���ʼ�����
	int modify(char *buf);//�޸�����
	int attachment(char *buf);//���͸���
	int download(char *buf);//���ظ���
};