#ifndef _COMM_H_
#define _COMM_H_

#include<errno.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<sys/types.h>

#define PATHNAME "."
#define PROJ_ID 0x6666



int Creat_shm(int size);
int Get_shm();
int Destory_shm(int shmid);



#endif
