#include "TcpClient.h"

TcpClient *TcpClient::instance = NULL;

TcpClient::TcpClient(void) {
	if(WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
		cout << "Error at WSAStartup()." << endl;
	isConnected = false;
}

TcpClient::~TcpClient(void) {
	WSACleanup();
}

bool TcpClient::connectServer(TcpAddress tcpAddress) {
	_socketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	_addrClient.sin_family = AF_INET;
	_addrClient.sin_addr.S_un.S_addr = inet_addr(tcpAddress.host.c_str());
	_addrClient.sin_port = htons(tcpAddress.port);

	isConnected = (connect(_socketClient, (SOCKADDR *)&_addrClient, sizeof(_addrClient)) == 0);
	return isConnected;
}

bool TcpClient::recvData(string &data) {
	memset(_recvBuf,0,sizeof(_recvBuf));
	if(recv(_socketClient, _recvBuf, 2000, 0) != SOCKET_ERROR) {
		data = _recvBuf;
		return true;
	}
	return false;
}

bool TcpClient::sendData(string data) {
	return (send(_socketClient, data.c_str(), data.length(), 0) == data.length());
}

void TcpClient::disConnect(void) {
	closesocket(_socketClient);
	isConnected = false;
}

TcpClient *TcpClient::getInstance(){

	if(instance == NULL)
		instance = new TcpClient;
	return instance;
}