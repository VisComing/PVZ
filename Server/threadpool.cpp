/*****************************************

线程池测试

结构体Job：函数指针，参数
任务队列job_head；函数：job_create();job_get();
信号量mutex_job;

线程池：20个线程
每个线程包括：线程函数thread_do；存放任务的临界区thread_buf及信号量mutex_thread;一个FLAG，标志此线程是否在工作中；

线程函数thread_do:
1.wait()
2.被唤醒后，从缓冲区中取任务信息，执行；
3.执行结束，清空缓冲区

任务分配函数job_alloc:
1.不断检测任务队列，若有任务，取出；
2.若无空闲线程且线程数未达上限，创建线程；
3.将任务放入线程池的缓冲区thread_buf，并用signal()唤醒线程

*************************************************/

#include <iostream>
#include <process.h>
#include <cstdlib>
#include <winsock2.h>
#include <mutex>
#pragma comment(lib,"ws2_32.lib")
using namespace std;

using namespace std;

const int THREADSIZE = 20;

typedef void* HANDLE;

typedef struct _job {
	int (*function)(int);
	int arg;

	struct _job* next;
}Job;

typedef struct _thread {
	Job buf;
	mutex Mutex;
	int flag;
}Thread;

Job* job_head = NULL;
HANDLE mutex_job;

Thread thread[THREADSIZE];
int thread_tot = 0;
int thread_using = 0;




void job_create(int (*function)(int), int arg) {
	Job* curr = job_head;
	for (; curr->next != NULL; curr = curr->next);
	curr->next = (Job*)malloc(sizeof(Job));
	curr = curr->next;
	curr->next = NULL;
	curr->function = function;
	curr->arg = arg;
	cout << "job_create\tcreate a job" << endl;
}

Job* job_get(Job* job) {
	Job* jobp = job_head->next;
	job_head->next = job_head->next->next;
	*job = *(jobp);
	free(jobp);
	cout << "job_get\tget a job" << endl;
	return job;
}

unsigned __stdcall thread_do(void* param) {
	int thread_id = *(int*)param;
	//WaitForSingleObject(thread[thread_id].mutex, INFINITE);
	thread[thread_id].Mutex.lock();
	Job job_do = thread[thread_id].buf;
	thread[thread_id].flag = 1;
	cout << "thread_do\tready to do a job" << endl;
	job_do.function(job_do.arg);
	thread[thread_id].flag = 0;
	memset(&thread[thread_id], 0, sizeof(Job));
}

unsigned __stdcall job_alloc(void* param) {
	while (1) {
		if (NULL != job_head->next) {
			if (thread_using == thread_tot && thread_tot < THREADSIZE) {
				_beginthreadex(NULL, 0, thread_do, NULL, 0, 0);
				thread_tot++;
				cout << "job_alloc\tcreate a thread, tot " << thread_tot << endl;
			}
			int i = 0;
			for (; i < THREADSIZE && thread[i].flag != 0; i++);//找到空闲线程
			job_get(&thread[i].buf);
			cout << "job_alloc\tput a job into thread, thread id: " << i << endl;
			thread_using++;
			thread[i].Mutex.unlock();
		}
	}
}

int print_num(int num){
	cout <<num << endl;
	return 0;
}

int main(){
	job_head = (Job*)malloc(sizeof(Job));
	job_head->next = NULL;
	mutex_job = CreateSemaphore(NULL, 1, 1, "mutex_job");

	/for (int i = 0; i < THREADSIZE; i++) {
		//thread[i].mutex = CreateSemaphore(NULL, 0, 1, "mutex_thread");
		thread[i].Mutex.unlock();
		thread[i].flag = 0;
	}

	_beginthreadex(NULL, 0, job_alloc, NULL, 0, 0);
	cout << "begin thread job_alloc" << endl;
	
	int num;
	while(1){
		
		cin >> num;
		job_create(&print_num, num);
	}
	
	
}



