#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
int counter=0; /*两个线程都能修改的共享变量 */
void thread1(void *arg);
void thread2(void *arg);
int main(int argc, char *argv[])
{
	pthread_t id1,id2;
	/*创建第 1 个线程*/
	pthread_create(&id1,NULL,(void *)thread1, NULL);
	/*创建第 2 个线程*/
	pthread_create(&id2,NULL,(void *)thread2, NULL);
	pthread_join(id1,NULL); /*等待第 1 个线程结束*/
	pthread_join(id2,NULL); /*等待第 2 个线程结束*/
	/*打印 counter 最后的值*/
	printf("最后的 counter 值为%d\n",counter);
	exit(0);
}
void thread1(void *arg) /*第 1 个线程执行代码*/
{
	int i,val;
	for(i=1;i<=5;i++){
		val = ++counter;
		printf("第 1 个线程:第%d 次循环,第 1 次引用 counter=%d\n",i,counter); /*LINE A*/
		sleep(3); /*睡眠或挂起 3 秒钟*/
		printf("第 1 个线程:第%d 次循环,第 2 次引用 counter=%d\n",i,counter); /*LINE B*/
		counter = val;
	}
}
void thread2(void *arg) /*第 2 个线程执行代码*/
{
	int i,val;
	for(i=1;i<=5;i++){
		val = ++counter;
		sleep(1); /*睡眠或挂起 1 秒钟*/
		printf("第 2 个线程:第%d 次循环,counter=%d\n",i,counter);
		counter = val;
	}
}

