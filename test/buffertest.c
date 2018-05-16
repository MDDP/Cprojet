#include "../src/buffer.h" // SUT

void serie1() {
  buffer *buff = initialisation(60, 5);
  printf("Buffer de taille %d, taille de ligne %d initialisé.\n", buff->taille, buff->t_ligne);
  int n = 1;
  
  //cas normal
  char* toEcrire = "a ecrire";
  for (int i = 0; i < 8; i++)
    ecrire(*(toEcrire+i), buff);
  //permet le strcmp
  ecrire('\0', buff);
  printf("Test%d: [ecrire] Contenu attendu: %s\ncontenu reçu: %s\n", n, toEcrire, buff->contenu);
  if (strcmp(buff->contenu, toEcrire) == 0) printf("Test passé\n\n");
  else printf("Test échoué\n\n");
  n++;
  
  int tmp = deplacer(-1, buff);
  printf("Test%d: [deplacerA] Position attendu 8\nPosition reçue %d\n", n, tmp);
  if (tmp == 8) printf("Test passé\n\n");
  else printf("Test échoué\n\n");
  n++;
  
  //autre cas normal
  toEcrire = " une phrase";
  for (int i = 0; i < 11; i++)
    ecrire(*(toEcrire+i), buff);
  ecrire('\0', buff);
  printf("Test%d: [ecrire] Contenu attendu: %s\ncontenu reçu: %s\n", n, "a ecrire une phrase", buff->contenu);
  if (strcmp(buff->contenu, "a ecrire une phrase") == 0) printf("Test passé\n\n");
  else printf("Test échoué\n\n");
  n++;
  
  deplacerA(0, buff);
  printf("Test%d: [deplacer] Position attendu 0\nPosition reçue %d\n", n, buff->cur_char);
  if (buff->cur_char == 0) printf("Test passé\n\n");
  else printf("Test échoué\n\n");
  n++;
  
  //cas d'écrasement
  toEcrire = "nouvelle phrase";
  for (int i = 0; i < 15; i++)
    ecrire(*(toEcrire+i), buff);
  ecrire('\0', buff);
  printf("Test%d: [ecrire] Contenu attendu: %s\ncontenu reçu: %s\n", n, toEcrire, buff->contenu);
  if (strcmp(buff->contenu, toEcrire) == 0) printf("Test passé\n\n");
  else printf("Test échoué\n\n");
  n++;
  
  deplacerA(0, buff);
  printf("Test%d: [deplacerA] Position attendu 0\nPosition reçue %d\n", n, buff->cur_char);
  if (buff->cur_char == 0) printf("Test passé\n\n");
  else printf("Test échoué\n\n");
  n++;
  
  //cas normal de suppression
  toEcrire = "ouvelle phrase";
  supprimer(buff);
  printf("Test%d: [supprimer] Contenu attendu: %s\ncontenu reçu: %s\n", n, toEcrire, buff->contenu);
  if (strcmp(buff->contenu, toEcrire) == 0) printf("Test passé\n\n");
  else printf("Test échoué\n\n");
  n++;
  
  tmp = deplacer(4, buff);
  printf("Test%d: [deplacer] Position attendu 4\nPosition reçue %d\n", n, tmp);
  if (tmp == 4) printf("Test passé\n\n");
  else printf("Test échoué\n\n");
  n++;
  
  //autre cas normal
  toEcrire = "ouvele phrase";
  supprimer(buff);
  printf("Test%d: [supprimer] Contenu attendu: %s\ncontenu reçu: %s\n", n, toEcrire, buff->contenu);
  if (strcmp(buff->contenu, toEcrire) == 0) printf("Test passé\n\n");
  else printf("Test échoué\n\n");
  n++;
  
  liberer(buff);
  printf("Buffer libéré\n\n");
}

void serie2 () {
  buffer *buff = initialisation(20, 10);
  printf("Buffer de taille %d, taille de ligne %d initialisé.\n", buff->taille, buff->t_ligne);
  int n = 1;
  
  //cas normal
  char* toEcrire = "Ceci est une phrase.";
  for (int i = 0; i < 20; i++)
    ecrire(*(toEcrire+i), buff);
  *(buff->contenu+20) = '\0';
  printf("Test%d: [ecrire] Contenu attendu: %s\ncontenu reçu: %s\n", n, toEcrire, buff->contenu);
  if (strcmp(buff->contenu, toEcrire) == 0) printf("Test passé\n\n");
  else printf("Test échoué\n\n");
  n++;
  
  deplacerA(19, buff);
  //cas normal de suppression
  toEcrire = "Ceci est une phrase";
  supprimer(buff);
  printf("Test%d: [supprimer] Contenu attendu: %s\ncontenu reçu: %s\n", n, toEcrire, buff->contenu);
  if (strcmp(buff->contenu, toEcrire) == 0) printf("Test passé\n\n");
  else printf("Test échoué\n\n");
  n++;
  
  //cas d'écriture après suppression
  toEcrire = "Ceci est une phrase??";
  ecrire('?', buff);
  ecrire('?', buff);
  *(buff->contenu+21) = '\0';
  printf("Test%d: [ecrire] Contenu attendu: %s\ncontenu reçu: %s\n", n, toEcrire, buff->contenu);
  if (strcmp(buff->contenu, toEcrire) == 0) printf("Test passé\n\n");
  else printf("Test échoué\n\n");
  n++;
  
  //Autre cas de suppression
  deplacerA(0, buff);
  toEcrire = "ci est une phrase??";
  supprimer(buff);
  supprimer(buff);
  printf("Test%d: [supprimer] Contenu attendu: %s\ncontenu reçu: %s\n", n, toEcrire, buff->contenu);
  if (strcmp(buff->contenu, toEcrire) == 0) printf("Test passé\n\n");
  else printf("Test échoué\n\n");
  n++;
  
  //cas normal d'insertion
  deplacerA(0, buff);
  toEcrire = "Ceci est une phrase??";
  insertion('C', buff);
  insertion('e', buff);
  printf("Test%d: [insertion] Contenu attendu: %s\ncontenu reçu: %s\n", n, toEcrire, buff->contenu);
  if (strcmp(buff->contenu, toEcrire) == 0) printf("Test passé\n\n");
  else printf("Test échoué\n\n");
  n++;
}

int main () {
  serie1();
  serie2();
}