#include "client.h"

mail a;
mail::mail(void)
{
	strcpy(user_name, "\0");
	strcpy(password, "\0");
	strcpy(receiver, "\0");
	strcpy(topic, "\0");
	strcpy(text, "\0");
	strcpy(attachment, "\0");
}

mail::~mail(void)
{
}

client::client(void)
{
	// 初始化 Winsock.
	int iResult = WSAStartup( MAKEWORD(2,2), &wsaData );
	if ( iResult != NO_ERROR );
		//cout<<"Error at WSAStartup()\n"<<endl;
	Client=SOCKET_ERROR;
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr( "127.0.0.1" );
	clientService.sin_port = htons( 27015 );
}

client::~client(void)
{
}

void client::ConnectToServer()
{
	// 连接到服务器.
	Client = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );//建立socket
	if ( connect( Client, (SOCKADDR*) &clientService, sizeof(clientService) ) == SOCKET_ERROR) {
		//cout<< "Failed to connect."<<endl;
		WSACleanup();
	}
	else ;//cout<<"Successfully connected! "<<endl;
}

void client::senddata(char sendbuf[Max_buf])
{
	//int bytesSent = send( Client, sendbuf, strlen(sendbuf), 0 );
	//QMessageBox::information(this, tr("Byte Number"), tr("%1").arg(bytesSent));
	string s1=base64_encode(reinterpret_cast<const unsigned char*>(sendbuf),strlen(sendbuf));
	strcpy(sendbuf,s1.c_str());
	int bytesSent = send( Client, sendbuf, strlen(sendbuf), 0 );

	if (bytesSent<0)  {
		//cout<<"Byte sent failed!    Client connection failed! "<<endl<<endl;
	}
	else {
		//cout<< "Bytes Sent: "<< bytesSent <<endl<<endl;
	}
}

void client::recvdata(char *recvbuf)
{
	SOCKET bytesRecv=SOCKET_ERROR;
	while( bytesRecv == SOCKET_ERROR ) {
		bytesRecv = recv( Client, recvbuf, Max_buf, 0 );
		if ( bytesRecv == 0 || bytesRecv == WSAECONNRESET ) {
			//cout<< "Connection Closed."<<endl;
			break;
		}
		else if (bytesRecv < 0){
			//cout<<"Receive nothing!!"<<endl;
			break;
		}
		else{
			//cout<< "Bytes Recv:"<< bytesRecv<<endl;
			//cout<<"the content is: "<<recvbuf<<endl<<endl;
			break;
		}		
	}
	string s1(recvbuf),s2;
	s2=base64_decode(s1);
	strcpy(recvbuf,s2.c_str());
	closesocket(Client);
}