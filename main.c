#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "AlduinPaarthurnaxIrileth.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

int main(){
    Grafo g = ConstruccionDelGrafo();
    u32* colorcitos = Bipartito(g);
    if(colorcitos!=NULL){
        for (u32 i= 0; i < g->n; i++) {
            printf("array: %u\n",colorcitos[i]);
        }
    } else {
        printf(":(\n");
    }
    return 0;
}