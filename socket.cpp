#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "socket.h"

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

void TCPSocket::connectToServer()
{
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
}

string TCPSocket::readFromServer()//返回的一定是完整的数据包，或者是个空串
{
	unsigned long bytesToRecv;
	if (ioctlsocket(sock, FIONREAD, &bytesToRecv) == 0)
	{
		if (bytesToRecv == 0)//缓冲区中没有数据
			return "";
		else
		{
			string ans;
			char ch[BUF_SIZE];
			int len = recv(sock, ch, BUF_SIZE, 0);
			for (int i = 0; i < len; i++) res += ch[i];
			for (int i = 0; i < res.size(); i++)
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
}

void TCPSocket::writeIntoServer(string message)
{
	send(sock, message.c_str(), message.size(), 0);
}

void TCPSocket::closeConnection()
{
	closesocket(sock);
	WSACleanup();
}
