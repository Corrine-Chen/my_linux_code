#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>


static void* Usage(const char* proc)
{
	printf("Usage:%s[local_ip][local_port]\n",proc);
}

int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		Usage(argv[0]);
		return 1;
	}

//	int fd = open("./log",O_CREAT|O_RDWR);
//	if(fd < 0)
//	{
//		perror("open()");
//		return fd;
//	}
//	close(1);

//	int ret = dup2(fd,1);
  	int sock = socket(AF_INET,SOCK_STREAM,0);
  	if(sock < 0 )
  	{
  	    perror("socket");
  		exit(2);
	}
	struct sockaddr_in server_sock;
	server_sock.sin_family = AF_INET;
	server_sock.sin_port = htons(atoi(argv[2]));
	server_sock.sin_addr.s_addr = inet_addr(argv[1]);
	if(connect(sock,(struct sockaddr*)&server_sock,sizeof(server_sock))<0)
	{
		printf("connect failed ");
		exit(3);
	}
	printf("connect success\n");
	char  buf[1024];
	while(1)
	{
		printf("Please Enter#");
		fflush(stdout);
		ssize_t s=read(0,buf,sizeof(buf)-1);
		if(s>0)
		{
			buf[s-1]=0;
			write(sock,buf,strlen(buf));
	    	ssize_t	s = read(sock,buf,sizeof(buf)-1);
			if(s>0)
			{
				buf[s] = 0;
				printf("server ehco:%s\n ",buf);
			}

		}

	//  	memset(buf,'\0',sizeof(buf));
//	  	fgets(buf,sizeof(buf),stdin);
  //    	if(strncmp("quit",buf,4)==0)
///		{
//			break;
//		}
	}
	
	return 0;
}
