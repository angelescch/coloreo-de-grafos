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
    //     for (u32 i= 0; i < n; i++) {
    //         printf("array: %u\n",colorcitos[i]);
    //     }
    // } else {
    //     printf(":(\n");
    // }
    u32 n = NumeroDeVertices(g);
    u32 * key = calloc(7, sizeof(u32));
    u32 * orden = calloc(n, sizeof(u32));
    for (u32 i = 0 ; i < n; ++i) {
        orden[i] = i;
    }
    key[0] = 1;
    key[1] = 2;
    key[2] = 6;
    key[3] = 6;
    key[4] = 0;
    key[5] = 4;
    key[6] = 5;
    char a = OrdenFromKey(n,key,orden);
    a = a;
    for (u32 i= 0; i < n; i++) {
        printf("array: %u\n",orden[i]);
    }

    // clock_t start = clock();
    // u32 colores_usados = Greedy(g, orden, colorcitos);
    // clock_t end = clock();
    // float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    // printf("cantidad de colores que usa Greedy: %u\n", colores_usados);
    // printf("tarda %f\n",seconds);
    return 0;
}