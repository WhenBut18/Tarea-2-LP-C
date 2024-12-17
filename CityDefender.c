#include <stdlib.h>
#include <stdio.h>
#include "Cartas.h"
#include "Tablero.h"

/*
    ***
    None
    ...
    ***
    int
    ***
    Se encarga de preguntar por consola la dificultad a elegir y utiliza las distintas funciones desarrolladas para generar una partida del juego.
 */
int main(){
    int eleccion;
    printf("Seleccione la Dificultad:\n1.- Facil\n2.- Medio\n3.- Dificil\nElija un numero: ");
    scanf("%d", &eleccion);
    switch (eleccion)
    {
    case 1:
        inicializarTablero(11);
        inicializarMazo();
        for (int i = 0; i < 30; i++){
            printf("Turno %d\n", i+1);
            mostrarTablero();
            mostrarMazo();
            usarCarta();
        }
        liberarMazo();
        mostrarTableroFinal();
        eliminarTablero();
        break;
    case 2:
        inicializarTablero(17);
        inicializarMazo();
        for (int i = 0; i < 25; i++){
            printf("Turno %d\n", i+1);
            mostrarTablero();
            mostrarMazo();
            usarCarta();
        }
        liberarMazo();
        mostrarTableroFinal();
        eliminarTablero();
        break;
    case 3:
        inicializarTablero(21);
        inicializarMazo();
        for (int i = 0; i < 15; i++){
            printf("Turno %d\n", i+1);
            mostrarTablero();
            mostrarMazo();
            usarCarta();
        }
        liberarMazo();
        mostrarTableroFinal();
        eliminarTablero();
        break;
    }
    return 0;
}
