La complejidad computacional de este reto es exagerado.
La parte que lo hace difícil es esta parte del input
```text
seeds: 4106085912 135215567 529248892 159537194 1281459911 114322341 1857095529 814584370 2999858074 50388481 3362084117 37744902 3471634344 240133599 3737494864 346615684 1585884643 142273098 917169654 286257440
```
En la primera parte, esta línea se interpreta como que cada número es una semilla, no representa
mayor problema.

En la segunda parte cambia la cosa, acá se interpreta como que en la lista se tratan de pares.
El primer número es la semilla y el segundo es el rango.
```text 
The values on the initial seeds: line come in pairs. Within each pair, the first value 
is the start of the range and the second value is the length of the range. So, in the 
first line of the example above:

seeds: 79 14 55 13

This line describes two ranges of seed numbers to be planted in the garden. 
The first range starts with seed number 79 and contains 14 values: 
79, 80, ..., 91, 92. 
The second range starts with seed number 55 and contains 13 values: 
55, 56, ..., 66, 67.
```
Si el input fuera "20 5" significa que las semillas serían "20 21 22 23 24". Al leer el
input es rápido hacer el cálculo que la cantidad de semillas a procesar pasa de 20 a 
casi **dos mil millones de semillas**