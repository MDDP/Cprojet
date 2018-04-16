#include <stdio.h>
#include <string.h>
#define NBCONFIG 6
/*
 * NBCONFIG représente le nombre de raccourcis dans config.txt
 */

void actualiseConfig(char control[]){
  FILE *config=fopen("config.txt","r");
  for(int i=0;i<NBCONFIG;i++){
    char line[9];
    fgets(line,9,config);
    control[i]=line[strlen(line)-2];
  }
  fclose(config);
}
