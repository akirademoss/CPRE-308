#include "include.h"
#define MAXLINE  50



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

	printf("%s", cmdPrompt);


	char line[50];
	char* linepass;
	char* cmd;
	char *p;

	char** args = calloc(2,(MAXLINE + 1) * sizeof(char));


	//allocate space for cmd
	cmd = malloc((MAXLINE + 1) * sizeof(char));

	//get the input from user
	fgets(line, MAXLINE, stdin);
	//if new line exists, replace with null terminator
    if(p=strchr(line, '\n')){
    	*p = '\0';
	}

	//get the string from the input
	linepass = strtok(line, " ");

	//copy to our allocated space
	strcpy(cmd, linepass);

	//change into a getArgs();
	int i = 0;
	while(linepass != NULL){
		//tokenize arg
		linepass = strtok(NULL, " ");
		//check for the null arg
		if(linepass != NULL){
			args[i] = linepass;
			printf("%s\n", args[i]);
		}
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

	if (strcmp(cmd, "exit") == 0){
		exit(0);
	}

	if (strcmp(cmd, "exit") == 0){
		exit(0);
	}
	



	



	}
}
