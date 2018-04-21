#include "buffer.h"

/*typedef struct buffer {
  char *contenu;
  int taille;
  int t_ligne;
  int cur_char;
  int dernier;
} buffer;*/

buffer *initialisation (int taille, int tl) {
  buffer *buff = (buffer*)malloc(sizeof(buffer));
  buff->taille = taille;
  buff->t_ligne = tl;
  buff->cur_char = 0;
  buff->dernier = 0;
  //On rajoute un octet supplémentaire pour pouvoir rajouter un '\0' dans la sauvegarde
  buff->contenu = (char*)malloc(buff->taille+1);
  return buff;
}

int deplacer (int n, buffer *buff) {
  if (buff->cur_char + n >= buff->taille || buff->cur_char + n < 0) return -1;
  buff->cur_char += n;
  return buff->cur_char;
}

int deplacerA (int n, buffer *buff) {
  if (n < 0 || n >= buff->taille) return 0;
  int dep = n - buff->cur_char;
  buff->cur_char = n;
  return dep;
}

void liberer (buffer *buff) {
  free(buff->contenu);
  free(buff);
}

void augmenter (buffer *buff) {
  buff->taille *= 2;
  //On rajoute un octet supplémentaire pour pouvoir rajouter un '\0' dans la sauvegarde
  buff->contenu = (char*)realloc(buff->contenu, buff->taille+1);
}

void reduire (buffer *buff) {
  buff->taille /= 2;
  //On rajoute un octet supplémentaire pour pouvoir rajouter un '\0' dans la sauvegarde
  buff->contenu = (char*)realloc(buff->contenu, buff->taille+1);
}

int ecrire (char c, buffer *buff) {
  char *contenu = buff->contenu;
  int ret = 1;
  if (buff->cur_char >= buff->taille) {
    //double la capacité puis écrit
    augmenter(buff);
    ret = 2;
  }
  *(contenu+ buff->cur_char) = c;
  buff->cur_char++;
  if (buff->cur_char > buff->dernier) buff->dernier = buff->cur_char;
  return ret;
}

int insertion (char c, buffer *buff) {
  char *contenu = buff->contenu;
  int ret = 1;
  if (buff->dernier == buff->taille-1) {
    augmenter(buff);
    ret = 2;
  }
  memmove(contenu+buff->cur_char+1, contenu+buff->cur_char, buff->dernier-buff->cur_char);
  *(contenu+ buff->cur_char) = c;
  buff->cur_char++;
  if (buff->cur_char > buff->dernier) buff->dernier = buff->cur_char;
  return ret;
}

char supprimer (buffer *buff) {
  char *contenu = buff->contenu;
  char ret = *(contenu+buff->cur_char);
  memmove(contenu+buff->cur_char, contenu+buff->cur_char+1, buff->dernier-buff->cur_char);
  buff->dernier--;
  if (buff->taille > 10 && buff->dernier < buff->taille/2) reduire(buff);
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
    //Rajout du '\0' pour écrire contenu dans f
    *(contenu + buff->dernier + 1) = '\0';
    fprintf(f, contenu);
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

int getPosY(buffer *buff) {
  return ((buff->cur_char+(buff->t_ligne-(buff->cur_char)))%buff->t_ligne)+1;
}

int getPosX(buffer *buff) {
  return (buff->cur_char)%buff->t_ligne;
}

