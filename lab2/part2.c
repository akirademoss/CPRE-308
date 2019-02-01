#include <stdio.h>
int main() {
fork();
fork();
//usleep(1);
// NOTE I am running this on Linux Ubuntu Bionic Beaver 18.04 LTS
// In 3.2 final points part nothing changed with the PIDs
printf("Process %d’s parent process ID is %d\n", getpid(), getppid());
//sleep(2);
return 0;
}