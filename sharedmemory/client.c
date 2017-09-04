#include"comm.h"


int main()
{

    int shmid =	Get_shm();
	sleep(5);
	char* shm_at=shmat(shmid,NULL,0);
	while(1)
	{
		printf("%s\n",shm_at);
		sleep(1);
	}
	shmdt(shm_at);
//	destory_shm(shmid);
	return 0;
}
