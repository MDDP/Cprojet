#include <stdio.h>
#include "buffer.h"

int main() {
  buffer *buff = initialisation(7,3);
  //for (int i = 0; i < 25; i++) ecrire('a', buff);
  chargement(buff, "a");
  printf("Résultat:\n");
  print(buff);
  //sauvegarde(buff, "a");
}