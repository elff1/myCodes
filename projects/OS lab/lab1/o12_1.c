#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex; /* the mutex to protect counter*/
int counter=0; /*两个线程都能修改的共享变量 */

void thread1(void *arg);
void thread2(void *arg);

int main(int argc, char *argv[])
{
	pthread_t id1,id2;
	
	/* Initialize the mutex*/
	if(pthread_mutex_init(&mutex, NULL) != 0) {
		perror("Mutex initialization");
		exit(1);
	}

	/*创建第 1 个线程*/
	if(pthread_create(&id1,NULL,(void *)thread1, NULL) != 0) {
		perror("Thread create");
		exit(1);
	}
	/*创建第 2 个线程*/
	if(pthread_create(&id2,NULL,(void *)thread2, NULL) != 0) {
		perror("Thread create");
		exit(1);
	}
	/*等待第 1 个线程结束*/
	if(pthread_join(id1,NULL) != 0) {
		perror("Thread join");
		exit(1);
	}
	/*等待第 2 个线程结束*/
	if(pthread_join(id2,NULL) != 0) {
		perror("Thread join");
		exit(1);
	}
	
	/* Destroy the mutex*/
	pthread_mutex_destroy(&mutex);
	/*打印 counter 最后的值*/
	printf("最后的 counter 值为%d\n",counter);
	exit(0);
}
void thread1(void *arg) /*第 1 个线程执行代码*/
{
	int i,val;

	for(i=1;i<=5;i++){
		/* lock the mutex*/
		pthread_mutex_lock(&mutex);
		val = ++counter;
		printf("第 1 个线程:第%d 次循环,第 1 次引用 counter=%d\n",i,counter); /*LINE A*/
		sleep(1); /*睡眠或挂起 1 秒钟*/
		printf("第 1 个线程:第%d 次循环,第 2 次引用 counter=%d\n",i,counter); /*LINE B*/
		counter = val;
		/* unlock the mutex*/
		pthread_mutex_unlock(&mutex);
		
		sleep(1);
	}
}

void thread2(void *arg) /*第 2 个线程执行代码*/
{
	int i,val;

	for(i=1;i<=5;i++){
		/* lock the mutex*/
		pthread_mutex_lock(&mutex);
		val = ++counter;
		sleep(2); /*睡眠或挂起 2 秒钟*/
		printf("第 2 个线程:第%d 次循环,counter=%d\n",i,counter);
		counter = val;
		/* unlock the mutex*/
		pthread_mutex_unlock(&mutex);
		
		sleep(1);
	}
}

