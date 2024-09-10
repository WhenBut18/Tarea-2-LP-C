#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Tablero.h"

void *** tablero = NULL;
Barco * barcos = NULL;
int tamanoActual;
int barcosActual;
int barcosTotal;

void inicializarAux(int cantBarcos, int cantS, int cantM, int cantL, int cantX){
    barcosActual = cantBarcos;
    barcosTotal = 0;
    barcos = (Barco*) malloc(barcosActual * sizeof(Barco));   
    for (int i = 0; i < barcosActual; i++){
        barcos[i].HP = 0;
    }
    for(int i = 0; i < cantS; i++){
        generadorBarco('S',rand()%500);
    }
    for(int i = 0; i < cantM; i++){
        generadorBarco('M',rand()%500);
    }
    for(int i = 0; i < cantL; i++){
        generadorBarco('L',rand()%500);
    }
    for(int i = 0; i < cantX; i++){
        generadorBarco('X',rand()%500);
    }
}
void inicializarTablero(int tamano) {
    srand(time(NULL));
    tamanoActual = tamano;
    tablero = (void ***) malloc(tamano * sizeof(void *));
    for (int i = 0; i < tamano; i++) {
        tablero[i] = (void **) malloc(tamano * sizeof(void *));
        if (tablero[i] == NULL) {
            return;
        }
        for (int j = 0; j < tamano; j++) {
            tablero[i][j] = (char *) malloc(sizeof(char));
            if (tablero[i][j] == NULL) {
                return;
            }
            *((char *)tablero[i][j]) = '~';
        }
    }
    printf("Memoria reservada exitosamente para el tablero de %d x %d\n", tamano, tamano);
    switch (tamano){
    case 11:
        inicializarAux(5,2,1,1,1);
        break;
    case 17:
        inicializarAux(7,3,2,1,1);
        break;
    case 21:
        inicializarAux(9,3,2,2,2);
        break;
    }
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
void generadorBarcoAux(int cantX, int cantY, int size, int valorX, int valorY){
    barcos[barcosTotal].posicionX = (int *) malloc(cantX * sizeof(int));
    barcos[barcosTotal].posicionY = (int *) malloc(cantY * sizeof(int));
    barcos[barcosTotal].HP = size;
    barcos[barcosTotal].tamano = size;
    for (int i = 0; i < cantX; i++){
        barcos[barcosTotal].posicionX[i] = valorX + i;
        printf("X: %d\n", barcos[barcosTotal].posicionX[i]);
    }
    for (int i = 0; i < cantY; i++){
        barcos[barcosTotal].posicionY[i] = valorY + i;
        printf("Y: %d\n", barcos[barcosTotal].posicionY[i]);
    }
}
void generadorBarco(char Tipo, int seed){
    srand(seed);
    int X = (rand()%tamanoActual)+1;
    int Y = (rand()%tamanoActual)+1;
    int sex = rand()%2;
    switch (Tipo) {
        case 'S': ;
            printf("%d %d\n", X, Y);
            if (sex == 0) { //* Generador Horizontal *//
                printf("hor\n");
                if (X+1 > tamanoActual){
                    printf("FUERA DE RANGO\n");
                    generadorBarco(Tipo, seed + X*Y);
                    return;
                }  
                if (casillaChecker(X, Y) == 0 && casillaChecker(X+1,Y) == 0){
                    generadorBarcoAux(2,1,2,X,Y);
                    return;
                } else {
                    printf("choque barco\n");
                    generadorBarco(Tipo, seed + X*Y);
                    return;
                }
            } else { //* Generador Vertical *//
                printf("ver\n");
                if (Y+1 > tamanoActual){
                    printf("FUERA DE RANGO\n");
                    generadorBarco(Tipo, (seed + X*Y));
                    return;
                }
                if (casillaChecker(X, Y) == 0 && casillaChecker(X,Y+1) == 0){
                    generadorBarcoAux(1,2,2,X,Y);
                    return;
                } else {
                    printf("choque barco\n");
                    generadorBarco(Tipo, (seed + X*Y));
                    return;
                }
            }    
        return;
        break;
        case 'M': ;
            printf("%d %d\n", X, Y);
            if (sex == 0) { //* Generador Horizontal *//
                printf("hor\n");
                if (X+2 > tamanoActual){
                    printf("FUERA DE RANGO\n");
                    generadorBarco(Tipo, seed + X*Y);
                    return;
                }  
                if (casillaChecker(X, Y) == 0 && casillaChecker(X+1,Y) == 0 && casillaChecker(X+2,Y) == 0){
                    generadorBarcoAux(3,1,3,X,Y);
                    return;
                } else {
                    printf("choque barco\n");
                    generadorBarco(Tipo, seed + X*Y);
                    return;
                }
            } else { //* Generador Vertical *//
                printf("ver\n");
                if (Y+2 > tamanoActual){
                    printf("FUERA DE RANGO\n");
                    generadorBarco(Tipo, (seed + X*Y));
                    return;
                }
                if (casillaChecker(X, Y) == 0 && casillaChecker(X,Y+1) == 0 && casillaChecker(X,Y+2) == 0){
                    generadorBarcoAux(1,3,3,X,Y);
                    return;
                } else {
                    printf("choque barco\n");
                    generadorBarco(Tipo, (seed + X*Y));
                    return;
                }
            }    
            return;
            break;
        case 'L':
            printf("%d %d\n", X, Y);
            if (sex == 0) { //* Generador Horizontal *//
                printf("hor\n");
                if (X+3 > tamanoActual){
                    printf("FUERA DE RANGO\n");
                    generadorBarco(Tipo, seed + X*Y);
                    return;
                }  
                if (casillaChecker(X, Y) == 0 && casillaChecker(X+1,Y) == 0 && casillaChecker(X+2,Y) == 0 && casillaChecker(X+3,Y) == 0){
                    generadorBarcoAux(4,1,4,X,Y);
                    return;
                } else {
                    printf("choque barco\n");
                    generadorBarco(Tipo, seed + X*Y);
                    return;
                }
            } else { //* Generador Vertical *//
                printf("ver\n");
                if (Y+3 > tamanoActual){
                    printf("FUERA DE RANGO\n");
                    generadorBarco(Tipo, (seed + X*Y));
                    return;
                }
                if (casillaChecker(X, Y) == 0 && casillaChecker(X,Y+1) == 0 && casillaChecker(X,Y+2) == 0 && casillaChecker(X,Y+3) == 0){
                    generadorBarcoAux(1,4,4,X,Y);
                    return;
                } else {
                    printf("choque barco\n");
                    generadorBarco(Tipo, (seed + X*Y));
                    return;
                }
            }    
            return;
            break;
        case 'X':
            printf("%d %d\n", X, Y);
            if (sex == 0) { //* Generador Horizontal *//
                printf("hor\n");
                if (X+4 > tamanoActual){
                    printf("FUERA DE RANGO\n");
                    generadorBarco(Tipo, seed + X*Y);
                    return;
                }  
                if (casillaChecker(X, Y) == 0 && casillaChecker(X+1,Y) == 0 && casillaChecker(X+2,Y) == 0  && casillaChecker(X+3,Y) == 0 && casillaChecker(X+4,Y) == 0){
                    generadorBarcoAux(5,1,5,X,Y);
                    return;
                } else {
                    printf("choque barco\n");
                    generadorBarco(Tipo, seed + X*Y);
                    return;
                }
            } else { //* Generador Vertical *//
                printf("ver\n");
                if (Y+4 > tamanoActual){
                    printf("FUERA DE RANGO\n");
                    generadorBarco(Tipo, (seed + X*Y));
                    return;
                }
                if (casillaChecker(X, Y) == 0 && casillaChecker(X,Y+1) == 0 && casillaChecker(X,Y+2) == 0 && casillaChecker(X,Y+3) == 0 && casillaChecker(X,Y+4) == 0){
                    generadorBarcoAux(1,5,5,X,Y);
                    return;
                } else {
                    printf("choque barco\n");
                    generadorBarco(Tipo, (seed + X*Y));
                    return;
                }
            }    
            return;
            break;
        default:
            printf("Tipo de barco invalido");
            break;
    }
}
int casillaChecker(int x, int y){
    for (int i = 0; i < barcosActual; i++){
        if (barcos[i].HP == 0){
            continue;
        }
        for (int j = 0; j < barcos[i].tamano; j++){
            if ((int *)barcos[i].posicionX[j] == NULL){
                break;
            }
            for (int k = 0; k < barcos[i].tamano; k++){
                if ((int *)barcos[i].posicionX[k] == NULL){
                    break;
                }
                if (barcos[i].posicionX[j] == x || barcos[i].posicionY[k] == y){
                    printf("CASILLA OCUPAA\n");
                    return -1;
                }
            }
        }
    }
    printf("desocupada\n");
    return 0;
}