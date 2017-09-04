#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<string.h>
#include <netinet/in.h>
#include<pthread.h>


static void usage(const char* proc)
{
		printf("Usage:%s [local_ip] [local_port]\n",proc);
}

int startup(const char* _ip,int _port)
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0 )
	{
		perror("socket");
		exit(2);
	}
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(_port);
	local.sin_addr.s_addr = inet_addr(_ip);

	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		perror("bind");
		exit(3);
	}

	if(listen(sock,10) < 0)
	{
		perror("listen");
		exit(4);
	}
	return sock;
}

void* handlerRequest(void* arg)
{
	int new_sock = (int)arg;
	while(1)
	{
		char buf[10240];
		size_t s=read(new_sock,buf,sizeof(buf)-1);
		if(s>0)
		{
			buf[s] =0;
			printf("client:%s\n",buf);
			write(new_sock,buf,strlen(buf));
		}
		else if(s==0)
		{
			close(new_sock);
			printf("client quit\n");
			break;
		}
		else
    	{
	    	perror("read");
	    	close(new_sock);
	    	break;
    	}
	}
}
  
  //./tcp_server ip port
int main(int argc,char* argv[] )
{
	if(argc!=3)
	{
		usage(argv[0]);
		return 1;
	}

    int	listen_sock = startup(argv[1],atoi(argv[2]));
////while(1)
////{
////	struct sockaddr_in client;
////	socklen_t len = sizeof(client);

////	int new_sock = accept(listen_sock,\
////			(struct sockaddr*)&client,&len);
////	if(new_sock<0)
////	{
////		perror("accept");
////		continue;
////	}

////	printf("get a new client ,%s:%d\n",\
////			inet_ntoa(client.sin_addr),\
////			ntohs(client.sin_port));

////	pthread_t id;
////	pthread_create(&id,NULL,handlerRequest,(void*)new_sock);
////	pthread_detach(id);
////}

      while(1)
      {
      	struct sockaddr_in client;
      	socklen_t len = sizeof(client);
    
      	int listen_sock = startup(argv[1],atoi(argv[2]));
      	int new_sock = accept(listen_sock,(struct sockaddr*)&client,&len);
    
      	if(new_sock<0)
      	{
      		perror("acc");
      		continue;
      	}
      	printf("get a new client ,%s:%d\n",inet_ntoa(client.sin_addr),
      			ntohs(client.sin_port));
  
  
      	pid_t id = fork();
      	if(id<0)
      	{
      		close(new_sock);
      	}
      	else if(id==0)//child
      	{
      		close(listen_sock);
      		if(fork()>0)
      		{
      			exit(0);
      		}
      		while(1)
      		{
    
      			char buf[1024];
      			ssize_t s= read(new_sock,buf,sizeof(buf)-1);
      			if(s>0)
      			{
      				buf[s]=0;
      				printf("client: %s\n",buf);
      				printf("client: %s\n",buf);
      				write(new_sock,buf,strlen(buf));
      		    }
      			else if(s==0)
      			{	
      				close(new_sock);
      				printf("client is quit\n");
      				break;
      			}
    
      			else
      			{
      		    
      				perror("read");
      				exit(5);	    
  
      			}
      		}
      	}
      	else 
      	{
      		close(new_sock);
      	}
  
  
      }

}


//    while(1)
//    {
//    	struct sockaddr_in client;
//    	socklen_t len = sizeof(client);
//  
//    	int listen_sock = startup(argv[1],atoi(argv[2]));
//    	int new_sock = accept(listen_sock,(struct sockaddr*)&client,&len);
//  
//    	if(new_sock<0)
//    	{
//    		perror("acc");
//    		continue;
//    	}
//    	printf("get a new client ,%s:%d\n",inet_ntoa(client.sin_addr),
//    			ntohs(client.sin_port));
//
//
//    	pid_t id = fork();
//    	if(id<0)
//    	{
//    		close(new_sock);
//    	}
//    	else if(id==0)//child
//    	{
//    		close(listen_sock);
//    		if(fork()>0)
//    		{
//    			exit(0);
//    		}
//    		while(1)
//    		{
//  
//    			char buf[1024];
//    			ssize_t s= read(new_sock,buf,sizeof(buf)-1);
//    			if(s>0)
//    			{
//    				buf[s]=0;
//    				printf("client: %s\n",buf);
//    				printf("client: %s\n",buf);
//    				write(new_sock,buf,strlen(buf));
//    		    }
//    			else if(s==0)
//    			{	
//    				close(new_sock);
//    				printf("client is quit\n");
//    				break;
//    			}
//  
//    			else
//    			{
//    		    
//    				perror("read");
//    				exit(5);	    
//
//    			}
//    		}
//    	}
//    	else 
//    	{
//    		close(new_sock);
//    	}
//
//
//    }
//}
  
  
  
  
  
///hile(1)
///
/// 	struct sockaddr_in client;
/// 	socklen_t len = sizeof(client);
/// 	int listen_sock = startup(argv[1],atoi(argv[2]));
/// 	int new_sock = accept(listen_sock,(struct sockaddr*)&client,&len);

/// 	if(new_sock<0)
/// 	{
///     	perror("acc");
///     	continue;
/// 	}

///     printf("get a new client ,%s:%d\n",inet_ntoa(client.sin_addr),\ 												ntohs(client.sin_port));
/// 	while(1)
/// 	{
///     	char buf[1024];

/// 	    ssize_t s= read(new_sock,buf,sizeof(buf)-1);

///     	if(s>0)
/// 		{
/// 			buf[s]=0;
/// 	    	printf("client: %s\n",buf);
/// 	    	write(new_sock,buf,strlen(buf));
///     	}
///     	else if(s==0)
///     	{	

/// 	    	close(new_sock);
/// 	    	printf("client is quit\n");
/// 	    	break;
///     	}
///     	else
///     	{
/// 	    	perror("read");
/// 	    	exit(5);
///     	}
/// 	}
///  }
///}

  


