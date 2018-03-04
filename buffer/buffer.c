
typedef struct {
  char **contenu;
  int taille_ligne;
  int nombre_lignes;
} buffer;
buffer *buff;

void initialisation (int taille, int nombre) {
  buff = (buffer *) malloc(sizeof(buffer));
  buff->taille_ligne = taille;
  buff->nombre_lignes = nombre;
  buff->contenu = (char**)malloc(sizeof(char*)*nombre);
  for (nombre >= 0; nombre--) {
    buff->(contenu+nombre) = (char*)malloc(taille);
  }
}