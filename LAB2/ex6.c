#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include<stdlib.h> 
#include <signal.h>

int main() {
int i=0, child;
child = fork();
if(child ==0) {
while(1) {
i++;
printf("child at count %d\n", i);
/* sleep for 1/100 of a second */
usleep(10000);
}
}
else {
printf("Parent sleeping \n");
sleep(10);
kill(child, SIGTERM);
printf("Child has been killed. Waiting for it... \n");
wait(NULL);
printf("Done. \n");
}
return 0;
}
