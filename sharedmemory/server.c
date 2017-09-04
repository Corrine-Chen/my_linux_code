#include"comm.h"

int main()
{
	int count=0;
	int shmid=Creat_shm(4096);
	sleep(5);
	char* sh_mat=shmat(shmid,NULL,0);
	sleep(5);
	while(count<4096)
	{
		sh_mat[count]='A'+count%26;
		sleep(1);
		count++;
		sh_mat[count]=0;
	}
	 shmdt(sh_mat);
	 sleep(5);
	 Destory_shm(shmid);
	return 0;
}

