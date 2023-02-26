# Coloreo de Grafos

## Qué realiza el programa
Apartir de un grafo y 3 valores enteros de α, β, ρ dados:
- Imprime el número de vértices, el número de lados y Delta.
- Determina si el grafo es Bipartito o no. Si lo es y tiene menos de 101
vértices, imprime las dos partes del grafo.
- Imprime la cantidad de colores que usa Greedy en Orden Natural.
- Imprime la cantidad de colores que usa Greedy en Welsh-Powell.
- Se realizarán (3β+1)(α+2) reórdenes a partir de la fuente
“inicial” de aleatoriedad ρ.
- Se imprimirá por pantalla el mejor coloreo obtenido.
- Se imprimirá una permutación del mejor coloreo obtenido por Greedy.
- Se imprimirá un recoloreo en base a la cardinalidad decreciente de los
bloques de colores.

## Compilación y Ejecutable

```shell
$ git clone https://github.com/angelescch/coloreo-de-grafos.git
$ cd coloreo-de-grafos
$ gcc -Wall -Werror -Wextra -pedantic -std=c99 -c FuncionesColoreo.c
AlmacenamientoGrafo.c queue.c
$ gcc -Wall -Werror -Wextra -pedantic -std=c99 AlmacenamientoGrafo.o queue.o
FuncionesColoreo.o -o coloreo main.c
$ ./coloreo alpha beta rho < path_al_archivo
```
donde path_al_archivo será la ruta al archivo que contiene el grafo siguiendo
el formato válido especificado a continuación. alpha, beta y rho serán los
valores que tomen las variables α, β, ρ ya que estas determinan la cantidad de
reordenamientos que se van a realizar.

Con los grafos provistos en la carpeta grafos-de-ejemplo, podemos hacer:
```shell
$ ./coloreo 23 56 5 < grafos-de-ejemplo/q10.corr.txt > resultados
```
Y en el archivo ```resultados``` que acabamos de generar podremos ver todo lo
que se imprimió.

## Formato Válido de Entrada para grafos
El formato de entrada será una variación de DIMACS, que es un formato
estandard para representar grafos, con algunos cambios.
- Las lineas pueden tener una cantidad arbitraria de caracteres.
- Al principio habrá cero o más lineas que empiezan con c las cuales son
lineas de comentario y son ignoradas.
- Los enteros están limitados a 32 bits sin signo.
- Luego hay una linea de la forma: p edge n m. Donde n y m son dos enteros.
Luego de m, y entre n y m, puede haber una cantidad arbitraria de espacios en
blancos. El primero número (n) representa el número de vértices y el segundo
(m) el número de lados.
- Luego siguen m lineas todas comenzando con e y dos enteros, representando un
lado. Es decir, lineas de la forma: e v w (luego de “w” y entre “v” y “w” puede
haber una cantidad arbitraria de espacios en blanco).
- No se puede fijar m = 0, es decir, siempre habrá al menos un lado. (y por lo
tanto, al menos dos vértices).
- Luego de esas m líneas puede haber una cantidad arbitraria de líneas de
cualquier formato las cuales son ignoradas.
- Que un grafo tenga el vértice v no implicará que el grafo tenga el vértice
v' con v' < v. Por ejemplo, los vértices pueden ser solo cinco, y ser 0, 1, 10,
15768, 1000000.
- Si aparece el lado e v w NO puede aparecer el lado e w v.
- El orden de los lados es indistinto en las líneas e.
- Si no se respeta el formato válido de entrada se detiene la carga y se
devuelve un puntero a ```NULL```.

## Tipos de Datos

### GrafoSt
Es una estructura, la cual contendrá con la información necesaria sobre el
grafo.
- El número de vértices.
- El número de lados.
- Los nombres y grados de todos los vertices.
- El Delta del grafo (el mayor grado).
- Quienes son los vecinos de cada vértice.
Los grafos que se carguen serán no dirigidos.

### Grafo
Es un puntero a una estructura de datos GrafoSt.

## Funciones de Construcción y Destrucción del grafo
```c
Grafo ConstruccionDelGrafo();
```
Lee un grafo desde **standard input** en el formato indicado anteriormente.
En caso de error, la función devolverá un puntero a ```NULL```. Esta función
tiene una complejidad de O(mlog(m)).

```c
void DestruccionDelGrafo(Grafo G);
```
Destruye G y libera la memoria alocada. Complejidad O(m).

## Funciones para extraer información del grafo
Las funciones detalladas en esta sección son todas todas O(1).

```c
u32 NumeroDeVertices(Grafo G);
```
Devuelve el número de vértices de G.

```c
u32 NumeroDeLados(Grafo G);
```
Devuelve el número de lados de G.

```c
u32 Delta(Grafo G);
```
Devuelve ∆(G), es decir, el mayor grado.

```c
u32 Nombre(u32 i,Grafo G);
```
Devuelve el nombre del vértice cuyo índice es i en el Orden Natural.
El nombre es el nombre del vértice con el que figuraba en los datos de entrada.
Pej, si los vértices son 174391,15,7,4,45,1,95980, entonces el orden natural
es: 1,4,7,15,45,95980,174391. Entonces: Nombre(6,G)=174391, Nombre(2,G)=7, etc.

Dado que el nombre de un vértice puede ser cualquier entero sin signo de 32
bits, esta función no tiene forma de reportar un error (que se produciría si se
la llama cuando i es mayor o igual que el número de vértices), asi que debe ser
usada con cuidado.

```c
u32 Grado(u32 i,Grafo G);
```
Devuelve el grado del vértice cuyo índice es i en el Orden Natural.
Si i es mayor o igual que el número de vértices, devuelve 2^32−1. (esto nunca
puede ser un grado, pues para que eso fuese un grado de algún vértice, el grafo
debería tener al menos 2^32 vértices, lo cual lo haría inmanejable).

```c
u32 IndiceONVecino(u32 j,u32 k,Grafo G);
```
Es la función que devuelve el índice en el Orden Natural de un vecino de un
vértice si j, k estan en los rangos adecuados, y 2^32−1 si no.

Si k es menor que el número de vértices y j es menor que el grado del vértice
cuyo índice es k en el Orden Natural entonces
```IndiceONVecino(j,k,Grafo G)``` es igual a i si y solo si el vecino j-ésimo
del vértice cuyo índice es k en el Orden Natural es el vértice cuyo índice es i
en el Orden Natural.

Si k es mayor o igual que el número de vértices o k es menor que el número de
vértices pero j es mayor o igual que el grado del vértice cuyo índice es k en
el Orden Natural entonces la función devuelve 2^32−1.

## Funciones de Coloreo

```c
u32* Bipartito(Grafo G);
```
Si χ(G) ≤ 2, (y como todos los grafos aceptados tienen al menos un lado,
χ(G) ≤ 2 es equivalente a χ(G) = 2) devuelve un puntero a un array de u32s que
tiene longitud n = número de vértices de G, y es un coloreo propio de G con los
colores 1 y 2, con la entrada i del array diciendo que color tiene el vértice
cuyo índice es i en el Orden Natural. Si χ(G) ≥3, devuelve un puntero a
```NULL.```

```c
u32 Greedy(Grafo G,u32* Orden,u32* Coloreo);
```
Corre greedy en G **comenzando con el color 0**, iterando sobre los vértices
siguiendo el orden dado en el array apuntado por ```Orden```, asumiendo que
```Orden[i]=k``` significa que el vértice cuyo índice es k en el Orden Natural
será el vértice procesado en Greedy en el lugar i. En otras palabras, Greedy
procesará los vértices en el orden de sus índices dado por
```Orden[0],Orden[1],Orden[2],``` etc.

Esta función asume que ```Orden``` es un array de n elementos que provee un
orden de los vértices, es decir, es una biyección. Tambien asume que
```Coloreo``` apunta a un sector de memoria con al menos n lugares disponibles.
La función escribe en el lugar i de ```Coloreo[]``` cual es el color que Greedy
le asigna al vértice cuyo índice es i en el Orden Natural. Retorna el número de
colores que usa Greedy, salvo que haya algún error, en cuyo caso retorna
2^32−1.

## Función para crear un orden a partir de claves
Esta función genera los ordenes que luego usará Greedy. Genera un orden a
partir de una clave, de esta forma, para conseguir diferentes ordenes, solo
debemos cambiar de clave.

```c
char OrdenFromKey(u32 n,u32* key,u32* Orden);
```
A partir del array apuntado por ```key```, el cual se asume que es de longitud
n, se llena el array al cual apunta ```Orden```, el cual se asume que tiene
suficiente memoria para al menos n entradas. También se asume que el rango de
```key``` es n o menor, es decir ```key[i]≤n``` para todo i. Lo que NO se
asume, y de hecho casi nunca será cierto, es que key sea una biyección.

Debe llenar ```Orden``` de forma tal que en el lugar 0 vaya el índice
i<sub>0</sub> tal que key[i<sub>0</sub>] sea el máximo de todos los valores
```key[i]``` (si hay varios i's que dan el máximo, se toma cualquiera), luego
en el lugar 1 va el índice i<sub>1</sub> != i<sub>0</sub> tal que
key[i<sub>1</sub>] sea el máximo de todos los valores ```key[i]``` excepto por
i<sub>0</sub>, etc.

Es decir, da un orden de los índices tal que ```Orden[i] != Orden[j]```
si i != j y tal que:
```key[Orden[0]]≥key[Orden[1]]≥key[Orden[2]]≥....≥ key[Orden[n-1]]```.

Esencialmente lo que hace es ordenar las claves de MAYOR a MENOR y su
complejidad es O(nlog(n)).

## Funciones para crear claves específicas
La primera crea claves aleatorias. Las otra dos en realidad crean un recoloreo
de los vértices, y la idea es luego pasarle ese recoloreo como clave a la
función ```OrdenFromKey```, para usar la propiedad VIT:

Sea G = (V , E) un grafo cuyos vértices estan coloreados con un coloreo propio
c con r colores {0, 1, ..., r − 1}.
Sea π una permutación de los números 0, 1, ..., r − 1, es decir,
π : {0, 1, ..., r − 1} → {0, 1, ..., r − 1} es una biyección.
Sea V<sub>i</sub> = {x ∈ V : c(x) = i}, i = 0, 1, ..., r − 1.
Ordenemos los vértices poniendo primero los vértices de V<sub>π(0)</sub> ,
luego los de V<sub>π(1)</sub> ,etc, hasta V<sub>π(r −1)</sub>.
(el orden interno de los vértices dentro de cada V<sub>π(i)</sub> es
irrelevante) Entonces Greedy en ese orden coloreará G con r colores o menos.

```c
void AleatorizarKeys(u32 n,u32 R,u32* key);
```
Usando como semilla de pseudoaleatoridad al número ```R```, “aleatoriza” las
entradas de ```key```. El array al cual apunta ```key``` se asume que tiene al
menos n entradas disponibles.

Es decir, en ```key[i]``` introduce un número “aleatorio” entre 0 y n −1.
La entrada obviamente no será verdaderamente aleatoria sino “pseudoaleatorio”,
dependiendo determinísticamente de la variable ```R```. Es decir, correr dos
veces esta función con R=4 pej, debe dar los mismos resultados, pero si R=12,
debe dar otro resultado, el cual debería ser sustancialmente distinto del
anterior.

Al ser cada entrada pseudoaleatoria, el array al cual apunta key no
necesariamente será una permutación de {0,1,...,n−1} (de hecho, casi nunca lo
será). Esto no es problema pues la función ```OrdenFromKey``` detallada arriba
luego usa este array y crea un orden.

```c
u32* PermutarColores(u32 n,u32* Coloreo,u32 R);
```
La función asume que ```Coloreo``` apunta a una región de memoria con al menos
n lugares. También asume que las entradas de ```Coloreo``` son números
compatibles con un coloreo de Greedy, es decir, para algún r > 0, aparecen r
colores y esos colores son números entre 0 y r−1.

Esta función lo que hace es permutar los colores: Aloca memoria para un array
de n lugares, y devuelve un puntero a ese array. Si hay algún error de
alocación, devuelve ```NULL```.

Las entradas de ese array son las mismas que las de ```Coloreo``` excepto que
se les cambia el nombre a los colores. Los nuevos nombres siguen siendo
0,1,...,r−1, pero si antes se tenía pej ```Coloreo[i]=4```, y denotamos por
ColoreoNuevo al array que hay que devolver, ahora puede ser pej
ColoreoNuevo[i]=7, y en ese caso no solo i sino todos los j tal que
Coloreo[j]=4 van a tener ahora ColoreoNuevo[j]=7. Por otro lado los indices k
tal que Coloreo[k]=7 ahora tendran otro color, pej ColoreoNuevo[k]=1 etc.
El reasignamiento de colores es pseudoaleatorio dependiendo de la semilla de
aleatoriedad ```R```.


```c
u32* RecoloreoCardinalidadDecrecienteBC(u32 n,u32* Coloreo);
```
(Cardinalidad Decreciente de los Bloques de Colores)

La función asume que ```Coloreo``` apuntan a una región de memoria con al menos
n lugares. También asume que las entradas de ```Coloreo``` son números
compatibles con un coloreo que empieza en 0, es decir, números entre 0 y algún
número r −1, y que todos los números 0,1,...,r −1 aparecen al menos una vez en
el rango de ```Coloreo```.

Esta función aloca memoria para un array de n lugares, y devuelve un puntero a
ese array. Si hay algún error de alocación, devuelve ```NULL```.

Especificación de lo que hace esta función:
Si Coloreo tiene r colores 0,1,..,r −1 definimos para cada color c:

IC<sub>c</sub> = conjunto de índices i tal que ```Coloreo[i]=c```.
Ordenar los colores en la forma c<sub>0</sub>,c<sub>1</sub>,...,c<sub>r−1</sub>
tales que |IC<sub>c<sub>0</sub></sub>|≥|IC<sub>c<sub>1</sub></sub>|≥
|IC<sub>c<sub>2</sub></sub>|≥... ≥|IC<sub>c<sub>r-1</sub></sub>|.
Renombra el color c<sub>k</sub> con el color k.
(es decir, si el array creado se llama pej NuevoColoreo, entonces Coloreo[i]=
c<sub>k</sub> ⇒ NuevoColoreo[i]= k).
