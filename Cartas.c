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
void * disparoSimple(int x, int y){
    if ()
    for (int i = 0; i < barcosActual; i++){
        
    }
}
void * disparoGrande(int x, int y){

}
void * disparoLineal(int x, int y){

}
void * disparoRadar(int x, int y){

}
void * disparo500KG(int x, int y){

}