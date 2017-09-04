
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<string.h>
#include <netinet/in.h>

static void* usage(const char* proc)
{
	printf("Usage:%s [local_ip] [local_port]\n",proc);
}

  //./tcp_server ip port
int main(int argc,char* argv[] )
{

	if(argc!=3)
	{
		usage(argv[0]);
		return 1;
	}
	char buf[1024];
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(atoi(argv[2]));
	local.sin_addr.s_addr = inet_addr(argv[1]);
	socklen_t len = sizeof(local);

	int sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock < 0 )
	{
		perror("socket");
		return 2;
	}
	//char * send = "hello";
	while(1)
	{
		printf("Please client enter:\n");
		char buf[1024];
		fflush(stdout);
		ssize_t s = read(0,buf,sizeof(buf)-1);
		buf[s]=0;
    	int s1 = sendto(sock, buf,strlen(buf),0,(struct sockaddr*)&local,len);
		if(s1<0)
		{
			perror("sendto");
			return 3; 
		}
		int r = recvfrom(sock ,buf, sizeof(buf)-1, 0,(struct sockaddr*) &local ,& len);
		if(r<0)
		{
			perror("recvfrom");
			return 4;
		}
		buf[r] = 0;
		printf("server ehco:%s\n ",buf);
	}
	return 0;
}





