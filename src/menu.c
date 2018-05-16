#include "menu.h"
#include <string.h>
#include "configuration.h"

int menu(){
	ITEM **my_items;
	int c;				
	MENU *my_menu;
	int n_choices, i;
	ITEM *cur_item;
	
	char control[NBCONFIG];
	actualiseConfig(control);
	
	char *choice1 = (char*)calloc(1, 21 * sizeof(char));
	strcpy(choice1, "Load          CTRL-");
	choice1[strlen(choice1)] = toupper(control[0]);

	char *choice2 = (char*)calloc(1, 21 * sizeof(char));
	strcpy(choice2, "Save          CTRL-");
	choice2[strlen(choice2)] = toupper(control[1]);

	char *choice3 = (char*)calloc(1, 21 * sizeof(char));
	strcpy(choice3, "\0");
	strcat(choice3, "Copy          CTRL-");
	choice3[strlen(choice3)] = toupper(control[2]);

	char *choice4 = (char*)calloc(1, 21 * sizeof(char));
	strcpy(choice4, "Paste         CTRL-");
	choice4[strlen(choice4)] = toupper(control[3]);

	char *choice5 = (char*)calloc(1, 21 * sizeof(char));
	strcpy(choice5, "Cut           CTRL-");
	choice5[strlen(choice5)] = toupper(control[4]);

	char *choice6 = (char*)calloc(1, 21 * sizeof(char));
	strcpy(choice6, "Clear         CTRL-");
	choice6[strlen(choice6)] = toupper(control[5]);
	
	char *choice7 = (char*)calloc(1, 21 * sizeof(char));
	strcpy(choice7, "Refresh       CTRL-");
	choice7[strlen(choice7)] = toupper(control[6]);

	char *choices[] = {
        	choice1,
        	choice2,
        	choice3,
        	choice4,
		choice5,
		choice6,
		choice7,
        };

	
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	n_choices = ARRAY_SIZE(choices);
	my_items = (ITEM **)calloc(n_choices+1, sizeof(ITEM *));

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
	free(choice1);
	free(choice2);
	free(choice3);
	free(choice4);
	free(choice5);
	free(choice6);
	free(choice7);
	free_item(my_items[0]);
	free_item(my_items[1]);
	free_menu(my_menu);
	endwin();
	return selection;
}
