#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Tablero.h"

void *** tablero = NULL;
int tamanoActual;

void inicializarTablero(int tamano) {
    tamanoActual=tamano;
    tablero = (void ***) malloc(tamano * sizeof(void *));
    if (tablero == NULL) {
        perror("Error al reservar memoria para el tablero");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < tamano; i++) {
        tablero[i] = (void **) malloc(tamano * sizeof(void *));
        if (tablero[i] == NULL) {
            perror("Error al reservar memoria para una fila del tablero");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < tamano; j++) {
            tablero[i][j] = (char *) malloc(sizeof(char));
            if (tablero[i][j] == NULL) {
                perror("Error al reservar memoria para una celda del tablero");
                exit(EXIT_FAILURE);
            }
            *((char *)tablero[i][j]) = '~'; // Inicializa cada celda con '#'
        }
    }
    printf("Memoria reservada exitosamente para el tablero de %d x %d\n", tamano, tamano);
}
void mostrarTablero(){
    if (tablero == NULL) {
        perror("Error Tablero no Inicializado");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < tamanoActual; i++) {
        for (int j = 0; j < tamanoActual; j++) { 
            printf("%c ", *((char *)tablero[i][j]));
        }
        printf("\n");
    }
}
void eliminarTablero(){
    for (int i = 0; i < tamanoActual; i++) {
        for (int j = 0; j < tamanoActual; j++) { 
            free(tablero[i][j]); // Libera la memoria de cada celda
        }
        free(tablero[i]); // Libera la memoria de cada fila
    }
    free(tablero); // Libera la memoria del tablero
}
int randomizer(){
    srand(time(1));
    return rand();
}
void generadorBarco(char Tipo){
    switch (Tipo) {
        case 'S':
            int X = randomizer();
            int Y = randomizer();
            if (randomizer()%2 == 0) {
                
            } else {

            }
            
            break;
        case 'M':
            /* code */
            break;
        case 'L':
            /* code */
            break;
        case 'XL':
            /* code */
            break;
        default:
            printf("Tipo de barco invalido");
            break;
    }
}