#include"semap.h"
int main()
{
	int semid=creatsem(1);
    initsem(semid,0,1);
	pid_t id=fork();
	int _semid=getsem();
	if(id<0)
	{
		perror("fork\0");
		return -1;
	}
	else if(id==0)//child
	{
		while(1)
		{
			//P(_semid,0);
			printf("hello ");
			fflush(stdout);
			sleep(1);
			printf("world\n");
			fflush(stdout);
			sleep(1);
			//V(_semid,0);
		}
	}
	else//father
	{
		while(1)
		{
			//P(semid,0);
			printf("I ");
			fflush(stdout);
			sleep(1);
			printf("DO!\n");
			fflush(stdout);
			sleep(1);
			//V(semid,0);
		}
		wait(NULL);
	}
	//destorysem(semid);

	return 0;
}
