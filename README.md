# TY (ty-compiler)

Este es un compiler experimental el cual compila un lenguaje de programacion con sintaxis en español. 
La idea de ty-compiler es que es un compilador diseñado para que cualquier persona hispanohablante pueda programar sin necesidad de aprender inglés primero.

---

El compiler esta escrito en C++, no es self-hosted.

## Sintaxis

Se puede observar en los testcases la idea de la sintaxis pero de forma simple es mutar:

if <-> si
elif <-> ysi
else <-> sino
while <-> mientras
(...)
y otras mas..


## Dependencias

x86-64 Linux, ld, gcc y NASM.

## Construccion

```
g++ -std=c++17 main.cpp -o ./ty

./ty ./ARCHIVO_A_COMPILAR
```

Luego para utilizarlo utilizar el ejecutable con la file a compilar, eso creará una file en assembly la cual luego debes usar NASM y ld.

```
nasm -f elf64 assembly.asm -o asm.o && ld asm.o -o ./NOMBRE_DEL_EJECUTABLE
```

## Aca podes ver como se creo

Video en youtube: [Creando un Compiler con sintaxis en Español #1.](https://www.youtube.com/watch?v=xDJL41mVM8k)
