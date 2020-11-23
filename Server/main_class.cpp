/* 2020.11.17
��ǰ���⣺
1.�̳߳أ�
��Ҫ�޸ģ�
1.��װ����class_recv
*/

#include <iostream>
#include <cstdio>
#include <WinSock2.h>
#include "head.h" 
#include <process.h>
#include "sqlite3.h"
#include <thread>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

static class Server 
{
	private:
		/*ȫ�ֱ���*/
		Client* head;
		unsigned int clientTot = 0;
		Match match;
		HANDLE mutexMatch;
		HANDLE mutexDb;
		HANDLE mutexLinklist;

		/*socketͨ�����ȫ�ֱ���*/
		WSADATA wsaData;
		SOCKET serverSocket;
		SOCKADDR_IN socketAddr;
		SOCKADDR_IN clientAddr;
		int clientAddrLen;

		/*���ݿ����ȫ�ֱ���*/
		sqlite3* db = NULL;
	
		void handleRequest(char* rbuf, Client* this_clientP);
		Request analysisRequest(char* hbuf);
		void waitMatch(Client* this_client);
		void xferMatchData(Client* this_client, Client* oppo_client);
		int recv_line1(SOCKET s, char* buf, int len, int flags);
		int recvLine(SOCKET s, char* buf, int len, int flags);
		int endLine(char* buf, int len);
		int dbOpen();
		int dbLogin(char* username, char* password);
		int dbRegister(char* username, char* password);
		void dbClose();
		int isOnline(char* username);

		unsigned __stdcall threadAccept(void* param);
		unsigned __stdcall threadServer(void* param);
		unsigned __stdcall threadMatching(void* param);

	public:
		int serverMain();
};

int main() 
{
	Server server;
	server.serverMain();
	return 0;
}

int Server::serverMain() 
{
	match.client[0] = NULL;
	match.client[1] = NULL;
	match.id[0] = 0;
	match.id[1] = 0;

	mutexMatch = CreateSemaphore(NULL, 1, 1, "mutex_match");
	mutexDb = CreateSemaphore(NULL, 1, 1, "mutex_db");
	mutexLinklist = CreateSemaphore(NULL, 1, 1, "mutex_linklist");

	head = (Client*)malloc(sizeof(Client));
	head->next = NULL;

	int result = dbOpen();
	if (!result) 
	{
		cout << "opening database failed" << endl;
	}
	
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	socketAddr.sin_family = AF_INET;
	socketAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	socketAddr.sin_port = htons(PORT);

	int n = ::bind(serverSocket, (LPSOCKADDR)&socketAddr, sizeof(socketAddr));
	if (n == SOCKET_ERROR) 
	{
		cout << "�˿ڰ�ʧ�ܣ�" << endl;
		return -1;
	}
	else 
	{
		cout << "�˿ڰ󶨳ɹ���" << PORT << endl;
	}
	int l = listen(serverSocket, 100);

	clientAddrLen = sizeof(clientAddr);

	_beginthreadex(NULL, 0, threadAccept, NULL, 0, 0);
	/*thread t(&Server::threadAccept, this);
	t.detach();*/
	
	while (1) 
	{
		Sleep(1000);
	}
}

unsigned __stdcall Server::threadAccept(void* param)
{
	while (1) 
	{
		Client* clientP = (Client*)malloc(sizeof(Client));	
		clientP->cSocket = accept(serverSocket, (SOCKADDR*)&clientAddr, &clientAddrLen);
		clientTot++;

		memcpy(clientP->IP, inet_ntoa(clientAddr.sin_addr), sizeof(clientP->IP));
		clientP->id = (char)clientTot;
		clientP->port = htons(clientAddr.sin_port);
		clientP->flag = 0;
		memset(clientP->username, 0, STRSIZE);

		WaitForSingleObject(mutexLinklist, INFINITE);
		clientP->next = head->next;
		head->next = clientP;
		ReleaseSemaphore(mutexLinklist, 1, NULL);

		_beginthreadex(NULL, 0, threadServer, clientP, 0, 0);
		/*thread t(&Server::threadServer, clientP, this);
		t.detach();*/

		cout << "------------------------------------------------" << endl;
		cout << "Socket:" << clientP->cSocket << " | IP:" << clientP->IP << " | Port:" << clientP->port << endl;
		cout << "[ACCEPT]" << endl;
		cout << "�ͻ�����������������" << endl;
	}
}

unsigned __stdcall Server::threadServer(void* param)
{
	Client* thisClient = (Client*)param;
	thisClient->threadId = _getpid();
	char rbuf[BUFSIZE];
	char sbuf[BUFSIZE];
	
	while (1) 
	{
		memset(rbuf, 0, BUFSIZE);
		int rbyte = recvLine(thisClient->cSocket, rbuf, sizeof(rbuf), 0);
		cout << "------------------------------------------------" << endl;
		cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
		printf("[RECV]\n");
		printf("len: %d\n", rbyte);
		printf("buf: %s\n", rbuf);
		if (rbyte > 0) 
		{
			handleRequest(rbuf, thisClient);		
		}
		else 
		{
			break;
		}
	}
	
	closesocket(thisClient->cSocket);
	cout << "------------------------------------------------" << endl;
	cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
	cout << "[CLOSE]" << endl;
	cout << "�ͻ����ѶϿ�����" << endl;

	memset(thisClient->username, 0, STRSIZE);
	WaitForSingleObject(mutexMatch, INFINITE);
	if (thisClient == match.client[0]) 
	{
		match.client[0] = NULL;
		match.id[0] = 0;
	}
	if (thisClient == match.client[1]) 
	{
		match.client[1] = NULL;
		match.id[1] = 0;
	}

	Client* temp = NULL;
	WaitForSingleObject(mutexLinklist, INFINITE);
	for (temp = head; temp->next != thisClient; temp = temp->next);
	temp->next = temp->next->next;
	ReleaseSemaphore(mutexLinklist, 1, NULL);
	free(thisClient);
	
	return 0;
}

void Server::handleRequest(char* rbuf, Client* thisClient)
{
	char sbuf[BUFSIZE];
	char hbuf[BUFSIZE];
	memset(sbuf, 0, BUFSIZE);
	memset(hbuf, 0, BUFSIZE);
	memcpy(hbuf, rbuf, BUFSIZE);
	Request request = analysisRequest(hbuf);
	cout << "------------------------------------------------" << endl;
	cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
	cout << "[HANDLE REQUEST]" << endl;
	if (0 == strcmp("REGISTER", request.type)) 
	{	
		cout << "request: ע�� | ";
		cout << "�û�����" << request.param[0] << " | ���룺" << request.param[1] << endl;
		int result = dbRegister(request.param[0], request.param[1]);
		if (1 == result) 
		{
			memset(sbuf, 0, BUFSIZE);
			memcpy(sbuf, "REGISTER;1;\n", strlen("REGISTER;1;\n"));
			cout << "reply: ע��ɹ���" << endl;
		}
		else 
		{
			memset(sbuf, 0, BUFSIZE);
			memcpy(sbuf, "REGISTER;0;\n", strlen("REGISTER;0;\n"));
			cout << "ע��ʧ��" << endl;
		}
		int sbyte = send(thisClient->cSocket, sbuf, strlen(sbuf), 0);
		cout << "------------------------------------------------" << endl;
		cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
		printf("[SEND]\n");
		printf("len: %d\n", sbyte);
		printf("buf: %s\n", sbuf);
	}
	else if (0 == strcmp("LOGIN", request.type)) 
	{
		cout << "�û�����" << request.param[0] << " | ���룺" << request.param[1] << endl;
		int result = dbLogin(request.param[0], request.param[1]);
		int online = isOnline(request.param[0]);
		if (0 == strcmp("", thisClient->username) && 0 == online && 1 == result)
		{
			memcpy(thisClient->username, request.param[0], STRSIZE);
			memset(sbuf, 0, BUFSIZE);
			memcpy(sbuf, "LOGIN;1;\n", strlen("LOGIN;1;\n"));
			cout << "��¼�ɹ���" << endl;
		}
		else 
		{
			memset(sbuf, 0, BUFSIZE);
			memcpy(sbuf, "LOGIN;0;\n", strlen("LOGIN;0;\n"));
			cout << "��¼ʧ��" << endl;
		}
		int sbyte = send(thisClient->cSocket, sbuf, strlen(sbuf), 0);
		cout << "------------------------------------------------" << endl;
		cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
		printf("[SEND]\n");
		printf("len: %d\n", sbyte);
		printf("buf: %s\n", sbuf);
	}
	else if (0 == strcmp("MATCH", request.type)) 
	{
		cout << "[MATCH]" << endl;
		cout << "����ƥ��..." << endl;
		waitMatch(thisClient);
	}
	else 
	{
		cout << "wrong request:" << request.type << endl;
		return;
	}
}

Request Server::analysisRequest(char* hbuf)
{
	Request result;
	memset(result.type, 0, STRSIZE);
	memset(result.param, 0, PARAMSIZE * STRSIZE);
	int k = 0;
	for (int i = 0; ';' != hbuf[k] && i < STRSIZE; i++, k++) 
	{
		result.type[i] = hbuf[k];
	}
	k++;
	for (int i = 0; '\n' != hbuf[k] && i < PARAMSIZE; i++, k++) 
	{
		for (int j = 0; ';' != hbuf[k] && j < STRSIZE; j++, k++) 
		{
			result.param[i][j] = hbuf[k];
		}
	}
	return result;
}

void Server::waitMatch(Client* thisClient)
{
	DWORD thisId = GetCurrentThreadId();
	Client* oppoClient = NULL;
	DWORD oppoId = 0;
	char sbuf[BUFSIZE];
	char rbuf[BUFSIZE];
	memset(sbuf, 0, BUFSIZE);
	memset(rbuf, 0, BUFSIZE);
	while (1) 
	{
		WaitForSingleObject(mutexMatch, INFINITE);
		if (2 == thisClient->flag) 
		{
			thisClient->flag = 0;
			ReleaseSemaphore(mutexMatch, 1, NULL);
			return;
		}
		if (NULL == match.client[0] && NULL == match.client[1]) 
		{
			cout << "------------------------------------------------" << endl;
			cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
			cout << "[MATCH]" << endl;
			cout << "�û�" << thisClient->cSocket << "�Ѽ��룬���ڵȴ�����..." << endl;
			match.client[0] = thisClient;
			match.id[0] = thisId;
			thisClient->flag = 1;
			_beginthreadex(NULL, 0, threadMatching, thisClient, 0, 0);
			/*thread t(&Server::threadAccept, thisClient, this);
			t.detach();*/
		}
		else if (NULL != match.client[0] && NULL == match.client[1] && thisClient != match.client[0]) 
		{
			cout << "------------------------------------------------" << endl;
			cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
			cout << "[MATCH]" << endl;
			cout << "�û�" << thisClient->cSocket << "�Ѽ��룬�����������..." << endl;
			thisClient->flag = 0;
			oppoClient = match.client[0];
			oppoId = match.id[0];
			match.client[0] = NULL;
			match.id[0] = 0;
			match.client[1] = thisClient;
			match.id[1] = thisId;
			ReleaseSemaphore(mutexMatch, 1, NULL);
			xferMatchData(thisClient, oppoClient);
			cout << "------------------------------------------------" << endl;
			cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
			cout << "[MATCH]" << endl;
			cout << "�����������û�" << thisClient->cSocket << "���˳�" << endl;
			return;
		}
		else if (NULL == match.client[0] && NULL != match.client[1] && thisClient != match.client[1]) 
		{
			cout << "------------------------------------------------" << endl;
			cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
			cout << "[MATCH]" << endl;
			cout << "�û�" << thisClient->cSocket << "��ȷ�ϣ�������ʼ��" << endl;
			thisClient->flag = 0;
			oppoClient = match.client[1];
			oppoId = match.id[1];
			match.client[1]= NULL;
			match.id[1] = 0;
			ReleaseSemaphore(mutexMatch, 1, NULL);
			memset(sbuf, 0, BUFSIZE);
			memcpy(sbuf, "MATCHSUCCESS;0;\n", BUFSIZE);
			int sbyte = send(thisClient->cSocket, sbuf, strlen(sbuf), 0);
			cout << "------------------------------------------------" << endl;
			cout << "Socket:" << oppoClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
			cout << "[SEND][MATCH] match data" << endl;
			printf("len: %d\n", sbyte);
			printf("buf: %s\n", sbuf);
			memset(sbuf, 0, BUFSIZE);
			memcpy(sbuf, "MATCHSUCCESS;1;\n", BUFSIZE);
			sbyte = send(oppoClient->cSocket, sbuf, strlen(sbuf), 0);
			cout << "------------------------------------------------" << endl;
			cout << "Socket:" << oppoClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
			cout << "[SEND][MATCH] match data" << endl;
			printf("len: %d\n", sbyte);
			printf("buf: %s\n", sbuf);
			xferMatchData(thisClient, oppoClient);
			cout << "------------------------------------------------" << endl;
			cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
			cout << "[MATCH]" << endl;
			cout << "�����������û�" << thisClient->cSocket << "���˳�" << endl;
			return;
		}
		else
		{
		}
		ReleaseSemaphore(mutexMatch, 1, NULL);
	}	
}

void Server::xferMatchData(Client* thisClient, Client* oppoClient)
{
	char rbuf[BUFSIZE];
	char sbuf[BUFSIZE];
	memset(rbuf, 0, BUFSIZE);
	memset(sbuf, 0, BUFSIZE);
	while (1) 
	{
		memset(rbuf, 0, BUFSIZE);
		int rbyte = recvLine(thisClient->cSocket, rbuf, BUFSIZE, 0);
		if (rbyte > 0) 
		{
			cout << "------------------------------------------------" << endl;
			cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
			cout << "[RECV][MATCH] match data" << endl;
			printf("len: %d\n", rbyte);
			printf("buf: %s\n", rbuf);
			if (0 == strcmp("WIN;\n", rbuf)) 
			{
				memset(sbuf, 0, BUFSIZE);
				memcpy(sbuf, "WIN;\n", BUFSIZE);
				int sbyte = send(thisClient->cSocket, sbuf, strlen(sbuf), 0);
				cout << "------------------------------------------------" << endl;
				cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
				cout << "[SEND][MATCH] match data" << endl;
				printf("len: %d\n", sbyte);
				printf("buf: %s\n", sbuf);
				memset(sbuf, 0, BUFSIZE);
				memcpy(sbuf, "LOSE;\n", BUFSIZE);
				sbyte = send(oppoClient->cSocket, sbuf, strlen(sbuf), 0);
				cout << "------------------------------------------------" << endl;
				cout << "Socket:" << oppoClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
				cout << "[SEND][MATCH] match data" << endl;
				printf("len: %d\n", sbyte);
				printf("buf: %s\n", sbuf);
				return;
			}
			else if (0 == strcmp("LOSE;\n", rbuf)) 
			{
				return;
			}
			else 
			{
				memset(sbuf, 0, BUFSIZE);
				memcpy(sbuf, rbuf, BUFSIZE);
				int sbyte = send(oppoClient->cSocket, sbuf, strlen(sbuf), 0);
				cout << "------------------------------------------------" << endl;
				cout << "Socket:" << oppoClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
				cout << "[SEND][MATCH] match data" << endl;
				printf("len: %d\n", sbyte);
				printf("buf: %s\n", sbuf);
			}
		}
		else 
		{
			cout << "recv error, socket:" << thisClient->cSocket << endl;
			return;
		}
	}
}

unsigned __stdcall Server::threadMatching(void* param)
{
	Client* thisClient = (Client*)param;
	char rbuf[BUFSIZE];
	while (1) 
	{
		if (1 != thisClient->flag) 
		{
			return 0;
		}
		memset(rbuf, 0, BUFSIZE);
		int rbyte = recvLine(thisClient->cSocket, rbuf, sizeof(rbuf), MSG_PEEK);
		if (rbyte > 0) 
		{
			if (0 == strcmp(rbuf, "CANCELMATCH;\n")) 
			{
				rbyte = recvLine(thisClient->cSocket, rbuf, sizeof(rbuf), 0);
				cout << "------------------------------------------------" << endl;
				cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
				cout << "[RECV][MATCH]" << endl;
				printf("len: %d\n", rbyte);
				printf("buf: %s\n", rbuf);
				WaitForSingleObject(mutexMatch, INFINITE);
				if (match.client[0] == thisClient && match.client[1] == NULL) 
				{
					match.client[0] = NULL;
					thisClient->flag = 2;
					cout << "------------------------------------------------" << endl;
					cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
					cout << "[MATCH]" << endl;
					cout << "�û�" << thisClient->cSocket << "ȡ����ƥ�䣡" << endl;
				}
				ReleaseSemaphore(mutexMatch, 1, NULL);
				return 1;
			}
			else 
			{
				return 0;
			}
		}
		else 
		{
			return 0;
		}
	}
}

int Server::dbOpen()
{
	int result = sqlite3_open("user.db", &db);
	char** errmsg = NULL;
	if (SQLITE_OK == result) 
	{
		sqlite3_exec(db, "create table if not exists user(username text primary key, password text not null)", 0, 0, errmsg);
		return 1;
	}
	else 
	{
		cout << "database open wrong" << endl;
		return 0;
	}
}

int Server::dbLogin(char* username, char* password)
{
	char sql[STRSIZE];
	memset(sql, 0, STRSIZE);
	sprintf(sql, "select username from user where username == \"%s\" and password == \"%s\"", username, password);
	char** dbresult;
	int row = -1, col = -1;
	char** errmsg = NULL;
	WaitForSingleObject(mutexDb, INFINITE);
	int result = sqlite3_get_table(db, sql, &dbresult, &row, &col, errmsg);
	ReleaseSemaphore(mutexDb, 1, NULL);
	if (SQLITE_OK != result) 
	{
		cout << "database select wrong" << endl;
		cout << errmsg << endl;
		return -1;
	}
	if (row > 0) 
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

int Server::dbRegister(char* username, char* password)
{
	char sql[STRSIZE];
	memset(sql, 0, STRSIZE);
	sprintf(sql, "select username from user where username == \"%s\"", username);
	char** dbresult;
	int row = -1, col = -1;
	char** errmsg = NULL;
	WaitForSingleObject(mutexDb, INFINITE);
	int result = sqlite3_get_table(db, sql, &dbresult, &row, &col, errmsg);
	ReleaseSemaphore(mutexDb, 1, NULL);
	if (SQLITE_OK != result) 
	{
		cout << "database select wrong" << endl;
		cout << errmsg << endl;
		return -1;
	}
	if (row == 0) 
	{
		memset(sql, 0, STRSIZE);
		sprintf(sql, "insert into user(username, password) values(\"%s\", \"%s\")", username, password);
		char** dbresult;
		WaitForSingleObject(mutexDb, INFINITE);
		result = sqlite3_exec(db, sql, 0, 0, errmsg);
		ReleaseSemaphore(mutexDb, 1, NULL);
		if (SQLITE_OK != result) 
		{
			cout << "database exec wrong" << endl;
			cout << errmsg << endl;
			return -1;
		}
		return 1;
	}
	else 
	{
		return 0;
	}
}

void Server::dbClose()
{
	sqlite3_close(db);
}

int Server::recv_line1(SOCKET s, char* buf, int len, int flags)
{
	int rbyte = recv(s, buf, len, MSG_PEEK);
	if (rbyte > 0) 
	{
		while (!endLine(buf, len)) 
		{
			int rbyte = recv(s, buf, len, MSG_PEEK);
		}
		rbyte = recv(s, buf, len, flags);	
	}
	return rbyte;
}

int Server::recvLine(SOCKET s, char* buf, int len, int flags) {
	int rbyte = recv(s, buf, len, flags);
	if (rbyte > 0) {
		if (0 == flags) 
		{
			while (!endLine(buf, len)) 
			{
				int temp = recv(s, buf, len - rbyte, flags);
				rbyte += len;
			}
		}
		else 
		{
			while (!endLine(buf, len)) 
			{
				int temp = recv(s, buf, len, flags);
				rbyte += len;
			}
		}
	}
	return rbyte;
}

int Server::endLine(char* buf, int len)
{
	for (int i = 0; i < len; i++) 
	{
		if ('\n' == buf[i]) 
		{
			return 1;
		}
	}
	return 0;
}

int Server::isOnline(char* username)
{
	WaitForSingleObject(mutexLinklist, INFINITE);
	for (Client* clientP = head->next; clientP != NULL; clientP = clientP->next)
	{
		if (0 == strcmp(clientP->username, username))
		{
			ReleaseSemaphore(mutexLinklist, 1, NULL);
			return 1;
		}
	}
	ReleaseSemaphore(mutexLinklist, 1, NULL);
	return 0;
}