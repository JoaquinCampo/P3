/*
  Módulo de definición de `Lista'.

  `Lista' es una estructura lineal de elementos de tipo `nat' ordenada de manera
  creciente, sin elementos repetidos.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#ifndef _LISTA_H
#define _LISTA_H

#include "utils.h"

struct rep_lista; // representación de `Lista`, definida en `lista.cpp`.
typedef rep_lista *Lista;

/* 
   Devuelve la lista vacía (sin elementos). 
   Ejecuta en O(1).
*/
Lista crear_lista();

/* 
   Devuelve una copia de `lst'.
   La lista devuelta no comparte memoria con `lst'. 
   Ejecuta en O(n) (siendo n el largo de la lista).
*/
Lista copia_lista(Lista lst);

/* 
   Devuelve una copia con los elementos de `lst' que son mayores o iguales a
   `primero'.
   La lista devuelta no comparte memoria con `lst'. 
   Ejecuta en O(n) (siendo n el largo de la lista).
*/
Lista copia_lista_desde(Lista lst, nat primero);

/* 
   Inserta `elem' en `lst' manteniendo el orden.
   Si ya estaba `elem' en `lst' no hace nada. 
   Ejecuta en O(n) (siendo n el largo de la lista).
*/
void insertar(nat elem, Lista &lst);

/* 
   Remueve `elem' de `lst'.
   Si no estaba `elem' en `lst' no hace nada.
   Ejecuta en O(n) (siendo n el largo de la lista). 
*/
void remover(nat elem, Lista &lst);

/* 
   Devuelve `true' si y sólo si `lst` es vacía (no tiene elementos). 
   Ejecuta en O(1).
*/
bool es_vacia_lista(Lista lst);

/* 
   Devuelve `true' si y sólo si `elem' pertenece a `lst'. 
   Ejecuta en O(n) (siendo n el largo de la lista).
*/
bool pertenece_a_lista(nat elem, Lista lst);

/* 
   Devuelve el primer elemento de `lst'.
   Precondición: ! es_vacia_lista(lst). 
   Ejecuta en O(1).
*/
nat primero(Lista lst);

/* 
   Devuelve el resto de `lst'.
   Precondición: ! es_vacia_lista(lst). 
   Ejecuta en O(1).   
*/
Lista resto(Lista lst);

/* 
   Libera la memoria asignada a `lst'. 
   Ejecuta en O(n) (siendo n el largo de la lista).
*/
void destruir_lista(Lista &lst);

/* 
   Imprime `lst' en la salida estándar.
   Se imprime en orden creciente. Después de cada elemento se imprime un espacio
   en blanco. Al final se imprime un punto. 
   Ejecuta en O(n) (siendo n el largo de la lista).
*/
void imprimir_lista(Lista lst);

/* Devuelve una lista leída desde la entrada estándar que cumple el formato de
 * `imprimir_lista'. */
Lista leer_lista();

#endif
