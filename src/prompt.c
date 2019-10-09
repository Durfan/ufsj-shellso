#include "./includes/main.h"
#include <limits.h>


void prompt(void) {
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

	printf("\u2514\u2574%s", prompt);
}

void currdir(void) {
	static char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return;

	printf("\u250C\u2574%s\n", cwd);
}

void initshell(void) {
	system("clear");
	printf("  _____ _    _ ______ _      _      ____   _____    ___  __\n");
	printf(" / ____| |  | |  ____| |    | |    / __ \\ / ____|  / _ \\/_ |\n");
	printf("| (___ | |__| | |__  | |    | |   | |  | | (___   | | | || | __ _\n");
	printf(" \\___ \\|  __  |  __| | |    | |   | |  | |\\___ \\  | | | || |/ _` |\n");
	printf(" ____) | |  | | |____| |____| |___| |__| |____) | | |_| || | (_| |\n");
	printf("|_____/|_|  |_|______|______|______\\____/|_____/   \\___(_)_|\\__,_|\n\n");                                                
}