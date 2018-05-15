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

  int cur_x=0, cur_y=0;
  
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

  //Boucle principale
  for(;;){
    move(buff->posY+3, buff->posX);
    int ch = getch();
    
    if(ch == '#') break;
    
    else if(ch == CTRL(control[0])){
      wprintw(bas,"copy");
      continue;
    }
    else if(ch == CTRL(control[1])){
      wprintw(bas,"paste");
      continue;
    }
    else if(ch == CTRL(control[2])){
      wprintw(bas,"cut");
      continue;
    }
    else if(ch == CTRL(control[3])){
      wprintw(bas,"clear");
      continue;	
    }
    else if(ch == CTRL(control[4])){
      wprintw(bas,"menu");
      continue;
    }
    else if(ch == CTRL(control[5])){
      wprintw(bas,"refresh");
      continue;
    }
    else if(ch == CTRL(control[6])){
      char *filename = "save.txt";
      sauvegarde(buff, filename);

      wclear(haut);
      box(haut, ACS_VLINE, ACS_HLINE);
      mvwprintw(haut, 1, 1, "File saved in %s",filename);
      wrefresh(haut);
      continue;
    }
    else if(ch == CTRL(control[7])){
      char *filename = "save.txt";
      wclear(bas);
      chargement(buff, filename);
      wprintw(bas, "%s", buff->contenu);
      wrefresh(bas);
      
      wclear(haut);
      box(haut, ACS_VLINE, ACS_HLINE);
      mvwprintw(haut, 1, 1, "File loaded",filename);
      wrefresh(haut);
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
        deplacer(-1,buff);
      }
      break;
      
    case KEY_RIGHT:
      if(buff->cur_char < buff->dernier){
        deplacer(1,buff);
      }
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
    mvwprintw(haut, 1, 1, "Press # to exit. Line %d, Column %d cur_y %d, curchar %d", buff->posY, buff->posX, cur_y, buff->cur_char);
    wrefresh(haut);
    wrefresh(bas); 
  }
  //Libère le buffer
  liberer(buff);
  //Arrête le mode curses
  endwin();
}
