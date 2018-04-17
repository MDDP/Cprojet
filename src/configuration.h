#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
 * NBCONFIG représente le nombre de raccourcis dans config.txt
 */
#define NBCONFIG 6

/*
 * Ouvre le fichier config.txt et attribut à
 * chaque fonction du buffer la lettre qui lui
 * est associée dans le fichier config.txt.
 * Le raccourci sera ensuite ctrl+lettre.
 */
void actualiseConfig (char control[]);

/*
 * Sauvegarde les commandes actuelles dans config.txt
 */
void sauvegardeConfig (char control[]);