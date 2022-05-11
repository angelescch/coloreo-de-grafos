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

    Coloreo[Orden[0]] = 0u;

    for (unsigned int u = 1u; u < n; ++u) {
        Coloreo[Orden[u]] = UINT32_MAX;
    }

    bool * available = calloc(n,sizeof(bool));
    for (unsigned int cr = 0u; cr < n; ++cr) {
        available[cr] = true;
    }

    for (unsigned int i = 1u; i < n; ++i) {
        u32 index_i = Orden[i];

        u32 grado_i = Grado(index_i,G);
        for (u32 j = 0u; j < grado_i; ++j) {
            if (Coloreo[IndiceONVecino(j,index_i,G)]!=UINT32_MAX) {
                available[Coloreo[IndiceONVecino(j,index_i,G)]] = false;
            }
        }

        unsigned int cr=0u;
        while (cr < n) {
            if (available[cr])
                break;
            ++cr;
        }

        Coloreo[index_i] = cr;

        if (cr+1u > cant_colores)
            ++cant_colores;

        for (u32 j = 0u; j < grado_i; ++j) {
            if (Coloreo[IndiceONVecino(j,index_i,G)]!=UINT32_MAX) {
                available[Coloreo[IndiceONVecino(j,index_i,G)]] = true;
            }
        }
    }
    free(available);
    available = NULL;

    return cant_colores;
}


//ordenamiento a partir de clave

char OrdenFromKey(u32 n,u32* key,u32* Orden) {
    tupla value_index = calloc(n, sizeof(struct tupla_s));
    if (value_index == NULL)
        return '1';
    for(u32 i = 0u; i < n; ++i) {
        value_index[i].v1 = key[i];
        value_index[i].v2 = i;
    }
    qsort((void*)value_index, n, sizeof(struct tupla_s), sort_tuple);
    u32 i = n-1u;
    u32 j = 0u;
    while(j < n) {
        Orden[j] = value_index[i].v2;
        ++j;
        --i;
    }
    free(value_index);
    value_index = NULL;
    return '0';
}

//claves aleatorias

void AleatorizarKeys(u32 n,u32 R,u32* key) {
    for (u32 i=0u; i < n ;++i) {
        srand(R+i);
        u32 random = rand();
        key[i] = random % n;
    }
}


//permutadores de colores
u32* PermutarColores(u32 n,u32* Coloreo,u32 R) {
    u32* ColoreoNuevo = calloc(n, sizeof(u32));

    if (ColoreoNuevo != NULL) {
        u32 r = 0u;
        for(u32 i = 0u; i < n; ++i) {
            if (Coloreo[i] > r) {
                r = Coloreo[i];
            }
        }
        ++r;
        u32* PermC = calloc(r, sizeof(u32));
        if (PermC == NULL) return NULL;
        srand(R);
        u32 random = rand();
        for (u32 i = 0u ; i < r ; ++i) {
            PermC[i] = (random+i) % r;
        }
        for (u32 i = 0u ; i<n ; ++i) {
            ColoreoNuevo[i] = PermC[Coloreo[i]];
        }
        free(PermC);
    }

    return ColoreoNuevo;
}



u32* RecoloreoCardinalidadDecrecienteBC(u32 n,u32* Coloreo) {
    u32* NuevoColoreo = calloc(n,sizeof(u32));
    tupla ConteoColores = calloc(n,sizeof(struct tupla_s));


    if (NuevoColoreo!=NULL && ConteoColores!=NULL) {
        // contar iterando una vez los colores: ConteoColoreo[Coloreo[i]] = cantidad de veces que se repite el color Coloreo[i]
        for (u32 i = 0; i < n; ++i) {
            ++ConteoColores[Coloreo[i]].v1;
            ConteoColores[Coloreo[i]].v2 = Coloreo[i];
        }

        qsort((void*)ConteoColores, n, sizeof(struct tupla_s), sort_tuple);

        u32 r = 0u;      // cuenta colores
        for (u32 i = 0; i < n; ++i) {
            if (ConteoColores[Coloreo[i]].v1 == 0)
                break;
            ++r;
        }

        u32* CambiarColor = calloc(r,sizeof(u32));
        if (CambiarColor == NULL) return NULL;

        u32 i = r-1u;
        u32 j = 0u;
        while(j < r) {
            CambiarColor[ConteoColores[i].v2] = j;
            ++j;
            --i;
        }

        for (u32 i = 0; i < n; ++i) {
            NuevoColoreo[i] = CambiarColor[Coloreo[i]];
        }


    } else {
        NuevoColoreo = NULL;
    }

    return NuevoColoreo;
}