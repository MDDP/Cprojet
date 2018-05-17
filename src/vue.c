#include "vue.h"

void lancer () {
  // Démarrer le mode curses
  initscr();
  //Activer les couleurs
  start_color();
  //Evite d'obtenir les touches ctrl, alt sous forme de suite de caractère
  raw();
  //Enlever les répétitions de caractère
  noecho();
  //Activer les touches ctrl, alt...
  keypad(stdscr,TRUE);
  
  //Initialise les configurations
  char control[NBCONFIG];
  actualiseConfig(control);

  //Initialise le buffer
  buffer *buff = initialisation(3000,80);
  
  //Initialise les fenêtres d'affichage
  WINDOW *haut, *bas;
  //Fenêtre contenant le buffer
  bas = newwin(LINES-3, COLS, 3, 0);
  //Fenêtre contenant les messages et les coordonées actuelles du curseur
  // Créé la même fenêtre que ci-dessus sauf que les coordonnées changent
  haut = subwin(stdscr, 3 , COLS, 0, 0);
  //Dessine les bordures de la fenêtre
  box(haut, ACS_VLINE, ACS_HLINE);
  mvwprintw(haut, 1, 1, "Press # to exit. Line %d, Column %d", getPosY(buff), getPosX(buff));
  //Activer la molette de la souris dans la fenêtre écriture
  scrollok(bas, TRUE);
  //Actualise les deux fenêtres
  wrefresh(bas);
  wrefresh(haut);
  init_pair(1, COLOR_CYAN, COLOR_BLACK);
  int selection = -1;
  int curChar = 0;
  int first = 0;
  char tmp [2048];
  int index = 0;
  //taille de la ligne en fonction de la fenetre
  if(COLS >= buff->t_ligne){
	modifierTaille(COLS, buff);
  }
  //Boucle principale
  for(;;){
    move(buff->posY+3, buff->posX);
    int ch = getch();
    
    if(ch == '#') break;

    else if(ch == CTRL(control[7])){
	selection = menu();
	actualiseConfig(control);
	wclear(haut);
	wclear(bas);
	box(haut, ACS_VLINE, ACS_HLINE);
      	mvwprintw(haut, 1, 1, "Menu loaded selection %d", selection);
      	wrefresh(haut);
	wprintw(bas, "%s", buff->contenu);
	wrefresh(bas);
      continue;
    }
    else if(ch == CTRL(control[6])){
	wclear(haut);
      	box(haut, ACS_VLINE, ACS_HLINE);
    	mvwprintw(haut, 1, 1, "Refresh");
     	wrefresh(haut);
	selection = -1;
      continue;
    }
    else if(ch == CTRL(control[0]) || selection == 0){
	char filename[50];
        for(int i=0; i<49; i++) filename[i] = '\0';
        int compteur = 0; 
        while(compteur<49) {
          wclear(haut);
          box(haut, ACS_VLINE, ACS_HLINE);
          mvwprintw(haut, 1, 1, "Enter file name: %s", filename);
          move(1, 18+compteur);
          wrefresh(haut);
          int ch = getch();
          if(ch == 10) {
            filename[compteur] = '\0';
            break;
          }
          else if((ch == 127 || ch == KEY_BACKSPACE) && compteur>0) {
            compteur--;
            filename[compteur] = '\0';
          }
          else {
            filename[compteur] = ch;
            compteur++;
          }
        }
	wclear(bas);
	chargement(buff, filename);
	wprintw(bas, "%s", buff->contenu);
	wrefresh(bas);

	wclear(haut);
	box(haut, ACS_VLINE, ACS_HLINE);
	mvwprintw(haut, 1, 1, "File loaded",filename);
	wrefresh(haut);
	selection = -1;
      continue;
    }
    else if(ch == CTRL(control[1]) || selection == 1){
	char filename[50];
        for(int i=0; i<49; i++) filename[i] = '\0';
        int compteur = 0; 
        while(compteur<49) {
          wclear(haut);
          box(haut, ACS_VLINE, ACS_HLINE);
          mvwprintw(haut, 1, 1, "Enter file name: %s", filename);
          move(1, 18+compteur);
          wrefresh(haut);
          int ch = getch();
          if(ch == 10) {
            filename[compteur] = '\0';
            break;
          }
          else if((ch == 127 || ch == KEY_BACKSPACE) && compteur>0) {
            compteur--;
            filename[compteur] = '\0';
          }
          else {
            filename[compteur] = ch;
            compteur++;
          }
        }
	sauvegarde(buff, filename);

	wclear(haut);
	box(haut, ACS_VLINE, ACS_HLINE);
	mvwprintw(haut, 1, 1, "File saved in %s",filename);
	wrefresh(haut);
	selection = -1;
      continue;
    }
    else if(ch == CTRL(control[2]) || selection == 2){
	wclear(haut);
      	box(haut, ACS_VLINE, ACS_HLINE);
      	mvwprintw(haut, 1, 1, "Copy");
	wrefresh(haut);
	memset(&tmp[0], 0, sizeof(tmp));
	index = 0;
	int min = curChar;
	int max	= buff->cur_char;
	if(curChar > buff->cur_char){
		max = curChar;
		min = buff->cur_char;
	}
	while(min < max){
		tmp[index] = *(buff->contenu + min);
		min++;
		index++;
	}
	selection = -1;
      continue;
    }
    else if(ch == CTRL(control[3]) || selection == 3){
	wclear(haut);
      	box(haut, ACS_VLINE, ACS_HLINE);
	mvwprintw(haut, 1, 1, "Paste");
	wrefresh(haut);
	wclear(bas);
	for (int i = 0; i < strlen(tmp); i++){
		if(tmp[i] == '\0'){
			break;
		}
		else{
			insertion(tmp[i], buff);
		}
	}
	wprintw(bas, "%s", buff->contenu);
	wrefresh(bas);
	selection = -1;
      continue;
    }
    else if(ch == CTRL(control[4]) || selection == 4){
	wclear(haut);
      	box(haut, ACS_VLINE, ACS_HLINE);
      	mvwprintw(haut, 1, 1, "Cut");
	wrefresh(haut);
	wclear(bas);
    	memset(&tmp[0], 0, sizeof(tmp));
	index = 0;
	int min = curChar;
	int max	= buff->cur_char;
	int tmpmin = min;
	if(curChar > buff->cur_char){
		max = curChar;
		min = buff->cur_char;
	}
	
	while(tmpmin < max){
        	tmp[index] = *(buff->contenu + tmpmin);
       		tmpmin++;
		index++;
	}

	deplacerA(max, buff);

	while(min < max){
		deplacer(-1, buff);
		supprimer(buff);
		max--;
	}
    
	wprintw(bas, "%s", buff->contenu);
	wrefresh(bas);
	selection = -1;
      continue;
    }
    else if(ch == CTRL(control[5]) || selection == 5){
	wclear(haut);
      	box(haut, ACS_VLINE, ACS_HLINE);
      	mvwprintw(haut, 1, 1, "Clear");
	wrefresh(haut);
	while(true){
		if(!(*(buff->contenu + (buff->cur_char)) != '\n' && buff->cur_char < buff->dernier))
			break;
		deplacer(1, buff);
		supprimer(buff);		
	}
	while(true){
		if(buff->posX != 0 && buff->cur_char > 0){
			deplacer(-1, buff);
			supprimer(buff);
		}
		else{
			break;
		}
	}
	wclear(bas);
	wprintw(bas, "%s", buff->contenu);
	wrefresh(bas);
	selection = -1;
      continue;	
    }

    switch(ch){

    case KEY_UP:
      if(buff->cur_char > 0){
	int tmpX = buff->posX;
	int tmpY = (buff->posY)-1;

	while(buff->posY != tmpY){
		if(buff->cur_char > 0){
			deplacer(-1, buff);
		}else{
			deplacerA(0, buff);
			break;
		}
	}

	int tmpCur_char = buff->cur_char;

	while(buff->posX != tmpX){
		if(buff->posX > 0){
			deplacer(-1, buff);
		}else{
			deplacerA(tmpCur_char, buff);
			break;
		}
	}
      }
      //wscrl(bas, -1);
      break;
    case KEY_DOWN:
      if(buff->cur_char >= 0){
	int tmpX = buff->posX;
	int tmpY = (buff->posY)+1;
	while(buff->posY != tmpY){
		if(buff->cur_char < buff->dernier){
			deplacer(1, buff);
		}else{
			deplacerA(buff->dernier, buff);
			break;
		}
	}
	
	while(buff->posX != tmpX){
		if(*(buff->contenu + (buff->cur_char)) != '\n' && buff->cur_char < buff->dernier){
			deplacer(1, buff);
		}else{
			break;
		}
	}
      }
      break;

    case KEY_LEFT:
      if(buff->cur_char > 0){
	if(first == 1){
		first = 0;
		wclear(bas);
		wprintw(bas, "%s", buff->contenu);	
	}
        deplacer(-1,buff);
      }
      break;
      
    case KEY_RIGHT:
      if(buff->cur_char < buff->dernier){
	if(first == 1){
		first = 0;
		wclear(bas);
		wprintw(bas, "%s", buff->contenu);	
	}
        deplacer(1,buff);
      }
      break;

    case KEY_SRIGHT:
	mvwchgat(bas, buff->posY, buff->posX, 1, A_STANDOUT, 1, NULL);
	if(first == 0){
		curChar = buff->cur_char;
		first = 1;
	}
	deplacer(1,buff);
	wrefresh(bas);
	break;

    case KEY_SLEFT:
	mvwchgat(bas, buff->posY, buff->posX, 1, A_STANDOUT, 1, NULL);
	if(first == 0){
		curChar = buff->cur_char;
		first = 1;
	}
	deplacer(-1,buff);
	wrefresh(bas);
	break;

    //Touche Entrée
    case 10 :
      if(buff->posX < buff-> t_ligne) {
	wclear(bas);
      	ecrire('\n', buff);
      	wprintw(bas, "%s", buff->contenu);
      }
      break;      

    case KEY_DC :
      break;
      
    case 127:
    case KEY_BACKSPACE :
      if(buff->cur_char > 0){
	deplacer(-1,buff);
	supprimer(buff);
	wclear(bas);
        wprintw(bas, "%s", buff->contenu);
      }
      break;
      
    case 410 :      // Char qui apparait quand on redimensionne
      break;
      
    default:
      wclear(bas);
      if(buff->cur_char < buff->dernier)
	insertion(ch, buff);
      else 
     	ecrire(ch, buff);
      wprintw(bas, "%s", buff->contenu);
      break;     
    }
    
    wclear(haut);
    box(haut, ACS_VLINE, ACS_HLINE);
    mvwprintw(haut, 1, 1, "Press # to exit. Line %d, Column %d, curchar %d, dernier %d" "control %c", buff->posY, buff->posX, buff->cur_char, buff->dernier, control[3]);
    wrefresh(haut);
    wrefresh(bas);
  }
  //Libère le buffer
  liberer(buff);
  //Arrête le mode curses
  endwin();
}
