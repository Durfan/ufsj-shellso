#include "./includes/main.h"

#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>


 void tknview(char **cmd) {
	for (int i=0; cmd[i] != NULL; i++) {
		printf(" \u25BA  %02d %02ld", i, strlen(cmd[i]));
		printf(" '%s'\n", cmd[i]);
	}
} 

char *cmdline(void) {

	char *line = NULL;
	size_t len = 0;
	ssize_t read = getline(&line,&len,stdin);

	if (read < 0) {
		free(line);
		return NULL;
	}
	else if (read > 512 ) {
		free(line);
		error(0,ENOBUFS,CRED"buffer nao cresce em arvore"CRSET);
		return NULL;
	}

	return line;
}

CMDtable *tokenizer(char *line) {
	int position = 0;
	CMDtable *cmdtable = iniTable();
	char *token;
	token = strtok(line, " \n");
	insCmd(cmdtable);
	while (token != NULL) {
		
		if(!strcmp(token, "<=")){
			token = strtok(NULL, " \n");//verificar depoisse token == NULL
			cmdtable->cmds[position]->input = open(token, O_RDONLY);
			if(cmdtable->cmds[position]->input == -1)
				printf("File error\n");
			
		}
		else if(!strcmp(token, ">=")){
			token = strtok(NULL, " \n");//verificar depoisse token == NULL
			mode_t permission = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
			cmdtable->cmds[position]->output = open(token, O_WRONLY | O_CREAT, permission);
			if(cmdtable->cmds[position]->input == -1)
				printf("File error\n");
			
		}
		else if(!strcmp(token, "|")){
			insArg(cmdtable->cmds[position],NULL);
			position++;
			insCmd(cmdtable);
		}
		else{
			insArg(cmdtable->cmds[position],token);
		}
		token = strtok(NULL, " \n");
	}
	insArg(cmdtable->cmds[position],NULL);
	free(token);
	return cmdtable;
}

void commandLoop(void) {
	char *cmd = NULL;
	do {
		printf("\u250C\u2574%s\n", currdir());
		printf("\u2514\u2574%s", prompt());
		cmd = cmdline();
		CMDtable *cmdtable = tokenizer(cmd);
		for (int i=0; i < cmdtable->ncmd; i++) {
			printf(" nargs : %d ->", cmdtable->cmds[i]->narg);
			for (int j=0; j < cmdtable->cmds[i]->narg; j++)
				printf(" %s", cmdtable->cmds[i]->args[j]);
				
			printf("\n");
		}
		pipeline(cmdtable);
		clrArg(cmdtable);

		free(cmdtable);
		free(cmd);
	} while (cmd != NULL);
}


int main(void) {

	/*insCmd(cmdtable);
	insCmd(cmdtable);
	insCmd(cmdtable);
	insCmd(cmdtable);
	
	printf(" ncmds : %d\n", cmdtable->ncmd);
	insArg(cmdtable->cmds[0],"arg1a");
	insArg(cmdtable->cmds[0],"arg1b");
	insArg(cmdtable->cmds[0],NULL);
	insArg(cmdtable->cmds[1],"arg2a");
	insArg(cmdtable->cmds[1],"arg2b");
	insArg(cmdtable->cmds[1],"arg2c");
	insArg(cmdtable->cmds[1],"arg2d");
	insArg(cmdtable->cmds[1],NULL);
	insArg(cmdtable->cmds[2],"arg3a");
	insArg(cmdtable->cmds[2],"arg3b");
	insArg(cmdtable->cmds[2],"arg3c");
	insArg(cmdtable->cmds[2],NULL);
	insArg(cmdtable->cmds[3],"arg4a");
	insArg(cmdtable->cmds[3],NULL);
	*/
	

 	//initshell();
	commandLoop(); 

	return EXIT_SUCCESS;
}