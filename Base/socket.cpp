#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "socket.h"
#include "cocos2d.h"
USING_NS_CC;
TCPSocket* TCPSocket::tcpSocket_{ nullptr };
std::mutex TCPSocket::mutex_;
std::mutex TCPSocket::mutex_read;
std::mutex TCPSocket::mutex_write;
TCPSocket::TCPSocket()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(host.c_str());
	sockAddr.sin_port = htons(port);
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
}

TCPSocket * TCPSocket::getInstance()
{
	std::lock_guard<std::mutex> lock(mutex_);//���������г���ӵ�иû����壬�����뿪������ʱ���Զ��ͷŻ�����
	if (tcpSocket_ == nullptr)
	{
		tcpSocket_ = new TCPSocket();
	}
	return tcpSocket_;
}

int TCPSocket::connectToServer()
{
	return connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));//�ɹ�����0��ʧ�ܷ���-1
}

string TCPSocket::readFromServer()//���ص�һ�������������ݰ��������Ǹ��մ�
{
	std::lock_guard<std::mutex> lock(mutex_read);
	unsigned long bytesToRecv;
	if (ioctlsocket(sock, FIONREAD, &bytesToRecv) == 0)
	{
		if (bytesToRecv != 0)//��������������ݣ���ô�����ݶ�����
		{
			char ch[BUF_SIZE];
			int len = recv(sock, ch, BUF_SIZE, 0);
			for (int i = 0; i < len; i++) res += ch[i];
		}
		string ans;//����res�е�����
		for (size_t i = 0; i < res.size(); i++)
		{
			if (res[i] == '\n')//�����˵�һ��\n��������res��ʼ������һ�������ľ���
			{
				res = res.substr(i + 1);
				return ans;
			}
			else
			{
				ans += res[i];
			}
		}

		return "";
	}
	else
	{
		return "error";
	}
}

void TCPSocket::writeIntoServer(string message)
{
	std::lock_guard<std::mutex> lock(mutex_write);
	int res = send(sock, message.c_str(), message.size(), 0);
	if (res < 0)
	{
		log("socket send error!");
	}
}

void TCPSocket::closeConnection()
{
	closesocket(sock);
	WSACleanup();
}
