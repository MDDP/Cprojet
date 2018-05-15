#include "menu.h"

char *choices[] = {
                        "Load          CTRL-L",
                        "Save          CTRL-S",
                        "Copy          CTRL-C",
                        "Paste         CTRL-V",
			"Cut           CTRL-X",
			"Clear         CTRL-A",
			"Refresh       CTRL-R",
                  };

int menu(){
	ITEM **my_items;
	int c;				
	MENU *my_menu;
	int n_choices, i;
	ITEM *cur_item;
	
	
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	n_choices = ARRAY_SIZE(choices);
	my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

	for(i = 0; i < n_choices; ++i)
	        my_items[i] = new_item(choices[i], "");
	my_items[n_choices] = (ITEM *)NULL;

	my_menu = new_menu((ITEM **)my_items);
	mvprintw(LINES - 2, 0, "ESC to Exit Menu");
	post_menu(my_menu);
	refresh();
	int selection = -1;
	for(;;){
		
		int c = getch();
		if (c == 27){
			break;
		}
		else if (c == 10){
			selection++;
			break;
		}
		switch(c){
			case KEY_DOWN:
				if(selection < 5)
					selection ++;
		        	menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				if(selection >= 0)
					selection--;
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			
		}
	}
	free_item(my_items[0]);
	free_item(my_items[1]);
	free_menu(my_menu);
	endwin();
	return selection;
}
