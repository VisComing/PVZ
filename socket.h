#pragma once
#include <string>
using namespace std;
#include <WinSock2.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")  //╪сть ws2_32.dll
const int BUF_SIZE = 1024;
class TCPSocket {
private:
	const string host = "123.56.111.64";
	const int port = 8634;
	string res;
	sockaddr_in sockAddr;
	SOCKET sock;
public:
	TCPSocket();
	void connectToServer();
	string readFromServer();
	void writeIntoServer(string);
	void closeConnection();
};