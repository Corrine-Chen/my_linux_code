#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<error.h>
#include<sys/wait.h>
#include<sys/types.h>
int main()
{
	char cmd[36];
	while(1)
	{
		printf("[test@cxt myshell]#:");
		fflush(stdout);
		ssize_t _s=read(0, cmd,sizeof(cmd));
		if(_s>0)
		{
			cmd[_s-1]='\0';
		}
		else
		{
			perror("read\n");
			return 1;
		}
		char *_argv[32];
		_argv[0]=cmd;
		int i=0;
		char *start=cmd;
		while(*start)
		{
			if(isspace(*start))
			{
		 		*start='\0';
				start++;
				_argv[i]=start;
				i++;
				continue;
			}
			start++;
		}
		_argv[i]=NULL;
        pid_t id=fork();
		if(id<0)
		{
			perror("fork");
		}
        else if(id==0)  //child ->run cmd
         {
			 execvp(_argv[0],_argv);
        	 exit(1);
         }
        else
        { 
            //printf("pid=%d ppid=%d\n",getpid(),getppid());
            int status=0;
	        pid_t	ret=waitpid(id, &status, 0);
		if(ret>0&&WIFEXITED(status))
	    {

		//	printf("exitcode=%d  signal=%d\n", (status>>8)&0xff, status&0xff);
		}
		else
		{
			perror("waitpid.");
		}
}
}

}
