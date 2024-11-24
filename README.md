Esto es un generador de datos para el segundo obligatorio de Base de datos 1. Tiene capacidad de generar los datos en formato sql oracle batch inserts o en formato csv, que se pueden cargar con `sqlplus` y los documentos `.ctl` encontrados en `res`. 

El generador es un documento `.c` y un documento `.inl`. El documento `.inl` es donde esta presente la lista de [X macros](https://en.wikipedia.org/wiki/X_macro), que es una tecnica de meta-programacion dentro de c/c++ usada para automatizar la escritura de codigo. 
Por ejemplo, esta tecnica se uso para la definicion de las 'lookup tables' o de los 'enums'.

## Compilacion

Ya que todo el codigo esta dentro de un documento `.c` se puede compilar el programa de manera muy simple. 
Si tiene `gcc` instalado y `make`, puede compilar con:
```
make
```
o: 
```
make build
```

## Correr 

Para correr el programa, puede correrlo con alguno de los siguientes formatos: 

```bash
nombre_de_ejecutable [seed] [sql/csv]
nombre_de_ejecutable [seed] [sql/csv] [max elements]
nombre_de_ejecutable [seed] [sql/csv] [min elements] [max elements]
```

Aca, la `seed` es la seed que se usa para la generacion randomica de datos, la cual debe ser un numero entero positivo. 
Esto permite al usuario generar los mismos datos en dos instancias distintas con los mismos argumentos. 
Tambien permite generar dos conjuntos de datos completamente distintos pero con la misma cantidad de elementos. 

La opcion `sql/csv` permite al usuario definir con que formato quiere recibir los datos. 

En el formato `sql`, se imprime el resultado a `res/inserts.sql`. 

En el formato `csv`, se imprime el resultado a varios documentos segun cada tabla especificada a `res/*.csv`. 
Para insertar los datos en los csv, se puede correr el script `res/run.sh` dentro de un contenedor de docker con la imagen [gvenzl/oracle-xe](https://hub.docker.com/r/gvenzl/oracle-xe), cambiando la `session` del script a la que uno configure dentro de sqlplus. 
Deben de haber otras formas de cargar los datos en csv fuera de esta forma, pero no experimentamos con eso. 

### Por que usar el formato csv?  

Basicamente es extremadamente rapido, por ejemplo cargar el resultado del la siguiente ejecucion: 

```
./crear_estado_tests 101 csv 100000 150000
```

El cual devolvio aproximadamente 740.000 datos para insertar, demoro aproximadamente 30 segundos (incluyendo el tiempo para correr el ddl.sql y typear `exit` para salir de sqlplus): 

```bash
real    0m26.245s
user    0m0.823s
sys     0m0.268s
```

Por el otro lado, los inserts los tuve que parar a los 10 minutos ya que no se lograron insertar los primeros 100.000 datos en ese tiempo. 
