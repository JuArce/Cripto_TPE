# Criptografía y Seguridad
# Trabajo Práctico: Esteganografía

## Autores

- [Arce, Julián Francisco](https://github.com/juarce)
- [Conca, María Victoria](https://github.com/Mickyconca)
- [Domingues, Paula Andrea](https://github.com/pdomins)

## Objetivos

Introducirse en el campo de la esteganografía y sus aplicaciones.

Experimentar con métodos de ocultamiento de información en archivos bmp, analizando ventajas y desventajas de cada uno.


## Compilación

La compilación se realiza con el siguiente comando:

```bash
make all
```

## Ejecución

En el mismo directorio, luego de la compilación, se encuentra el archivo ejecutable:

* `stegobmp`

Para ejecutar el mismo:
```bash
./stegobmp -MODE [-in filename] -p filename -out filename -steg <LSB1|LSB4|LSBI> [-a <aes128|aes192|aes256|des>] [-m <ecb|cfb|ofb|cbc>] [-pass password] [-help] 
```
Los modos disponibles son los siguientes:
| Modos |  Descripcion | 
|----| ------------------ |
| -embed    | Indica que se va a ocultar información. |
| -extract  | Indica que se va a extrar información. |

Los parámetros admitidos por el programa son los siguientes:
| Comandos |  Descripcion | 
|----| ------------------ |
| -in filename                      | Archivo que se va a ocultar. |
| -p filename                       | Archivo bmp que será el portador. |
| -out filename                     | Archivo de salida obtenido. |
| -steg <LSB1\|LSB4\|LSBI>          | Algoritmo de esteganografiado: LSB de 1 bit, LSB de 4 bits, LSB Improved. |
| -a <aes128\|aes192\|aes256\|des>  | Algoritmo de encripción: aes128, aes192, aes256, des. Se asume aes128 por default. |
| -m <ecb\|cfb\|ofb\|cbc>           | Modo de encripción: ecb, cfb, ofb, cbc. Se asume CBC por default. |
| -pass password                    | Contraseña de encripción. Si no se pasa este parámetro sólo se esteganografía. |
| -help                             | Imprime el manual de uso del programa. |

## Limpieza

La limpieza de los archivos generados se realiza con el siguiente comando:

```bash
make clean
```

## Documentación
En la carpeta docs se encuentran el enunciado, las cuestiones a analizar y el informe realizado.
