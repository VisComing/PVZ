#pragma once
#include <string>
using namespace std;
#include <WinSock2.h>
#include <windows.h>
#include <mutex>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll
const int BUF_SIZE = 1024;
class TCPSocket {
private:
	const string host = "192.168.3.9";
	const int port = 8000;
	string res;
	sockaddr_in sockAddr;
	SOCKET sock;
	static TCPSocket * tcpSocket_;
	static std::mutex mutex_;
	static std::mutex mutex_read;
	static std::mutex mutex_write;
protected:
	TCPSocket();
	~TCPSocket() {}
public:
	TCPSocket(TCPSocket &other) = delete;
	void operator=(const TCPSocket &) = delete;
	static TCPSocket *getInstance();
	int connectToServer();//返回0表示连接成功，返回-1表示连接失败，阻塞
	string readFromServer();//返回空串或者句子或者error字符串
	void writeIntoServer(string);
	void closeConnection();
};