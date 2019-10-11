#include "./includes/main.h"

int main(int argc, char **argv) {

	if (argc == 1) {
		system("clear");
		initshell();
		commandLoop();
	}

	else if (argc == 2) {
		initshell();
		readfile(argv[1]);
		exit(EXIT_SUCCESS);
	}
	else {
		initshell();
		printf(PROGNAME": %s\n", strerror(ENOENT));
		exit(EXIT_FAILURE);
	}

	printf("Saindo...\n");
	return EXIT_SUCCESS;
}