#include <stdlib.h>
#include <stdio.h>
#include "Cartas.h"
#include "Tablero.h"

Mano Cartas;

/*
    ***
    None
    ***
    void
    ***
    Se encarga de reservar la memoria para las cartas de struct Mano.
*/
void inicializarMazo(){
    Cartas.disponibles = 5;
    Cartas.carta = (void **) malloc(Cartas.disponibles * sizeof(void*));
    for (int i = 0; i < Cartas.disponibles; i++){
        Cartas.carta[i] = (void *) disparoSimple;
    }
}

/*
    ***
    None
    ***
    void
    ***
    Imprime en consola que carta actualmente en cada posicion de la baraja de cartas.
*/
void mostrarMazo(){
    printf("Cartas:\n| ");
    for (int i = 0; i < Cartas.disponibles; i++){
        if (Cartas.carta[i] == disparoSimple){
            printf("Simple | ");
        } else if (Cartas.carta[i] == disparoGrande)
        {
            printf("Grande | ");
        } else if (Cartas.carta[i] == disparoLineal)
        {
            printf("Lineal | ");
        } else if (Cartas.carta[i] == disparoRadar)
        {
            printf("Radar | ");
        } else if (Cartas.carta[i] == disparo500KG)
        {
            printf("500KG | ");
        } 
    }
    printf("\n");
}

/*
    ***
    probS : int
    probG : int
    probL : int
    probR : int
    probKG : int
    seed : int
    ***
    void *
    ***
    Se encarga de administrar las probabilidades otorgadas por las variables probS, probG, probL, probR, probKG, y de devolver el puntero a funcion dependiendo de que
    haya tocado, ademas usa el seed para en caso de que ya se haya usado el disparo de 500KG generar otro numero aleatorio para asegurar no repeticiones.
*/
void * disparoAleatorio(int probS,int probG, int probL, int probR, int probKG, int seed){
    srand(seed + probS + probG + probL);
    int dado = (rand() % 101) + 1;
    if (probKG == 0){
        if (dado > 0 && dado <= probS){
            return (void*)disparoSimple;
        } else if (dado > probS && dado <= probS + probG){
            return (void*)disparoGrande;
        } else if (dado > probS + probG && dado <= probS + probG + probL){
            return (void*)disparoLineal;
        } else if (dado > probS + probG + probL && dado <= probS + probG + probL + probR){
            return (void*)disparoRadar;
        } else {
            printf("ERROR PORCENTUAL");
            return (void*)disparoSimple;
        }
    } else {
        if (dado > 0 && dado <= probS){
            return (void*)disparoSimple;
        } else if (dado > probS && dado <= probS + probG){
            return (void*)disparoGrande;
        } else if (dado > probS + probG && dado <= probS + probG + probL){
            return (void*)disparoLineal;
        } else if (dado > probS + probG + probL && dado <= probS + probG + probL + probR){
            return (void*)disparoRadar;
        } else if (dado > probS + probG + probL + probR && dado <= probS + probG + probL + probR + probKG){
            if (Cartas.disponibles < 5){
                disparoAleatorio(probS, probG, probL, probR, probKG, rand()%500);
            }
            return (void*)disparo500KG;
        } else {
            printf("ERROR PORCENTUAL");
            return (void*)disparoSimple;
        }
    }
}

/*
    ***
    x : int
    y : int
    ***
    void *
    ***
    Se encarga de efectuar el disparo simple utilizando el casillaChecker para saber si hay o no un barco en esa casilla, cambiando el caracter del tablero
    a X en caso de acertar y en O en caso de errar. Retorna un puntero de funcion de la funcion disparoAleatorio.
*/
void * disparoSimple(int x, int y){

    if (casillaChecker(x, y) == -1){
        printf("IMPACTO CONFIRMADO\n");
        *((char *)tablero[y-1][x-1]) = 'X';
    } else {
        *((char *)tablero[y-1][x-1]) = 'O';
        printf("DISPARO AL AGUA\n");
    }
    return (void *) disparoAleatorio(65,20,5,10,0,rand()%500);
}

/*
    ***
    x : int
    y : int
    ***
    void *
    ***
    Se encarga de efectuar el disparo Grande utilizando el casillaChecker para saber si hay o no un barco en esa casilla, cambiando el caracter del tablero
    a X en caso de acertar y en O en caso de errar. Retorna un puntero de funcion de la funcion disparoAleatorio.
*/
void * disparoGrande(int x, int y){
    for (int l = x-1; l < x+2; l++) {
        if (l < 1 || l > tamanoActual){
            printf("cueclk");
            continue;
        }
        for (int t = y-1;  t< y+2; t++){
            printf("%d %d\n",y, t);
            if (t < 1 || l > tamanoActual){
                printf("cueclk");
                continue;
            }
            if (casillaChecker(l, t) == -1){
                printf("IMPACTO CONFIRMADO\n");
                *((char *)tablero[t-1][l-1]) = 'X';
            } else {
                *((char *)tablero[t-1][l-1]) = 'O';
                printf("DISPARO AL AGUA\n");
            }
        }
    }
    return disparoAleatorio(80, 3, 10, 5, 2, rand()%500);
}

/*
    ***
    x : int
    y : int
    ***
    void *
    ***
    Se encarga de efectuar el disparo Lineal utilizando el casillaChecker para saber si hay o no un barco en esa casilla, cambiando el caracter del tablero
    a X en caso de acertar y en O en caso de errar. Retorna un puntero de funcion de la funcion disparoAleatorio.
*/
void * disparoLineal(int x, int y){
    int eleccion;
    printf("Seleccione Tipo de disparo:\n1.- Vertical\n2.- Horizontal\nSeleccione un numero: ");
    scanf("%d",&eleccion);
    switch (eleccion)
    {
    case 1:
        for (int l = y-2; l < y+3; l++) {
            if (l < 1 || l > tamanoActual){
                continue;
            }
            if (casillaChecker(x, l) == -1){
                printf("IMPACTO CONFIRMADO\n");
                *((char *)tablero[l-1][x-1]) = 'X';
            } else {
                *((char *)tablero[l-1][x-1]) = 'O';
                printf("DISPARO AL AGUA\n");
            }
        } 
        break;
    case 2:
        for (int l = x-2; l < x+3; l++) {
            if (l < 1 || l > tamanoActual){
                continue;
            }
            if (casillaChecker(l, y) == -1){
                printf("IMPACTO CONFIRMADO\n");
                *((char *)tablero[y-1][l-1]) = 'X';
            } else {
                *((char *)tablero[y-1][l-1]) = 'O';
                printf("DISPARO AL AGUA\n");
            }
        } 
        break;
    }
    return disparoAleatorio(85, 5, 2, 6, 2, rand()%500);
}

/*
    ***
    x : int
    y : int
    ***
    void *
    ***
    Se encarga de efectuar el disparo Radar utilizando el casillaChecker para saber si hay o no un barco en esa casilla, cambiando el caracter del tablero
    a ? en caso de acertar. Retorna un puntero de funcion de la funcion disparoAleatorio.
*/
void * disparoRadar(int x, int y){
    for (int l = x-2; l < x+3; l++) {
        if (l < 1 || l > tamanoActual){
            continue;
        }
        for (int t = y-2; t< y+3; t++){
            if (t < 1 || l > tamanoActual){
                continue;
            }
            if (casillaChecker(l, t) == -1){
                if (*((char *)tablero[t-1][l-1]) == 'X'){
                    continue;
                } else {
                    printf("BARCO DETECTADO\n");
                    *((char *)tablero[t-1][l-1]) = '?';
                }
            }
        }
    }
    return disparoAleatorio(75, 15, 5, 2, 3, rand()%500);
}

/*
    ***
    x : int
    y : int
    ***
    void *
    ***
    Se encarga de efectuar el disparo 500KG utilizando el casillaChecker para saber si hay o no un barco en esa casilla, cambiando el caracter del tablero
    a X en caso de acertar y en O en caso de errar. Retorna un puntero de funcion de la funcion disparoAleatorio.
*/
void * disparo500KG(int x, int y){
    printf("PREPARANDO CAÑON ULTRAMEGAHIPERDUPER DESTRUCCION ASEGURADAD\n");
    for (int l = x-5; l < x+6; l++) {
        if (l < 1 || l > tamanoActual){
            continue;
        }
        for (int t = y-5; t< y+6; t++){
            if (t < 1 || l > tamanoActual){
                continue;
            }
            if (casillaChecker(l, t) == -1){
                *((char *)tablero[t-1][l-1]) = 'X';
                printf("IMPACTO CONFIRMADO\n");
            } else {
                *((char *)tablero[t-1][l-1]) = 'O';
            }
        }
    }
    return disparoAleatorio(75, 15, 5, 2, 3, rand()%500);
}

/*
    ***
    None
    ***
    void
    ***
    Libera la memoria del mazo.
*/
void liberarMazo(){
    free(Cartas.carta);
    Cartas.carta = NULL;
}

/*
    ***
    None
    ***
    void
    ***
    Se encarga de preguntar por pantalla la carta a utilizar y de ejecutarla respectivamente, y en caso de que se use la carta de 500KG intercambia la carta almacenada en la ultima
    posicion con la carta que fue utilizada, y le resta -1 a la cantidad disponible de cartas para que quede deshabilitado un cañon.
*/
void usarCarta(){
    int eleccion;
    int x,y;    
    printf("Seleccione una Carta (1-%d): ",Cartas.disponibles);
    scanf("%d", &eleccion);
    printf("X: ");
    scanf("%d", &x);
    printf("Y: ");
    scanf("%d", &y);
    if (x > tamanoActual || y > tamanoActual){
        printf("Las coordenadas X:%d Y:%d se encuentran fuera de rango, intente nuevamente",x,y);
        usarCarta();
        return;
    }
    void *(*funcionUsar) (int,int) = Cartas.carta[eleccion-1];
    Cartas.carta[eleccion-1]= funcionUsar(x,y);
    if (funcionUsar == disparo500KG){
        Cartas.carta[eleccion-1] = Cartas.carta[Cartas.disponibles-1];
        Cartas.disponibles--;
    }
}
