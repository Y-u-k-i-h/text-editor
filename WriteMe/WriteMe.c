#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include "WriteMe.h"

struct termios orig_termios;

int main() {
	enableRawMode();

	char c;
	while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
		if (iscntrl(c)) {
			printf("%d\n", c);
		} else {
			printf("%d ('%c')\n", c, c);
		}
	}
	
	return EXIT_SUCCESS;
}

void disableRawMode() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {

	tcgetattr(STDIN_FILENO, &orig_termios); /* Fetch currernt terminal settings */
	atexit(disableRawMode);

	struct termios raw  = orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON | ISIG); /* Turn off canonical, echo, sigs */

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); /* Updates terminal settings */
}

