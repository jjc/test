/******************************************************************************
* �ļ�����: hello.c
* �ļ�����: һ�����ơ�hello wrold����pthread���ų�������˵���̣߳�thread����
*     ��������ֹ
* �ļ�����: ����ϲ hyuxi2005@126.com
* д�����ڣ�2012.12.15
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define HELLO_WORLD_THREAD_NUM  5

void *hello_world_thread(void *arg)
{
   printf("pthread's Hello World!\n");
	/**  
	* @function void pthread_exit(void *status)
	*     ��ֹ�������̣߳�
	* @param status��
	*     ͨ��status�����˳�״̬����pthread_join���ʹ��
	* @return ��
	*     �޷���ֵ��Ҳ�����ص�����÷���
	* @note 
	*     ��������߳���δ���룬���߳�ID ��status ָ�����˳�״̬�����ֲ��䣬ֱ��Ӧ�ó������pthread_join() �Եȴ����̡߳�
	*     ���򣬽�����status���߳�ID �����������ա�
	*/
   pthread_exit(NULL);

   return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t threads[HELLO_WORLD_THREAD_NUM];
	int rc;
	int i;
	for(i=0;i<HELLO_WORLD_THREAD_NUM;i++)
	{
		/**  
		* @function int pthread_create(pthread_t * thread, const pthread_attr_t * attr, void * (*start_routine)(void *), void *arg)
		*     ���ո������߳�����attr����һ�����̣�process���ﴴ��һ���µ��̣߳�thread��
		* @param attr��
		*     ���attrΪNULL�����ڲ�ʹ��Ĭ�ϵ����Դ����̡߳�����ڴ����߳�֮���޸�attr���򲻻���Ѿ��������̲߳������á�
		* @param thread��
		*     �����̳߳ɹ��󣬽�thread id�洢��thread����ظ������ߡ�����thrad��ֵ��δ����ġ�
		* @param start_routine��
		*     �̴߳����ɹ��󣬿�ʼִ���̵߳���ں���start_routine��
		* @param arg��
		*     ������ͨ��argָ���߳���ں���start_routineר�õĲ���ָ�롣
		* @return ��
		*     0 �����ɹ�����0
		*     EAGAIN ������ϵͳ���ƣ��紴�����߳�̫�࣬һ��������ഴ���̸߳���PTHREAD_THREADS_MAX��
		*     EINVAL attr ��ֵ��Ч
		* @note pthread_create�����̺߳��߳���ں�������ʼִ�У�����Ҫ��ʾ����start_routine��ʼִ�С�
		*     ���ȷʵ��Ҫ���˹��̷�Ϊcreate��start2��������start_routine�Ժ�ִ�У�
		*     start_routine����ͨ���ȴ�һ������������condition variable������ͬ���ķ�ʽʵ�֡�
		*/
		rc = pthread_create(&threads[i], NULL, hello_world_thread, NULL);
		if (rc)
		{
			printf("ERROR: pthread_create failed with %d\n", rc);
			return -1;
		}
	}

	for(i=0;i<HELLO_WORLD_THREAD_NUM;i++)
	{
		/**  
		* @function int pthread_join(pthread_t thread, void **status);
		*     �ȴ�thread�߳���ֹ
		*     ���threadָ�����̻߳�û����ֹ�������µ����̹߳���ֱ��threadָ�����߳���ֹΪֹ��
		* @param thread��
		*     ���ȴ��ĵ���ֹ�߳�
		* @param status��
		*     ���status��ֵ������NULL����ô����ֵ��ͨ��pthread_exit���ݹ����ġ�
		* @return ��
		*     0 �߳��Ѿ���ֹ
		*     ESRCH ����̲߳��ܵȴ�ͬһ���߳���ɣ��������һ���̻߳�ɹ���ɡ������߳̽���ֹ��������ESRCH ����
		*     EINVAL һ���ʾthread����Ч�Ĳ���
		*     EDEADLK ��鵽����״̬
		* @note 
		*     ��������߳���δ���룬���߳�ID ��status ָ�����˳�״̬�����ֲ��䣬ֱ��Ӧ�ó������pthread_join() �Եȴ����̡߳�
		*     ���򣬽�����status���߳�ID �����������ա�
		*/
		pthread_join(threads[i], NULL);
	}
	
	printf("INFO: All threads have been exit!!!\n");

	return 0;
}