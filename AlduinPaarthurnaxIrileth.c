#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "AlduinPaarthurnaxIrileth.h"

// Retorna el minimo color disponible para colorear el vertice i en {1,2}, tal que el
// coloreo es propio. Retorna NULL si no hay color disponible en {1,2}. 
static u32* get_color(u32 i,Grafo G, u32* colores) {
    u32 grad_i = Grado(i, G);
    u32* res = NULL;
    const u32 c1 = 1u;
    const u32 c2 = 2u;
    bool c1_disp = true;
    bool c2_disp = true;

    u32 k = 0u;
    while (k < grad_i && (c1_disp || c2_disp)) {
        u32 vec_index = IndiceONVecino(k,i,G);
        u32 IONerr = (u32)(pow(2,32)-1);
        // si IndiceONVecino no dio error...
        if (vec_index != IONerr) {
            u32 c_vec = colores[vec_index];
            c1_disp = c1_disp && (c_vec!=c1);
            c2_disp = c2_disp && (c_vec!=c2);
        }
        else {
            printf("Error en IndiceONVecino.");
            break;
        }
        ++k;
    }
    // devuelve el c1 si esta disponible, sino el c2 si esta disponible...
    if (c1_disp) {
        res = malloc(sizeof(u32));
        *res = c1;
    }
    else if (c2_disp) {
        res = malloc(sizeof(u32));
        *res = c2;
    }

    return res;
}

u32* Bipartito(Grafo  G) {
    u32 n_vert = NumeroDeVertices(G);
    bool es_bipartito = true;
    u32* colores = calloc(n_vert, sizeof(u32));
    u32* col = NULL;
    
    u32 i = 0u;
    while (es_bipartito && i < n_vert) {
        col = get_color(i,G,colores);
        if (col != NULL) {
            colores[i] = *col;
        }
        else {
            es_bipartito = false;
            free(colores);
            colores = NULL;
        }
        ++i;
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