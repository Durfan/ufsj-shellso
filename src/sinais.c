#include "./includes/main.h"

void monitor(int sig, siginfo_t *info, void *ucontext) {
	(void)ucontext;
	printf("SIG %d ", sig);
	printf("PID %d ", info->si_pid);
	printf("Status: %d ",  info->si_status);
	printf("Time: %ldct\n", info->si_utime);
}

void sinais(void) {
	struct sigaction sa;
	memset(&sa,0,sizeof sa);
	sa.sa_sigaction = &monitor;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGCHLD,&sa,NULL);
}

void killzumbies(void) {
	for (pid_t pid = waitpid(-1,NULL,WNOHANG);
		pid != 0 && pid != -1;
		pid = waitpid(-1,NULL,WNOHANG)) {
			#ifdef DEBUG
			printf("PID %d: Headshot!\n", pid);
			#endif
		}
}