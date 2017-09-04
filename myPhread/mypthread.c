#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
void* start_routine(void*arg)
{
	int count=5;
	while(count)
	{
		pthread_t  tid=pthread_self();
	    pid_t	pid=getpid();
		printf("I am a new pthread:tid:%lu  pid:%d\n",tid,pid);
		count--;
		sleep(1);
        pthread_detach(tid);
	    //pthread_exit((void*)(123));
	    //pthread_detach(pthread_self());
	}
 //pthread_detach(pthread_self());
}
int main()
{
	pthread_t id;
	void* val=NULL;
	if(pthread_create(&id,NULL,*start_routine, NULL)!=0)
	{
		printf("%d:%s\n",id,strerror(id));
	}
	//pthread_detach(id);
  //  pthread_t  tid=pthread_self();
//	pid_t	pid=getpid();
	int ret=pthread_join(id,&val);
	//printf("I am a mian pthread:tid:%lu pid:%d\n ",tid,pid);
	printf("new pthread was died.main pthread will die:%d\n",ret);
	printf("%s\n",strerror(ret));
	return 0;
}
