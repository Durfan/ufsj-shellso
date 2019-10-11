#include "./includes/main.h"

int main(void) {

	initshell();
	commandLoop();

	printf("Saindo...\n");
	return EXIT_SUCCESS;
}