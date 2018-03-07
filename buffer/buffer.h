typedef struct buffer buffer;

/*
 * Prend en argument une taille de ligne ainsi qu'un nombre de lignes
 * Renvoie un pointeur de buffer
 */
buffer *initialisation(int taille, int nombre);

/*
 * Prend un caractère c en entrée et l'ajoute à la position au buffer buff si c'est possible.
 * Renvoie 1 si tout c'est bien passé, -1 en cas d'erreur.
 */
int ajout (char c, buffer *buff);

/*
 * Juste une fonction pour tester l'initialisation du buffer
 */
void test (char *texte, buffer *buff);