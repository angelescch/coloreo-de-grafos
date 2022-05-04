#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "AlduinPaarthurnaxIrileth.h"
#include "stack.h"

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


// u32 Greedy(Grafo G,u32* Orden,u32* Coloreo) {

// }

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