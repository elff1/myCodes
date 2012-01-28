
#include <Winsock2.h>
#include <tchar.h>
#include "MusicMatch.h"
#include <iostream>
#include <string>
#include <fstream>
#pragma comment(lib,"ws2_32.lib")

#include <stdio.h>  


using namespace std;

int receive_file();
 MusicMatch match;
//
//int main(int argc, char** argv){
////	freopen("asd.txt","w",stdout);
//	if (argc==3)
//	{
//		cout<<"Wrong argument...\n"<<endl;
//		return 0;
//	}
//
//	//string temp_name = argv[1];
//	//string track_name = argv[2];
//	//cout<<temp_name<<" " << track_name<<endl;
//	MusicMatch match;
//	if (match.insert("alloutoflove.wav","alloutoflove")==false)
//	{
//	//	cout<<temp_name<<" "<<track_name<<endl<<"File not exists..."<<endl;
//		return 0;
//	}
//	;
//	cout<<"Finish inserting..."<<endl;
////	fclose(stdout);
//	return 0;
//} 
//
//int main(int argc, char** argv){
//
//	if (argc!=3)
//	{
//		cout<<"Wrong argument...\n"<<endl;
//		return 0;
//	}
//
//	string temp_name = argv[1];
//	string track_name = argv[2];
//	cout<<temp_name<<" " << track_name<<endl;
//	MusicMatch match;
//	if (match.insert(temp_name,track_name)==false)
//	{
//		cout<<temp_name<<" "<<track_name<<endl<<"File not exists..."<<endl;
//		return 0;
//	}
//	;
//	cout<<"Finish inserting..."<<endl;
//	return 0;
//}
//} 
//int receive_file();
//
int main (){
	 

//	while (1)
	{
	
		receive_file();
		return 0;
		//std::freopen("a.txt","w",stdout);
	//std::printf("等待输入音频源....\n");
// 	receive_file();
	//MusicMatch match;
//	freopen("a.txt","w",stdout);
	//std::map<int, double> pp = match.match("E:\\test.wav");
	//std::map<int, double>::iterator iter = pp.begin();
	/*for(;iter != pp.end();iter++)
	{
		std::cout<<iter->first<<" "<<iter->second<<endl;
	}*/
	}
}

/*
*socket 服务器端 
*/ 
int doOperation(string *result, char* file_path)
{
	match.initialize();
	std::map<int, double> pp = match.match(file_path,result );
	return 0;
};

int receive_file()
{
	 
	//初始化winsock 
	WSADATA wsaD;
	WSAStartup(MAKEWORD(1,1),&wsaD);
	//创建监听套接字
	SOCKET slisten=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); 
	// 绑定主机地址和监听套接字
	struct sockaddr_in my_addr;   //主机地址 
	my_addr.sin_family=AF_INET;
	my_addr.sin_port=htons(4321); //指定端口
	my_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	bind(slisten,(struct sockaddr *)&my_addr,sizeof(my_addr));
	//启动监听
	struct sockaddr_in c_addr;  //客户地址 
	int addr_len=sizeof(c_addr);

	listen(slisten,5);
	//开始接收数据
	SOCKET sconnect; //通过监听套接字创建连接套接字
	string result[10];
	char buf[64];
	memset(buf,0,64);
	int readsize = 0;
	//int len = recv(sconnect,buf,32,0);
	//readsize = atoi(buf);
	//cout<<readsize<<endl;
	int writesize = 0;
	while(true)
	{  
		memset(buf,0,64);
		cout<<"等待客户端请求..."<<endl;
		sconnect=accept(slisten,(struct sockaddr*)&c_addr,&addr_len); 
		int len=recv(sconnect,buf,64,0);  //通过连接套接字接收数据

		cout<<"File Name："<<buf<<endl;
		cout<<"收到查询请求，正在执行处理..."<<endl;
		int num = doOperation(result, buf);
		num = 10;
		cout<<"处理完毕，发送结果..."<<endl;
		string name ="10";
		int s = send(sconnect,name.c_str(),name.length(),0);
		send(sconnect,"\n",1,0);
		for (int i=0;i<num;i++)
		{
			s = send(sconnect,result[i].c_str(),result[i].length(),0);
			cout<<"output:"<<result[i].c_str()<<endl;
			send(sconnect,"\n",1,0);
		}
		cout<<"结果发送完毕..."<<endl;
	} 
	closesocket(sconnect);
	closesocket(slisten);
	WSACleanup();
 
	return 0;
} 










//
//
//int receive_file()
//{
//	fstream file("test.wav",ios::out|ios::binary);
//	//初始化winsock 
//	WSADATA wsaD;
//	WSAStartup(MAKEWORD(1,1),&wsaD);
//	//创建监听套接字
//	SOCKET slisten=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); 
//	// 绑定主机地址和监听套接字
//	struct sockaddr_in my_addr;   //主机地址 
//	my_addr.sin_family=AF_INET;
//	my_addr.sin_port=htons(4321); //指定端口
//	my_addr.sin_addr.s_addr=htonl(INADDR_ANY);
//	bind(slisten,(struct sockaddr *)&my_addr,sizeof(my_addr));
//	//启动监听
//	struct sockaddr_in c_addr;  //客户地址 
//	int addr_len=sizeof(c_addr);
//
//	listen(slisten,5);
//	//开始接收数据
//	SOCKET sconnect=accept(slisten,(struct sockaddr*)&c_addr,&addr_len); //通过监听套接字创建连接套接字
//	char data[1024]; //存储接收的字符
//	char buf[32];
//	memset(buf,0,32);
//	int readsize = 0;
//	int len = recv(sconnect,buf,32,0);
//	readsize = atoi(buf);
//	cout<<readsize<<endl;
//	int writesize = 0;
//	while(true)
//	{  
//		int len=recv(sconnect,data,1024,0);  //通过连接套接字接收数据
//		file.write(data,len);
//		writesize += len;
//		if(writesize == readsize)
//			break;
//	}
//	file.close();
//
//	string name = "i love you";
//	int s = send(sconnect,name.c_str(),name.length(),0);
//	cout<<"done"<<endl;
//
//	closesocket(sconnect);
//	closesocket(slisten);
//	WSACleanup();
//
//	return 0;
//} 