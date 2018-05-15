#include "buffer.h"

buffer *initialisation (int taille, int tl) {
  buffer *buff = (buffer*)malloc(sizeof(buffer));
  buff->taille = taille;
  buff->t_ligne = tl;
  buff->cur_char = 0;
  buff->dernier = 0;
  buff->posX = 0;
  buff->posY = 0;
  //On rajoute un octet supplémentaire pour pouvoir rajouter un '\0' dans la sauvegarde
  buff->contenu = (char*)malloc(buff->taille+1);
  return buff;
}

void liberer (buffer *buff) {
  free(buff->contenu);
  free(buff);
}

//Double la capacité du buffer
void augmenter (buffer *buff) {
  buff->taille *= 2;
  //On rajoute un octet supplémentaire pour pouvoir rajouter un '\0' dans la sauvegarde
  buff->contenu = (char*)realloc(buff->contenu, buff->taille+1);
}

//Diminue de moitié la taille du buffer
void reduire (buffer *buff) {
  buff->taille /= 2;
  //On rajoute un octet supplémentaire pour pouvoir rajouter un '\0' dans la sauvegarde
  buff->contenu = (char*)realloc(buff->contenu, buff->taille+1);
}

//actualise la position pour la vue selon le char c
void actualiserPos (char c, buffer *buff) {
  if (c == '\n' || buff->posX == buff->t_ligne-1) {
    buff->posX = 0;
    buff->posY += 1;
  } else
    buff->posX += 1;
}

//permet d'actualiser la vue selon un déplacement de n caractères
//un déplacement positif (avancement) ne fait qu'itérer actualiserPos jusqu'à arriver
//à la position indiquée par buff.cur_char + n
//un déplacement négatif force à recompter la position depuis le début du buffer
void actualiserPosDep (int n, buffer *buff) {
  char *contenu = buff->contenu;
  char cur;
  int i;
  if (n < 0) {
    buff->posX = 0;
    buff->posY = 0;
    i = 0;
  } else {
    i = buff->cur_char;
  }
  for (; i < buff->cur_char + n; i++) {
    cur = *(contenu + i);
    actualiserPos(cur, buff);
  }
}

int deplacer (int n, buffer *buff) {
  if (buff->cur_char + n > buff->dernier || buff->cur_char + n < 0) return -1;
  actualiserPosDep(n, buff);
  buff->cur_char += n;
  return buff->cur_char;
}

int deplacerA (int n, buffer *buff) {
  if (n < 0 || n > buff->dernier) return 0;
  int dep = n - buff->cur_char;
  actualiserPosDep(dep, buff);
  buff->cur_char = n;
  return dep;
}

void modifierTaille (int tl, buffer *buff) {
  buff->t_ligne = tl;
  //On sauvegarde la position actuelle du curseur puis on le remet à 0
  int tmp = buff->cur_char;
  buff->cur_char = 0;
  //Et on utilise deplacer pour recalculer la position visuelle
  deplacerA(tmp, buff);
}

int ecrire (char c, buffer *buff) {
  char *contenu = buff->contenu;
  int ret = 1;
  if (buff->cur_char >= buff->taille) {
    //double la capacité puis écrit si on a atteint la taille maximale
    augmenter(buff);
    ret = 2;
  }
  *(contenu+ buff->cur_char) = c;
  buff->cur_char++;
  if (buff->cur_char > buff->dernier) buff->dernier = buff->cur_char;
  actualiserPos(c, buff);
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
  buff->dernier += 1;
  actualiserPos(c, buff);
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

int sauvegarde (buffer *buff, char *filename) {
  FILE *f = fopen(filename, "w");
  if (f != NULL) {
    char *contenu = buff->contenu;
    //Rajout du '\0' pour écrire contenu dans f
    *(contenu + buff->dernier) = '\0';
    fputs(contenu, f);
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

void print (buffer *buff) {
  char *contenu = buff->contenu;
  *(contenu + buff->dernier + 1) = '\0';
  printf("%s\n", contenu);
}

int getPosY(buffer *buff) {
  return ((buff->cur_char+(buff->t_ligne-(buff->cur_char)))%buff->t_ligne)+1;
}

int getPosX(buffer *buff) {
  return (buff->cur_char)%buff->t_ligne+1;
}
