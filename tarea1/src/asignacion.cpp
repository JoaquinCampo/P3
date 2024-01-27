/*
  Módulo de implementación de `Asignacion'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/asignacion.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

nat eid(par p) { return p.eid; };

nat hid(par p) { return p.hid; };

struct rep_asignacion {
  par elem;
  rep_asignacion *sig;
};

Asignacion crear_asignacion() { return NULL; }

void insertar_par(par elem, Asignacion &lst) {
  rep_asignacion *nuevo = new rep_asignacion;
  nuevo->elem = elem;
  nuevo->sig = lst;
  lst = nuevo;
}

void remover_par(par p, Asignacion &lst) {
  if ((lst != NULL) && (eid(p) == lst->elem.eid) && (hid(p) == lst->elem.hid)) {
    rep_asignacion *aborrar = lst;
    lst = lst->sig;
    delete aborrar;
  } else if (lst != NULL) {
    rep_asignacion *cursor = lst;
    while ((cursor->sig != NULL) && ((eid(p) != cursor->sig->elem.eid) || (hid(p) != cursor->sig->elem.hid))) {
      cursor = cursor->sig;
    }
    if (cursor->sig != NULL) {
      rep_asignacion *aborrar = cursor->sig;
      cursor->sig = cursor->sig->sig;
      delete aborrar;
    } // else no está elem en lst, no se hace nada
  } // else lst == NULL, no se hace nada
}

Asignacion copia_Asignacion(Asignacion lst) {
  Asignacion res;
  if (lst == NULL)
    res = NULL;
  else {
    res = new rep_asignacion;
    rep_asignacion * ultimo = res;
    ultimo->elem = lst->elem;
    while (lst->sig != NULL) {
      lst = lst->sig;
      ultimo->sig = new rep_asignacion;
      ultimo = ultimo->sig;
      ultimo->elem = lst->elem;
    }
    ultimo->sig = NULL;
  }
  return res;
}

bool es_vacia_asignacion(Asignacion lst) { return (lst == NULL); }

bool pertenece_a_asignacion(par p, Asignacion lst) {
  while ((lst != NULL) && ((eid(p) != lst->elem.eid)||(hid(p) != lst->elem.hid))) {
    lst = lst->sig;
  }
  return (lst != NULL);
}

par primer_par(Asignacion lst) {
  assert(!es_vacia_asignacion(lst));
  return lst->elem;
}

Asignacion resto_pares(Asignacion lst) {
  assert(!es_vacia_asignacion(lst));
  return lst->sig;
}

void imprimir_par(par p) { printf("(%u,%u) ", p.eid, p.hid); }

void imprimir_asignacion(Asignacion lst, nat n) {
  int* parejas = new int[n];
  for (nat i = 0; i < n; i++) parejas[i] = -1;
  while(!es_vacia_asignacion(lst)) {
    parejas[eid(primer_par(lst))] = hid(primer_par(lst));
    lst = resto_pares(lst);
  }
  for (nat i = 0; i < n; i++)
    if (parejas[i] == -1)
      printf("(%d, libre) ", i);
    else
      printf("(%d, %d) ", i, parejas[i]);

  printf("\n");
  delete [] parejas;
}

nat cantidad(Asignacion lst) {
  nat cant = 0;
  while (!es_vacia_asignacion(lst)) {
    cant++;
    lst = resto_pares(lst);
  }
  return cant;
}

void destruir_asignacion(Asignacion &lst) {
  while (lst != NULL) {
    rep_asignacion *aborrar = lst;
    lst = lst->sig;
    delete aborrar;
  }
}
