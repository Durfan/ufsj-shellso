#ifndef _SINAIS_H
#define _SINAIS_H

void monitor(int sig, siginfo_t *info, void *ucontext);
void sinais(void);
void killzumbies(void);

#endif // _SINAIS_H