#include "./includes/main.h"

int builtin(Command *cmd) {
	if (strcmp(cmd->argv[0],"cd") == 0)
		return 1;
	return 0;
}

int cmdcd(Command *cmd) {

	if (cmd->argv[1] == NULL)
		fprintf(stderr, "lsh: expected argument to \"cd\"\n");
	else {
		if (chdir(cmd->argv[1]) != 0)
			perror("lsh");
	}
	
	return 1;
}