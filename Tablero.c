#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Tablero.h"

void *** tablero = NULL;
Barco * barcos = NULL;
int tamanoActual;
int barcosActual;

void inicializarAux(int cantBarcos, int cantS, int cantM, int cantL, int cantX){
    barcosActual = 0;
    barcos = (Barco*) malloc(cantBarcos * sizeof(Barco));
    for (int i = 0; i < cantBarcos; i++){
        barcos[i].HP = 0;
    }
    for(int i = 0; i < cantS; i++){
        generadorBarco('S',rand()%500);
        printf("Barco numero %d\n", barcosActual);
    }
    for(int i = 0; i < cantM; i++){
        generadorBarco('M',rand()%500);
        printf("Barco numero %d\n", barcosActual);
    }
    for(int i = 0; i < cantL; i++){
        generadorBarco('L',rand()%500);
        printf("Barco numero %d\n", barcosActual);
    }
    for(int i = 0; i < cantX; i++){
        generadorBarco('X',rand()%500);
        printf("Barco numero %d\n", barcosActual);
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
    barcos[barcosActual].posicionX = (int *) malloc(cantX * sizeof(int));
    barcos[barcosActual].posicionY = (int *) malloc(cantY * sizeof(int));
    barcos[barcosActual].HP = size;
    barcos[barcosActual].tamano = size;
    barcos[barcosActual].cantX = 0;
    barcos[barcosActual].cantY = 0;
    for (int i = 0; i < cantX; i++){
        barcos[barcosActual].posicionX[i] = valorX + i;
        printf("X: %d\n", barcos[barcosActual].posicionX[i]);
        barcos[barcosActual].cantX++;
    }
    for (int i = 0; i < cantY; i++){
        barcos[barcosActual].posicionY[i] = valorY + i;
        printf("Y: %d\n", barcos[barcosActual].posicionY[i]);
        barcos[barcosActual].cantY++;
    }
    barcosActual++;
}
void generadorBarco(char Tipo, int seed){
    srand(seed);
    int X = (rand()%tamanoActual)+1;
    int Y = (rand()%tamanoActual)+1;
    int sex = (rand()%2);
    switch (Tipo) {
        case 'S': ;
            printf("%d %d\n", X, Y);
            if (sex == 1) { //* Generador Horizontal *//
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
        for (int j = 0; j < barcos[i].cantX; j++){
            for (int k = 0; k < barcos[i].cantY; k++){
                if (barcos[i].posicionX[j] == x && barcos[i].posicionY[k] == y){
                    printf("CASILLA OCUPAA\n");
                    return -1;
                }
            }
        }
    }
    printf("desocupada\n");
    return 0;
}
void mostrarTableroFinal(){
    for (int i = 0; i < barcosActual; i++){ /*Comienza a recorrer el Array de Structs Barcos*/
        printf("CHECK BARCO %d\n", i);
        for (int j = 0; j < barcos[i].cantX; j++){ /*Comienza a recorrer la posicionX de un struck perteneciente al Array*/
            printf("CHECK X %d\n", j);
            printf("%d\n", barcos[i].posicionX[j]);
            for (int k = 0; k < barcos[i].cantY; k++){ /*Comienza a recorrer la posicionY de un struck perteneciente al Array*/
                printf("CHECK Y %d\n", k);
                printf("%d\n", barcos[i].posicionY[k]);
                
                *((char *)tablero[((int)barcos[i].posicionY[k])-1][((int)barcos[i].posicionX[j])-1]) = 'H';
                printf("no cra\n");
            }
        }
    }
    mostrarTablero();
    for (int i = 0; i < barcosActual; i++){
        for (int j = 0; j < barcos[i].cantX; j++){
            free((void *)barcos[i].posicionX[j]);
        }
        for (int j = 0; j < barcos[i].cantY; j++){
            free((void *)barcos[i].posicionY[j]);
        }
        free(barcos[i].posicionX);
        free(barcos[i].posicionY);
    }
    free(barcos);
}