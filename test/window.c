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
    
	int cur_x=0, cur_y=3, maxcur_x=80, maxcur_y=100;
    haut = newwin(LINES-3, COLS, 3, 0);
    scrollok(haut, TRUE);
    //bas = newwin(3 , COLS, LINES - 3, 0); 
    bas = subwin(stdscr, 3 , COLS, 0, 0); // Créé la même fenêtre que ci-dessus sauf que les coordonnées changent
    box(bas, ACS_VLINE, ACS_HLINE);
    mvwprintw(bas, 1, 1, "Press # to exit. Line %d, Column %d", cur_y-3, cur_x);

    wrefresh(haut);
    wrefresh(bas);
    
	for(;;){
		move(cur_y, cur_x);
		int ch = getch();
		if(ch == '*'){							//sauvegarde
    		FILE *save=fopen("save.txt","w");	//crée un fichier save.txt qui va mettre
    		putwin(haut,save);					//tout les caracteres introduit avec
    		fclose(save);						//WPRINTW (ne marche pas avec addch chgat)
    		break;
		}
		if(ch=='$'){							//charge le fichier save.txt
            FILE *save=fopen("save.txt","r");
			haut=getwin(save);
    		fclose(save);
    		wrefresh(haut);
    		continue;
		}
		if(ch == '#') break;
		switch(ch){
			case KEY_UP:
				if(cur_y > 3) cur_y -= 1;
                else if(cur_y == 3) wscrl(haut, -1);
				break;
			case KEY_DOWN:
				if(cur_y < maxcur_y) cur_y += 1;
                if(cur_y-3 >= LINES-3){
                    wscrl(haut, 1);
                    move(LINES-1, cur_x);
                }
				break;
			case KEY_LEFT:
				if(cur_x > 0) cur_x -= 1;
                if(cur_x == maxcur_x){
                    cur_x = 0;
                    cur_y++;
                    move(cur_y, cur_x);
                }
				break;
			case KEY_RIGHT:
				if(cur_x<maxcur_x) cur_x+=1;
                if(cur_x == 0) cur_y--;
				break;
            case 10 :   /* Touche Entrée */
                if(cur_y < maxcur_y) {
                    cur_x = 0;
                    cur_y += 1;
                    move(LINES-1, cur_x);
                    wprintw(haut, "%c", '\n');
                }
                break;
			case KEY_DC :
				delch();
				break;
			case 127:
            case KEY_BACKSPACE :
                if(cur_x == 0 && cur_y > 0){     /* Reposition du curseur à la ligne précédente,  */  
                    cur_y -= 1;                  /* Pas encore de buffer donc on peut pas revenir */
                   	cur_x = maxcur_x-1;			 /* au dernier caractère de la ligne précédente   */   
                }
                else
                    cur_x-=1;
                delch();
                break;
            case 410 :      /* Char qui apparait quand on redimensionne */
                break;
			default:
                if(cur_y < maxcur_y && cur_x==maxcur_x){
					cur_x=0;
					cur_y++;
                }
                wmove(haut, cur_y-3, cur_x);
				wprintw(haut, "%c",ch);
                if(cur_x != COLS) cur_x+=1;
                if(cur_y-3 >= LINES-3 && cur_x < maxcur_x) move(LINES-1, cur_x); /*Srolling du texte*/
				break;     
		}
        wclear(bas);
        box(bas, ACS_VLINE, ACS_HLINE);
		mvwprintw(bas, 1, 1, "Press # to exit. Line %d, Column %d", cur_y-3, cur_x);
        wrefresh(haut);
        wrefresh(bas);
	}
    
	endwin();			/* End curses mode */

    free(haut);
    free(bas);
	return 0;
}
