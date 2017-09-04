#include<stdio.h>
#include<pthread.h>

static int count=0;
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
void* start_routine(void* val)
{
	int t=5000;
	while(t)
	{

    	pthread_mutex_lock(&lock);
		int val=0;
		val=count;
		printf("%d\n",count);
		t--;
		count=val+1;
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}
int main()
{
//	pthread_mutex_init(lock,NULL);
	void* val=NULL;
	pthread_t tid1,tid2,tid3,tid4;
	pthread_create(&tid1,NULL,*start_routine,NULL);
	pthread_create(&tid2,NULL,*start_routine,NULL);
	pthread_create(&tid3,NULL,*start_routine,NULL);
	pthread_create(&tid4,NULL,*start_routine,NULL);
	pthread_join(tid1,&val);
	pthread_join(tid2,&val);
	pthread_join(tid3,&val);
	pthread_join(tid4,&val);
	printf("%d\n",count);
//	pthread_mutex_destory(&lock);
	return 0;
}
