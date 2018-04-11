typedef struct buffer buffer;

/*
 * Prend en argument une taille de ligne ainsi qu'un nombre de lignes
 * Renvoie un pointeur de buffer
 */
buffer *initialisation(int taille, int nombre);

/*
 * Prend un caractère c en entrée et l'ajoute à la position courante du buffer si c'est possible.
 * Renvoie 1 si on a juste ajouté un caratère
 * 		   2 si on a dû passer à la ligne suivante
 *		   3 si on a dû décaler le buffer d'une ligne
 */
int ecrire (char c, buffer *buff);

/*
 * Juste une fonction pour tester l'initialisation du buffer
 */
void print (buffer *buff);

void liberer (buffer *buff);

/*
 * Double la capacité du buffer
 */
buffer *expand (buffer *buff);