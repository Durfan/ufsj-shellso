#include "./includes/main.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void commandLoop(void) {
	char cmd[MAXCMD];
	Table *table;
	
	do {
		currdir();
		prompt();

		if (fgets(cmd,MAXCMD,stdin) && strcmp(cmd,"\n")) {
			table = iniTable();
			tkenizer(table,cmd);

			#ifdef DEBUG
			toknview(table);
			#endif

			if (!strcmp(table->cmd[0]->argv[0],"fim")) {
				clrArg(table);
				exit(EXIT_SUCCESS);
			}
			else if (!strcmp(table->cmd[0]->argv[0],"cd"))
				cdcmd(table->cmd[0]);
			else
				pipeline(table);

			clrArg(table);
		}

		freebuf(cmd);

	} while (!feof(stdin));
}

void tkenizer(Table *table, char *line) {
	char *token = strtok(line," \n");
	insCmd(table);

	int i = 0;
	while (token != NULL) {

		if (strcmp(token,"<=") == 0) {
			token = strtok(NULL, " \n");
			table->cmd[i]->input = open(token, O_RDONLY);

			if (table->cmd[i]->input == -1)
				perror(PROGNAME);
		}
		else if (strcmp(token,"=>") == 0) {
			token = strtok(NULL, " \n");
			mode_t permission = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
			table->cmd[i]->output = open(token, O_WRONLY | O_CREAT, permission);

			if (table->cmd[i]->input == -1)
				perror(PROGNAME);
		}
		else if (strcmp(token,"&") == 0) {
			token = strtok(NULL, " \n");
			table->cmd[i]->and = 1;
		}
		else if (strcmp(token,"|") == 0) {
			insArg(table->cmd[i++],NULL);
			insCmd(table);
		}
		else
			insArg(table->cmd[i],token);

		token = strtok(NULL," \n");
	}

	insArg(table->cmd[i],NULL);
}

void pipeline(Table *table) {
	int fd[2];
	pid_t pid;
	int fdd = 0;

	for (int i = 0; i < table->ncmd; i++) {

		pipe(fd);

		if ((pid = fork()) == -1) {
			perror(PROGNAME);
			exit(1);
		}

		else if (pid == 0) {

			if (table->cmd[i]->input)
				fdd = table->cmd[i]->input;

			if (table->cmd[i]->output) {
				dup2(table->cmd[i]->output,1);
				close(fd[1]);
			}

			dup2(fdd,0);

			if (i != (table->ncmd-1))
				dup2(fd[1],1);

			close(fd[0]);
			if (execvp(table->cmd[i]->argv[0],table->cmd[i]->argv) == -1)
				perror(PROGNAME);
			exit(1);
		}

		else {
			if (table->cmd[i]->and == 0)
				wait(NULL);
			else {
				signal(SIGCHLD,SIG_IGN);
				printf("PID: %d\n", pid);
			}
			close(fd[1]);
			fdd = fd[0];
		}
	}
}

void toknview(Table *table) {
	for (int i=0; i < table->ncmd; i++) {
		printf("\u25BA argc: %02d \u27A1 ", table->cmd[i]->argc-1);
		for (int j=0; j < table->cmd[i]->argc; j++)
			printf(" %s", table->cmd[i]->argv[j]);
		printf("\n");
	}
}

int cdcmd(Command *cmd) {

	if (cmd->argv[1] == NULL)
		printf(PROGNAME": %s\n", strerror(ENOENT));
	else if (chdir(cmd->argv[1]) != 0)
		perror(PROGNAME);
	
	return 1;
}