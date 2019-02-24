#include "include.h"
#include <limits.h>
#define MAXLINE  50

/**
 * Code to parse user input into an array of strings
 */
char** parse(void){
	//2d array - pointer to pointer - string array for cmdArgs
	char** args = calloc(3,(MAXLINE + 1) * sizeof(char));
	char line[50];
	char* linepass;
	char* p;

	//get the input from user
	//then replace '\n' with '\0'
	//next tokenize input
	fgets(line, MAXLINE, stdin);
    if(p=strchr(line, '\n')){
    	*p = '\0';
	}
	linepass = strtok(line, " ");
	args[0] = linepass;


	//get arguments preceeding inital command
	int i = 1;
	while(linepass != NULL){
		linepass = strtok(NULL, " ");
		if(linepass != NULL){
			args[i] = linepass;
			//printf statement for testing only
			//printf("%s\n", args[i]);
		}
		i++;
	}
	return args;
}

/**
 * Code to get the name of the shell
 */
char* getShellName(int argc, char* argv[]){
	char* shName;
	if(argc > 1 && argv[1] == "-p") {
		sleep(1);
		shName = strcat(argv[2], "> "); 
	}
	else{
		 shName = "308sh> ";
	}
	return shName;
}

/**
 * Builtin Command functionalities
 */
void builtIn(char** args){
	char cwd[PATH_MAX];
	if (strcmp(args[0], "exit") == 0){ exit(0);}
	if (strcmp(args[0], "pid") == 0){ printf("PID: %d\n", getpid());}
	if (strcmp(args[0], "ppid") == 0){ printf("PPID: %d\n", getppid());}
	if (strcmp(args[0], "get") == 0){ printf("%s\n", getenv(args[1]));}
	if (strcmp(args[0], "cd") == 0){ if(args[1] != NULL){ chdir(args[1]);}}
	if (strcmp(args[0], "pwd") == 0){ 
		if (getcwd(cwd, sizeof(cwd)) != NULL) {
      		printf("%s\n", cwd);
   		} else {
       		perror("getcwd() error");
		}
	}
	if (strcmp(args[0], "set") == 0){ 
		if(args[1] != NULL){
			if(args[2] == NULL){
				unsetenv(args[1]);
			}
			else{
				setenv(args[1], args[2], 1);
			}
		}
	}
}

/**
 * Primary functional logic
 */
int main(int argc, char *argv[]){
	char* shellName;

	shellName = getShellName(argc, argv);

	while(1){
	char* input;
	char** cmdArgs;

	printf("%s", shellName);
	cmdArgs = parse();
	builtIn(cmdArgs);
	}
}
