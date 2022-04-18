#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "AlduinPaarthurnaxIrileth.h"

u32* Bipartito(Grafo  G) {
    u32 n = NumeroDeVertices(G);
    bool es_bipartito = true;
    // colors[i] = devuelve el color del vertice cuyo indice es i
    u32* colors = calloc(n, sizeof(u32));

    // asignar color 1 al primer vertice
    // asignar el color 2 a sus vecinos (se conserva que sea propio)
    
    // iterar sobre los vertices siguientes
        // si alguno de sus vecinos tienen un color
            // if ("sus vecinos ocupan a lo sumo un color")
                // se le asigna el color opuesto y se seguira con otro vertice
            // else ("sus vecinos hacen uso de 2 colores")
                // es_bipartito = false
                // break

    if (!es_bipartito) {
        free(colors);
    }

    return colors;
}

u32 Greedy(Grafo G,u32* Orden,u32* Coloreo) {

}

//ordenamiento a partir de clave

char OrdenFromKey(u32 n,u32* key,u32* Orden) {

}

//claves aleatorias

void AleatorizarKeys(u32 n,u32 R,u32* key) {

}


//permutadores de colores
u32* PermutarColores(u32 n,u32* Coloreo,u32 R) {

}

u32* RecoloreoCardinalidadDecrecienteBC(u32 n,u32* Coloreo) {

}