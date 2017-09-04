#include<stdio.h>
#include<unistd.h>
int main()
{
	int i=0;
	char bar[102];
	bar[0]='\0';
	const char *p="-\\|//";
	while(i<=100){
		printf("[%-100s] [%d%%] %c \r",bar,i,p[i%4]);
		fflush(stdout);
		bar[i++]='#';
		bar[i]='\0';
		usleep(500000);
}
printf("\n");
return 0;
}
