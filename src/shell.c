#include "./includes/main.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

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

void commandLoop(void) {
	char *cmd = NULL;
	Table *cmdtable;
	
	do {
		currdir();
		prompt();

		cmd = cmdline();
		cmdtable = tokenizer(cmd);

		#ifdef DEBUG
		toknview(cmdtable);
		#endif

		pipeline(cmdtable);

		clrArg(cmdtable);
		free(cmdtable);
		free(cmd);

	} while (!feof(stdin));
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

void pipeline(Table *table) {
	int fd[2];
	pid_t pid;
	int fdd = 0;

	for (int i = 0; i < table->ncmd; i++) {

		pipe(fd);

		if ((pid = fork()) == -1) {
			perror("fork");
			exit(1);
		}

		else if (pid == 0) {

			if (table->cmd[i]->input)
				fdd = table->cmd[i]->input;

			if (table->cmd[i]->output)
				dup2(table->cmd[i]->output, 1);

			dup2(fdd, 0);

			if (i != (table->ncmd-1))
				dup2(fd[1], 1);

			close(fd[0]);
			if (execvp(table->cmd[i]->argv[0],table->cmd[i]->argv) == -1)
				error(0,errno,table->cmd[i]->argv[0]);
			exit(1);
		}

		else {
			wait(NULL);
			close(fd[1]);
			fdd = fd[0];
		}
	}
}

void toknview(Table *table) {
	for (int i=0; i < table->ncmd; i++) {
		printf(" \u25BA argc: %02d \u27A1 ", table->cmd[i]->argc-1);
		for (int j=0; j < table->cmd[i]->argc; j++)
			printf(" %s", table->cmd[i]->argv[j]);
		printf("\n");
	}
}