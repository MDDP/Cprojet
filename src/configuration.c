#include "configuration.h"

void actualiseConfig (char control[]) {
  FILE *config = fopen("config.txt","r");
  for(int i = 0; i < NBCONFIG; i++){
    char line[9];
    fgets(line,9,config);
    control[i] = line[strlen(line)-2];
  }
  fclose(config);
}

void sauvegardeConfig (char control[]) {
  FILE *config = fopen("config.txt", "w");
  fputs("'cpy':", config);
  fputc(control[0], config);
  fputc('\n', config);
  fputs("'pst':", config);
  fputc(control[1], config);
  fputc('\n', config);
  fputs("'cut':", config);
  fputc(control[2], config);
  fputc('\n', config);
  fputs("'clr':", config);
  fputc(control[3], config);
  fputc('\n', config);
  fputs("'men':", config);
  fputc(control[4], config);
  fputc('\n', config);
  fputs("'rfs':", config);
  fputc(control[5], config);
  fputc('\n', config);
  fclose(config);
}