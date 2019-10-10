#include "./includes/main.h"

Table *iniTable(void) {
	Table *table = malloc(sizeof(Table));
	if (table == NULL)
		error(EXIT_FAILURE,errno,__func__);

	table->buffer = 0;
	table->ncmd = 0;
	table->cmd = NULL;

	return table;
}

Command *iniCMD(void) {
	Command *cmd = malloc(sizeof(Command));
	if (cmd == NULL)
		error(EXIT_FAILURE,errno,__func__);

	cmd->buffer = 0;
	cmd->argc   = 0;
	cmd->argv   = NULL;
	cmd->input  = 0;
	cmd->output = 0;

	return cmd;
}

void insCmd(Table *table) {
	table->buffer += sizeof(Command*);

	if (table->cmd == NULL)
		table->cmd = malloc(table->buffer);
	else
		table->cmd = realloc(table->cmd, table->buffer);

	if (table->cmd == NULL)
		error(EXIT_FAILURE,errno,__func__);

	table->cmd[table->ncmd++] = iniCMD();
}

void insArg(Command *cmd, char *arg) {
	cmd->buffer += sizeof(char*);

	if (cmd->argv == NULL)
		cmd->argv = malloc(cmd->buffer);
	else
		cmd->argv = realloc(cmd->argv, cmd->buffer);

	if (cmd->argv == NULL)
		error(EXIT_FAILURE,errno,__func__);

	cmd->argv[cmd->argc++] = arg;
}

void clrArg(Table *table) {
	for (int i=0; i < table->ncmd; i++) {
		free(table->cmd[i]->argv);
		free(table->cmd[i]);
	}
	free(table->cmd);
	free(table);
}