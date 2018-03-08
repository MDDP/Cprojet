#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//Fichiers 
char *BUFF_AVANT = ".avant";
char *BUFF_APRES = ".apres";

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

int decharger (int nlignes) {
  //FILE *f = fopen(BUFF_AVANT, ")
  return 0;
}

int ajout (char c, buffer *buff) {
  char **contenu = buff->contenu;
  if (buff->cur_char < buff->taille_ligne) {
    *(*(contenu + buff->cur_ligne) + buff->cur_char) = c;
    return 1;
  } else if (buff->cur_ligne < buff->nombre_lignes) {
    buff->cur_ligne++;
    buff->cur_char = 0;
    *(*(contenu + buff->cur_ligne) + buff->cur_char) = c;
    return 2;
  } else {
    decharger(1);
    buff->cur_char = 0;
    *(*(contenu + buff->cur_ligne) + buff->cur_char) = c;
    return 3;
  }
}

void test (char *texte, buffer *buff) {
  char **contenu = buff->contenu;
  for (int i = 0; i < buff->nombre_lignes; i++) {
    strcpy(*(contenu+i),texte);
    printf("%s\n",*(contenu+i));
  }
}