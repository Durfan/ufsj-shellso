#ifndef _SHELL_H
#define _SHELL_H

char *getinput(void);
void commandLoop(void);
void tkenizer(Table *table, char *line);
void pipeline(Table *table);
void toknview(Table *table);

#endif // _SHELL_H