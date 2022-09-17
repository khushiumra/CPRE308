#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include<stdlib.h>

int main () {
int ret;
ret = fork();

printf("The ret value is: %d\n", ret);

if(ret == 0)
{
	/* this is the child process */
printf("The child process ID is %d\n", getpid());
printf("The child's parent process ID is %d\n", getppid());
}
else {
	/*this is the paremt process */
printf("The parent process ID is %d\n", getpid());
printf("The parent's parent process ID is %d\n", getppid());
}
sleep(2);
return 0;
}
