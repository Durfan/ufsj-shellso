#include "./includes/main.h"

void pipeline(CMDtable *cmdtable){
	int fd[2];
	pid_t pid;
	int fdd = 0;				/* Backup */
    
    
	for(int i = 0; i < cmdtable->ncmd; i++) {
        
		pipe(fd);				/* Sharing bidiflow */
		
		if ((pid = fork()) == -1) {
			perror("fork");
			exit(1);
		}
		else if (pid == 0) {
			if(cmdtable->cmds[i]->input){
        		fdd = cmdtable->cmds[i]->input;
    		}
			if(cmdtable->cmds[i]->output){
				dup2(cmdtable->cmds[i]->output, 1);
    		}
            dup2(fdd, 0);
			if (i != (cmdtable->ncmd-1)) {
                dup2(fd[1], 1);
			}
			close(fd[0]);
			execvp(cmdtable->cmds[i]->args[0], cmdtable->cmds[i]->args);
			exit(1);
		}
		else {
			wait(NULL); 		/* Collect childs */
			close(fd[1]);
			fdd = fd[0];
		}
	}
}