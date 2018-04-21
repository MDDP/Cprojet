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

  int cur_x=0, cur_y=3;
  
  //Initialise les configurations
  char control[NBCONFIG];
  actualiseConfig(control);

  //Initialise le buffer
  buffer *buff = initialisation(300,80);
  
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
    move(cur_y,cur_x);
    int ch = getch();
    if(ch == '#') break;
    //Sauvegarde
    if(ch == '*'){
      //A mettre dans un control+lettre
      continue;
    }
    //Charge
    if(ch=='$'){							
      //A mettre dans un control+lettre
      continue;
    }
    if(ch == CTRL(control[0])){
      wprintw(bas,"copy");
      continue;
    }
    if(ch == CTRL(control[1])){
      wprintw(bas,"paste");
      continue;
    }
    if(ch == CTRL(control[2])){
      wprintw(bas,"cut");
      continue;
    }
    if(ch == CTRL(control[3])){
      wprintw(bas,"clear");
      continue;	
    }
    if(ch == CTRL(control[4])){
      wprintw(bas,"menu");
      continue;
    }
    if(ch == CTRL(control[5])){
      wprintw(bas,"refresh");
      continue;
    }
    switch(ch){
/*
    case KEY_UP:
      if(cur_y > 3) cur_y -= 1;
      else if(cur_y == 3) wscrl(bas, -1);
      break;
    case KEY_DOWN:
      if(cur_y < maxcur_y) cur_y += 1;
      if(cur_y-3 >= LINES-3){
	wscrl(bas, 1);
	move(LINES-1, cur_x);
      }
      break;
*/
    case KEY_LEFT:
      if(cur_x > 0) cur_x -= 1;
      if(cur_x == buff->t_ligne){
	cur_x = 0;
	cur_y++;
	move(cur_y, cur_x);
      }
      deplacer(-1,buff);
      break;
      
    case KEY_RIGHT:
      if(cur_x<buff->t_ligne) cur_x+=1;
      if(cur_x == 0) cur_y--;
      deplacer(1,buff);
      break;

/*    //Touche Entrée
    case 10 :
      if(cur_y < maxcur_y) {
	cur_x = 0;
	cur_y += 1;
	move(LINES-1, cur_x);
	wprintw(bas, "%c", '\n');
      }
      break;      
*/
    case KEY_DC :
      break;
      
    case 127:
    case KEY_BACKSPACE :
      if(cur_x == 0 && cur_y > 0){   // Repodsition du curseur à la ligne précédente,
	cur_y -= 1;                  // au dernier caractère de la ligne précédente
	cur_x = buff->t_ligne-1;	     // Pas encore fait
      }
      else {
	cur_x-=1;
	deplacer(-1,buff);
	supprimer(buff);
      }
      wclear(bas);
      wprintw(bas, "%s", buff->contenu);
      break;
      
    case 410 :      // Char qui apparait quand on redimensionne
      break;
      
    default:
      cur_x+=1;
      wclear(bas);
      ecrire(ch, buff);
      wprintw(bas, "%s", buff->contenu);
      break;     
    }
    
    wclear(haut);
    box(haut, ACS_VLINE, ACS_HLINE);
    mvwprintw(haut, 1, 1, "Press # to exit. Line %d, Column %d cur_x %d curchar %d", getPosY(buff), getPosX(buff), cur_x, buff->cur_char);
    wrefresh(haut);
    wrefresh(bas); 
  }

  //Arrête et libère les fenêtres
  free(bas);
  free(haut);
  //Arrête le mode curses
  endwin();
}
