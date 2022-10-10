/* My UNIX Shell
Programming Project I
CprE 308 - 2022

Name: Khushveen Kaur Umra
NetID: kumra@iastate.edu 

IMPORTANT: To run this program, execute:

make clean && make && ./shell "uName> " */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

char uName[30]; // Variable to save the user name when prompted
int bgStat; // To check and save the status of the bg process
int bgPID; // To check and save the PID of the bg process

#define MAX_INPUT_LENGTH 256 // The maximum length of each string being prompted

char rawCommand[MAX_INPUT_LENGTH]; // Variable for the raw command entered by the user
char* args[MAX_INPUT_LENGTH]; // To split the command prompted in seperate args

void bgProcess();
void customCommand(char **argv);
void commandExecution();
void argsBuild(char** list);
void processPID();
void processPPID();
void workingPWD();
void changeDirectory();
void setVariable();
void getVariable();
void programCommand(bool isBackground);
bool isBackground();

/* This is the 'main' of the program. 
It runs an infinite loop accepting inputs from the user and runs commands until the user wishes to exit
When the user requests to exit, the function will return '0' */

int main(int argc, char** argv) {

while(1)
{
	bgProcess();
	customCommand(argv);
	commandExecution();
}
	return 0;
}

/* The following function is responsible for printing the username of the shell.
It also accepts a '-p <prompt> option on the command line when it is initiated, and the <prompt> option will become the user prompt.
If the option is not specified, the default prompt of "308sh> " will be used. */

void customCommand(char **argv)
{
	strcpy(uName, "308sh> ");
	
	if(argv[1] != NULL)
	if(strcmp(argv[1], "-p") == 0)
{
	strcpy(uName, argv[2]);
}

	int x = 0;
	for(x = 0; x <= strlen(uName); x++)
{
	if(uName[x] == '\"')
{
	uName[x] = '\0';
}	
}
	printf("%s", uName);
}

/* 'commandExecution' is a function which will execute the prompted built-in commands and other Linux commands
It supports two types of user commands, 1) built-in commands, 2) program commands 
It also exits the program when requested by the user */

void commandExecution() 
{
	argsBuild(args);

/* Here we will check if the user does not input any command. 
It will check for all the possible ways of knowing there is no input, or if there is a blank line entered */

	if(args[0] == NULL ||
	strcmp(args[0], " ") == 0 ||
	strcmp(args[0], "\n") == 0 ||
	strcmp(args[0], "\0") == 0 ||
	strcmp(args[0], "\t") == 0 )
{	
	return;
}

/*Here we will check if the user has requested to 'exit' the program. 
This will be executed when the user has typed 'exit, and will handle the program accordingly 
Once the user has typed 'exit', it will alert the user that the program is being terminated. */

if(strcmp(args[0],"exit") == 0)
{	
	printf("The program is now being terminated.. \n");
	exit(0); 
}

/* If the user does not request to exit the program, the process will continue and will print the following values of the ongoing process */

/* The following statements will be executed when the user has prompted built-in commands to interact with the shell program, such as cd, cd<dir>, etc. */

/* This will print the PID of the current ongioing process */

else if(strcmp(args[0], "pid") == 0)
{
	processPID();
}

/* This will print the parents PID of the current ongoing process */

else if(strcmp(args[0], "ppid") == 0)
{	
	processPPID();
}

/*This will print the current working directory */

else if(strcmp(args[0], "pwd") == 0)
{
	workingPWD();
}

/* This will be executed when the user prompts to change the directory from the current working directory */

else if(strcmp(args[0], "cd") == 0)
{
	changeDirectory();
}

/* This will set and reset an environment variable */

else if(strcmp(args[0], "set") == 0)
{
	setVariable();
}

/* This will get an environment variable */

else if(strcmp(args[0], "get") == 0)
{
	getVariable();
}

/* The following else statement will be executed when the user as prompted program(LINUX) commands, and it will handle the program accordingly 
It will make sure that the commands being prompted by the user are not "blank" inputs, and instead are program commands */

else {
	if(args[0] != NULL 
	&& !strcmp(args[0], " ") == 0
	&& !strcmp(args[0], "\n") == 0
	&& !strcmp(args[0], "\0") == 0 
	&& !strcmp(args[0], "\t") == 0 )
{
	programCommand(isBackground());

		}
	}
}

/* The following function will be executed when the user has prompted program(LINUX) commands and will handle the program accordingly.
This will also ensure to check if the processes have been terminated with or without an error.
This will also handle any ongoing processes in the background */

void programCommand(bool isBackground) 
{
	int ret = fork(); // 'ret' is the PID of the child process
	int status;

	if(ret == 0)

/* The following if-else statements are for the Child process */

{
	if(!isBackground)

	printf("Child %d: Started   \n", getpid());


	else

	printf("Child %d: Started   (Bg) \n", getpid());


	// This will execute the commands prompted
	
		execvp(args[0], args);

	/* If "execvp" fails, the following statement will displayed to alert the user of an error
	   It will also manually terminate the child process */

	printf("Cannot execute %s: No such file or directory found \n", args[0]);
	exit(1);
}

/* The following if-else statements are for the Parent Process */

	else{

		if(!isBackground) {
	/* It will wait only if the process is not a background process */

	waitpid(ret, &status, NULL);

	if(status) 
{
	printf("ERROR %d: %s Exit 1 \n", ret, args[0]);
}

 /* If not, the process will be terminated normally */

	else {
	printf("Child %d, Exit %d  \n", ret, status);
}
}

/* If it is a background process, it will set the variables accordingly */

	else {
	bgStat = status;
	bgPID = ret;
		}
	}
}

/* The following function will terminate the background process, which may or may not end with an error.
If there is an error, this function will also handle it accordingly */

void bgProcess()
{
	usleep(100000);

	int bgPID = waitpid(-1, &bgStat, WNOHANG);

/* This will check if a background process is currently running, and will be executed accordingly */

	if(bgPID > 0)
{
	if(bgStat)
{
	printf("ERROR: Child %d, Exit 1 (Bg)  \n", bgPID);
}
	else 
{
	printf("Child %d, Exit 0 (Bg)  \n", bgPID);
}
}

	else if(WIFSIGNALED(bgStat) != 0)
{

/* If true, the background process will be killed forcefully */

	printf("Child %d, Killed (Bg)  \n", bgPID);
}
}


/* The following function will return the boolean value 'true' if the user wants to run the command in the background.
OR, it will return the boolean value 'false' is the user does not want to run the command in the background. */

bool isBackground()
{
	int x = 0;

	while(args[x] != NULL)
{
     /* To count the index of the last argument */
	x++;
}

  /* To check if the last argument was '&' */

	if(strcmp(args[x-1], "&") == 0)
{
	args[x-1] = NULL;
	return true;
}

	return false;
}

/* The following function will build the args that are needed for the execvp command.
It will also split the while command to usables sections into a char array[] */

void argsBuild(char** arguments)
{
	/* To read the whole line prompted at once */

	fgets(rawCommand, MAX_INPUT_LENGTH, stdin);
	char* eachCommand = strtok(rawCommand, "\n");

	/* To check if the command is empty */
	if(eachCommand == NULL)
{
	return;
}

	/* The following will build each command accordingly */

	while(*eachCommand != '\0') {
		while(*eachCommand == ' ' || *eachCommand == '\n') {
			*eachCommand++ = '\0';
}
	*arguments++ = eachCommand;
	
	while(*eachCommand == ' ' || *eachCommand == '\n') {
		eachCommand++;
}

	*arguments = '\0';
}
}



/* The following function is responsible for printing the PID of the current process */

void processPID()
{
	printf("PID: %d  \n", getpid());
}

/* The following function is responsible for printing the PPID of the current process */

void processPPID()
{
	printf("PPID: %d  \n", getppid());
}

/* The following function is responsible for printing the current working directory */

void workingPWD()
{
	char cwd[MAX_INPUT_LENGTH];
	getcwd(cwd, sizeof(cwd));
	printf("%s/  \n", cwd);
}

/* The following function will set and resest an environment variable */

void setVariable()
{
	if(args[1] != NULL && args[2] != NULL)
{
	setenv(args[1], args[2], 1);
}
	else if(args[1] != NULL && args[2] == NULL) 
{
	unsetenv(args[1]);
}
	else {
	printf("ERROR: Missing <var> tag \n");
}
}

/* The following will print the given environment variable */

void getVariable()
{
	if(args[1] != NULL)
{
	printf("Value of %s: %s \n", args[1], getenv(args[1]));
}
	else
{
	printf("ERROR: Missing <var> tag \n");
}
}

/* The following function will handle and the print the 'cd' command.
When the user prompts the command 'cd', it will move the current working directory to HOME, and will be able to move from its relative path */

void changeDirectory()
{
	
	char *arg;
	if(args[1] != NULL)
{
	/* The following will be executed if the user wishes to go back a directory */
	
	if(strcmp(args[1], "..") == 0)
{
	arg = "..";
}
	/* To check if the command is empty. */
	
	else if(strcmp(args[1], "") == 0 || strcmp(args[1], " ") == 0)
{

	/* If true, it will move the path to the HOME directory of the user */

	arg = getenv("HOME");
}

/* If the user has specified the directly in the prompt, the following will move the current working directory to the requested directory */

	else {
	char cwd[MAX_INPUT_LENGTH];
	getcwd(cwd, sizeof(cwd));
	strcat(cwd, "/");
	arg = cwd;
}
}
	else {
	arg = getenv("HOME");
}

 /* It will also check whether the directory prompted has been found or not */

	if(chdir(arg))
{
	printf("ERROR %s: No such file or directory found  \n", args[1]);
}
}
