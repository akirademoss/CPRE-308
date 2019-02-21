#include "include.h"

int main(int argc, char *argv[]){
	char* cmdPrompt;
	if(argc > 1 && argv[1] == "-p") {
		sleep(1);
		cmdPrompt = strcat(argv[2], "> "); 
	}
	else{
		 cmdPrompt = "308sh> ";
	}

	while(1){

	printf(cmdPrompt);


	char line[50];
	char* cmd;
	char* args[4];
	char pos*;

	fgets(line, 50, stdin);
	if((pos=strchr(line, '\n)) != NULL){
		*pos = '\0';
	}

	cmd = strtok(line, " ");
	int i=0;
	while(cmd != NULL){
		args[i] = strtok(NULL, " ");
		i++;
	}

	if (strcmp(cmd, "exit") == 0){
		exit(0);
	}
	if (strcmp(cmd, "exit") == 0){
		exit(0);
	}
	if (strcmp(cmd, "exit") == 0){
		exit(0);
	}
	if (strcmp(cmd, "exit") == 0){
		exit(0);
	}
	if (strcmp(cmd, "exit") == 0){
		exit(0);
	}




	}
}
