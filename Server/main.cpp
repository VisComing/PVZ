/* 2020.11.24
Server - Linux版本
*/

#include <iostream>
#include <cstdio>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "head.h" 
#include <pthread.h>
#include "sqlite3.h"
#include <thread>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;



/*全局变量*/
Client* head;					/*客户端链表头*/
unsigned int clientTot = 0;		/*客户端总数*/
Match match;					/*匹配队列*/

/*信号量*/
//HANDLE mutexMatch;
//HANDLE mutexDb;
//HANDLE mutexLinklist;
sem_t semMatch;			/*匹配队列*/
sem_t semDb;			/*数据库*/
sem_t semLinklist;		/*客户端链表*/

/*socket通信相关全局变量*/
//WSADATA wsaData;
SOCKET serverSocket;
SOCKADDR_IN socketAddr;
SOCKADDR_IN clientAddr;
socklen_t clientAddrLen;

/*sqlite3数据库相关全局变量*/
sqlite3* db = NULL;
	
/*函数*/
int handleRequest(char*, Client*);
Request analysisRequest(char*);
int waitMatch(Client*);
int xferMatchData(Client*, Client*);
int recvLine1(SOCKET, char*, int, int);
int recvLine(SOCKET, char*, int, int);
int recvSingleLine(Client*, SOCKET, char*, int, int);
int endLine(char*, int);
int dbOpen();
int dbLogin(char*, char*);
int dbRegister(char*, char*);
void dbClose();
int isOnline(char*);

unsigned  threadAccept(void*);
unsigned  threadServer(void*);
unsigned  threadMatching(void*);
unsigned  threadHeartBeat(void*);


int main() 
{
	thpoolMain();

	match.client[0] = NULL;
	match.client[1] = NULL;
	//match.id[0] = 0;
	//match.id[1] = 0;

	//mutexMatch = CreateSemaphore(NULL, 1, 1, "mutex_match");
	//mutexDb = CreateSemaphore(NULL, 1, 1, "mutex_db");
	//mutexLinklist = CreateSemaphore(NULL, 1, 1, "mutex_linklist");
	sem_init(&semMatch, 0, 1);
	sem_init(&semDb, 0, 1);
	sem_init(&semLinklist, 0, 1);
	head = (Client*)malloc(sizeof(Client));
	head->next = NULL;

	int result = dbOpen();
	if (!result) 
	{
		cout << "opening database failed" << endl;
	}
	
	//WSAStartup(MAKEWORD(2, 2), &wsaData);

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	socketAddr.sin_family = AF_INET;
	socketAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	socketAddr.sin_port = htons(PORT);

	int n = ::bind(serverSocket, (struct sockaddr*)&socketAddr, sizeof(socketAddr));
	
	std::cout << "端口绑定成功：" << PORT << endl;

	int l = listen(serverSocket, 100);

	clientAddrLen = sizeof(clientAddr);

	//_beginthreadex(NULL, 0, threadAccept, NULL, 0, 0);
	jobCreate((int(*)(void*))threadAccept, NULL);
	
	while (1) 
	{
		sleep(5);
	}
}

unsigned  threadAccept(void* param)
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

		//WaitForSingleObject(mutexLinklist, INFINITE);
		sem_wait(&semLinklist);
		clientP->next = head->next;
		head->next = clientP;
		//ReleaseSemaphore(mutexLinklist, 1, NULL);
		sem_post(&semLinklist);

		//_beginthreadex(NULL, 0, threadServer, clientP, 0, 0);
		jobCreate((int(*)(void*))threadServer, clientP);

		cout << "------------------------------------------------" << endl;
		cout << "Socket:" << clientP->cSocket << " | IP:" << clientP->IP << " | Port:" << clientP->port << endl;
		cout << "[ACCEPT]" << endl;
		cout << "客户端已连接至服务器" << endl;
	}

	return 0;
}

unsigned  threadServer(void* param)
{
	Client* thisClient = (Client*)param;
	//thisClient->threadId = _getpid();
	char rbuf[BUFSIZE];
	char sbuf[BUFSIZE];
	
	//_beginthreadex(NULL, 0, threadHeartBeat, thisClient, 0, 0);
	jobCreate((int(*)(void*))threadHeartBeat, thisClient);

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
			int ret = handleRequest(rbuf, thisClient);		
			if(-1 == ret){
				break;
			}
		}
		else 
		{
			cout << "------------------------------------------------" << endl;
			cout << "user " << thisClient->cSocket << " offline" << endl;
			break;
		}
	}
	
	close(thisClient->cSocket);
	cout << "------------------------------------------------" << endl;
	cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
	cout << "[CLOSE]" << endl;
	cout << "客户端已断开连接" << endl;

	memset(thisClient->username, 0, STRSIZE);
	//WaitForSingleObject(mutexMatch, INFINITE);
	sem_wait(&semMatch);
	if (thisClient == match.client[0]) 
	{
		match.client[0] = NULL;
		//match.id[0] = 0;
	}
	if (thisClient == match.client[1]) 
	{
		match.client[1] = NULL;
		//match.id[1] = 0;
	}
	//ReleaseSemaphore(mutexMatch, 1, NULL);
	sem_post(&semMatch);
	thisClient->cSocket = 0;

	Client* temp = NULL;
	//WaitForSingleObject(mutexLinklist, INFINITE);
	sem_wait(&semLinklist);
	for (temp = head; temp->next != thisClient; temp = temp->next);
	temp->next = temp->next->next;
	//ReleaseSemaphore(mutexLinklist, 1, NULL);
	sem_post(&semLinklist);
	free(thisClient);
	thisClient = NULL;
	
	return 0;
}

int handleRequest(char* rbuf, Client* thisClient)
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
		cout << "request: 注册 | ";
		cout << "用户名" << request.param[0] << " | 密码" << request.param[1] << endl;
		int result = dbRegister(request.param[0], request.param[1]);
		if (1 == result) 
		{
			memset(sbuf, 0, BUFSIZE);
			memcpy(sbuf, "REGISTER;1;\n", strlen("REGISTER;1;\n"));
			cout << "reply: 注册成功！" << endl;
		}
		else 
		{
			memset(sbuf, 0, BUFSIZE);
			memcpy(sbuf, "REGISTER;0;\n", strlen("REGISTER;0;\n"));
			cout << "reply: 注册失败" << endl;
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
		cout << "用户名" << request.param[0] << " | 密码" << request.param[1] << endl;
		int result = dbLogin(request.param[0], request.param[1]);
		int online = isOnline(request.param[0]);
		if (0 == strcmp("", thisClient->username) && 0 == online && 1 == result)
		{
			memcpy(thisClient->username, request.param[0], STRSIZE);
			memset(sbuf, 0, BUFSIZE);
			memcpy(sbuf, "LOGIN;1;\n", strlen("LOGIN;1;\n"));
			cout << "reply: 登录成功！" << endl;
		}
		else if(1 != result)
		{
			memset(sbuf, 0, BUFSIZE);
			memcpy(sbuf, "LOGIN;0;\n", strlen("LOGIN;0;\n"));
			cout << "reply: 登录失败" << endl;
		}
		else
		{
			memset(sbuf, 0, BUFSIZE);
			memcpy(sbuf, "LOGIN;2;\n", strlen("LOGIN;2;\n"));
			cout << "reply: 登录失败，用户已登录" << endl;
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
		cout << "正在匹配..." << endl;
		int ret = waitMatch(thisClient);
		if(-1 == ret){
			return -1;
		}
	}
	else 
	{
		cout << "wrong request:" << request.type << endl;
	}
	return 0;
}

Request analysisRequest(char* hbuf)
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

int waitMatch(Client* thisClient)
{
	//DWORD thisId = GetCurrentThreadId();
	Client* oppoClient = NULL;
	//DWORD oppoId = 0;
	char sbuf[BUFSIZE];
	char rbuf[BUFSIZE];
	memset(sbuf, 0, BUFSIZE);
	memset(rbuf, 0, BUFSIZE);
	while (1) 
	{
		//WaitForSingleObject(mutexMatch, INFINITE);
		sem_wait(&semMatch);
		if (2 == thisClient->flag) 
		{
			thisClient->flag = 0;
			//ReleaseSemaphore(mutexMatch, 1, NULL);
			sem_post(&semMatch);
			return 0;
		}
		if (NULL == match.client[0] && NULL == match.client[1]) 
		{
			cout << "------------------------------------------------" << endl;
			cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
			cout << "[MATCH]" << endl;
			cout << "用户" << thisClient->cSocket << "已加入，正在等待对手..." << endl;
			match.client[0] = thisClient;
			//match.id[0] = thisId;
			thisClient->flag = 1;
			//_beginthreadex(NULL, 0, threadMatching, thisClient, 0, 0);
			jobCreate((int(*)(void*))threadMatching, thisClient);
		}
		else if (NULL != match.client[0] && NULL == match.client[1] && thisClient != match.client[0]) 
		{
			cout << "------------------------------------------------" << endl;
			cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
			cout << "[MATCH]" << endl;
			cout << "用户" << thisClient->cSocket << "已加入，即将进入比赛..." << endl;
			thisClient->flag = 3;
			oppoClient = match.client[0];
			//oppoId = match.id[0];
			match.client[0] = NULL;
			//match.id[0] = 0;
			match.client[1] = thisClient;
			//match.id[1] = thisId;
			//ReleaseSemaphore(mutexMatch, 1, NULL);
			sem_post(&semMatch);
			oppoClient->flag = 3;
			xferMatchData(thisClient, oppoClient);
			thisClient->flag = 0;
			oppoClient->flag = 0;
			cout << "------------------------------------------------" << endl;
			cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
			cout << "[MATCH]" << endl;
			cout << "比赛结束，用户" << thisClient->cSocket << "已退出" << endl;
			return 0;
		}
		else if (NULL == match.client[0] && NULL != match.client[1] && thisClient != match.client[1]) 
		{
			cout << "------------------------------------------------" << endl;
			cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
			cout << "[MATCH]" << endl;
			cout << "用户" << thisClient->cSocket << "已确认，比赛开始！" << endl;
			thisClient->flag = 0;
			oppoClient = match.client[1];
			//oppoId = match.id[1];
			match.client[1]= NULL;
			//match.id[1] = 0;
			//ReleaseSemaphore(mutexMatch, 1, NULL);
			sem_post(&semMatch);
			sleep(3);

			memset(sbuf, 0, BUFSIZE);
			memcpy(sbuf, "MATCHSUCCESS;0;\n", BUFSIZE);
			int sbyte = send(thisClient->cSocket, sbuf, strlen(sbuf), 0);
			cout << "------------------------------------------------" << endl;
			cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
			cout << "[SEND][MATCH] match data" << endl;
			printf("len: %d\n", sbyte);
			printf("buf: %s\n", sbuf);

			memset(sbuf, 0, BUFSIZE);
			memcpy(sbuf, "MATCHSUCCESS;1;\n", BUFSIZE);
			sbyte = send(oppoClient->cSocket, sbuf, strlen(sbuf), 0);
			cout << "------------------------------------------------" << endl;
			cout << "Socket:" << oppoClient->cSocket << " | IP:" << oppoClient->IP << " | Port:" << oppoClient->port << endl;
			cout << "[SEND][MATCH] match data" << endl;
			printf("len: %d\n", sbyte);
			printf("buf: %s\n", sbuf);
			sleep(5);

			memset(sbuf, 0, BUFSIZE);
			memcpy(sbuf, "START;\n", BUFSIZE);
			sbyte = send(thisClient->cSocket, sbuf, strlen(sbuf), 0);
			cout << "------------------------------------------------" << endl;
			cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
			cout << "[SEND][MATCH] match data" << endl;
			printf("len: %d\n", sbyte);
			printf("buf: %s\n", sbuf);

			sbyte = send(oppoClient->cSocket, sbuf, strlen(sbuf), 0);
			cout << "------------------------------------------------" << endl;
			cout << "Socket:" << oppoClient->cSocket << " | IP:" << oppoClient->IP << " | Port:" << oppoClient->port << endl;
			cout << "[SEND][MATCH] match data" << endl;
			printf("len: %d\n", sbyte);
			printf("buf: %s\n", sbuf);

			int ret = xferMatchData(thisClient, oppoClient);
			if(-1 == ret)
			{
				cout << "------------------------------------------------" << endl;
				cout << "user " << thisClient->cSocket << " offline" << endl;
				return -1;
			}
			cout << "------------------------------------------------" << endl;
			cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
			cout << "[MATCH]" << endl;
			cout << "比赛结束，用户" << thisClient->cSocket << "已退出" << endl;
			return 0;
		}
		else
		{
		}
		//ReleaseSemaphore(mutexMatch, 1, NULL);
		sem_post(&semMatch);
	}	
}

int xferMatchData(Client* thisClient, Client* oppoClient)
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
			if (0 == strcmp("HeartBeat;\n", rbuf))
			{
				/*cout << "------------------------------------------------" << endl;
				cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
				cout << "[RECV][HEARTBEAT]" << endl;
				printf("len: %d\n", rbyte);
				printf("buf: %s\n", rbuf);*/
			}
			else
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
					cout << "Socket:" << oppoClient->cSocket << " | IP:" << oppoClient->IP << " | Port:" << oppoClient->port << endl;
					cout << "[SEND][MATCH] match data" << endl;
					printf("len: %d\n", sbyte);
					printf("buf: %s\n", sbuf);
					return 0;
				}
				else if (0 == strcmp("LOSE;\n", rbuf))
				{
					return 0;
				}
				else
				{
					memset(sbuf, 0, BUFSIZE);
					memcpy(sbuf, rbuf, BUFSIZE);
					int sbyte = send(oppoClient->cSocket, sbuf, strlen(sbuf), 0);
					cout << "------------------------------------------------" << endl;
					cout << "Socket:" << oppoClient->cSocket << " | IP:" << oppoClient->IP << " | Port:" << oppoClient->port << endl;
					cout << "[SEND][MATCH] match data" << endl;
					printf("len: %d\n", sbyte);
					printf("buf: %s\n", sbuf);
				}
			}
			
		}
		else 
		{
			cout << "------------------------------------------------" << endl;
			cout << "user " << thisClient->cSocket << " offline" << endl;
			memset(sbuf, 0, BUFSIZE);
			memcpy(sbuf, "WIN;\n", BUFSIZE);
			int sbyte = send(oppoClient->cSocket, sbuf, strlen(sbuf), 0);
			cout << "------------------------------------------------" << endl;
			cout << "Socket:" << oppoClient->cSocket << " | IP:" << oppoClient->IP << " | Port:" << oppoClient->port << endl;
			cout << "[SEND][MATCH] match data" << endl;
			printf("len: %d\n", sbyte);
			printf("buf: %s\n", sbuf);
			return -1;
		}
	}
}

unsigned  threadMatching(void* param)
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
		if (rbyte > 0 && thisClient->flag == 1) 
		{
			if (0 == strcmp(rbuf, "CANCELMATCH;\n")) 
			{
				rbyte = recvLine(thisClient->cSocket, rbuf, sizeof(rbuf), 0);
				cout << "------------------------------------------------" << endl;
				cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
				cout << "[RECV][MATCH]" << endl;
				printf("len: %d\n", rbyte);
				printf("buf: %s\n", rbuf);
				//WaitForSingleObject(mutexMatch, INFINITE);
				sem_wait(&semMatch);
				if (match.client[0] == thisClient && match.client[1] == NULL) 
				{
					match.client[0] = NULL;
					thisClient->flag = 2;
					cout << "------------------------------------------------" << endl;
					cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
					cout << "[MATCH]" << endl;
					cout << "用户" << thisClient->cSocket << "取消了匹配！" << endl;
				}
				//ReleaseSemaphore(mutexMatch, 1, NULL);
				sem_post(&semMatch);
				return 1;
			}
			else if (0 == strcmp(rbuf, "HeartBeat;\n"))
			{
				rbyte = recvLine(thisClient->cSocket, rbuf, sizeof(rbuf), 0);
				/*cout << "------------------------------------------------" << endl;
				cout << "Socket:" << thisClient->cSocket << " | IP:" << thisClient->IP << " | Port:" << thisClient->port << endl;
				cout << "[RECV][HEARTBEAT]" << endl;
				printf("len: %d\n", rbyte);
				printf("buf: %s\n", rbuf);*/
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

int dbOpen()
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

int dbLogin(char* username, char* password)
{
	char sql[STRSIZE];
	memset(sql, 0, STRSIZE);
	sprintf(sql, "select username from user where username == \"%s\" and password == \"%s\"", username, password);
	char** dbresult;
	int row = -1, col = -1;
	char** errmsg = NULL;
	//WaitForSingleObject(mutexDb, INFINITE);
	sem_wait(&semDb);
	int result = sqlite3_get_table(db, sql, &dbresult, &row, &col, errmsg);
	//ReleaseSemaphore(mutexDb, 1, NULL);
	sem_post(&semDb);
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

int dbRegister(char* username, char* password)
{
	char sql[STRSIZE];
	memset(sql, 0, STRSIZE);
	sprintf(sql, "select username from user where username == \"%s\"", username);
	char** dbresult;
	int row = -1, col = -1;
	char** errmsg = NULL;
	//WaitForSingleObject(mutexDb, INFINITE);
	sem_wait(&semDb);
	int result = sqlite3_get_table(db, sql, &dbresult, &row, &col, errmsg);
	//ReleaseSemaphore(mutexDb, 1, NULL);
	sem_post(&semDb);
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
		//WaitForSingleObject(mutexDb, INFINITE);
		sem_wait(&semDb);
		result = sqlite3_exec(db, sql, 0, 0, errmsg);
		//ReleaseSemaphore(mutexDb, 1, NULL);
		sem_post(&semDb);
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

void dbClose()
{
	sqlite3_close(db);
}

int recvLine1(SOCKET s, char* buf, int len, int flags)
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

int recvLine(SOCKET s, char* buf, int len, int flags) {
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

int recvSingleLine(Client* client, SOCKET s, char* rbuf, int len, int flags) 
{
	char tempbuf[BUFSIZE];
	memset(tempbuf, 0, BUFSIZE);
	if ('\0' == client->buf[0])
	{
		int rbyte = recvLine(client->cSocket, tempbuf, BUFSIZE, 0);
		if (rbyte > 0) 
		{
			strcat(client->buf, tempbuf);
		}
		else {
			client->buf[0] = (char)-1;
		}
		
	}
	if (client->buf[0] < 0) {
		return -1;
	}
	
	int i = 0;
	for (; '\n' != client->buf[i] && '\0' != client->buf[i] && i < BUFSIZE; i++) {
		rbuf[i] = client->buf[i];
	}
	rbuf[i] = client->buf[i];
	i++;
	if (MSG_PEEK != flags)
	{
		/*将client->buf中内容前移*/
		memset(tempbuf, 0, BUFSIZE);
		memcpy(tempbuf, client->buf + i, BUFSIZE - i);
		memset(client->buf, 0, BUFSIZE);
		memcpy(client->buf, tempbuf, BUFSIZE);
	}
	return i;

}

int endLine(char* buf, int len)
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

int isOnline(char* username)
{
	//WaitForSingleObject(mutexLinklist, INFINITE);
	sem_wait(&semLinklist);
	for (Client* clientP = head->next; clientP != NULL; clientP = clientP->next)
	{
		if (0 == strcmp(clientP->username, username))
		{
			//ReleaseSemaphore(mutexLinklist, 1, NULL);
			sem_post(&semLinklist);
			return 1;
		}
	}
	//ReleaseSemaphore(mutexLinklist, 1, NULL);
	sem_post(&semLinklist);
	return 0;
}

unsigned  threadHeartBeat(void* param)
{
	Client* client = (Client*)param;
	Client remClient = *client;
	char sbuf[BUFSIZE];
	memset(sbuf, 0, BUFSIZE);
	memcpy(sbuf, "HeartBeat;\n", strlen("HeartBeat;\n"));
	while (remClient.cSocket == client->cSocket) {
		int sbyte = send(client->cSocket, sbuf, strlen(sbuf), 0);
		/*cout << "------------------------------------------------" << endl;
		cout << "Socket:" << client->cSocket << " | IP:" << client->IP << " | Port:" << client->port << endl;
		cout << "[SEND][HEARTBEAT]" << endl;
		printf("len: %d\n", sbyte);
		printf("buf: %s\n", sbuf);*/
		sleep(5);
	}
	return 0;
}