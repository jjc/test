/******************************************************************************
* �ļ�����: hello.c
* �ļ�����: һ�����ơ�hello wrold����pthread���ų�������˵���̣߳�thread����
*     ��������ֹ,��hello_arg�Ļ��������Ӷ�exit��join��status���Դ��롣
* �ļ�����: ����ϲ hyuxi2005@126.com
* д�����ڣ�2012.12.15
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HELLO_WORLD_THREAD_NUM  2

void *hello_world_thread(void *arg)
{
	/* �����߳�ʱ��arg�������ݵ���int*���ͣ������������ת������ */
	int id = *((int*)arg);
	
	/* ͨ����ӡ��Ϣ��֪���ǵڼ����������߳���ִ���� */
	printf("pthread's Hello World! I am %d\n",id);
	if(id%2 ==0)
	{
		/* ���id��2��������argָ�����ڴ��ͷţ��������µ��ڴ���status���ظ�pthread_join */
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

	/* ���id���ܱ�2���������߷����µ��ڴ�statusʧ�ܣ���arg��Ϊstatus���ظ�pthread_join */
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
		/* ��iֵ��ŵ� thread_args[i]*/
		int *thread_arg = malloc(sizeof(int));
		if(thread_arg==NULL)
		{
			printf("ERROR: no memory!\n");
			return -1;
		}

		*thread_arg = i;

		/* �����߳�ʱ��Ϊÿ���̵߳��������ڴ���Ϊarg���� */
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