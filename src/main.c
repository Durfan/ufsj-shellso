#include "./includes/main.h"

#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>

void tknview(char **cmd) {
	for (int i=0; cmd[i] != NULL; i++) {
		printf(" \u25BA  %02d %02ld", i, strlen(cmd[i]));
		printf(" '%s'\n", cmd[i]);
	}
}

char *cmdline(void) {

	char *line = NULL;
	size_t len = 0;
	ssize_t read = getline(&line,&len,stdin);

	if (read < 0) {
		free(line);
		return NULL;
	}
	else if (read > 512 ) {
		free(line);
		error(0,ENOBUFS,CRED"buffer nao cresce em arvore"CRSET);
		return NULL;
	}

	return line;
}

char **tokenizer(char *cmd) {
	int pos = 0;
	char **tokens = malloc(512 * sizeof(char));

	if (tokens == NULL) {
		free(cmd);
		error_at_line(EXIT_FAILURE,errno,__FILE__,__LINE__-3,__func__);
	}

	char *token = strtok(cmd, " \n");
	while (token != NULL) {

		if (strlen(token) > 64) {
			error(0,EINVAL,token);
			return NULL;
		}

		tokens[pos++] = token;
		token = strtok(NULL," \n");
	}
	tokens[pos] = NULL;

	#ifdef DEBUG
	tknview(tokens);
	#endif

	return tokens;
}

void commandLoop(void) {
	char *cmd = NULL;
	char **args;

	do {
		printf("\u250C\u2574%s\n", currdir());
		printf("\u2514\u2574%s", prompt());
		cmd = cmdline();
		args = tokenizer(cmd);
		free(args);
		free(cmd);
	} while (cmd != NULL);
}


int main(void) {

	initshell();
	commandLoop();

	return EXIT_SUCCESS;
}