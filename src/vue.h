#include <ncurses.h>
#include <signal.h>
#include "buffer.h"
#include "menu.h"
#define CTRL(c) (c & 037)

/*
 * Donne à filename la valeur entrée par l'utilisateur
 */
void getFilename (char* filename);

/*
 * Rafraichit et affiche un message dans la fenêtre du haut
 */
void afficheHautMessage (char* message);

/*
 * Rafraichit et affiche un message dans la fenêtre du haut
 * avec le paramètre char* donné en argument
 */
void afficheHautMessageParameterStr (char* message, char* parameter);

/*
 * Rafraichit et affiche un message dans la fenêtre du haut
 * avec le paramètre int donné en argument
 */
void afficheHautMessageParameterInt (char* message, int parameter);

/*
 * Rafraichit et affiche le contenu du buffer dans la fenêtre du bas
 */
void afficheBufferBas (buffer *buff);

/*
 * Lance le programme
 */
void lancer ();
