#include "./includes/main.h"


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