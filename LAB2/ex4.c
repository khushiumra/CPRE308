#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

int i=0, j=0, pid;
pid = fork();
if (pid == 0) {
for(i=0; i<5000000; i++)
printf("Child: %d\n", i);
} else {
for(j=0; j<5000000; j++)
printf("Parent: %d\n", j);
}
}
