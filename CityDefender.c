#include <stdlib.h>
#include <stdio.h>
#include "Cartas.h"
#include "Tablero.h"

int main(int argc, char const *argv[]){
    int eleccion;
    printf("Seleccione la Dificultad:\n1.- Facil\n2.- Medio\n3.- Dificil\nElija un numero: ");
    scanf("%d", &eleccion);
    switch (eleccion)
    {
    case 1:
        inicializarTablero(11);
        mostrarTablero();
        eliminarTablero();
        break;
    case 2:
        inicializarTablero(17);
        mostrarTablero();
        eliminarTablero();
        break;
    case 3:
        inicializarTablero(21);
        mostrarTablero();
        eliminarTablero();
        break;
    }
    return 0;
}
