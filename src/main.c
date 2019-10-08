#include "./includes/main.h"

#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>

void tknview(char ***cmd) {
	for (int i=0; cmd[i] != NULL; i++) {
		for (int j=0; cmd[i][j] != NULL; j++){
			printf(" \u25BA  %02d %02ld", i, strlen(cmd[i][j]));
			printf(" '%s'\n", cmd[i][j]);
		}
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

char ***tokenizer(char *cmd) {
	int pos = 0;
	int num_comand = 1;
	char ***tokens = (char ***) malloc (sizeof(char **));
	tokens[0] = malloc(512 * sizeof(char));

	if (tokens[0] == NULL) {
		free(cmd);
		error_at_line(EXIT_FAILURE,errno,__FILE__,__LINE__-3,__func__);
	}

	char *token = strtok(cmd, " \n");
	while (token != NULL) {

		if (strlen(token) > 64) {
			error(0,EINVAL,token);
			return NULL;
		}
		
		if(!strcmp(token, "|")){
			token = NULL;
			tokens[num_comand-1][pos++] = token;
			pos = 0;
			num_comand++;
			tokens = (char ***) realloc (tokens,(num_comand) * sizeof(char**));
		}else {
			tokens[num_comand-1][pos++] = token;
		}
		token = strtok(NULL," \n");
	}

	tokens[num_comand-1][pos] = NULL;
	tokens[num_comand] = NULL;
	for (int j =0; tokens[j] != NULL; j++)
		for(int i =0; tokens[0][i] != NULL;i++){
			printf("%s %d %d\n", tokens[j][i], j, i);
		}
	printf("%s aqui\n", tokens[1][0]);
	free(tokens[0]);
	#ifdef DEBUG
	tknview(tokens);
	#endif

	return tokens;
}

void free_args(char ***args){
	int  i;
	for(i = 0; args[i] != NULL; i++){
		for(int j; args[i][j] != NULL; j++){
			free(args[i][j]);
		}	
		free(args[i]);
	}
	free(args);
}

void commandLoop(void) {
	char *cmd = NULL;
	char ***args;

	do {
		printf("\u250C\u2574%s\n", currdir());
		printf("\u2514\u2574%s", prompt());
		cmd = cmdline();
		args = tokenizer(cmd);
		//for(int i = 0; args[i] != NULL; i++){
		//	for(int j = 0; args[i][j] != NULL; j++){
	//			printf("%s\n", args[i][j]);
	//		}
	//	}
		
		//free_args(args);
		//free(cmd);
	} while (cmd != NULL);
}


int main(void) {

	initshell();
	commandLoop();

	return EXIT_SUCCESS;
}