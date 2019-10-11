#include "./includes/main.h"

int main(int argc, char **argv) {
	initshell();
	shellFile(argc, argv);

	printf("Saindo...\n");
	return EXIT_SUCCESS;
}