#include "./includes/main.h"


CMDtable *iniTable(void) {
	CMDtable *table = malloc(sizeof(CMDtable));

	table->buffer = 0;
	table->ncmd = 0;
	table->cmds = NULL;

	return table;
}

CMD *iniCMD(void) {
	CMD *cmd = malloc(sizeof(CMD));

	cmd->buffer = 0;
	cmd->narg = 0;
	cmd->args = NULL;

	return cmd;
}

void insCmd(CMDtable *table) {
	table->buffer += sizeof(CMD*);

	if (table->cmds == NULL)
		table->cmds = malloc(table->buffer);
	else
		table->cmds = realloc(table->cmds, table->buffer);

	if (table->cmds == NULL)
		error(EXIT_FAILURE,errno,__func__);

	table->cmds[table->ncmd++] = iniCMD();
}

void insArg(CMD *cmd, char *arg) {
	cmd->buffer += sizeof(char*);

	if (cmd->args == NULL){
		cmd->args = malloc(cmd->buffer);
		cmd->input = 0;
		cmd->output = 0;
	}
	else
		cmd->args = realloc(cmd->args, cmd->buffer);

	if (cmd->args == NULL)
		error(EXIT_FAILURE,errno,__func__);

	cmd->args[cmd->narg++] = arg;
}

void clrArg(CMDtable *table) {
	for (int i=0; i < table->ncmd; i++) {
		free(table->cmds[i]->args);
		free(table->cmds[i]);
	}
	free(table->cmds);
}