
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

int lsh_launch(char **args) {
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0) {
		if (execvp(args[0], args) == -1) {
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
	return lsh_launch(args);
}

char **lsh_split_line(char *line) {
	int bufsize = LSH_TOK_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if (!tokens) {
		fprintf(stderr, "lsh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, LSH_TOK_DELIM);
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

		token = strtok(NULL, LSH_TOK_DELIM);
	}
	tokens[position] = NULL;

	return tokens;
}

void commandLoop(void) {
	char *input = NULL;
	char **args;
  	int status;

	do {
		printf("\u250C\u2574%s\n", currdir());
		printf("\u2514\u2574%s", prompt());
		input = inputline();
		args = lsh_split_line(input);
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