#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void creat_daemon()
{

	umask(0);
	pid_t id = fork();
	if(id > 0)//father
	{
		return ;
	}
	else if(id < 0)
	{
		perror("fork");
		return ;
	}

	setsid();

	signal(SIGCHLD,SIG_IGN);

	if(id = fork()<0)
	{
		printf("fork errot\n");
		return ;
	}
	else if(id!=0)
	{
		return;
	}

	if(chdir("/")<0)
	{
		printf("chdir error\n");
		return ;
	}
	close(0);
 	close(1);
    close(2);
}
int main()
{
	creat_daemon();
	while(1)
	{
		sleep(1);
	}
	return 0;
}
