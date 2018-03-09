typedef struct buffer buffer;

/*
 * Prend en argument une taille de ligne ainsi qu'un nombre de lignes
 * Renvoie un pointeur de buffer
 */
buffer *initialisation(int taille, int nombre);

/*
 * transfère n lignes du buffer dans le fichier BUFF_AVANT
 * les lignes suivantes sont décalées et on réalloue n lignes
 */
int decharger (int n, buffer *buff);

/*
 * Prend un caractère c en entrée et l'ajoute à la position au buffer buff si c'est possible.
 * Renvoie 0 si il y a eu un  problème
 * Renvoie 1 si on a juste ajouté un caratère
 * 		   2 si on a dû passer à la ligne suivante
 *		   3 si on a dû décaler le buffer d'une ligne
 */
int ajout (char c, buffer *buff);

/*
 * Juste une fonction pour tester l'initialisation du buffer
 */
void print (buffer *buff);