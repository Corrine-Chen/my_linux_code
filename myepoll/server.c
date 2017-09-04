#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/select.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/epoll.h>
#include<unistd.h>

#define M 56


static void Usage(const char* proc)
{
	printf("usage:%s [local_ip] [local_port]\n",proc);
}

int startup(char* ip,int port )
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("socket");
		exit(2);
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
    local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);

	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		perror("bind");
		exit(3);
	}
	

	if(listen(sock,10)<0){
		perror("listen");
		exit(4);
	}

	return sock;
}

int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		Usage(argv[0]);
		return 0;
	}

	
	int listen_sock = startup(argv[1],atoi(argv[2]));



	 int ep_fd = epoll_create(256);
	 if(ep_fd<0){
		 perror("epoll_create");
		 exit(5);
	 }

	 struct epoll_event ev;
     ev.events = EPOLLIN;
	 ev.data.fd = listen_sock;

		
	if(epoll_ctl(ep_fd,EPOLL_CTL_ADD,listen_sock,&ev)<0)
	{
		perror("epoll_ctl");
		exit(6);    
	}

	int timeout = 10000;
    int nums = -1;//就绪事件的个数
    int maxevent = M;
	struct epoll_event array[M];

	while(1){
		nums = epoll_wait(ep_fd,array,maxevent,timeout);
		switch(nums){
			case -1:
				perror("epoll_wait");//epoll_wait出错
				break;
			case 0:
				printf("timeout...\n");//超时
				break;
			default:
				{
					int i=0;
					for(;i<nums;++i)
					{//遍历就绪事件
						if(array[i].data.fd==listen_sock && array[i].events & EPOLLIN){//listen_sock的读事件
							struct sockaddr_in client;
							socklen_t len = sizeof(client);
							//创建new_sock
							int new_sock = accept(listen_sock,\
									(struct sockaddr*)&client,&len);
							if(new_sock<0){
								perror("accept");
								exit(7);
							}
							//建立客户端的连接
							printf("get a new client:[%s:%d]\n",inet_ntoa(client.sin_addr),\
									ntohs(client.sin_port));
							//listen_sock的读事件完成后，此时客户端可以向客户端写数据，将关心的写时间加入句柄中
							struct epoll_event event;
							event.events = EPOLLIN;
							event.data.fd = new_sock;
							epoll_ctl(ep_fd,EPOLL_CTL_ADD,new_sock,&event);
						}else if(array[i].data.fd != listen_sock){//普通事件
							if(array[i].events & EPOLLIN)//读就绪
							{//read ready
								int buf[1024];
						    	ssize_t s = read(array[i].data.fd,buf,sizeof(buf)-1);//BUG!!!
						    	if(s<0){
							    	perror("read");
							    	close(array[i].data.fd);
							    	epoll_ctl(ep_fd,EPOLL_CTL_DEL,array[i].data.fd,0);
							    	exit(8);
						    	}else if(s==0){
							    	printf("clilent is quit\n");
							    	close(array[i].data.fd);
			    			    	epoll_ctl(ep_fd,EPOLL_CTL_DEL,array[i].data.fd,0);
						    	}else{
						        	buf[s] = 0;
						        	printf("client#:%s\n",buf);
						        	array[i].events = EPOLLOUT; 

						    	//读 取成功，将该时间再改为写
				    			epoll_ctl(ep_fd,EPOLL_CTL_MOD,\
					    		array[i].data.fd,&array[i]);
						    	}
							}else if(array[i].events & EPOLLOUT){//write ready写事件就绪
						    	const char* msg = "HTTP/1.0 OK 200\r\n\r\n\
							    	<html><ht>hello workd</ht></html>";//向网页输出hello worl
						    	array[i].events = EPOLLIN;
						    	epoll_ctl(ep_fd,EPOLL_CTL_MOD,\
										  array[i].data.fd,&array[i]);
								    }
				    		}else{//other ready
						}
					}
				}
		}
	}
	return 0;
}
