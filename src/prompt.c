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
	if (getcwd(cwd,sizeof(cwd)) == NULL)
		return;

	printf("\u250C\u2574%s\n", cwd);
}

void initshell(void) {
	printf(CGRN"%s/SOTP1", PROGNAME);
	printf(" %d.", MAJORVER);
	printf("%dv"CRST"\n", MINORVER);
}