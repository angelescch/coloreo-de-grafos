#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "AlduinPaarthurnaxIrileth.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

int main(){
    Grafo g = ConstruccionDelGrafo();
    // u32* colorcitos = Bipartito(g);
    // if(colorcitos!=NULL){
    //     for (u32 i= 0; i < g->n; i++) {
    //         printf("array: %u\n",colorcitos[i]);
    //     }
    // } else {
    //     printf(":(\n");
    // }
    u32 n = NumeroDeVertices(g);
    u32 * colorcitos = calloc(n, sizeof(u32));
    u32 * orden = calloc(n, sizeof(u32));
    for (u32 i = 0 ; i < n; ++i) {
        orden[i] = i;
    }
    clock_t start = clock();
    u32 colores_usados = Greedy(g, orden, colorcitos);
    clock_t end = clock();
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("cantidad de colores que usa Greedy: %u\n", colores_usados);
    printf("tarda %f\n",seconds);
    return 0;
}