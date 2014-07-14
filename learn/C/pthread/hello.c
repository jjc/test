/******************************************************************************
* 文件名称: hello.c
* 文件描述: 一个类似“hello wrold”的pthread入门程序，用于说明线程（thread）的
*     创建和终止
* 文件作者: 黄玉喜 hyuxi2005@126.com
* 写作日期：2012.12.15
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
	*     终止调用者线程，
	* @param status：
	*     通过status设置退出状态，与pthread_join配对使用
	* @return ：
	*     无返回值，也不返回到其调用方。
	* @note 
	*     如果调用线程尚未分离，则线程ID 和status 指定的退出状态将保持不变，直到应用程序调用pthread_join() 以等待该线程。
	*     否则，将忽略status。线程ID 可以立即回收。
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
		*     按照给定的线程属性attr，在一个进程（process）里创建一个新的线程（thread）
		* @param attr：
		*     如果attr为NULL，则内部使用默认的属性创建线程。如果在创建线程之后修改attr，则不会对已经创建的线程产生作用。
		* @param thread：
		*     创建线程成功后，将thread id存储在thread里，返回给调用者。否则thrad的值是未定义的。
		* @param start_routine：
		*     线程创建成功后，开始执行线程的入口函数start_routine。
		* @param arg：
		*     调用者通过arg指定线程入口函数start_routine专用的参数指针。
		* @return ：
		*     0 创建成功返回0
		*     EAGAIN 超出了系统限制，如创建的线程太多，一个进程最多创建线程个数PTHREAD_THREADS_MAX。
		*     EINVAL attr 的值无效
		* @note pthread_create创建线程后，线程入口函数即开始执行，不需要显示控制start_routine开始执行。
		*     如果确实需要将此过程分为create和start2步来控制start_routine稍后执行，
		*     start_routine可以通过等待一个条件变量（condition variable）进行同步的方式实现。
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
		*     等待thread线程终止
		*     如果thread指代的线程还没有终止，将导致调用线程挂起，直到thread指代的线程终止为止。
		* @param thread：
		*     所等待的的终止线程
		* @param status：
		*     如果status的值不等于NULL，那么它的值是通过pthread_exit传递过来的。
		* @return ：
		*     0 线程已经终止
		*     ESRCH 多个线程不能等待同一个线程完成，否则仅有一个线程会成功完成。其他线程将终止，并返回ESRCH 错误。
		*     EINVAL 一般表示thread是无效的参数
		*     EDEADLK 检查到死锁状态
		* @note 
		*     如果调用线程尚未分离，则线程ID 和status 指定的退出状态将保持不变，直到应用程序调用pthread_join() 以等待该线程。
		*     否则，将忽略status。线程ID 可以立即回收。
		*/
		pthread_join(threads[i], NULL);
	}
	
	printf("INFO: All threads have been exit!!!\n");

	return 0;
}