#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/select.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<poll.h>
#include<unistd.h>

#define SIZE 1024
static void usage(const char* proc)
{
	    printf("usage:%s [local_ip] [local_port\n]",proc);
}

int startup(char* ip,int port)
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock<0){
		perror("socket");
		exit(2);
	}
			
	struct sockaddr_in client;
	client.sin_family = AF_INET;
	client.sin_port = htons(port);
	client.sin_addr.s_addr = inet_addr(ip);
							
	if(bind(sock,(struct sockaddr*)&client,sizeof(client))<0){
		perror("bind");
		exit(3);
	}
								
	if(listen(sock,10)<0){
		perror("bind");
		exit(4);
	}
	return sock;
}

int main(int argc,char* argv[])
{
	if(argc!=3){
		usage(argv[0]);
		return 1;
	}
		
	int listen_sock = startup(argv[1],atoi(argv[2]));
			
	struct pollfd pd[SIZE];
				
	int i=0;
	for(;i<SIZE;++i){
		pd[i].fd=-1;
	}
						
	pd[0].fd = listen_sock;
	pd[0].events = POLLIN;
	pd[0].revents = 0;
	int timeout = 5000;
	while(1){
												
		switch(poll(pd,SIZE,timeout)){
			case -1:
				perror("poll");
				break;
			case 0:
				printf("timeout..\n");
				break;
			default:
				{
					i=0;
					for(;i<SIZE;++i){
						if(i==0 && pd[0].revents & POLLIN){
							struct sockaddr_in client;
							socklen_t len = sizeof(client);
							int new_sock = accept(listen_sock,(struct sockaddr*)&client,&len);
							if(new_sock<0){
								perror("accept");
								exit(5);
							}
							printf("get a client:[%s:%d]\n",inet_ntoa(client.sin_addr),\
									ntohs(client.sin_port));
							int j=0;
							for(j=1;j<SIZE;++j){
								if(pd[j].fd<0){
									break;
								}//if
							}//for
							if(j==SIZE){
								printf("pd is full\n");
								break;
							}else{
								pd[j].fd = new_sock;
								pd[j].events = POLLIN;
							}//if
						}else if(i!=0){
							if(pd[i].revents & POLLOUT){
								char buf[1024];
								printf("Please Enter:");
								fflush(stdout);
								read(0,buf,sizeof(buf)-1);
								write(pd[i].fd,buf,strlen(buf)-1);
								pd[i].events = POLLIN;
							}else if(pd[i].revents & POLLIN){
								char msg[1024];
								ssize_t s = read(pd[i].fd,msg,sizeof(msg)-1);
								if(s<0){
									perror("read");
									exit(6);
								}else if(s==0){
									printf("clinet is quit\n");
									close(pd[i].fd);
									pd[i].fd = -1;
								}else{
									msg[s] = 0;
									printf("client say:%s",msg);
									pd[i].events = POLLOUT;
								}//read
							}else{
							}//
						}//else if
					}//for
				}//default
		}//switch
	}//while
	return 0;
}
