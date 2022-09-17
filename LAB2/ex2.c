#include <sys/types.h>
       #include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
fork();
fork();
usleep(1);
printf("Process %d's parent process ID is %d\n", getpid(), getppid());
return 0;
}
