#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <mutex>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

const int THREADSIZE = 20;

typedef struct _job 
{										/*Job:任务，包含一个函数指针及此函数的变量*/
	int ( *function)(void*);
	void* arg;

	struct _job* next;
}Job;

typedef struct _thread 
{										/*Thread:线程，包含一个存储任务的缓冲区和一个标志是否在执行任务的flag*/
	Job buf;
	int flag;
}Thread;

typedef struct _thpool 
{
	Job* jobHead = NULL;				/*任务队列（链表）头*/

	Thread thread[THREADSIZE];			/*n个线程*/
	int threadTot = 0;
	int threadUsing = 0;

	//HANDLE mutexJob;
	//HANDLE mutexThread;
	sem_t semJob;
	sem_t semThread;
	
}Thpool;

Thpool thpool;

void jobCreate(int ( *function)(void*), void* arg);
Job* jobGet(Job* job);
void* threadDo(void*);
void* jobAlloc(void*);
int thpoolMain();

void jobCreate(int ( *function)(void*), void* arg) 
{
	//WaitForSingleObject(thpool.mutexJob, INFINITE);
	sem_wait(&thpool.semJob);
	Job* curr = thpool.jobHead;
	for (; curr->next != NULL; curr = curr->next);
	curr->next = (Job*)malloc(sizeof(Job));
	curr = curr->next;
	curr->next = NULL;
	curr->function = function;
	curr->arg = arg;
	//ReleaseSemaphore(thpool.mutexJob, 1, NULL);
	sem_post(&thpool.semJob);

	std::cout << "job_create\tcreate a job" << endl;
}

Job* jobGet(Job* job) 
{
	//WaitForSingleObject(thpool.mutexJob, INFINITE);
	sem_wait(&thpool.semJob);
	Job* jobp = thpool.jobHead->next;
	thpool.jobHead->next = thpool.jobHead->next->next;
	//ReleaseSemaphore(thpool.mutexJob, 1, NULL);
	sem_post(&thpool.semJob);
	*job = *(jobp);
	free(jobp);

	std::cout << "job_get\t\tget a job" << endl;
	return job;
}

void* threadDo(void* param) 
{
	int thread_id = *(int*)param;
	//WaitForSingleObject(thpool.mutexThread, INFINITE);
	sem_wait(&thpool.semThread);
	thpool.threadTot++;
	//ReleaseSemaphore(thpool.mutexThread, 1, NULL);
	sem_post(&thpool.semThread);

	cout << "thread_do\tthread " << thread_id << " start" << endl;
	
	while (1) 
	{
		//WaitForSingleObject(thpool.mutexThread, INFINITE);
		sem_wait(&thpool.semThread);
		if (1 == ::thpool.thread[thread_id].flag) 
		{
						
			Job job_do = ::thpool.thread[thread_id].buf;
			//ReleaseSemaphore(thpool.mutexThread, 1, NULL);
			sem_post(&thpool.semThread);
			cout << "thread_do\tready to do a job" << endl;
			job_do.function(job_do.arg);
			//WaitForSingleObject(thpool.mutexThread, INFINITE);
			sem_wait(&thpool.semThread);
			::thpool.thread[thread_id].flag = 0;
			thpool.threadUsing--;
			cout << "thread_do\tthread " << thread_id << " free" << endl;
			
			memset(&::thpool.thread[thread_id], 0, sizeof(Job));
			
		}
		//ReleaseSemaphore(thpool.mutexThread, 1, NULL);
		sem_post(&thpool.semThread);
		sleep(1);
	}
}

void* jobAlloc(void* param) 
{
	while (1) 
	{
		//WaitForSingleObject(thpool.mutexJob, INFINITE);
		sem_wait(&thpool.semJob);
		if (NULL != thpool.jobHead->next) 
		{
			//ReleaseSemaphore(thpool.mutexJob, 1, NULL);
			sem_post(&thpool.semJob);

			//WaitForSingleObject(thpool.mutexThread, INFINITE);
			sem_wait(&thpool.semThread);
			if (thpool.threadUsing == thpool.threadTot && thpool.threadTot < THREADSIZE) 
			{
				//_beginthreadex(NULL, 0, threadDo, &thpool.threadTot, 0, 0);
				pthread_t thThreadDo;
				pthread_create(&thThreadDo, NULL, threadDo, &thpool.threadTot);
				cout << "job_alloc\tcreate a thread, tot " << thpool.threadTot << endl;
			}

			int i = 0;
			for (; i < THREADSIZE && ::thpool.thread[i].flag != 0; i++);
			if (i < THREADSIZE) 
			{
				jobGet(&::thpool.thread[i].buf);
				cout << "job_alloc\tput a job into thread, thread id: " << i << endl;
				thpool.threadUsing++;
				//::thread[i].Mutex.unlock();
				::thpool.thread[i].flag = 1;
				cout << "job_alloc\tthread " << i << " occupied" << endl;
			}
			//ReleaseSemaphore(thpool.mutexThread, 1, NULL);
			sem_post(&thpool.semThread);
		}
		else
		{
			//ReleaseSemaphore(thpool.mutexJob, 1, NULL);
			sem_post(&thpool.semJob);
		}
		
		sleep(1);
	}
}

int printNum(int* num)
{
	int temp = *num;
	sleep(5);
	cout << "out:" << temp << endl;
	return 0;
}

int thpoolMain()
{
	thpool.jobHead = (Job*)malloc(sizeof(Job));
	thpool.jobHead->next = NULL;
	//thpool.mutexJob = CreateSemaphore(NULL, 1, 1, "mutex_job");
	//thpool.mutexThread = CreateSemaphore(NULL, 1, 1, "mutex_thread");
	sem_init(&thpool.semJob, 1, 1);
	sem_init(&thpool.semThread, 1, 1);

	for (int i = 0; i < THREADSIZE; i++) 
	{
		//thread[i].mutex = CreateSemaphore(NULL, 0, 1, "mutex_thread");
		//thpool.thread[i].Mutex.lock();
		thpool.thread[i].flag = 0;
	}

	//_beginthreadex(NULL, 0, jobAlloc, NULL, 0, 0);
	pthread_t thJobAlloc;
	pthread_create(&thJobAlloc, NULL, jobAlloc, NULL);
	cout << "begin thread job_alloc" << endl;
		
	return 0;
}
