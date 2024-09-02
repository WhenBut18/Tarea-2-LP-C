#include <stdlib.h>
#include <stdio.h>
#include "Cartas.h"
#include "Tablero.h"

int main(int argc, char const *argv[]){
    int tamano = 10;
    inicializarTablero(tamano);
    mostrarTablero();
    eliminarTablero();
    return 0;
}
