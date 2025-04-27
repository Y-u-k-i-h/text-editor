#include <termios.h>
#include <stdlib.h>

#pragma once

void enableRawMode();

void diasableRawMode();

void die(const char* s);
