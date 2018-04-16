#include <stdio.h>
#include "buffer.h"

int main() {
  buffer *buff = initialisation(20,5);
  for (int i = 0; i < 25; i++) ecrire('a', buff);
  printf("Résultat écrire:\n");
  print(buff);
  
  
  deplacer(-1,buff);
  ecrire('b', buff);
  printf("Résultat deplacer:\n");
  print(buff);
  
  
  deplacerA(5,buff);
  for (int i = 0; i < 25; i++) ecrire('b', buff);
  printf("Résultat deplacerA:\n");
  print(buff);
  
  
  deplacer(-1,buff);
  insertion('s', buff);
  printf("Résultat insertion:\n");
  print(buff);
  
  
  deplacerA(0,buff);
  chargement(buff, "a");
  printf("Résultat chargement:\n");
  print(buff);
  
  
  return 0;
}