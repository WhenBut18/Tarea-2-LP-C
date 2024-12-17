#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Tablero.h"

/*Declaracion de la variablex EXTERN*/
void *** tablero = NULL;
Barco * barcos = NULL;
int tamanoActual;
int barcosActual;

/*
    ***
    cantBarcos : int
    cantS : int
    cantM : int
    cantL : int
    cantX : int
    ***
    void
    ***
    Esta es una funcion auxiliar de la funcion inicializarTablero, la cual se encarga de generar de memoria para los struct barcos dependiendo de cantBarcos,
    como tambien administrar la generacion de los diferentes tipos de barcos dependiendo del valor de los cantS, cantM, cantL, cantX, siendo estos la cantidad de barcos
    1x2, 1x3, 1x4, 1x5 respectivamente.
*/
void inicializarAux(int cantBarcos, int cantS, int cantM, int cantL, int cantX){
    barcosActual = 0;
    barcos = (Barco*) malloc(cantBarcos * sizeof(Barco));
    for (int i = 0; i < cantBarcos; i++){
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

/*
    ***
    tamano : int
    ***
    void
    ***
    Esta funcion se encarga de inicializar el tablero utilizando como informacion el tamaño que debe tener este, entregada en tamano y posteriormente almacenado en una
    variable EXTERN llamada tamanoActual para que sea usada por otra funciones. Ademas utiliza la funcion inicializarAux para generar los barcos correspondientes a cada
    tamaño de tablero/dificultad.
*/
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

/*
    ***
    None
    ***
    void
    ***
    Una funcion simple para mostrar el estado actual del tablero.
*/
void mostrarTablero(){
    for (int i = 0; i < tamanoActual; i++) {
        for (int j = 0; j < tamanoActual; j++) { 
            printf("%c ", *((char *)tablero[i][j]));
        }
        printf("\n");
    }
}

/*
    ***
    None
    ***
    void
    ***
    Una funcion simple que se encarga de eliminar y liberar la memoria almacenada para el tablero.
*/
void eliminarTablero(){
    for (int i = 0; i < tamanoActual; i++) {
        for (int j = 0; j < tamanoActual; j++) { 
            free(tablero[i][j]);
            tablero[i][j] = NULL;
        }
        free(tablero[i]);
        tablero[i] = NULL;
    }
    free(tablero);
    tablero = NULL;
}

/*
    ***
    cantX : int
    cantX : int
    size : int
    valorX: int
    valorY : int
    ***
    void
    ***
    Una funcion auxiliar de generadorBarco que se encarga de reservar la memoria para las variables posicionX y posicionY del array de structs Barco ya generado,
    usando para esto las variables cantX, cantY y size, y tambien se encarga de darle los valores correspodiente del barco generado a los arrays posicionX/Y.
*/
void generadorBarcoAux(int cantX, int cantY, int size, int valorX, int valorY){
    barcos[barcosActual].posicionX = (int *) malloc(cantX * sizeof(int));
    barcos[barcosActual].posicionY = (int *) malloc(cantY * sizeof(int));
    barcos[barcosActual].HP = size;
    barcos[barcosActual].tamano = size;
    barcos[barcosActual].cantX = 0;
    barcos[barcosActual].cantY = 0;
    for (int i = 0; i < cantX; i++){
        barcos[barcosActual].posicionX[i] = valorX + i;
        barcos[barcosActual].cantX++;
    }
    for (int i = 0; i < cantY; i++){
        barcos[barcosActual].posicionY[i] = valorY + i;
        barcos[barcosActual].cantY++;
    }
    barcosActual++;
}

/*
    ***
    Tipo : char
    Seed : int
    
    ***
    Tipo de Retorno o None
    ***
    Se encarga de generar el tipo de barco correspondiente a la variable Tipo, utilizando la recursividad en caso de que el barco se salga de las casillas
    o este se intente generar encima de otro barco. Seed es utilizado para asegurar la aleatoridad de la generacion de forma que cada iteracion de la
    funcion en recursividad de un resultado diferente. Utiliza generadorBarcoAux y casillaChecker.
*/
void generadorBarco(char Tipo, int seed){
    srand(seed);
    int X = (rand()%tamanoActual)+1;
    int Y = (rand()%tamanoActual)+1;
    int orientacion = (rand()%2);
    switch (Tipo) {
        case 'S': ;
            if (orientacion == 1) { //* Generador Horizontal *//
                if (X+1 > tamanoActual){
                    generadorBarco(Tipo, seed + X*Y);
                    return;
                }  
                if (casillaChecker(X, Y) == 0 && casillaChecker(X+1,Y) == 0){
                    generadorBarcoAux(2,1,2,X,Y);
                    return;
                } else {
                    generadorBarco(Tipo, seed + X*Y);
                    return;
                }
            } else { //* Generador Vertical *//
                if (Y+1 > tamanoActual){
                    generadorBarco(Tipo, (seed + X*Y));
                    return;
                }
                if (casillaChecker(X, Y) == 0 && casillaChecker(X,Y+1) == 0){
                    generadorBarcoAux(1,2,2,X,Y);
                    return;
                } else {
                    generadorBarco(Tipo, (seed + X*Y));
                    return;
                }
            }    
        return;
        break;
        case 'M': ;
            if (orientacion == 0) { //* Generador Horizontal *//
                if (X+2 > tamanoActual){
                    generadorBarco(Tipo, seed + X*Y);
                    return;
                }  
                if (casillaChecker(X, Y) == 0 && casillaChecker(X+1,Y) == 0 && casillaChecker(X+2,Y) == 0){
                    generadorBarcoAux(3,1,3,X,Y);
                    return;
                } else {
                    generadorBarco(Tipo, seed + X*Y);
                    return;
                }
            } else { //* Generador Vertical *//
                if (Y+2 > tamanoActual){
                    generadorBarco(Tipo, (seed + X*Y));
                    return;
                }
                if (casillaChecker(X, Y) == 0 && casillaChecker(X,Y+1) == 0 && casillaChecker(X,Y+2) == 0){
                    generadorBarcoAux(1,3,3,X,Y);
                    return;
                } else {
                    generadorBarco(Tipo, (seed + X*Y));
                    return;
                }
            }    
            return;
            break;
        case 'L':
            if (orientacion == 0) { //* Generador Horizontal *//
                if (X+3 > tamanoActual){
                    generadorBarco(Tipo, seed + X*Y);
                    return;
                }  
                if (casillaChecker(X, Y) == 0 && casillaChecker(X+1,Y) == 0 && casillaChecker(X+2,Y) == 0 && casillaChecker(X+3,Y) == 0){
                    generadorBarcoAux(4,1,4,X,Y);
                    return;
                } else {
                    generadorBarco(Tipo, seed + X*Y);
                    return;
                }
            } else { //* Generador Vertical *//
                if (Y+3 > tamanoActual){
                    generadorBarco(Tipo, (seed + X*Y));
                    return;
                }
                if (casillaChecker(X, Y) == 0 && casillaChecker(X,Y+1) == 0 && casillaChecker(X,Y+2) == 0 && casillaChecker(X,Y+3) == 0){
                    generadorBarcoAux(1,4,4,X,Y);
                    return;
                } else {
                    generadorBarco(Tipo, (seed + X*Y));
                    return;
                }
            }    
            return;
            break;
        case 'X':
            if (orientacion == 0) { //* Generador Horizontal *//
                if (X+4 > tamanoActual){
                    generadorBarco(Tipo, seed + X*Y);
                    return;
                }  
                if (casillaChecker(X, Y) == 0 && casillaChecker(X+1,Y) == 0 && casillaChecker(X+2,Y) == 0  && casillaChecker(X+3,Y) == 0 && casillaChecker(X+4,Y) == 0){
                    generadorBarcoAux(5,1,5,X,Y);
                    return;
                } else {
                    generadorBarco(Tipo, seed + X*Y);
                    return;
                }
            } else { //* Generador Vertical *//
                if (Y+4 > tamanoActual){
                    generadorBarco(Tipo, (seed + X*Y));
                    return;
                }
                if (casillaChecker(X, Y) == 0 && casillaChecker(X,Y+1) == 0 && casillaChecker(X,Y+2) == 0 && casillaChecker(X,Y+3) == 0 && casillaChecker(X,Y+4) == 0){
                    generadorBarcoAux(1,5,5,X,Y);
                    return;
                } else {
                    generadorBarco(Tipo, (seed + X*Y));
                    return;
                }
            }    
            return;
            break;
        default:
            break;
    }
}

/*
    ***
    x : int
    y : int
    ***
    int
    ***
    Revisa el array de structs Barco en busca de algun barco que este ubicado en la coordenadas representadas por las variables x e y, retorna un 0 si no encuentra
    ningun conflicto y -1 si encuentra un barco ya generado en la posicion.
*/
int casillaChecker(int x, int y){
    for (int i = 0; i < barcosActual; i++){
        if (barcos[i].HP == 0){
            continue;
        }
        for (int j = 0; j < barcos[i].cantX; j++){
            for (int k = 0; k < barcos[i].cantY; k++){
                if (barcos[i].posicionX[j] == x && barcos[i].posicionY[k] == y){
                    return -1;
                }
            }
        }
    }
    return 0;
}

/*
    ***
    None
    ***
    Void
    ***
    Al igual que el tablero esta funcion muestra el tablero por consola, pero en esta ocasion tambien recorre el array de structs Barco para ir verificando si los barcos 
    fueron destruidos o no, si fueron destruidos no hace nada, si no lo fueron reemplaza el simbolo acutal del tablero por un H. Ademas tambien libera la memoria del 
    array de structs Barco.
*/
void mostrarTableroFinal(){
    
    for (int i = 0; i < barcosActual; i++){ /*Comienza a recorrer el Array de Structs Barcos*/
        for (int j = 0; j < barcos[i].cantX; j++){ /*Comienza a recorrer la posicionX de un structs perteneciente al Array*/
            for (int k = 0; k < barcos[i].cantY; k++){ /*Comienza a recorrer la posicionY de un structs perteneciente al Array*/
                if (*((char *)tablero[((int)barcos[i].posicionY[k])-1][((int)barcos[i].posicionX[j])-1]) == 'X'){
                    continue;
                }
                *((char *)tablero[((int)barcos[i].posicionY[k])-1][((int)barcos[i].posicionX[j])-1]) = 'H';
            }
        }
    }
    printf("PARTIDA TERMINADA\nO: Disparos al agua\nX: Disparos Acertados\nH: Barcos sobrevivientes");
    mostrarTablero();
    for (int i = 0; i < barcosActual; i++){
        free(barcos[i].posicionX);
        free(barcos[i].posicionY);
    }
    free(barcos);
}