#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "socket.h"

TCPSocket* TCPSocket::tcpSocket_{ nullptr };
std::mutex TCPSocket::mutex_;
std::mutex TCPSocket::mutex_read;
std::mutex TCPSocket::mutex_write;
TCPSocket::TCPSocket()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(host.c_str());
	sockAddr.sin_port = htons(port);
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
}

TCPSocket * TCPSocket::getInstance()
{
	std::lock_guard<std::mutex> lock(mutex_);//在作用域中持续拥有该互斥体，控制离开作用域时，自动释放互斥量
	if (tcpSocket_ == nullptr)
	{
		tcpSocket_ = new TCPSocket();
	}
	return tcpSocket_;
}

int TCPSocket::connectToServer()
{
	return connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));//成功返回0，失败返回-1
}

string TCPSocket::readFromServer()//返回的一定是完整的数据包，或者是个空串
{
	std::lock_guard<std::mutex> lock(mutex_read);
	unsigned long bytesToRecv;
	if (ioctlsocket(sock, FIONREAD, &bytesToRecv) == 0)
	{
		if (bytesToRecv == 0)//缓冲区中没有数据
		{
			return "";
		}
		else
		{
			string ans;
			char ch[BUF_SIZE];
			int len = recv(sock, ch, BUF_SIZE, 0);
			for (int i = 0; i < len; i++) res += ch[i];
			for (size_t i = 0; i < res.size(); i++)
			{
				if (res[i] == '\n')
				{
					res = res.substr(i + 1, res.size() - i);
					break;
				}
				else
				{
					ans += res[i];
				}
			}
			return ans;
		}
	}
	else
	{
		return "error";
	}
}

void TCPSocket::writeIntoServer(string message)
{
	std::lock_guard<std::mutex> lock(mutex_write);
	send(sock, message.c_str(), message.size(), 0);
}

void TCPSocket::closeConnection()
{
	closesocket(sock);
	WSACleanup();
}
