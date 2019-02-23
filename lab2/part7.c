#include <unistd.h>
int main() {
for(int i =0 ; i < 2; i ++){
execl("/bin/ls", "ls", NULL);
sleep(5);
printf("What happened?\n");
}
}
