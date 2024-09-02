#ifndef H_TABLERO
#define H_TABLERO

extern void *** tablero;
extern int tamanoActual;

void inicializarTablero(int tamano);
void mostrarTablero();
void eliminarTablero();
void generadorBarco(char Tipo);
int randomizer();
#endif
