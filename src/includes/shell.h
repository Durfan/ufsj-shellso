#ifndef _SHELL_H
#define _SHELL_H

void shellFile(int argc, char **argv);
void commandFile(char **argv);
void commandLoop(void);
void tkenizer(Table *table, char *line);
void pipeline(Table *table);
void toknview(Table *table);

#endif // _SHELL_H