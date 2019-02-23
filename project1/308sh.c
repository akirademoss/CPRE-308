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

	printf(cmdPrompt);


	char line[50];
	char* linepass;
	char* cmd;
	char *p;

	char* cmd1;
	char** args;

	//allocate space for cmd
	cmd = malloc((MAXLINE + 1) * sizeof(char));

	//get the input from user
	fgets(line, MAXLINE, stdin);
	//if new line exists, replace with null terminator
    if(p=strchr(line, '\n')){
    	*p = '\0';
	}
	
	/* working code
	cmd = malloc((MAXLINE + 1) * sizeof(char));
	linepass = strtok(line, " ");
	strcpy(cmd, linepass);
	printf("%s ", &cmd[0]);
	*/

	//get the string from the input
	linepass = strtok(line, " ");
	//copy to our allocated space
	strcpy(cmd, linepass);


	//printf("%s ", &cmd[0]);


	//free(cmd);
	int i=0;
	int len;

	len = strlen(linepass);
	printf("%d", len);

	while(linepass != NULL || (i < 4)){
		linepass = strtok(NULL, " ");
		//*args = (char *) malloc((strlen(cmd) + 1) * sizeof(char));
		//initialize 
		//(*args)[0] = cmd;
		//strcpy((*args)[0], cmd);
		i++;
		if(linepass != NULL){
			printf(" %s\n", linepass);
		}
		//free(cmd);
	}

	if (strcmp(cmd, "exit") == 0){
		exit(0);
	}

	



	}
}
