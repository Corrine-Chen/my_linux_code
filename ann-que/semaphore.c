#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

#define  SIZE 64

sem_t blanks,datas;
int queue[SIZE];


void* Producter(void* arg)
{
	int i=0;
	while(1)
	{
		sem_wait(&blanks);
		int data=rand()%1234;
		queue[i]=data;
		printf("Producter:  %d\n",data);
		sem_post(&datas);
		i++;
		i%=SIZE;
		sleep(1);
	}
}
void* Consumer(void* arg)
{
	int i=0;
	while(1)
	{
		sem_wait(&datas);
		int data;
		data=queue[i];
		printf("Consumer:  %d\n",data);
		i++;
		i%=SIZE;
		sem_post(&blanks);
	}
}
int main()
{
	sem_init(&blanks,0,64);
	sem_init(&datas,0,0);
	pthread_t tid1;
	pthread_t tid2;
	pthread_create(&tid1,NULL,*Producter,NULL);
	pthread_create(&tid2,NULL,*Consumer,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);


	return 0;
}
