#ifndef H_TABLERO
#define H_TABLERO

extern void *** tablero;
extern int tamanoActual;
extern int barcosActual;

typedef struct Barco{ // Struct para almacenar los barcos y sus posiciones.
    int HP;
    int tamano;
    int * posicionX;
    int * posicionY;
    int cantX;
    int cantY;
} Barco;

extern Barco * barcos;

void inicializarTablero(int tamano);
void inicializarAux(int cantBarcos, int cantS, int cantM, int cantL, int cantX);
void mostrarTablero();
void eliminarTablero();
void mostrarTableroFinal();

void generadorBarco(char Tipo, int seed);
int casillaChecker(int x, int y);
void generadorBarcoAux(int cantX, int cantY, int size, int valorX, int valorY);

#endif
