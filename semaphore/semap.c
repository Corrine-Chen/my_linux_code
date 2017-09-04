#include"semap.h"
int makesem(int nsems,int flag)
{
	int sem;
	key_t key;
	key=ftok(PATH,PROJ_ID);
	if(key<0)
	{
		perror("ftok");
	}
	sem=semget(key,nsems,flag);
	if(sem <0)
	{
		perror("semget");
	}
	return 0;
}
int creatsem(int nsems)
{
    return makesem(nsems,IPC_CREAT |IPC_EXCL|0666); 
}
int getsem()
{
    return makesem(0, IPC_CREAT);
}
int destorysem(int semid)
{
	int ret = semctl(semid,0,IPC_RMID);
	if(ret<0)
	{
		perror("semctl1");
	}
	return 0;
}
int initsem(int semid,int which,int val)
{
	union semun un;
	un.val=val;
	if(semctl(semid,which,SETVAL,un)<0)
	{
		perror("semstl2");
	}
	return 0;
}
int comm(int semid,int which,unsigned nosps)
{
	struct sembuf sbuf;
	sbuf.sem_num=which;
	sbuf.sem_op=nosps;
	sbuf.sem_flg=0;
	if(semop(semid,&sbuf,1)<0)
	{
		perror("semop");
		return -1;
	}
	return 0;

}
int P(int semid,int which)
{
	return comm(semid,which,-1);
}
int V(int semid,int which)
{
    return comm(semid,which,1);
}
