#include "Mysocket.h"

Mysocket::Mysocket()
{
	Server=SOCKET_ERROR; 
	AcceptSocket=SOCKET_ERROR;
	// 初始化 
	int iResult = WSAStartup( MAKEWORD(2,2), &wsaData ); 
	if ( iResult != NO_ERROR ) 
		cout<<"Error at WSAStartup()"<<endl; 

	// 建立socket 
	Server = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP ); 

	if ( Server == INVALID_SOCKET ) { 
		cout<< "Error at socket(): "<< WSAGetLastError()<<endl; 
		WSACleanup(); 
		return; 
	} 

	// 绑定socket 
	service.sin_family = AF_INET; 
	service.sin_addr.s_addr = INADDR_ANY; 
	service.sin_port = htons( 27015 ); 
	service.sin_family = AF_INET; 
	service.sin_addr.s_addr = INADDR_ANY; 
	service.sin_port = htons( 27015 ); 

	if ( bind( Server, (SOCKADDR*) &service, sizeof(service) ) == SOCKET_ERROR ) { 
		cout<< "bind() failed."<<endl; 
		closesocket(Server); 
		return; 
	} 

	// 监听 socket 
	if ( listen( Server, 5 ) == SOCKET_ERROR ) 
		cout<< "Error listening on socket."<<endl; 
}
Mysocket::~Mysocket()
{

}
//接受连接
void Mysocket::AcceptConnect(){
	cout<< "Waiting for a client to connect..."<<endl; 
	while (1) { 
		AcceptSocket = SOCKET_ERROR; 
		while ( AcceptSocket == SOCKET_ERROR ) { 
			AcceptSocket = accept( Server, NULL, NULL ); 
		} 
		cout<< "Client Connected."<<endl; 
		string s=GetIP();
		cout<<"Client IP is: "<<s.c_str()<<endl;
		break; 
	} 

}

//发送数据
void Mysocket::senddata(char *sendbuf){
	int bytesSent=0; 
	string s1;
	cout<< "Bytes Sent: "<< bytesSent <<endl<<endl;
	s1=base64_encode(reinterpret_cast<const unsigned char*>(sendbuf),strlen(sendbuf));
	strcpy(sendbuf,s1.c_str());
	bytesSent = send( AcceptSocket, sendbuf, strlen(sendbuf), 0 ); 
	if (bytesSent<0)  {
		closesocket(AcceptSocket);
		AcceptSocket=SOCKET_ERROR;
		cout<<"Byte sent failed!    Client connection failed! "<<endl<<endl;
	}
	else {
		closesocket(AcceptSocket);
		AcceptSocket=SOCKET_ERROR;
	}
}

//接收数据
void Mysocket::recvdata(char *recvbuf){
	int bytesRecv=0; 
	bytesRecv = recv( AcceptSocket, recvbuf, Max_buf, 0 );
	string s1(recvbuf),s2;
	s2=base64_decode(s1);
	strcpy(recvbuf,s2.c_str());
	cout<< "Bytes Recv: "<< bytesRecv <<endl;
	//cout<< "Client asking: "<< recvbuf <<endl;
}

//获得接口的IP
string Mysocket::GetIP(){              
	SOCKADDR_IN   remote_addr; 
	string strIP;
	int   remote_addr_len	=   sizeof(remote_addr); 

	unsigned long uIp;
	if(SOCKET_ERROR!=getpeername(AcceptSocket,(SOCKADDR*)&remote_addr,&remote_addr_len)) 
	{ 
		uIp=remote_addr.sin_addr.s_addr;  
	} 

	in_addr addr;    
	memcpy(&addr, &uIp, sizeof(uIp));    
	strIP = inet_ntoa(addr);    
	return strIP;
}