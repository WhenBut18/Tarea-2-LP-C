#include <stdlib.h>
#include <stdio.h>
#include "Cartas.h"
#include "Tablero.h"

Mano Cartas;

void inicializarMazo(){
    Cartas.disponibles = 5;
    Cartas.carta = (void **) malloc(Cartas.disponibles * sizeof(void*));
    for (int i = 0; i < Cartas.disponibles; i++){
        Cartas.carta[i] = (void *) disparoSimple;
    }
}
/*
mostrarMazo(){
    for (int i = 0; i < Cartas.disponibles; i++){
        if (Cartas.carta[i] == disparoSimple){
            printf("si");
        }else{
            printf("no");
        }
    }
    
}
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
        }
    }
    
    
}
void * disparoSimple(int x, int y){
    for (int i = 0; i < barcosActual; i++){
        for (int j = 0; j < barcos[i].tamano; j++){
            if((int *) barcos[i].posicionX[j] == NULL){
                break;
            }
            for (int k = 0; k < barcos[i].tamano; k++){
                if((int *) barcos[i].posicionY[k] == NULL){
                    break;
                }
                if (barcos[i].posicionX[j] == x && barcos[i].posicionY[k] == y){
                    printf("IMPACTO CONFIRMADO\n");
                    *((char *)tablero[y][x]) = 'X';
                    return disparoAleatorio(65, 20, 5, 10, 0, rand()%500);
                }  
            }  
        }
    }
    *((char *)tablero[y][x]) = 'O';
    printf("DISPARO AL AGUA\n");
    return disparoAleatorio(65, 20, 5, 10, 0, rand()%500);
}
void * disparoGrande(int x, int y){

}
void * disparoLineal(int x, int y){

}
void * disparoRadar(int x, int y){

}
void * disparo500KG(int x, int y){

}