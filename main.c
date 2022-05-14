//gcc -Wall -Werror -Wextra -pedantic -std=c99 -c AlduinPaarthurnaxIrileth.c AniquilamientoPositronicoIonizanteGravitatorio.c Stack.c
//gcc -Wall -Werror -Wextra -pedantic -std=c99 AniquilamientoPositronicoIonizanteGravitatorio.o Stack.o AlduinPaarthurnaxIrileth.o -o test main.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <inttypes.h>
#include "AlduinPaarthurnaxIrileth.h"
#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

static void ActualizarMejorColoreo(u32 n, u32* mejor_coloreo_array, u32* coloreo) {
    for (u32 i=0u; i < n ; ++i) {
        mejor_coloreo_array[i] = coloreo[i];
    }
}

// static bool isProperColoring(Grafo G, u32* coloreo) {
//     bool is_proper = true;
//     u32 n = NumeroDeVertices(G);
//     for(u32 i = 0u; i < n && is_proper; ++i) {
//         for(u32 j=0u; j < Grado(i, G) && is_proper; ++j) {
//             if (coloreo[i]==coloreo[IndiceONVecino(j,i,G)]) is_proper = false;
//         }
//     }
//     return is_proper;
// }

int main(int argc, char* argv[]){
    argc = argc;
    u32 cantidad_colores_usados, R, cantidad_greedys=0u,  menor_coloreo=UINT32_MAX, cantidad_colores_usados_anteriormente;
    u32* key_permutacion_coloreo;
    char error;
    int alpha = atoi(argv[1]), beta = atoi(argv[2]), rho = atoi(argv[3]);
    beta = beta;
    Grafo g = ConstruccionDelGrafo();

    u32 n = NumeroDeVertices(g);
    u32 m = NumeroDeLados(g);
    u32 d = Delta(g);

    printf("Número de vértices: %u, Número de lados: %u, Delta del grafo: %u\n", n, m, d);

    // Bipartito.
    u32* colorcitos = Bipartito(g);
    if(colorcitos!=NULL){
        printf("El grafo es bipartito\n");
        if (n < 101) {
            printf("\n\nListado de vértices de la Primera Parte:\n");
            printf("[");
            for (u32 i; i<n ;++i) {
                if (colorcitos[i]==1) {
                    printf("%u ,", Nombre(i,g));
                }
            }
            printf("]\n\n");

            printf("\n\nListado de vértices de la Segunda Parte:\n");
            printf("[");
            for (u32 i; i<n ;++i) {
                if (colorcitos[i]==2) {
                    printf("%u ,", Nombre(i,g));
                }
            }
            printf("]\n\n");
        }
    } else {
        printf("\nEl grafo no es bipartito\n");
    }
    // bool b = isProperColoring(g, colorcitos);
    // printf("es propio?: %d", b);
    free(colorcitos);




    // inicializacion y alocación de arreglos.
    u32 * key = calloc(n, sizeof(u32));
    u32 * orden = calloc(n, sizeof(u32));
    u32 * coloreo = calloc(n, sizeof(u32));
    u32 * mejor_coloreo_array = calloc(n, sizeof(u32));

    // Semilla Inicial.
    srand(rho);

    // crea orden natural.
    R = rand();
    for (u32 i = 0 ; i < n; ++i) {
        orden[i] = i;
    }
    cantidad_colores_usados = Greedy(g, orden, coloreo);
    ++cantidad_greedys;
    if (cantidad_colores_usados<menor_coloreo) {
        menor_coloreo = cantidad_colores_usados;
        ActualizarMejorColoreo(n, mejor_coloreo_array, coloreo);
    }
    printf("\n\nCantidad de colores que usa Greedy en ON: %u\n", cantidad_colores_usados);
    for (int j = 0; j < beta; ++j) {
        cantidad_colores_usados_anteriormente = cantidad_colores_usados;
        error = OrdenFromKey(n, coloreo, orden);
        cantidad_colores_usados = Greedy(g, orden, coloreo);
        ++cantidad_greedys;
        if (cantidad_colores_usados<menor_coloreo) {
            menor_coloreo = cantidad_colores_usados;
            ActualizarMejorColoreo(n, mejor_coloreo_array, coloreo);
        }
        //printf("Cantidad de colores que usa Greedy en ON VIT-iterando %u veces (1): %u\n", j+1, cantidad_colores_usados);
        if (cantidad_colores_usados_anteriormente < cantidad_colores_usados){
            printf("VIT no se cumple D:");
            return EXIT_FAILURE; //ver como vamos a manejar este error, si pasa lloro :( porque no debería pasar pero en esta vida uno nunca sabe
        }
        cantidad_colores_usados_anteriormente = cantidad_colores_usados;
        key_permutacion_coloreo = PermutarColores(n, coloreo, R);
        error = OrdenFromKey(n, key_permutacion_coloreo, orden);
        cantidad_colores_usados = Greedy(g, orden, coloreo);
        ++cantidad_greedys;
        if (cantidad_colores_usados<menor_coloreo) {
            menor_coloreo = cantidad_colores_usados;
            ActualizarMejorColoreo(n, mejor_coloreo_array, coloreo);
        }
        //printf("Cantidad de colores que usa Greedy en ON VIT-iterando %u veces (2): %u\n", j+1, cantidad_colores_usados);
        if (cantidad_colores_usados_anteriormente < cantidad_colores_usados){
            printf("VIT no se cumple D:");
            return EXIT_FAILURE;
        }
        free(key_permutacion_coloreo);
        cantidad_colores_usados_anteriormente = cantidad_colores_usados;
        key_permutacion_coloreo = RecoloreoCardinalidadDecrecienteBC(n, coloreo);
        error = OrdenFromKey(n, key_permutacion_coloreo, orden);
        cantidad_colores_usados = Greedy(g, orden, coloreo);
        ++cantidad_greedys;
        if (cantidad_colores_usados<menor_coloreo) {
            menor_coloreo = cantidad_colores_usados;
            ActualizarMejorColoreo(n, mejor_coloreo_array, coloreo);
        }
        //printf("Cantidad de colores que usa Greedy en ON VIT-iterando %u veces (3): %u\n", j+1, cantidad_colores_usados);
        if (cantidad_colores_usados_anteriormente < cantidad_colores_usados){
            printf("VIT no se cumple D:");
            return EXIT_FAILURE;
        }
        free(key_permutacion_coloreo);
    }




    // crea orden Welsh-Powell
    R = rand();
    for (u32 i = 0 ; i < n; ++i) {
        key[i]=Grado(i,g);
    }
    error = OrdenFromKey(n, key, orden);
    cantidad_colores_usados = Greedy(g, orden, coloreo);
    ++cantidad_greedys;
    if (cantidad_colores_usados<menor_coloreo) {
        menor_coloreo = cantidad_colores_usados;
        ActualizarMejorColoreo(n, mejor_coloreo_array, coloreo);
    }
    printf("\n\nCantidad de colores que usa Greedy en Welsh-Powell: %u\n", cantidad_colores_usados);
    for (int j = 0; j < beta; ++j) {
        cantidad_colores_usados_anteriormente = cantidad_colores_usados;
        error = OrdenFromKey(n, coloreo, orden);
        cantidad_colores_usados = Greedy(g, orden, coloreo);
        ++cantidad_greedys;
        if (cantidad_colores_usados<menor_coloreo) {
            menor_coloreo = cantidad_colores_usados;
            ActualizarMejorColoreo(n, mejor_coloreo_array, coloreo);
        }
        //printf("Cantidad de colores que usa Greedy en Welsh-Powell VIT-iterando %u veces (1): %u\n", j+1, cantidad_colores_usados);
        if (cantidad_colores_usados_anteriormente < cantidad_colores_usados){
            printf("VIT no se cumple D:");
            return EXIT_FAILURE; //ver como vamos a manejar este error, si pasa lloro :( porque no debería pasar pero en esta vida uno nunca sabe
        }
        cantidad_colores_usados_anteriormente = cantidad_colores_usados;
        key_permutacion_coloreo = PermutarColores(n, coloreo, R);
        error = OrdenFromKey(n, key_permutacion_coloreo, orden);
        cantidad_colores_usados = Greedy(g, orden, coloreo);
        ++cantidad_greedys;
        if (cantidad_colores_usados<menor_coloreo) {
            menor_coloreo = cantidad_colores_usados;
            ActualizarMejorColoreo(n, mejor_coloreo_array, coloreo);
        }
        //printf("Cantidad de colores que usa Greedy en Welsh-Powell VIT-iterando %u veces (2): %u\n", j+1, cantidad_colores_usados);
        if (cantidad_colores_usados_anteriormente < cantidad_colores_usados){
            printf("VIT no se cumple D:");
            return EXIT_FAILURE;
        }
        free(key_permutacion_coloreo);
        cantidad_colores_usados_anteriormente = cantidad_colores_usados;
        key_permutacion_coloreo = RecoloreoCardinalidadDecrecienteBC(n, coloreo);
        error = OrdenFromKey(n, key_permutacion_coloreo, orden);
        cantidad_colores_usados = Greedy(g, orden, coloreo);
        ++cantidad_greedys;
        if (cantidad_colores_usados<menor_coloreo) {
            menor_coloreo = cantidad_colores_usados;
            ActualizarMejorColoreo(n, mejor_coloreo_array, coloreo);
        }
        //printf("Cantidad de colores que usa Greedy en Welsh-Powell VIT-iterando %u veces (3): %u\n", j+1, cantidad_colores_usados);
        if (cantidad_colores_usados_anteriormente < cantidad_colores_usados){
            printf("VIT no se cumple D:");
            return EXIT_FAILURE;
        }
        free(key_permutacion_coloreo);
    }




    // alpha Greedy's
    for(int i = 0; i < alpha; ++i) {
        R = rand();
        AleatorizarKeys(n, R,key);
        error = OrdenFromKey(n, key, orden);
        error = error;
        cantidad_colores_usados = Greedy(g, orden, coloreo);
        ++cantidad_greedys;
        if (cantidad_colores_usados < menor_coloreo) {
            menor_coloreo = cantidad_colores_usados;
            ActualizarMejorColoreo(n, mejor_coloreo_array, coloreo);
        }
        //printf("\n\nCantidad de colores que usa Greedy en reordenamiento %u: %u\n",i+3, cantidad_colores_usados);
        for (int j = 0; j < beta; ++j) {
            cantidad_colores_usados_anteriormente = cantidad_colores_usados;
            error = OrdenFromKey(n, coloreo, orden);
            cantidad_colores_usados = Greedy(g, orden, coloreo);
            ++cantidad_greedys;
            if (cantidad_colores_usados<menor_coloreo) {
                menor_coloreo = cantidad_colores_usados;
                ActualizarMejorColoreo(n, mejor_coloreo_array, coloreo);
            }
            //printf("Cantidad de colores que usa Greedy en reordenamiento %u VIT-iterando %u veces (1): %u\n", i+3, j+1, cantidad_colores_usados);
            if (cantidad_colores_usados_anteriormente < cantidad_colores_usados){
                printf("VIT no se cumple D:");
                return EXIT_FAILURE; //ver como vamos a manejar este error, si pasa lloro :( porque no debería pasar pero en esta vida uno nunca sabe, muy sad seria...
            }
            cantidad_colores_usados_anteriormente = cantidad_colores_usados;
            key_permutacion_coloreo = PermutarColores(n, coloreo, R);
            error = OrdenFromKey(n, key_permutacion_coloreo, orden);
            cantidad_colores_usados = Greedy(g, orden, coloreo);
            ++cantidad_greedys;
            if (cantidad_colores_usados<menor_coloreo) {
                menor_coloreo = cantidad_colores_usados;
                ActualizarMejorColoreo(n, mejor_coloreo_array, coloreo);
            }
            //printf("Cantidad de colores que usa Greedy en reordenamiento %u VIT-iterando %u veces (2): %u\n", i+3, j+1, cantidad_colores_usados);
            if (cantidad_colores_usados_anteriormente < cantidad_colores_usados){
                printf("VIT no se cumple D:");
                return EXIT_FAILURE;
            }
            free(key_permutacion_coloreo);
            cantidad_colores_usados_anteriormente = cantidad_colores_usados;
            key_permutacion_coloreo = RecoloreoCardinalidadDecrecienteBC(n, coloreo);
            error = OrdenFromKey(n, key_permutacion_coloreo, orden);
            cantidad_colores_usados = Greedy(g, orden, coloreo);
            ++cantidad_greedys;
            if (cantidad_colores_usados<menor_coloreo) {
                menor_coloreo = cantidad_colores_usados;
                ActualizarMejorColoreo(n, mejor_coloreo_array, coloreo);
            }
            //printf("Cantidad de colores que usa Greedy en reordenamiento %u VIT-iterando %u veces (3): %u\n", i+3, j+1, cantidad_colores_usados);
            if (cantidad_colores_usados_anteriormente < cantidad_colores_usados){
                printf("VIT no se cumple D:");
                return EXIT_FAILURE;
            }
            free(key_permutacion_coloreo);
        }
    }




    printf("\n\nMejor cantidad de colores obtenida: %u\n", menor_coloreo);
    printf("Se hicieron en total %u Greedy's\n\n", cantidad_greedys);

    free(key);
    free(orden);
    free(coloreo);
    free(mejor_coloreo_array);

    DestruccionDelGrafo(g);


    // u32 colores_usados = Greedy(g, orden, coloreo);
    // for (u32 i= 0; i < n; i++) {
    //     printf("coloreo de greedy[%u]: %u\n",i,coloreo[i]);
    // }

    // AleatorizarKeys(n, 457568,key);
    // for (u32 i= 0; i < n; i++) {
    //     printf("key[%u]: %u\n",i,key[i]);
    // }

    // char h = OrdenFromKey(n,key,orden);
    // h = h;
    // for (u32 i= 0; i < n; i++) {
    //     printf("orden[%u]: %u\n",i,orden[i]);
    // }
    // u32* coloreonovo = PermutarColores(n,coloreo, 4);
    // for (u32 i= 0; i < n; i++) {
    //     printf("permutado coloreo de greedy[%u]: %u\n",i,coloreonovo[i]);
    // }

    // u32 *RecoloreoCardinal = RecoloreoCardinalidadDecrecienteBC(n, coloreo);
    // for (u32 i= 0; i < n; i++) {
    //     printf("recoloreo de greedy[%u]: %u\n",i,RecoloreoCardinal[i]);
    // }

    // free(key);
    // free(orden);
    // free(coloreo);
    // free(coloreonovo);
    // free(RecoloreoCardinal);
    // DestruccionDelGrafo(g);
    // // clock_t start = clock();
    // u32 colores_usados = Greedy(g, orden, colorcitos);
    // clock_t end = clock();
    // float seconds = (float)(end - start) / CLOCKS_PER_SEC;
    // printf("cantidad de colores que usa Greedy: %u\n", colores_usados);
    // printf("tarda %f\n",seconds);
    return EXIT_SUCCESS;
}