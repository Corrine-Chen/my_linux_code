#include"comm.h"

int comm_shm(int size,int flags)
{
	int  key=ftok(PATHNAME,PROJ_ID);
	if(key<0)
	{
		perror("ftok");
		return -1;
	}
	int shmid=shmget(key,size,flags);
	if(shmid<0)
	{
		perror("shmid");
		return -2;
	}
	return shmid;

}
int Creat_shm(int size)
{
	return comm_shm(4096,IPC_CREAT|IPC_EXCL|0666);
}
int Get_shm()
{
	return comm_shm(0,IPC_CREAT);
}
int Destory_shm(int shmid)
{
	if(shmctl(shmid,IPC_RMID,NULL)<0)
	{
		perror("shmctl");
		return -1;
	}
}
