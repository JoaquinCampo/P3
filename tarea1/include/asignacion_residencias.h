
#ifndef __ASIGNACION_RESIDENCIAS__
#define __ASIGNACION_RESIDENCIAS__

/*
  Módulo de definición de `asignacion.h'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "utils.h"
#include "asignacion.h"

/**
 * Devuelve una asignacion de estudiantes a hospitales de manera tal que:
 * cada estudiante esté asignado a lo sumo a un hospital
 * se cubran todos los cupos de los hospitales, y
 * no existan inestabilidades de tipo 1 ni 2.
 *
 * @param m       Cantidad de hospitales, con identificadores en [0,m-1]
 *
 * @param C       Arreglo de naturales de tamaño m
 *                C[i] contiene la cantidad de cupos ofrecidos por el hospital hi 
 * 
 * @param n       Cantidad de estudiantes, con identificadores en [0,n-1]
 *
 * @param hPrefs  Matriz de preferencias de hospitales sobre estudiantes (mxn)
 *                hPrefs[i,j] contiene el identificador del estudiante en la posición j de la lista de preferencias de hi
 * 
 * @param ePrefs  Matriz de preferencias de estudiantes sobre hospitales (nxm) 
 *                ePrefs[i,j] contiene el identificador del hospital en la posición j de la lista de preferencias de ei
 * 
 * @return      Devuelve una asignacion, que es una lista de pares (e,h) (ver asignacion.h), 
 *              de manera tal que si el par (e,h) está en la asignación entonces 
 *              el estudiante e está asignado al hospital h para realizar su residencia.
 *              El algoritmo debe ejecutar en orden O(n*m)
 * 
 */

/* PRE-condición: La suma total de los cupos ofrecidos por los hospitales es menor o igual a la cantidad total de estudiantes. */
/* Esto es, Sum_{i=0}^{m-1} C[i] <= n */
Asignacion asignarResidencias(nat m, nat* C, nat n, nat** hPrefs, nat** ePrefs);

#endif
