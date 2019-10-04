
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

void initshell(void) {
	system("clear");
	printf("  _____ _    _ ______ _      _      ____   _____    ___  __\n");
	printf(" / ____| |  | |  ____| |    | |    / __ \\ / ____|  / _ \\/_ |\n");
	printf("| (___ | |__| | |__  | |    | |   | |  | | (___   | | | || | __ _\n");
	printf(" \\___ \\|  __  |  __| | |    | |   | |  | |\\___ \\  | | | || |/ _` |\n");
	printf(" ____) | |  | | |____| |____| |___| |__| |____) | | |_| || | (_| |\n");
	printf("|_____/|_|  |_|______|______|______\\____/|_____/   \\___(_)_|\\__,_|\n\n");                                                
}

void history(char* input) {
	if (!strlen(input))
		return;
	FILE *fp = fopen("history.txt", "a");
	assert(fp);
	fprintf(fp,"%s",input);
	fclose(fp);
}

char *currdir(void) {
	static char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return NULL;
	return cwd;
}

char *prompt(void) {
	static char prompt[1024];
	char username[LOGIN_NAME_MAX];
	char hostname[HOST_NAME_MAX];
	
	getlogin_r(username, LOGIN_NAME_MAX);
	gethostname(hostname, HOST_NAME_MAX);
	
	strcpy(prompt,"[");
	strcat(prompt,username);
	strcat(prompt,"@");
	strcat(prompt,hostname);
	strcat(prompt,"]$ ");

	return prompt;
}

char *inputline(void) {
	char *line = NULL;

	size_t bufsize;
	ssize_t read = getline(&line,&bufsize,stdin);
	if (read < 0) {
        return NULL;
    }
	return line;
}

void multi_pipe(char **args) {
	char **lsh_split_line(char *line, int flag);
	int status, fd1[2], fd2[2];
	int i = 0;
	char **arg;
	pipe(fd1);
	pid_t pid;
	
	while(args[i] != NULL){
		if(i == 1){
			free(arg);
		}
		arg = lsh_split_line(args[i], 1);
		if(args[i+1] != NULL){
			if(i%2!= 0){
				pipe(fd2);
			}
			else{
				pipe(fd1);
			}
		}
		pid = fork();
		if (pid == -1) { 
			perror("fork");
			exit(1);
		} 
		if (pid == 0) { // child process
			if(i == 0){
				close(fd1[0]);
				dup2(fd1[1], 1);
			}
			else if(args[i+1] != NULL && i > 0){
				if(i % 2!=0){
					dup2(fd1[0], 0);
					close(fd2[0]);
					dup2(fd2[1], 1);
				} else {
					dup2(fd2[0], 0);
					close(fd1[0]);
					dup2(fd1[1], 1);
				}
			} else if(args[i+1] == NULL){
				if(i % 2!=0){
					close(fd1[1]);
					dup2(fd1[0], 0);
				}  else {
					close(fd2[1]);
					dup2(fd2[0], 0);
				}
			}
			execvp(arg[0], arg);
			perror("pipe error");
			exit(1);
		}
		else { //father process
			if(i == 0){
				close(fd1[1]);
			}
			else if(i > 0 && args[i+1] != NULL){
				if(i % 2 != 0){
					close(fd1[0]);
					close(fd2[1]);
				}
				else{
					close(fd1[1]);
					close(fd2[0]);
				}
			}
			else if(args[i+1] == NULL){
				if(i % 2 != 0){
					close(fd1[0]);
				}
				else{
					close(fd2[0]);
				}
			}
		}
		wait(&status);
		i++;
	}
	free(arg);
}

int lsh_launch(char **args) {
	char **lsh_split_line(char *line, int flag);
	pid_t pid, wpid;
	int status;
	char **arg = lsh_split_line(args[0], 1);
	pid = fork();
	if (pid == 0) {
		if (execvp(arg[0], arg) == -1) {
			perror("lsh");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0) {
		perror("lsh");
	}
	else {
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
  	}
	return 1;
}

int lsh_execute(char **args) {
	if (args[0] == NULL)
		return 1;
	else if(args[1] != NULL){
		multi_pipe(args);
		return 0;
	}
	else{
		return lsh_launch(args);
		return 0;
	}
}

char **lsh_split_line(char *line, int flag) {
	int bufsize = LSH_TOK_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if (!tokens) {
		fprintf(stderr, "lsh: allocation error\n");
		exit(EXIT_FAILURE);
	}
	if(!flag){
		token = strtok(line, "|");
	}else{
		token = strtok(line, LSH_TOK_DELIM);
	}
	while (token != NULL) {
		tokens[position] = token;
		position++;

		if (position >= bufsize) {
			bufsize += LSH_TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens) {
				fprintf(stderr, "lsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		if(!flag){
			token = strtok(NULL, "|");
		}else{
			token = strtok(NULL, LSH_TOK_DELIM);
		}
	}
	tokens[position] = NULL;

	return tokens;
}

char **copy_arguments(char **args, int start, int end){
	char **arg = (char **) malloc((end-start+1)*sizeof(char*));
	int i;
	for(i = start; i < end; i++){
		arg[i-start] = (char *) malloc (strlen(args[i]) * sizeof(char));
		strcpy(arg[i - start], args[i]);
	}
	arg[i-start] = NULL;
	return arg;
}

void commandLoop(void) {
	char *input = NULL;
	char **args;
  	int status;

	do {
		printf("\u250C\u2574%s\n", currdir());
		printf("\u2514\u2574%s", prompt());
		input = inputline();
		args = lsh_split_line(input, 0);
		status = lsh_execute(args);
		history(input);
		free(input);
		free(args);
	} while (1);
}


int main(void) {

	initshell();
	commandLoop();

	return EXIT_SUCCESS;
}