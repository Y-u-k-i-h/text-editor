#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

void disableRawMode() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {

	tcgetattr(STDIN_FILENO, &orig_termios); /* Fetch currernt terminal settings */
	atexit(disableRawMode);

	struct termios raw  = orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON); /* Turn off ECHO and ECHO */

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); /* Updates terminal settings */
}

int main() {
	enableRawMode();

	char c;
	while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
	
	return EXIT_SUCCESS;
}
