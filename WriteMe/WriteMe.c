#include <termios.h>
#include <stdlib.h>
#include <unistd.h>

void enableRawMode() {
	struct termios raw;

	tcgetattr(STDIN_FILENO, &raw); /* Fetch currernt terminal settings */

	raw.c_lflag &= ~(ECHO); /* Turn off ECHO */

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); /* Updates terminal settings */
}

int main() {
	enableRawMode();

	char c;
	while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
	
	return EXIT_SUCCESS;
}
