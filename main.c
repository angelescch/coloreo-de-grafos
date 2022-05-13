
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "AlduinPaarthurnaxIrileth.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

int main(int argc, char* argv[]){
    argc = argc;
    u32 cantidad_colores_usados, R;
    char error;
    int alpha = atoi(argv[1]), beta = atoi(argv[2]), rho = atoi(argv[3]);
    beta = beta;
    Grafo g = ConstruccionDelGrafo();

    u32 n = NumeroDeVertices(g);
    u32 m = NumeroDeLados(g);
    u32 d = Delta(g);

    printf("Número de vértices: %u, Número de lados: %u, Delta del grafo: %u\n", n, m, d);

    // Bipartito
    u32* colorcitos = Bipartito(g);
    if(colorcitos!=NULL){
        printf("El grafo es bipartito\n");
        if (n < 101) {
            printf("\n\nListado de vértices de la Primera Parte:\n");
            printf("[");
            for (u32 i; i<n ;++i) {
                if (colorcitos[i]==1) {
                    printf("%u, ", Nombre(i,g));
                }
            }
            printf("]\n\n");

            printf("\n\nListado de vértices de la Segunda Parte:\n");
            printf("[");
            for (u32 i; i<n ;++i) {
                if (colorcitos[i]==2) {
                    printf("%u, ", Nombre(i,g));
                }
            }
            printf("]\n\n");
        }
    } else {
        printf("\nEl grafo no es bipartito\n");
    }

    u32 * key = calloc(n, sizeof(u32));
    u32 * orden = calloc(n, sizeof(u32));
    u32 * coloreo = calloc(n, sizeof(u32));


    // crea orden natural
    for (u32 i = 0 ; i < n; ++i) {
        orden[i] = i;
    }
    cantidad_colores_usados = Greedy(g, orden, coloreo);
    printf("Cantidad de colores que usa Greedy en ON: %u\n", cantidad_colores_usados);

    // crea orden Welsh-Powell
    for (u32 i = 0 ; i < n; ++i) {
        key[i]=Grado(i,g);
    }
    error = OrdenFromKey(n, key, orden);
    cantidad_colores_usados = Greedy(g, orden, coloreo);
    printf("Cantidad de colores que usa Greedy en Welsh-Powell: %u\n", cantidad_colores_usados);

    for(int i = 0; i < alpha; ++i) {
        srand(rho);
        R = rand();
        rho = R;
        AleatorizarKeys(n, R,key);
        error = OrdenFromKey(n, key, orden);
        error = error;
        cantidad_colores_usados = Greedy(g, orden, coloreo);
        printf("Cantidad de colores que usa Greedy en reordenamiento %u: %u\n",i+3, cantidad_colores_usados);
    }



    u32 colores_usados = Greedy(g, orden, coloreo);
    for (u32 i= 0; i < n; i++) {
        printf("coloreo de greedy[%u]: %u\n",i,coloreo[i]);
    }

    AleatorizarKeys(n, 457568,key);
    for (u32 i= 0; i < n; i++) {
        printf("key[%u]: %u\n",i,key[i]);
    }

    char h = OrdenFromKey(n,key,orden);
    h = h;
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