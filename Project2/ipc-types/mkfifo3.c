#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define PIPE_READ_END 0
#define PIPE_WRITE_END 1

int main(){
	FILE* f;
	mkfifo(“./myfifo”, 0666);
	while(1){
		f = fopen(“./myfifo”, “w”);
		char usrin[512];
		scanf(“%511s”, &usrin);
		fprintf(f, “%s\n”, usrin);
		fflush(f);
		fclose(f);
 }

	return 0;
}

Then can use tail -f myfifo to get output in another terminal
