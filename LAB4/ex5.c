 #include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void my_routine();

	int ret;
int main()
{
	ret = fork();
	signal(SIGINT, my_routine);
	printf("entering infinite loop \n");
	while(1)
{
	sleep(10);
}

	printf("can't get here \n");
}

	void my_routine()
{
	printf("Return value from fork = %d \n", ret);
}

