#include "./includes/main.h"

int builtin(Command *cmd) {
	if (strcmp(cmd->argv[0],"cd") == 0)
		return 1;
	return 0;
}

int cmdcd(Command *cmd) {

	if (cmd->argv[1] == NULL)
		fprintf(stderr, "teste \"cd\"\n");
	else {
		if (chdir(cmd->argv[1]) != 0)
			perror("shellos");
	}
	
	return 1;
}