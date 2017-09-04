#ifndef __COMM_H__
#define __COMM_H__
#include<stdio.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<errno.h>
#include<string.h>

#define SERVER_TYPE 1
#define CLIENT_TYPE 2
#define PATHNAME "."
#define PROJ_ID 0x6666
#define SIZE 128

struct msgbuf {
	long mtype;       /* message type, must be > 0 */
	char mtext[SIZE];    /* message data */
 };
int CreatmesQueue();
int GetmesQueue();
int SentmesQueue(int mspid,long type,const char* _info);
int ReceivermesQueue(int msgid,long type,char out[]);
int DestorymesQueue(int mspid);

#endif
