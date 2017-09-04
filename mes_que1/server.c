#include"comm.h"

int main()
{
	int msgid=CreatmesQueue();
	char out[SIZE];
	while(1)//receive->send
	{
		ReceivermesQueue(msgid,CLIENT_TYPE,out);
		printf("client>%s\n",out);
		printf("Please enter $:");
		fflush(stdout);
		ssize_t s=read(0,out,sizeof(out)-1);
		if(s > 0)
		{
			out[s-1]='\0';
			SentmesQueue(msgid,SERVER_TYPE,out);
		}
	}

	DestorymesQueue(msgid);


	return  0;
}
