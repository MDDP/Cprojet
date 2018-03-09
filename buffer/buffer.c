#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//Fichiers 
char *BUFF_AVANT = "avant.buff";
char *BUFF_APRES = "apres.buff";

typedef struct buffer {
  char **contenu;
  int taille_ligne;
  int nombre_lignes;
  //ligne courante dans le buffer
  int cur_ligne;
  //charactère courant dans le buffer
  int cur_char;
  //nombres de lignes déchargées dans le BUFF_AVANT (pour matcher les numéros de lignes de l'affichage)
  int lignes_dechar;
} buffer;

buffer *initialisation (int taille, int nombre) {
  buffer *buff = (buffer *) malloc(sizeof(buffer));
  buff->taille_ligne = taille;
  buff->nombre_lignes = nombre;
  buff->cur_ligne = 0;
  buff->cur_char = 0;
  buff->lignes_dechar = 0;
  char **contenu = (char**)malloc(sizeof(char*)*nombre);
  for (;nombre >= 0; nombre--) *(contenu+nombre) = (char*)malloc(taille);
  buff->contenu = contenu;
  return buff;
}

int decharger (int n, buffer *buff) {
  buff->lignes_dechar++;
  FILE *f = fopen(BUFF_AVANT, "a");
  char **contenu = buff->contenu;
  //écriture des n lignes dans BUFF_AVANT
  for (int i = 0; i < nl; i++) fwrite(*(contenu+i), 1, strlen(*(contenu+i), f);
  //réalloue le bon nombre de lignes pour contenu
  contenu = realloc(contenu+n, buff->nombre_lignes);
  for (int i = buff->nombre_lignes - n; i < buff->nombre_lignes; i++) *(contenu+i) = (char*) malloc(buff->taille_ligne);
  return 1;
}

int ajout (char c, buffer *buff) {
  char **contenu = buff->contenu;
  int ret = 0;
  if (buff->cur_char < buff->taille_ligne) {
    ret = 1;
  } else if (buff->cur_ligne < buff->nombre_lignes) {
    //passage à la ligne suivante
    buff->cur_ligne++;
    buff->cur_char = 0;
    ret = 2;
  } else {
    //On décharge une ligne et on redécale le curseur
    if (!decharger(1, buff)) return 0;
    buff->cur_char = 0;
    ret = 3;
  }
  *(*(contenu + buff->cur_ligne) + buff->cur_char) = c;
  return ret;
}

void print (buffer *buff) {
  char **contenu = buff->contenu;
  for (int i = 0; i < buff->nombre_lignes; i++) printf("%s\n",*(contenu+i))
}