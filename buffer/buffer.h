typedef struct buffer buffer;

/*
 * Prend en argument une taille de buffer (nombre de caractère) et une taille de ligne
 * Renvoie un pointeur de buffer
 */
buffer *initialisation(int taille, int tl);

/*
 * Prend un caractère c en entrée et l'ajoute à la position courante du buffer si c'est possible.
 * Renvoie 1 si on a juste ajouté un caratère
 * 		   2 si on a dû décaler le buffer d'une ligne
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

/*
 * Copie le contenu du buffer dans le fichier indiqué par filename
 * Renvoie 1 si la copie est effectuée sans problème
 *		   0 en cas d'erreur
 */
int sauvegarde (buffer *buff, char *filename);

/*
 * Copie le contenu du fichier indiqué par filename dans le buffer
 * Renvoie 1 si la copie est effectuée sans problème
 *		   0 en cas d'erreur
 */
int chargement (buffer *buff, char *filename);