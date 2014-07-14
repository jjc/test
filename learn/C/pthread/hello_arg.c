/******************************************************************************
* 文件名称: hello.c
* 文件描述: 一个类似“hello wrold”的pthread入门程序，用于说明线程（thread）的
*     创建和终止,增加了hello_world_thread arg参数的示例，可以区别是哪个线程打印
*     pthread's Hello World!
* 文件作者: 黄玉喜 hyuxi2005@126.com
* 写作日期：2012.12.15
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define HELLO_WORLD_THREAD_NUM  5

void *hello_world_thread(void *arg)
{
	/* 创建线程时，arg参数传递的是int*类型，所以这里给他转换过来 */
	int id = *((int*)arg);
	
	/* 通过打印信息就知道是第几个创建的线程在执行了 */
	printf("pthread's Hello World! I am %d\n",id);

	pthread_exit(NULL);

	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t threads[HELLO_WORLD_THREAD_NUM];
	int rc;
	int i;
	int *thread_args = malloc(HELLO_WORLD_THREAD_NUM*sizeof(int));
	if(thread_args == NULL)
	{
		printf("ERROR: no memory \n");
		return -1;
	}

	for(i=0;i<HELLO_WORLD_THREAD_NUM;i++)
	{
		/* 将i值存放到 thread_args[i]*/
		thread_args[i] = i;
		/* 创建线程时，将thread_args[i]地址 作为arg参数传递给 hello_world_thread */
		/* 网上有些代码示例是用的局部变量地址作为arg参数，这是不安全的，因此我从堆上分配内存作为arg参数。 */
		rc = pthread_create(&threads[i], NULL, hello_world_thread, (void*)&thread_args[i]);
		if (rc)
		{
			printf("ERROR: pthread_create failed with %d\n", rc);
			return -1;
		}
	}

	for(i=0;i<HELLO_WORLD_THREAD_NUM;i++)
	{
		pthread_join(threads[i], NULL);
	}
	
	printf("INFO: All threads have been exit!!!\n");

	/* 别忘了释放前面分配的内存 */
	if(thread_args)
	{
		free(thread_args);
	}

	return 0;
}