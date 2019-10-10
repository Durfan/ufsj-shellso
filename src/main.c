#include "./includes/main.h"


void tknview(Table *table) {
	for (int i=0; i < table->ncmd; i++) {
		printf(" \u25BA argc: %02d \u27A1 ", table->cmd[i]->argc-1);
		for (int j=0; j < table->cmd[i]->argc; j++)
			printf(" %s", table->cmd[i]->argv[j]);
		printf("\n");
	}
}

char *cmdline(void) {

	char *line = NULL;
	size_t len = 0;
	ssize_t read = getline(&line,&len,stdin);

	if (read < 0)
		return NULL;
	else if (read > 512 ) {
		error(0,ENOBUFS,CRED"buffer nao cresce em arvore"CRSET);
		return NULL;
	}

	return line;
}

Table *tokenizer(char *line) {
	int i = 0;

	Table *table = iniTable();
	char *token = strtok(line," \n");
	insCmd(table);

	while (token != NULL) {

		if (!strcmp(token,"<=")) {
			token = strtok(NULL, " \n"); //verificar depois se token == NULL
			table->cmd[i]->input = open(token, O_RDONLY);

			if (table->cmd[i]->input == -1)
				error(0,errno,__func__);
		}

		else if (!strcmp(token,"=>")) {
			token = strtok(NULL, " \n"); //verificar depois se token == NULL
			mode_t permission = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
			table->cmd[i]->output = open(token, O_WRONLY | O_CREAT, permission);

			if (table->cmd[i]->input == -1)
				error(0,errno,__func__);
		}

		else if (!strcmp(token,"|")) {
			insArg(table->cmd[i++],NULL);
			insCmd(table);
		}

		else
			insArg(table->cmd[i],token);

		token = strtok(NULL," \n");
	}

	insArg(table->cmd[i],NULL);

	return table;
}

void commandLoop(void) {
	char *cmd = NULL;
	Table *cmdtable;
	
	do {
		currdir();
		prompt();

		cmd = cmdline();
		cmdtable = tokenizer(cmd);

		#ifdef DEBUG
		tknview(cmdtable);
		#endif

		pipeline(cmdtable);

		clrArg(cmdtable);
		free(cmdtable);
		free(cmd);

	} while (!feof(stdin));
}


int main(void) {

	initshell();
	commandLoop();

	printf("Saindo...\n");
	return EXIT_SUCCESS;
}