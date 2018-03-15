#include <stdio.h>
#include "buffer.h"

int main() {
  buffer *buff = initialisation(1,5);
  for (int i = 0; i < 100; i++) ajout('a', buff);
  printf("Résultat:\n");
  print(buff);
}