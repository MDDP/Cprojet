#include <ncurses.h>
#include <signal.h>
#include "buffer.h"
#include "configuration.h"
#define CTRL(c) (c & 037)

void lancer ();