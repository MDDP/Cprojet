#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct buffer {
  //Représente le contenu du buffer
  char *contenu;
  //Indique la taille totale du buffer
  int taille;
  //Indique la taille d'une "ligne"
  int t_ligne;
  //Indique la position courante dans le buffer
  int cur_char;
  //Indique la position du dernier caractère dans contenu
  int dernier;
} buffer;

buffer *initialisation (int taille, int tl) {
  buffer *buff = (buffer*)malloc(sizeof(buffer));
  buff->taille = taille;
  buff->t_ligne = tl;
  buff->cur_char = 0;
  buff->dernier = 0;
  buff->contenu = (char*)malloc(buff->taille);
  return buff;
}

void liberer (buffer *buff) {
  free(buff->contenu);
  free(buff);
}

buffer *expand (buffer *buff) {
  buff->taille *= 2;
  buff->contenu = (char*)realloc(buff->contenu, buff->taille);
  return buff;
}

int ecrire (char c, buffer *buff) {
  char *contenu = buff->contenu;
  int ret = 0;
  if (buff->cur_char < buff->taille) {
    ret = 1;
  } else {
    //double la capacité puis écrit
    expand(buff);
    ret = 2;
  }
  *(contenu+ buff->cur_char) = c;
  buff->cur_char++;
  if (buff->cur_char > buff->dernier) buff->dernier = buff->cur_char;
  return ret;
}

void print (buffer *buff) {
  char *contenu = buff->contenu;
  *(contenu + buff->dernier + 1) = '\0';
  printf("%s\n", contenu);
}

int sauvegarde (buffer *buff, char *filename) {
  FILE *f = fopen(filename, "w");
  if (f != NULL) {
    char *contenu = buff->contenu;
    *(contenu + buff->dernier + 1) = '\0';
    fprintf(f, "%s", contenu);
    fclose(f);
    return 1;
  } else
    return 0;
}

int chargement (buffer *buff, char *filename) {
  FILE *f = fopen(filename, "r");
  if (f != NULL) {
    char c = fgetc(f);
    while (c != EOF) {
      ecrire(c, buff);
      c = fgetc(f);
    }
    fclose(f);
    return 1;
  } else
    return 0;
}