/*** INCLUDES ***/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>

#include "WriteMe.h"


/*** DATA ***/

struct termios orig_termios;


/*** INIT ***/

int main() {
	enableRawMode();

	while (1) {

		char c = '\0';
		if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN) {
			die("read");
		}

		if (iscntrl(c)) {
			printf("%d\r\n", c);
		} else {
			printf("%d ('%c')\r\n", c, c);
		}
		if (c == 'q')
			break;
	}
	
	return EXIT_SUCCESS;
}


/*** FUNCTION DEFINITION ***/

void disableRawMode() {
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) {
		die("tcsetattr");
	}
}

void enableRawMode() {
	
	/* Fetch current terminal settings */
	if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
		die("tcgetattr");
	}

	atexit(disableRawMode);

	struct termios raw  = orig_termios;

	/* Turn off some terminal artributes */
	raw.c_cflag |= (CS8);
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_iflag &= ~(ICRNL | IXON);
	raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;

	/* Updates terminal settings */
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw)) {
		die("tcsetattr");
	}
}

void die(const char* s) {
	perror(s);
	exit(1);
}
