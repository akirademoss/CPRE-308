/**
 * @author Akira DeMoss
 * @date 2/24/19
 */

#include "include.h"
#include <limits.h>
#define MAXLINE  50

/**
 * Boolean type definition
 */
typedef enum bool { false, true };

/**
 * Code to get the name of the shell
 * @param argc - # of strings in command line arguments
 * @param argv - string array of commandline arguments
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
 * Code to parse user input into an array of strings
 * @return args - string array of commandline arguments
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
 * Builtin Command functionalities
 * @param args - string array of commandline arguments
 * @return true if the command is a built in command, false if the command is not
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

/**
 * Executable commands
 * @param args - string array of commandline arguments
 */
void executable(char** args){
	int failed;
	pid_t child;
	long pid_exit;
	int status;
	char* command = malloc((MAXLINE + 1) * sizeof(char));


	strcpy(command, args[0]);
	child = fork();
	if (child < 1) {
		printf("[%ld]  %s\n", ((long) getpid()), command);
		failed = execvp(command, args);
		if(failed == -1){
			printf("Cannot exec command '%s': No such file or path variable exists\n", command);
			kill(getpid(), SIGTERM);
			return;
		}
		return;
	} else {
		pid_exit = (long) child;
		wait(&status);
		if (WIFEXITED(status)) {
			printf("[%ld]  %s Exit %d\n", pid_exit, command, WEXITSTATUS(status));
		} else if (WIFSIGNALED(status)) {
			printf("[%ld]  %s Exit %d\n",  ((long) getpid()), command, WTERMSIG(status));
		}
	}
	
}

/**
 * Primary functional logic
 * @param argc - # of strings in command line arguments
 * @param argv - string array of commandline arguments
 */
int main(int argc, char *argv[]){
	char* shellName;

	shellName = getShellName(argc, argv);

	while(1){
	char* input;
	char** cmdArgs;

	printf("%s", shellName);
	cmdArgs = parse();
	if(builtIn(cmdArgs) == 0)
		{executable(cmdArgs);}
	}

	return 0;
}
