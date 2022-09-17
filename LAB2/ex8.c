#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include<stdlib.h> 
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
int child, status;

child = fork();
if(child == 0){
srand(time(NULL));
if(rand() < RAND_MAX/4) {
/* kill self with a signal */
kill(getpid(), SIGTERM);
}
return rand();
}
else {
wait(&status);
if (WIFEXITED(status)) {
printf("child exited with satus %d\n", WEXITSTATUS(status));
} else if (WIFSIGNALED(status)) {
printf("Child exited with signal %d\n", WTERMSIG(status));
}
}
return 0;
}

