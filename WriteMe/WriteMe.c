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
			printf("%d\r\n", c);
		} else {
			printf("%d ('%c')\r\n", c, c);
		}
	}
	
	return EXIT_SUCCESS;
}

void disableRawMode() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
	
	/* Fetch currernt terminal settings */
	tcgetattr(STDIN_FILENO, &orig_termios); 
	atexit(disableRawMode);

	struct termios raw  = orig_termios;

	/* Turn off some terminal artributes */
	raw.c_cflag |= (CS8);
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_iflag &= ~(ICRNL | IXON);
	raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);

	/* Updates terminal settings */
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

