/*
  Módulo de definición de `Cola'.

  `Cola' es una estructura lineal con comportamiento FIFO cuyos
   elementos son de tipo `nat'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#ifndef _COLA_H
#define _COLA_H

#include "utils.h"

struct rep_cola; // representación de `Cola', definida en `cola.cpp'.
typedef rep_cola *Cola;

/*  
   Devuelve una cola vacía (sin elementos).
   Ejecuta en O(1).
*/
Cola crear_cola();

/* 
   Encola `elem' en `c'.
   Ejecuta en O(1).
*/
void encolar(nat elem, Cola &c);

/*
   Remueve de `c' el elemento que está en el frente.
   Si es_vacia_cola(c) no hace nada. 
   Ejecuta en O(1).
*/
void desencolar(Cola &c);

/* 
   Devuelve `true' si y sólo si `c' es vacía (no tiene elementos). 
   Ejecuta en O(1).
*/
bool es_vacia_cola(Cola c);

/* 
   Devuelve el elemento que está en el frente de `c'.
   Precondición: ! es_vacia_cola(c). 
   Ejecuta en O(1).
*/
nat frente(Cola c);

/*  
   Libera la memoria asignada a `c'.
   Ejecuta en O(n) (siendo n el largo de la cola).
*/
void destruir_cola(Cola &c);

#endif
