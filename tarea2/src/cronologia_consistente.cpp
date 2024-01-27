/*
  Módulo de implementación de `cronologia_consistente'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
*/
#include <cstddef>
#include "../include/utils.h"
#include "../include/lista_datos.h"
#include "../include/lista.h"
#include "../include/grafo.h"
#include "../include/cronologia_consistente.h"

Cronologia cronologia_consistente(nat n, ListaDatos tipo1, ListaDatos tipo2)
{
  bool existe_cr_consistente = false;
  Grafo graph = crear_grafo(2 * n, true);
  Cronologia cr = new evento[2 * n];
  for (nat i = 1; i <= n; i++)
  {
    agregar_vertice(i, graph);
    agregar_vertice(i + n, graph);
    agregar_arista(i, i + n, graph); // para cada persona identificada con i, el valor i representa cuando nace y i+n cuando muere
  }
  while (tipo1 != NULL) //inserto los datos en el grafo
  {
    dato d = primer_dato(tipo1);
    agregar_arista(id1(d) + n, id2(d), graph); // el acontecimiento de que muera id1 sucede antes de que nazca id2
    tipo1 = resto_datos(tipo1);
  }
  while (tipo2 != NULL) //inserto los datos en el grafo
  {
    dato d = primer_dato(tipo2);
    agregar_arista(id1(d), id2(d) + n, graph); // el acontecimiento de que muera id2 sucede despues de que nazca id1
    agregar_arista(id2(d), id1(d) + n, graph); // el acontecimiento de que muera id1 sucede despues de que nazca id2
    tipo2 = resto_datos(tipo2);
  }
  nat cant = cantidad_vertices(graph);
  Lista sin_Incidentes = crear_lista();
  for (nat i = 1; i <= cant; i++)//lleno la lista de vertices sin incidentes
  {
    if (in_grado(i, graph) == 0)
    {
      insertar_al_final(i, sin_Incidentes);
    }
  }
  nat *orden = new nat[cant + 1];
  for (nat i = 1; i <= cant; i++) // array con la cantidad de aristas incidentes a cada vertice
  {
    orden[i] = in_grado(i, graph);
  }
  nat cant_agregados = 0;
  while (!es_vacia_lista(sin_Incidentes))
  {
    nat actual = primero(sin_Incidentes);
    Lista restar = copia_lista(adyacentes(actual, graph));
    comienzo(restar);
    while (existe_actual(restar))
    {
      nat ady = siguiente(restar);
      orden[ady]--;
      if (orden[ady] == 0)
        insertar_al_final(ady, sin_Incidentes);
    }
    destruir_lista(restar);
    evento agregar;
    if (actual <= n)
    {
      agregar.id = actual;
      agregar.tipo = nace;
    }
    else
    {
      agregar.id = actual - n;
      agregar.tipo = muere;
    }
    cr[cant_agregados] = agregar;
    cant_agregados++;
    remover_al_inicio(sin_Incidentes);
  }
  destruir_lista(sin_Incidentes);
  delete[] orden;
  destruir_grafo(graph);
  if (cant_agregados == cant)
  {
    existe_cr_consistente = true;
  }
  if (existe_cr_consistente)
  { // si existe, retornarla en cr
    return cr;
  }
  else
  { // si no existe, liberar la memoria asociada a cr y retornar NULL
    delete[] cr;
    return NULL;
  }
}
