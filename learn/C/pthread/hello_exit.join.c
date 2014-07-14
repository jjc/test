/******************************************************************************
* 文件名称: hello.c
* 文件描述: 一个类似“hello wrold”的pthread入门程序，用于说明线程（thread）的
*     创建和终止,在hello_arg的基础，增加对exit，join的status测试代码。
* 文件作者: 黄玉喜 hyuxi2005@126.com
* 写作日期：2012.12.15
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HELLO_WORLD_THREAD_NUM  2

void *hello_world_thread(void *arg)
{
	/* 创建线程时，arg参数传递的是int*类型，所以这里给他转换过来 */
	int id = *((int*)arg);
	
	/* 通过打印信息就知道是第几个创建的线程在执行了 */
	printf("pthread's Hello World! I am %d\n",id);
	if(id%2 ==0)
	{
		/* 如果id被2整除，将arg指代的内存释放，并分配新的内存存放status返回给pthread_join */
		char *status = malloc(strlen("i have free arg's memory")+1);
		if(status)
		{
			memset(status,0x00,strlen("i have free arg's memory")+1);
			memcpy(status,"i have free arg's memory",strlen("i have free arg's memory"));
			printf("thread %d: %s %p, but malloc %p\n",id,status, arg,status);
			free(arg);

			pthread_exit((void*)status);
		}
	}

	/* 如果id不能被2整除，或者分配新的内存status失败，将arg作为status返回给pthread_join */
	printf("thread %d: wait pthread_join free arg's memory %p\n",id,arg);
	pthread_exit(arg);

	

	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t threads[HELLO_WORLD_THREAD_NUM];
	int rc;
	int i;
	char *status=NULL;

	for(i=0;i<HELLO_WORLD_THREAD_NUM;i++)
	{
		/* 将i值存放到 thread_args[i]*/
		int *thread_arg = malloc(sizeof(int));
		if(thread_arg==NULL)
		{
			printf("ERROR: no memory!\n");
			return -1;
		}

		*thread_arg = i;

		/* 创建线程时，为每个线程单独分配内存作为arg参数 */
		printf("main: arg' memory %p\n", thread_arg);
		rc = pthread_create(&threads[i], NULL, hello_world_thread, (void*)thread_arg);
		if (rc)
		{
			printf("ERROR: pthread_create failed with %d\n", rc);
			return -1;
		}
	}

	for(i=0;i<HELLO_WORLD_THREAD_NUM;i++)
	{
		pthread_join(threads[i], &status);
		if(status)
		{
			if(memcmp(status,"i have free arg's memory",strlen("i have free arg's memory"))==0)
			{
				printf("--join %d: I'm freeing status's memory %p\n",i, status);
			}
			else
			{
				printf("--join %d: I'm freeing arg's memory  %p\n",i,status);
			}
			free(status);
		}
	}
	
	printf("INFO: All threads have been exit!!!\n");

	return 0;
}