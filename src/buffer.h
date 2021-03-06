#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * char *contenu; 	  Représente le contenu du buffer
 * int taille; 		  Indique la taille totale du buffer
 * int t_ligne; 	  Indique la taille d'une "ligne" pour la vue
 * int cur_char; 	  Indique la position courante dans le buffer
 * int dernier; 	  Indique la position du dernier caractère dans
 *					  contenu
 * int posX et posY;  Indiquent la position pour l'affichage. Elles sont
 *					  actualisées à chaque fois que cur_char est modifié
 */
typedef struct buffer {
  char *contenu;
  int taille;
  int t_ligne;
  int cur_char;
  int dernier;
  int posX;
  int posY;
} buffer;

/*
 * Prend en argument une taille de buffer (nombre de caractère) et une
 * taille de ligne.
 * Renvoie un pointeur de buffer.
 * Renvoie NULL si les arguments sont incorrectes.
 */
buffer *initialisation(int taille, int tl);

/*
 * Libère l'espace mémoire alloué à contenu et à buff.
 */
void liberer (buffer *buff);

/*
 * Deplace la position courante de buff de n caractères.
 * Renvoie la position courante de buff.
 * 		   -1 si la position courante serait invalide après opération.
 */
int deplacer (int n, buffer *buff);

/*
 * Deplace la position courante de buff à la position n.
 * Renvoie le nombre de caractère de différence.
 * 		   0 si la position est inchangée ou invalide.
 */
int deplacerA (int n, buffer *buff);

/*
 * Modifier la taille de la ligne dans buff en tl et recalcule la
 * position visuelle pour matcher la nouvelle taille de ligne.
 */
void modifierTaille (int tl, buffer *buff);

/*
 * Prend un caractère c en entrée et l'écrit à la position courante
 * du buffer (en remplaçant le caractère précédent si il existe).
 * Renvoie 1 si on a juste écrit un caratère.
 * 		   2 si on a expand le buffer.
 */
int ecrire (char c, buffer *buff);

/*
 * Prend un caractère c en entrée et l'insère à la position
 * courante du buffer et décale le reste des caractères.
 * Renvoie 1 si on a juste ajouté un caratère.
 * 		   2 si on a expand le buffer.
 */
int insertion (char c, buffer *buff);

/*
 * Supprime le caractère à la position courante dans le buffer et
 * diminue la taille du buffer si elle a atteint la moitié.
 * Renvoie le caractère supprimé.
 */
char supprimer (buffer *buff);

/*
 * Copie le contenu du buffer dans le fichier indiqué par filename.
 * Renvoie 1 si la copie est effectuée sans problème.
 *		   0 en cas d'erreur.
 */
int sauvegarde (buffer *buff, char *filename);

/*
 * Copie le contenu du fichier indiqué par filename dans le buffer.
 * Renvoie 1 si la copie est effectuée sans problème.
 *		   0 en cas d'erreur.
 */
int chargement (buffer *buff, char *filename);

/*
 * Fonction pour tester le contenu du buffer.
 */
void print (buffer *buff);