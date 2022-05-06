#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

#include "AlduinPaarthurnaxIrileth.h"
#include "Stack.h"

u32* Bipartito(Grafo  G) {
    u32 n = NumeroDeVertices(G);
    u32 * colores = calloc(n, sizeof(u32));
    stack vertex_stack = stack_empty();
    colores[0u] = 1u;
    u32 grado_0 = Grado(0u,G);

    for (u32 j=0u; j < grado_0;++j) {
        vertex_stack = stack_push(vertex_stack, IndiceONVecino(j,0u,G));
    }

    while (!stack_is_empty(vertex_stack)) {
        bool posible_1 = true;
        bool posible_2 = true;
        u32 i = stack_top(vertex_stack);
        vertex_stack = stack_pop(vertex_stack);

        for (u32 j=0u; j < Grado(i,G) ;++j) {
            if (colores[IndiceONVecino(j,i,G)]==1u) {
                posible_1 = false; 
            } else if (colores[IndiceONVecino(j,i,G)]==2u) {
                posible_2 = false;
            } else if (colores[IndiceONVecino(j,i,G)]==0u) {
                vertex_stack = stack_push(vertex_stack, IndiceONVecino(j,i,G));
            }
        }

        if (posible_1) {
            colores[i] = 1u;
        } else if (posible_2) {
            colores[i] = 2u;
        } else {
            free(colores);
            colores = NULL;
            break;
        }
    }

    return colores;
}


u32 Greedy(Grafo G,u32* Orden,u32* Coloreo) {
    u32 n = NumeroDeVertices(G);
    u32 cant_colores = 1u;

    // Assign the first color to first vertex
    Coloreo[Orden[0]] = 0u;

    // Initialize remaining V-1 vertices as unassigned
    for (unsigned int u = 1; u < n; u++)
        Coloreo[Orden[u]] = UINT32_MAX; // no color is assigned to u

    // A temporary array to store the available colors. True
    // value of available[cr] would mean that the color cr is
    // assigned to one of its adjacent vertices
    bool available[n];
    for (unsigned int cr = 0; cr < n; cr++)
        available[cr] = false;


    // Assign colors to remaining V-1 vertices
    for (unsigned int u = 1; u < n; u++) {

        // Process all adjacent vertices and flag their colors
        // as unavailable
        u32 grado_i = Grado(Orden[u],G);
        for(u32 j = 0u; j < grado_i; ++j) {
            if (Coloreo[IndiceONVecino(j,Orden[u],G)]!=UINT32_MAX)
                available[Coloreo[IndiceONVecino(j,Orden[u],G)]] = true;
        }

        // Find the first available color
        unsigned int cr;
        for (cr = 0; cr < n; cr++) {
            if (available[cr] == false)
                break;
        }

        Coloreo[Orden[u]] = cr; // Assign the found color

        if (cr+1 > cant_colores)
            cant_colores = cr+1; // Update how many colors we already use

        // Reset the values back to false for the next iteration
        for(u32 j = 0u; j < grado_i; ++j) {
            if (Coloreo[IndiceONVecino(j,Orden[u],G)]!=UINT32_MAX)
                available[Coloreo[IndiceONVecino(j,Orden[u],G)]] = false;
        }
    }

    return cant_colores;
}

// //ordenamiento a partir de clave

// char OrdenFromKey(u32 n,u32* key,u32* Orden) {

// }

// //claves aleatorias

// void AleatorizarKeys(u32 n,u32 R,u32* key) {

// }


// //permutadores de colores
// u32* PermutarColores(u32 n,u32* Coloreo,u32 R) {

// }

// u32* RecoloreoCardinalidadDecrecienteBC(u32 n,u32* Coloreo) {

// }