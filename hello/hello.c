#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>


//int main()
//{
//   pid_t id = fork();
//   if(id == 0)//child
//   {
//   	printf("I am child ,my pid is:%d;my father pid is:%d \n",getpid(),getppid());
//   }
//   else if(id > 0)//parent
//   {
//   	sleep(2);
//   	printf("I am father:%d \n",getpid());
//   }
//   else
//   {
//   	perror("fork error");
//   	return -1;
//   }
//   return 0;
//}
//
void* start_routine1()
{
	printf("I am a thread1 ,my tid is:%u\n",pthread_self());
	return NULL;
}
void* start_routine2()
{
	printf("I am a thread1 ,my tid is:%u\n",pthread_self());
	return NULL;
}
int main()
{
	pthread_t tid1;
	pthread_t tid2;
	pthread_create(&tid1,NULL, start_routine1, NULL);
	pthread_create(&tid2,NULL, start_routine2, NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	return 0;
}












