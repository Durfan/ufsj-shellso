#ifndef _SHELL_H
#define _SHELL_H

void commandLoop(void);
void tkenizer(Table *table, char *line);
int  warpPipe(Table *table);
void toknview(Table *table);

int cdcmd(Command *cmd);

#endif // _SHELL_H