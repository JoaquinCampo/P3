/*
  Módulo de implementación de `Cola'.

  `Cola' es una estructura lineal con comportamiento FIFO cuyos
   elementos son de tipo `nat'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/cola.h"

#include <stddef.h>
#include <assert.h>

struct nodo {
  nat elem;
  nodo *sig;
};

struct rep_cola {
  nodo *primero, *ultimo;
};

Cola crear_cola() {
  Cola res = new rep_cola;
  res->primero = res->ultimo = NULL;
  return res;
}

void encolar(nat elem, Cola &c) {
  nodo *nuevo = new nodo;
  nuevo->elem = elem;
  nuevo->sig = NULL;
  if (c->primero == NULL)
    c->primero = nuevo;
  else
    c->ultimo->sig = nuevo;

  c->ultimo = nuevo;
}

void desencolar(Cola &c) {
  if (!es_vacia_cola(c)) {
    nodo *borrar = c->primero;
    c->primero = borrar->sig;
    if (c->ultimo == borrar)
      c->ultimo = c->primero;
    delete borrar;
  }
}

bool es_vacia_cola(Cola c) { return (c->primero == NULL); }

nat frente(Cola c) {
  assert(c->primero != NULL);
  return c->primero->elem;
}

void destruir_cola(Cola &c) {
  while (c->primero != NULL) {
    nodo *aborrar = c->primero;
    c->primero = c->primero->sig;
    delete aborrar;
  }
  delete c;
}
