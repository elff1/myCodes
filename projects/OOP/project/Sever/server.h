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
	int login(char *buf);//处理登录请求
	int check(char *buf);//处理查看邮件请求
	int mail(char *buf);//处理发送邮件请求
	int sign_in(char *buf);//处理注册请求
	int delete_mail(char *buf);//处理删除邮件请求
	int modify(char *buf);//修改密码
	int attachment(char *buf);//发送附件
	int download(char *buf);//下载附件
};