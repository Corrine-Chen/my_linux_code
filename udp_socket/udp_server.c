
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

    int sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock < 0 )
	{
    	perror("socket");
		return 2;
	}

    char buf[1024];
    struct sockaddr_in local;
    local.sin_family = AF_INET;
	local.sin_port = htons(atoi(argv[2]));
    local.sin_addr.s_addr = inet_addr(argv[1]);
	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		perror("bind");
    	return 3;
	}
	while(1)
	{

        struct sockaddr_in client;

    	socklen_t len = sizeof(client);
	//	printf("get a new client ,%s:%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    	int r = recvfrom(sock ,buf, sizeof(buf)-1, 0,(struct sockaddr*) &client ,& len);
    	if(r<0)
    	{
    		perror("recvfrom");
    		return 3;
    	}
		buf[r] = 0;
		char send[1024];
		printf("%s\n",buf);
		int s = sendto(sock, buf,r,0,(struct sockaddr*)&client,len);
    	if(s < 0 )
		{
			perror("sentto");
    		return 4;
    	}
	}
	return 0;
}




