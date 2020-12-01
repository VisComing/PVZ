#pragma once

#include <iostream>
#include <sys/socket.h>
using namespace std;

const int PORT = 18000;			/*socket通信端口*/
const int BUFSIZE = 1024;		/*缓冲区最大长度*/
const int STRSIZE = 128;		/*数组最大胀肚*/
const int PARAMSIZE = 10;		/*请求参数最大数量*/
const int PLAYERSIZE = 2;		/*参与一局游戏的玩家数量*/

typedef struct sockaddr_in SOCKADDR_IN;
typedef int SOCKET;
typedef struct sockaddr SOCKADDR;

typedef struct _client 
{
	SOCKET cSocket;			/*客户端socket*/
	unsigned int id;		/*客户端id*/
	char IP[20];			
	unsigned short port;

	char buf[BUFSIZE];		/*客户端接收缓冲区*/

	//DWORD threadId;

	char username[STRSIZE];	/*客户端当前登录的用户名*/
		
	int flag;				/*游戏匹配状态*/

	struct _client* next;
}Client;

typedef struct _request 
{
	char type[STRSIZE];
	char param[PARAMSIZE][STRSIZE];
}Request;

typedef struct _match 
{
	Client* client[PLAYERSIZE];
	//DWORD id[2];
}Match;

int thpoolMain();
void jobCreate(int( *function)(void*), void* arg);