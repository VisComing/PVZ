#pragma once

#include <iostream>
#include <WinSock2.h>
using namespace std;

const int PORT = 8000;
const int BUFSIZE = 1024;
const int STRSIZE = 128;
const int PARAMSIZE = 10;

typedef struct _client 
{
	SOCKET cSocket;		/*�ͻ����׽���*/
	unsigned int id;		/*�ͻ������*/
	char IP[20];			/*�ͻ���IP*/
	unsigned short port;

	DWORD threadId;

	char username[STRSIZE];

	int flag;

	struct _client* next;
}Client;

typedef struct _request 
{
	char type[STRSIZE];
	char param[PARAMSIZE][STRSIZE];
}Request;

typedef struct _match 
{
	Client* client[2];
	DWORD id[2];
}Match;

int thpoolMain();
void jobCreate(int( *function)(void*), void* arg);