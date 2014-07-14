/******************************************************************************
* �ļ�����: hello.c
* �ļ�����: һ�����ơ�hello wrold����pthread���ų�������˵���̣߳�thread����
*     ��������ֹ,������hello_world_thread arg������ʾ���������������ĸ��̴߳�ӡ
*     pthread's Hello World!
* �ļ�����: ����ϲ hyuxi2005@126.com
* д�����ڣ�2012.12.15
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define HELLO_WORLD_THREAD_NUM  5

void *hello_world_thread(void *arg)
{
	/* �����߳�ʱ��arg�������ݵ���int*���ͣ������������ת������ */
	int id = *((int*)arg);
	
	/* ͨ����ӡ��Ϣ��֪���ǵڼ����������߳���ִ���� */
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
		/* ��iֵ��ŵ� thread_args[i]*/
		thread_args[i] = i;
		/* �����߳�ʱ����thread_args[i]��ַ ��Ϊarg�������ݸ� hello_world_thread */
		/* ������Щ����ʾ�����õľֲ�������ַ��Ϊarg���������ǲ���ȫ�ģ�����ҴӶ��Ϸ����ڴ���Ϊarg������ */
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

	/* �������ͷ�ǰ�������ڴ� */
	if(thread_args)
	{
		free(thread_args);
	}

	return 0;
}