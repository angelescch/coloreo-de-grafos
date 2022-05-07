#ifndef __API_H
#define __API_H


#include "AniquilamientoPositronicoIonizanteGravitatorio.h"

//coloreantes

// Retorna NULL si Chi(G)>2
// Retorna un arreglo a de u32 si Chi(G)==2, donde para cada i,
// con 0<=i<=n, n cantidad de vertices, a[i] es el color del vertice
// cuyo indice es i en el orden natural. 
u32* Bipartito(Grafo  G);

u32 Greedy(Grafo G,u32* Orden,u32* Coloreo);

//ordenamiento a partir de clave

char OrdenFromKey(u32 n,u32* key,u32* Orden);

// //claves aleatorias

void AleatorizarKeys(u32 n,u32 R,u32* key);


//permutadores de colores
u32* PermutarColores(u32 n,u32* Coloreo,u32 R);

// u32* RecoloreoCardinalidadDecrecienteBC(u32 n,u32* Coloreo);




#endif

