
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h>

void initshell(void) {
	system("clear");
	printf("  _____ _    _ ______ _      _      ____   _____    ___  __\n");
	printf(" / ____| |  | |  ____| |    | |    / __ \\ / ____|  / _ \\/_ |\n");
	printf("| (___ | |__| | |__  | |    | |   | |  | | (___   | | | || | __ _\n");
	printf(" \\___ \\|  __  |  __| | |    | |   | |  | |\\___ \\  | | | || |/ _` |\n");
	printf(" ____) | |  | | |____| |____| |___| |__| |____) | | |_| || | (_| |\n");
	printf("|_____/|_|  |_|______|______|______\\____/|_____/   \\___(_)_|\\__,_|\n\n");                                                
}

char *inputline(void) {
	char *line = NULL;
	ssize_t bufsize = 0;
	getline(&line, &bufsize, stdin);
	return line;
}


void prompt(void) {
	char *user = getenv("USER");
	char host[1024];
	char cwd[PATH_MAX];
	char *line;
	char **args;

	gethostname(host,1024);

	do {
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			printf("\u250C\u2574%s\n", cwd);
		
		printf("\u2514\u2574[%s@%s]$ ", user, host);
		line = inputline();

		free(line);
	} while (1);
}


int main(int argc, char **argv) {

	initshell();
	prompt();

	return EXIT_SUCCESS;
}