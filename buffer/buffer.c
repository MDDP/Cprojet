#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct buffer {
  char **contenu;
  int taille_ligne;
  int nombre_lignes;
  //ligne courante
  int cur_ligne;
  //charactère courant
  int cur_char;
} buffer;

buffer *initialisation (int taille, int nombre) {
  buffer *buff = (buffer *) malloc(sizeof(buffer));
  buff->taille_ligne = taille;
  buff->nombre_lignes = nombre;
  buff->cur_ligne = 0;
  buff->cur_char = 0;
  char **contenu = (char**)malloc(sizeof(char*)*nombre);
  for (;nombre >= 0; nombre--) *(contenu+nombre) = (char*)malloc(taille);
  buff->contenu = contenu;
  return buff;
}

int ajout (char c, buffer *buff) {
  char **contenu = buff->contenu;
  if (buff->cur_char < buff->taille_ligne) {
   *(*(contenu+buff->cur_ligne)+buff->cur_char) = c;
    return 1;
  } else {
    return -1;
  }
}

void test (char *texte, buffer *buff) {
  char **contenu = buff->contenu;
  for (int i = 0; i < buff->nombre_lignes; i++) {
    strcpy(*(contenu+i),texte);
    printf("%s\n",*(contenu+i));
  }
}