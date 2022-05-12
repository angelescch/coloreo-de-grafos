
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
    u32 * key = calloc(n, sizeof(u32));
    u32 * orden = calloc(n, sizeof(u32));
    u32 * coloreo = calloc(n, sizeof(u32));
    for (u32 i = 0 ; i < n; ++i) {
        orden[i] = i;
    }
    u32 colores_usados = Greedy(g, orden,coloreo);
    for (u32 i= 0; i < n; i++) {
        printf("coloreo de greedy[%u]: %u\n",i,coloreo[i]);
    }
    AleatorizarKeys(n, 457568,key);
    for (u32 i= 0; i < n; i++) {
        printf("key[%u]: %u\n",i,key[i]);
    }
    char a = OrdenFromKey(n,key,orden);
    a = a;
    for (u32 i= 0; i < n; i++) {
        printf("orden[%u]: %u\n",i,orden[i]);
    }
    u32* coloreonovo = PermutarColores(n,coloreo, 4);
    for (u32 i= 0; i < n; i++) {
        printf("permutado coloreo de greedy[%u]: %u\n",i,coloreonovo[i]);
    }

    u32 *RecoloreoCardinal = RecoloreoCardinalidadDecrecienteBC(n, coloreo);
    for (u32 i= 0; i < n; i++) {
        printf("recoloreo de greedy[%u]: %u\n",i,RecoloreoCardinal[i]);
    }

    free(key);
    free(orden);
    free(coloreo);
    free(coloreonovo);
    free(RecoloreoCardinal);
    DestruccionDelGrafo(g);
    // clock_t start = clock();
    // u32 colores_usados = Greedy(g, orden, colorcitos);
    // clock_t end = clock();
    // float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    printf("cantidad de colores que usa Greedy: %u\n", colores_usados);
    // printf("tarda %f\n",seconds);
    return 0;
}