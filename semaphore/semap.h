#ifndef __SEMAP_H__ 
#define __SEMAP_H__
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<unistd.h>
#include<wait.h>
#include<errno.h>
#define PATH "."
#define PROJ_ID 0x6666
#define nsem 1;
union semun {
     int  val;
	 struct semid_ds *buf;    
	 unsigned short  *array;  
	 struct seminfo  *__buf;
};

int creatsem(int nsems);
int getsem();
int initsem(int semid,int which,int val);
int destorysem(int semid);
int P(int semid,int which);
int v(int semid,int which);

#endif
