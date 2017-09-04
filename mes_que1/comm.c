#include"comm.h"


int comm_que(int msflg)
{
	int key=ftok( PATHNAME,PROJ_ID);
	if(key<0)
	{
		perror("ftok");
		return -1;
	}
	int mspid=msgget(key,msflg);
	if(mspid<0)
	{
		perror("mesget");
		return -2;
	}
	return mspid;

}
int CreatmesQueue()
{
	return comm_que(IPC_CREAT|IPC_EXCL|0666);
}
 int GetmesQueue()
 {
 	return comm_que(IPC_CREAT);
 }
 int SentmesQueue(int mspid,long type,const char* _info)
{
	struct msgbuf buf;
	buf.mtype=type;
    strcpy(buf.mtext,_info);
    if(msgsnd(mspid,&buf,sizeof(buf.mtext),0)<0)
	{
		perror("msgsnd");
		return -1;
	}
	return 0;

}
int ReceivermesQueue(int msgid,long type,char out[])
{
	struct msgbuf buf;
	if(msgrcv(msgid,&buf,sizeof(buf.mtext),type,0)<0)
	{
		perror("msgrcv");
		return -1;
	}
	strcpy(out,buf.mtext);
	return 0;
}
int DestorymesQueue(int mspid)
{
	if(msgctl(mspid,IPC_RMID,NULL)<0)
	{
		perror("msgctl");
		return -1;
	}
}
