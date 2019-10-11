#include "./includes/main.h"

void readfile(char *file) {

	FILE *fp = fopen(file,"r");
	if (fp == NULL) {
		perror(PROGNAME);
		exit(EXIT_FAILURE);
	}

	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	Table *table;

	while ((read = getline(&line,&len,fp)) != -1) {

		if (strcmp(line,"\n") != 0) {
			printf("\u25BA $%s", line);
			table = iniTable();
			tkenizer(table,line);

			if (!strcmp(table->cmd[0]->argv[0],"fim")) {
				clrArg(table);
				break;
			}
			else {
				warpPipe(table);
				clrArg(table);
			}
		}
	};

	printf("\n");
	killzumbies();
	free(line);
	fclose(fp);
}