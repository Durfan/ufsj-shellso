#ifndef _SHELL_H
#define _SHELL_H

char *cmdline(void);
void commandLoop(void);
Table *tokenizer(char *line);
void pipeline(Table *table);
void toknview(Table *table);

#endif // _SHELL_H