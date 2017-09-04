#include<stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>

int fds_array[sizeof(fd_set)*8];
static void* Usage(const char* proc)
{
	printf("Usage:%s[local_ip][local_port]\n",proc);
}

int starup(const char* ip,int port)
{
	int  sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		perror("socket");
		return 1;
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);


	int b=bind(sock,(struct sockaddr*)&local,sizeof(local));
	if(b<0)
	{
		perror("bind");
		return 2;
	}


	if(listen(sock,10)<0)
	{
		perror("listen");
		return 3;
	}
	return sock;
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		Usage(argv[0]);
		return 4;
	}


	int listen_sock = starup(argv[1],atoi(argv[2]));
	fd_set rfds;
	fd_set wfds;
	FD_ZERO(&rfds);
	FD_ZERO(&wfds);
	int i=0;
	int num = sizeof(fds_array)/sizeof(fds_array[0]);
	for(; i<num; ++i)
	{
		fds_array[i] = -1;
	}
	fds_array[0] = listen_sock;
	while(1)
	{
		int maxfd = -1;
		for(i=0; i<num; i++)
		{
			if(fds_array[i]==-1)
			{
				continue;
			}
			FD_SET(fds_array[i],&rfds);
			FD_SET(fds_array[i],&wfds);
			if(maxfd<fds_array[i])
			{
				maxfd = fds_array[i];
			}
		}

		switch(select(maxfd+1,&rfds,&wfds,NULL,NULL))
		{
			case 0:
				printf("timeout...\n");
				break;
			case -1:
				perror("select");
				break;
			default:
				{   ///at least one read event ready
					for(i=0; i<num; i++)
					{
						struct sockaddr_in client;
						socklen_t len = sizeof(client);
						if(fds_array[i]<0)
						{
							continue;
						}
						if(i==0 && FD_ISSET(listen_sock,&rfds))
						{
							int new_sock = accept(listen_sock,\
									(struct sockaddr*)&client,&len);
							if(new_sock<0)
							{
								perror("accept");
								continue;
							}
							printf("get a client [%s:%d]\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
							int j=0;
							for(;j<num; j++)
							{
								if(fds_array[j]<0)
								{
									break;
								}
							}
							if(j==num)
							{
								printf("fd_set full\n");
								close(new_sock);
							}
							else
							{
								fds_array[j] = new_sock;
							}
						}
						else if(i!=0 &&( FD_ISSET(fds_array[i],&rfds)||(FD_ISSET(fds_array[i],&wfds))))
						{
							char buf[1024];
							if(FD_ISSET(fds_array[i],&rfds))
							{
							//	char buf[1024];
							    ssize_t s= read(fds_array[i],buf,sizeof(buf)-1);
							    if(s>0)
						    	{
							    	buf[s]=0;
							    	printf("client#%s\n",buf);

									if(FD_ISSET(fds_array[i],&wfds))
									{
										printf("please enter:");
										fflush(stdout);
										ssize_t r = read(0,buf,sizeof(buf)-1);
										if(r>0)
										{
											buf[r] = 0;
											ssize_t w = write(fds_array[i],buf,strlen(buf));
        					            	if(w>0)
        				                	{
										    	buf[w] = 0;
								    	    	printf("server echo:%s\n",buf);
        				                    }
        				                    else if(w==0)
        				                    {
        					                 	printf("no data enter\n");
        					                	close(fds_array[i]);
        					                	fds_array[i] = -1;
        					                }
        				                    else
        				                    {
        					                	printf("server error\n");
        					                	close(fds_array[i]);
        					                	fds_array[i] = -1;
								    		}
										}
								  	}
						    	}
						    	else if(s==0)
						    	{
							    	printf("client is quit\n");
							    	close(fds_array[i]);

									fds_array[i] = -1;
							    }
						    	else
						    	{
 							    	printf("client error\n");
							    	close(fds_array[i]);
							 
									fds_array[i] = -1;
						    	}
							}

						}
						else{

						}
					}
				}
			break;
		}

	}

}
