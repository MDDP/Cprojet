#include <curses.h>

int main()
{
	initscr();			/* Start curses mode */
	printw("Press '#' to exit\n");	/*        Exit       */
	start_color();
	//init_pair(1, COLOR_CYAN, COLOR_YELLOW);
	keypad(stdscr,TRUE);
	noecho();
	int cur_x=0, cur_y=0, maxcur_x=80, maxcur_y=100;
	mvprintw(LINES - 1, 0, "Line %d, Column %d", cur_y, cur_x);
	for(;;){
		move(cur_y,cur_x);
		int ch = getch();
		if(ch == '#') break;
		switch(ch){
			case KEY_UP:
				if(cur_y>0) cur_y-=1;
				break;
			case KEY_DOWN:
				if(cur_y<maxcur_y) cur_y+=1;
				break;
			case KEY_LEFT:
				if(cur_x>0) cur_x-=1;
				break;
			case KEY_RIGHT:
				if(cur_x<maxcur_x) cur_x+=1;
				break;
			case KEY_DC :
				cur_x-=1;
				delch();
				break;
			default:
				cur_x++;
				if(cur_x==maxcur_x){
					cur_x=0;
					cur_y++;
				}
				addch(ch | A_BOLD | A_UNDERLINE);
				chgat(1, A_BOLD, 1, NULL);
				mvprintw(LINES - 1, 0, "Line %d, Column %d", cur_y, cur_x);
				break;
		}
		

	}
	refresh();			/* Print it on to the real screen */
	endwin();			/* End curses mode		  */

	return 0;
}

