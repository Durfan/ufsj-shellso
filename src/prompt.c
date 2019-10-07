#include "./includes/main.h"
#include <limits.h>


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

char *currdir(void) {
	static char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return NULL;
	return cwd;
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