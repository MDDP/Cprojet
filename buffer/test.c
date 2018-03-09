#include <stdio.h>

int main() {
  FILE *f = fopen("a","a");
  fputc('a',f);
  fputc('b',f);
  fseek(f,0,SEEK_SET);
  fputc('c',f);
}