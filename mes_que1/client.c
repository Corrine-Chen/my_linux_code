#include"comm.h"

int main()
{
	int msgid=GetmesQueue();
	char out[SIZE];
	while(1)//sent->rece
	{//send
		printf("please enter $: ");
		fflush(stdout);
		ssize_t s=read(0,out,sizeof(out)-1);
		if(s>0)
		{
			out[s-1]='\0';
			SentmesQueue(msgid,CLIENT_TYPE,out);
		}
		//rece
		ReceivermesQueue(msgid,SERVER_TYPE,out);
		printf("server >%s\n",out);

	}



	return  0;
}
