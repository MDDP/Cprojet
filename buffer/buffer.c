#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct buffer {
  char *contenu;
  int nb_ligne;
  int t_ligne;
  int cur_ligne;
  int cur_char;
  int dernier;
} buffer;

buffer *initialisation (int tl, int nbl) {
  buffer *buff = (buffer*)malloc(sizeof(buffer));
  buff->nb_ligne = nbl;
  //le +1 sert pour les retours à la ligne
  buff->t_ligne = tl+1;
  buff->cur_ligne = 0;
  buff->cur_char = 0;
  buff->dernier = 0;
  char *contenu = (char*)malloc(nbl*(tl));
  *contenu = '\0';
  return buff;
}

void liberer (buffer *buff) {
  free(buff->contenu);
  free(buff);
}

buffer *expand (buffer *buff) {
  buff->nb_ligne *= 2;
  buff->contenu = (char*)realloc(buff->contenu, buff->nb_ligne);
  return buff;
}

int sautligne (buffer *buff) {
  char *contenu = buff->contenu;
  int pos = (buff->cur_ligne * buff->t_ligne) + buff->cur_char;
  *(contenu+pos) = '\n';
  //passage à la ligne suivante
  buff->cur_ligne++;
  buff->cur_char = 0;
  return pos;
}

int ecrire (char c, buffer *buff) {
  int pos;
  char *contenu = buff->contenu;
  int ret = 0;
  if (c == '\n') {
    pos = sautligne(buff);
    ret = 1;
  } else {
    if (buff->cur_char < buff->t_ligne-1) {
      ret = 1;
    } else if (buff->cur_ligne < buff->nb_ligne) {
      sautligne(buff);
      ret = 2;
    } else {
      //double la capacité puis passe à la ligne suivante
      expand(buff);
      sautligne(buff);
      ret = 3;
    }
    pos = (buff->cur_ligne * buff->t_ligne) + buff->cur_char;
    *(contenu+pos) = c;
      buff->cur_char++;
  }
  if (pos > buff->dernier) buff->dernier = pos;
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
    return 1;
  } else
    return 0;
}