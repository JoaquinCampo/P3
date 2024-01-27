/*
  Módulo de definición de `Pila'.

  `Pila' es una estructura lineal con comportamiento LIFO cuyos
   elementos son de tipo `nat'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#ifndef _PILA_H
#define _PILA_H

#include "utils.h"

struct rep_pila; // representación de `Pila', definida en `pila.cpp'.
typedef rep_pila *Pila;

/* 
  Devuelve una pila vacía (sin elementos). 
  Ejecuta en O(1).
*/
Pila crear_pila();

/* 
  Apila `elem' en `p'. 
  Ejecuta en O(1).  
*/
void apilar(nat elem, Pila &p);

/* 
  Remueve de `p' el elemento que está en la cima.
  Si es_vacia_pila(p) no hace nada. 
  Ejecuta en O(1).  
*/
void desapilar(Pila &p);

/* 
  Devuelve `true' si y sólo si `p' es vacía (no tiene elementos). 
  Ejecuta en O(1).  
*/
bool es_vacia_pila(Pila p);

/* 
  Devuelve el elemento que está en la cima de `p'.
  Precondición: ! es_vacia_pila(p). 
  Ejecuta en O(1).  
*/
nat cima(Pila p);

/* 
  Libera la memoria asignada a `p'. 
  Ejecuta en O(n) siendo n el largo de la pila.
*/
void destruir_pila(Pila &p);

#endif
