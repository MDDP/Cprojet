#include <curses.h>
#include <menu.h>
#include <ctype.h>

#include "configuration.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

int menu ();
