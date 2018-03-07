#include "buffer.h"

int main() {
  //Créer un buffer de 10 lignes de 10 caractères
  buffer *buff = initialisation(10,10);
  test("test\0",buff);
}