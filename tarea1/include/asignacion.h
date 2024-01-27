/*
 * Módulo de definición de `asignacion'.
 *
 * `Asignacion' es una estructura lineal de elementos de tipo par.
 * El tipo par es una dupla de identificadores (eid, hid), donde eid identifica a un estudiante y hid identifica a un hospital.
 *
 * Laboratorio de Programación 3.
 * InCo-FIng-UDELAR
 *
 * En los tiempos de ejecución `n' indica la cantidad de elementos que contiene la lista
 * al momento de invocar a la operación, salvo que se indique lo contrario. 
 */

#ifndef _ASIGNACION_H
#define _ASIGNACION_H

#include "utils.h"

struct par {
  nat eid;
  nat hid;
}; // par de naturales

// Retrona el campo id1 del dato d.
nat eid(par p);

// Retorna el campo id2 del dato d.
nat hid(par p);

// representación de `Asignacion', definida en `asignacion.cpp'.
struct rep_asignacion;
typedef rep_asignacion* Asignacion;

/* 
Devuelve la lista vacía (sin elementos). 
Tiempo: O(1)
*/
Asignacion crear_asignacion();

/*
Devuelve una copia de `lst'. La lista devuelta no comparte memoria con `lst'.
Tiempo: O(n)
*/
Asignacion copia_asignacion(Asignacion lst);

/* 
Inserta `elem' al inicio de `lst'. 
Tiempo: O(1)
*/
void insertar_par(par elem, Asignacion &lst);

/* 
Remueve la primera ocurrencia del par `p' de `lst'. Si `p' no pertenece a `lst' no hace nada. 
Tiempo: O(n)
*/
void remover_par(par p, Asignacion &lst);

/* 
Devuelve `true' si y sólo si `lst' es vacía (no tiene elementos). 
Tiempo: O(1)
*/
bool es_vacia_asignacion(Asignacion lst);

/*
Devuelve la cantidad de elementos de lst. 
Tiempo: O(n)
*/
nat cantidad(Asignacion lst);

/* 
Devuelve `true' si y sólo si `p' está en `lst'. 
Tiempo: O(n) 
*/
bool pertenece_a_asignacion(par p, Asignacion lst);

/* 
Devuelve el primer elemento de `lst'.
Precondición: ! es_vacia_Asignacion(lst). 
Tiempo: O(1) 
*/
par primer_par(Asignacion lst);

/* 
Devuelve el resto de `lst' (es decir, la lista sin su primer elemento).
La función no modifica la lista original (no elimina el primer elemento).
Precondición: ! es_vacia_Asignacion(lst). 
Tiempo: O(1)
*/
Asignacion resto_pares(Asignacion lst);

/* 
Libera la memoria asignada a `lst'. 
Tiempo: O(n) 
*/
void destruir_asignacion(Asignacion &lst);

/* 
Imprime `lst' en la salida estándar.
Formato: (p1_eid,p1_hid) (p2_eid,p2_hid) ... `.'
   Después de cada elemento se imprime un espacio en
   blanco. 
Si un estudiante no quedó asignado se imprime como pareja "libre".
*/
void imprimir_asignacion(Asignacion lst, nat n);

#endif