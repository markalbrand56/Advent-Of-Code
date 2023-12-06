# PD
Sin este cambio en la parte 2
```c
char *current_line = strdup(lines[i]);
```
El programa no funciona, ya que strtok intenta volver a empezar a leer el string, pero en la siguiente
iteración del bucle en H strtok intenta seguir leyendo la misma línea y no encuentra nada, por lo que
devuelve NULL y el programa termina antes de tiempo.

```c
char *current_line = strdup(lines[i]);
char *tkn = strtok(current_line, ":");
tkn = strtok(NULL, ":");
char *nums = strtok(tkn, " ");
```