#ifndef _CMDTABLE_H
#define _CMDTABLE_H

typedef struct command_t {
	int buffer;
	int argc;
	char **argv;
	int input;
	int output;
	int and;
} Command;

typedef struct Table_t {
	int buffer;
	int ncmd;
	Command **cmd;
} Table;

Table *iniTable(void);
Command *iniCMD(void);
void insCmd(Table *table);
void insArg(Command *cmd, char *arg);
void clrArg(Table *table);

#endif // _CMDTABLE_H