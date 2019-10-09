#include "./includes/main.h"

#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>


void tknview(CMDtable *table) {
	for (int i=0; i < table->ncmd; i++) {
		printf(" \u25BA nargs : %d ->", table->cmds[i]->narg);
		for (int j=0; j < table->cmds[i]->narg; j++)
			printf(" %s", table->cmds[i]->args[j]);
		printf("\n");
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

void tokenizer(CMDtable *table, char *cmd) {
	int position = 0;

	char *token = strtok(cmd, " \n");
	insCmd(table);

	while (token != NULL) {

		if (!strcmp(token,"|")) {
			insArg(table->cmds[position],NULL);
			position++;
			insCmd(table);
		}
		else
			insArg(table->cmds[position],token);

		token = strtok(NULL, " \n");
	}

	insArg(table->cmds[position],NULL);
	free(token);
}

void commandLoop(void) {
	char *cmd = NULL;
	CMDtable *cmdtable = iniTable();
	
	do {

		currdir();
		prompt();
		cmd = cmdline();
		tokenizer(cmdtable,cmd);

		#ifdef DEBUG
		tknview(cmdtable);
		#endif

		clrArg(cmdtable);
		free(cmd);

	} while (cmd != NULL);

	free(cmd);
	free(cmdtable);
}


int main(void) {

	commandLoop();

	return EXIT_SUCCESS;
}