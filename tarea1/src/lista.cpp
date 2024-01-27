/*
  Módulo de implementación de `Lista'.

  `Lista' es una estructura lineal de elementos de tipo `nat' ordenada de manera
  creciente, sin elementos repetidos.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/lista.h"
#include "../include/utils.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct rep_lista {
  nat elem;
  rep_lista *sig;
};

Lista crear_lista() {
  Lista res = new rep_lista; // celda falsa
  res->sig = NULL;
  return res;
}

Lista copia_lista(Lista lst) {
  Lista res = new rep_lista;
  Lista ultimo = res;
  while (lst->sig != NULL) {
    lst = lst->sig;
    ultimo->sig = new rep_lista;
    ultimo = ultimo->sig;
    ultimo->elem = lst->elem;
  }
  ultimo->sig = NULL;
  return res;
}

Lista copia_lista_desde(Lista lst, nat primero) {
  Lista res = new rep_lista;
  Lista ultimo = res;
  while ((lst->sig != NULL) && (lst->sig->elem < primero)) {
    lst = lst->sig;
  }
  while (lst->sig != NULL) {
    lst = lst->sig;
    ultimo->sig = new rep_lista;
    ultimo = ultimo->sig;
    ultimo->elem = lst->elem;
  }
  ultimo->sig = NULL;
  return res;
}

void insertar(nat elem, Lista &lst) {
  rep_lista *cursor = lst;
  while ((cursor->sig != NULL) && (elem > cursor->sig->elem)) {
    cursor = cursor->sig;
  }
  if ((cursor->sig == NULL) || (elem < cursor->sig->elem)) {
    rep_lista *nuevo = new rep_lista;
    nuevo->elem = elem;
    nuevo->sig = cursor->sig;
    cursor->sig = nuevo;
  } // else ya está elem en lst, no se hace nada
}

void remover(nat elem, Lista &lst) {
  rep_lista *cursor = lst;
  while ((cursor->sig != NULL) && (elem > cursor->sig->elem)) {
    cursor = cursor->sig;
  }
  if ((cursor->sig != NULL) && (elem == cursor->sig->elem)) {
    rep_lista *aborrar = cursor->sig;
    cursor->sig = cursor->sig->sig;
    delete aborrar;
  } // else no está elem en lst, no se hace nada
}

bool es_vacia_lista(Lista lst) { return (lst->sig == NULL); }

bool pertenece_a_lista(nat elem, Lista lst) {
  rep_lista *cursor = lst;
  while ((cursor->sig != NULL) && (elem > cursor->sig->elem)) {
    cursor = cursor->sig;
  }
  return ((cursor->sig != NULL) && (elem == cursor->sig->elem));
}

nat primero(Lista lst) {
  assert(!es_vacia_lista(lst));
  return lst->sig->elem;
}

Lista resto(Lista lst) {
  assert(!es_vacia_lista(lst));
  return lst->sig;
}

void destruir_lista(Lista &lst) {
  while (lst != NULL) {
    rep_lista *aborrar = lst;
    lst = lst->sig;
    delete aborrar;
  }
  delete lst;
}

void imprimir_lista(Lista lst) {
  while (!es_vacia_lista(lst)) {
    printf("%d ", primero(lst));
    lst = resto(lst);
  }
  printf(".");
}

Lista leer_lista() {
  Lista res = crear_lista();
  char strnum[10]; // suficiente espacio para enteros de 32 bits
  int cant_scanf = scanf("%s", strnum);
  assert(cant_scanf == 1);
  (void)(cant_scanf); // para evitar el warning al compilar con -NDEBUG
  nat anterior, elem;
  /* se lee el primero para inicializar 'anterior' con el objetivo de controlar
   * que la lista está ordenada de manera estricta (no se excluye que el primer
   * elemento sea 0) */
  if (strcmp(strnum, ".")) {
    rep_lista *ultimo = res;
    elem = atoi(strnum);
    //    insertar(elem, res);
    ultimo->sig = new rep_lista;
    ultimo = ultimo->sig;
    ultimo->elem = elem;
    anterior = elem;
    // se lee el resto
    cant_scanf = scanf("%s", strnum);
    assert(cant_scanf == 1);
    while (strcmp(strnum, ".")) {
      elem = atoi(strnum);
      assert(anterior < elem);
      // insertar(elem, res);
      ultimo->sig = new rep_lista;
      ultimo = ultimo->sig;
      ultimo->elem = elem;
      anterior = elem;
      cant_scanf = scanf("%s", strnum);
      assert(cant_scanf == 1);
    };
    ultimo->sig = NULL;
  }
  (void)anterior; // para evitar el warning al compilar con -NDEBUG
  return res;
}
