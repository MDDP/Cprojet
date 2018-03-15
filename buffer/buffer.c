#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct buffer {
  char **contenu;
  //indique la taille courante des lignes (permet de rajouter un '\0')
  int *cur_taille;
  //taille maximale d'une ligne
  int taille_ligne;
  //nombre de lignes dans la buffer
  int nombre_lignes;
  //ligne courante dans le buffer
  int cur_ligne;
  //charactère courant dans le buffer
  int cur_char;
} buffer;

buffer *initialisation (int taille, int nombre) {
  buffer *buff = (buffer *) malloc(sizeof(buffer));
  //pour rajouter le \0
  buff->taille_ligne = taille;
  buff->nombre_lignes = nombre;
  int *cur_t = (int *)malloc(sizeof(int)*nombre);
  for (int i = 0; i < nombre; i++) *(cur_t + i) = 0;
  buff->cur_taille = cur_t;
  buff->cur_ligne = 0;
  buff->cur_char = 0;
  char **contenu = (char**)malloc(sizeof(char*)*nombre);
  for (;nombre >= 0; nombre--){
    *(contenu+nombre) = (char*)malloc(taille+1);
  }
  buff->contenu = contenu;
  return buff;
}

// NE MARCHE PAS SAIS PAS POURQUOIx
int expand (buffer *buff) {
  //int nouv_nombre = buff->nombre_lignes*2;
  printf("d");
  //char **contenu = buff->contenu;
  printf("d");
  //contenu = realloc(contenu, nouv_nombre);
  printf("d");
  //int *cur_taille = buff->cur_taille;
  printf("d");
  //cur_taille = realloc(cur_taille, nouv_nombre);
  printf("d");
  /*for (int i = buff->nombre_lignes; i < nouv_nombre; i++){
    *(contenu+i) = (char*) malloc(buff->taille_ligne+1);
    buff->cur_taille[i] = 0;
  }*/
  //buff->contenu = contenu;
  //buff->cur_taille = cur_taille;
  //buff->nombre_lignes = nouv_nombre;
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
    //double la capacité puis passe à la ligne suivante
    expand(buff);
    //buff->cur_ligne++;
    buff->cur_char = 0;
    ret = 3;
  }
  *(*(contenu + buff->cur_ligne) + buff->cur_char) = c;
  buff->cur_char++;
  return ret;
}

void print (buffer *buff) {
  char **contenu = buff->contenu;
  for (int i = 0; i < buff->nombre_lignes; i++){
    *(contenu+i)[(buff->cur_taille[i])] = '\0';
    printf("l%d. %s\n", i,*(contenu+i));
  }
}