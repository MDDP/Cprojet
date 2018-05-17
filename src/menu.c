#include "menu.h"

int menu(){
	ITEM **my_items;			
	MENU *my_menu;
	int n_choices, i;
	
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
	strcpy(choice7, "Edit          CTRL-");
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

	char *subChoices[] = {
		"Load",
		"Save",
		"Copy",
		"Paste",
		"Cut",
		"Clear",
		"Edit config",
		"Menu",
	};
	
	initscr();
	cbreak();
	noecho();
	raw();
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
			selection = -1;
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
	
	if(selection == 6){
		clear();
		n_choices = ARRAY_SIZE(subChoices);
		my_items = (ITEM **)calloc(n_choices+1, sizeof(ITEM *));

		for(i = 0; i < n_choices; ++i)
			my_items[i] = new_item(subChoices[i], "");
		my_items[n_choices] = (ITEM *)NULL;

		my_menu = new_menu((ITEM **)my_items);
		mvprintw(LINES - 3, 0, "Select a command to edit");
		mvprintw(LINES - 2, 0, "ESC to Exit Sub-Menu");
		post_menu(my_menu);
		refresh();
		int subSelection = -1;
		for(;;){
			int c = getch();
			
			if (c == 27){
				break;
			}
			else if (c == 10){
				subSelection++;
				break;
			}
			switch(c){
				case KEY_DOWN:
					if(subSelection < 6)
						subSelection ++;
					menu_driver(my_menu, REQ_DOWN_ITEM);
					break;
				case KEY_UP:
					if(subSelection >= 0)
						subSelection--;
					menu_driver(my_menu, REQ_UP_ITEM);
					break;
		
			}
		}
		int contains = 0;
		if(subSelection != -1){
			mvprintw(LINES - 2, 0, "Choice : %d | Next input is the new shortcut", subSelection);
			refresh();
			for(;;){
				int c = getch();
				for(int i = 0; i < strlen(control); i++){
					if(c == control[i]){
						mvprintw(LINES - 4, 0, "Already used");
						contains = 1;
						break;
					}
					else{
						contains = 0;
					}
				}
				if (c == 27){
					break;
				}
				if(contains == 1){
					continue;
				}else{
					control[subSelection] = c;
					sauvegardeConfig(control);
					break;
				}
			}
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
