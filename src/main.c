#include "./includes/main.h"

#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct cmd_t {
	int buffer;
	int narg;
	char **args;
} CMD;

typedef struct cmdtable_t {
	int availscmd;	// Numero de comandos simples disponiveis
	int ncmd;		// Numero de comandos simples
	struct cmd_t **cmds;
	char *outFile;
	char *inputFile;
} CMDtable;


CMDtable *iniTable(void) {
	CMDtable *cmdtable = malloc(sizeof(CMDtable));

	cmdtable->availscmd = 0;
	cmdtable->ncmd = 0;
	cmdtable->cmds = NULL;

	return cmdtable;
}

CMD *iniCMD(void) {
	CMD *cmd = malloc(sizeof(CMD));

	cmd->buffer = 0;
	cmd->narg = 0;
	cmd->args = NULL;

	return cmd;
}

void insArg(CMD *cmd, char *arg) {
	if (cmd->args == NULL) {
		cmd->buffer = strlen(arg)+1;
		cmd->args = malloc(cmd->buffer * sizeof(char));
		cmd->args[cmd->narg] = arg;
	}

	cmd->buffer += strlen(arg)+1;
	cmd->args = realloc(cmd->args, cmd->buffer * sizeof(char));
	cmd->args[cmd->narg++] = arg;
}

/* void tknview(char **cmd) {
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
} */


int main(void) {

	CMDtable *cmdtable = iniTable();

	cmdtable->ncmd = 4;
	cmdtable->cmds = malloc(cmdtable->ncmd * sizeof(CMD));
	cmdtable->cmds[0] = iniCMD();
	cmdtable->cmds[1] = iniCMD();
	cmdtable->cmds[2] = iniCMD();
	cmdtable->cmds[3] = iniCMD();

	insArg(cmdtable->cmds[0],"arg1a");
	insArg(cmdtable->cmds[0],"arg1b");
	insArg(cmdtable->cmds[1],"arg2a");
	insArg(cmdtable->cmds[1],"arg2b");
	insArg(cmdtable->cmds[1],"arg2c");
	insArg(cmdtable->cmds[1],"arg2d");
	insArg(cmdtable->cmds[2],"arg3a");
	insArg(cmdtable->cmds[2],"arg3b");
	insArg(cmdtable->cmds[2],"arg3c");
	insArg(cmdtable->cmds[3],"arg4a");

	for (int i=0; i < cmdtable->ncmd; i++) {
		for (int j=0; j < cmdtable->cmds[i]->narg; j++)
			printf(" %s", cmdtable->cmds[i]->args[j]);
		printf("\n");
	}

	free(cmdtable->cmds[0]->args);
	free(cmdtable->cmds[1]->args);
	free(cmdtable->cmds[2]->args);
	free(cmdtable->cmds[3]->args);
	free(cmdtable->cmds[0]);
	free(cmdtable->cmds[1]);
	free(cmdtable->cmds[2]);
	free(cmdtable->cmds[3]);
	free(cmdtable);

/* 	initshell();
	commandLoop(); */

	return EXIT_SUCCESS;
}