#ifndef _CMDTABLE_H
#define _CMDTABLE_H

typedef struct cmd_t {
	int buffer;
	int narg;
	char **args;
} CMD;

typedef struct cmdtable_t {
	int buffer;
	int ncmd;
	CMD **cmds;
} CMDtable;

CMDtable *iniTable(void);
CMD *iniCMD(void);
void insCmd(CMDtable *table);
void insArg(CMD *cmd, char *arg);
void clrArg(CMDtable *table);

#endif // _CMDTABLE_H