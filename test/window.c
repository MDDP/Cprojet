#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

int main(){
    WINDOW *haut, *bas;
	initscr();			/* Start curses mode */
	start_color();
	//init_pair(1, COLOR_CYAN, COLOR_YELLOW);
	keypad(stdscr,TRUE);
    
	noecho();
    
	int cur_x=0, cur_y=0, maxcur_x=80, maxcur_y=100;
    haut = newwin(LINES - 4, COLS, 0, 0);
    scrollok(stdscr, TRUE);
    //bas = newwin(3 , COLS, LINES - 3, 0); 
    bas = subwin(stdscr, 3 , COLS, LINES - 3, 0); // Créé la même fenêtre que ci-dessus sauf que les coordonnées changent
    box(bas, ACS_VLINE, ACS_HLINE);
    mvwprintw(bas, 1, 1, "Press # to exit. Line %d, Column %d", cur_x, cur_y);
    
    wrefresh(haut);
    wrefresh(bas);
    
	for(;;){
		move(cur_y, cur_x);
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
            case 10 :   /* Touche Entrée */
                if(cur_y < maxcur_y) {
                    cur_x = 0;
                    cur_y += 1;
                }
                break;
			case KEY_DC :
				delch();
				break;
            case KEY_BACKSPACE :
                if(cur_x == 0 && cur_y > 0){     /* Reposition du curseur à la ligne précédente,  */  
                    cur_y -= 1;                  /* Pas encore de buffer donc on peut pas revenir */
                                                 /* au dernier caractère de la ligne précédente   */   
                }
                else
                    cur_x-=1;
                delch();
                break;
            case 410 :      /* Char qui apparait quand on redimensionne */
                break;
			default:
				cur_x+=1;  
				if(cur_x==maxcur_x){
					cur_x=0;
					cur_y++;
                }	
				addch(ch);
				chgat(1, A_BOLD, 1, NULL);
				break;     
		}
		mvwprintw(bas, 1, 1, "Press # to exit. Line %d, Column %d", cur_x, cur_y);
        wrefresh(haut);
        wrefresh(bas);
	}
    
	endwin();			/* End curses mode */

    free(haut);
    free(bas);
	return 0;
}
