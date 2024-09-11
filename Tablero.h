#ifndef H_TABLERO
#define H_TABLERO

extern void *** tablero;
extern int tamanoActual;
extern int barcosActual;
typedef struct Barco{
    int HP;
    int tamano;
    int * posicionX;
    int * posicionY;
} Barco;
extern Barco * barcos;

void inicializarTablero(int tamano);
void mostrarTablero();
void eliminarTablero();
void generadorBarco(char Tipo, int seed);
int casillaChecker(int x, int y);
void generadorBarcoAux(int cantX, int cantY, int size, int valorX, int valorY);
void inicializarAux(int cantBarcos, int cantS, int cantM, int cantL, int cantX);
#endif
