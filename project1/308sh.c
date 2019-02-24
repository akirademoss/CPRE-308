#include "include.h"
#include <limits.h>
#define MAXLINE  50

//boolean type
typedef enum bool { false, true };

/**
 * Code to parse user input into an array of strings
 */
char** parse(void){
	//2d array - pointer to pointer - string array for cmdArgs
	char** args = calloc(3,(MAXLINE + 1) * sizeof(char));
	char line[50];
	char* linepass;
	char* p;
	//gets the input from user, replace '\n' with '\0', then tokenize input
	fgets(line, MAXLINE, stdin);
    if(p=strchr(line, '\n')){
    	*p = '\0';
	}
	linepass = strtok(line, " ");
	args[0] = linepass;
	//gets arguments preceeding inital command and stores them into an array
	int i = 1;
	while(linepass != NULL){
		linepass = strtok(NULL, " ");
		if(linepass != NULL){
			args[i] = linepass;
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
enum bool builtIn(char** args){
	char cwd[PATH_MAX];
	//builtIn commands logic
	if (strcmp(args[0], "exit") == 0){ exit(0);}
	else if (strcmp(args[0], "pid") == 0){ printf("PID: %d\n", getpid());}
	else if (strcmp(args[0], "ppid") == 0){ printf("PPID: %d\n", getppid());}
	else if (strcmp(args[0], "get") == 0){ printf("%s\n", getenv(args[1]));}
	else if (strcmp(args[0], "cd") == 0){ if(args[1] != NULL){ chdir(args[1]);}}
	else if (strcmp(args[0], "pwd") == 0){ 
		if (getcwd(cwd, sizeof(cwd)) != NULL) {printf("%s\n", cwd);} else { perror("getcwd() error");}}
	else if (strcmp(args[0], "set") == 0){ 
		if(args[1] != NULL){if(args[2] == NULL){unsetenv(args[1]);}else{ setenv(args[1], args[2], 1);}}}
	else{
		return false;
	}
	return true;
}

void executable(char** args){
	printf("begin executable: %s\n", args[0]);
	int failed = 0;
	char* command = malloc((MAXLINE + 1) * sizeof(char));
	strcpy(command, args[0]);
	failed = execvp(command, args);
	if(failed <0){
		printf("Cannot exec command '%s': No such file or path variable exists\n", command);
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
	if(builtIn(cmdArgs) < 1){
		printf("main before executable: %s\n", cmdArgs[0]);
		executable(cmdArgs);
	}

	}
}
