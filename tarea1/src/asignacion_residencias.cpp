/* 5280080 */

/*
  Módulo de implementación de `asignacion_residencias'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/asignacion_residencias.h"
#include <cstddef>
#include <lista.h>
#include <asignacion.h>

par crearPar(nat hid, nat eid)
{
  par p;
  p.eid = eid;
  p.hid = hid;
  return p;
}

Asignacion asignarResidencias(nat m, nat *C, nat n, nat **hPrefs, nat **ePrefs)
{
  Asignacion devolver = crear_asignacion(); // Crear asignacion vacia
  Lista hospNOLlenos = crear_lista();       // Lista de hospitales NO llenos
  par feo = crearPar(m, n);                 // Crear par feo para comparar
  par *asignados = new par[n];              // Crear arreglo de pares para guardar asignaciones
  nat *Next = new nat[m];     // Array de preferencias de hospitales
  nat **estPref = new nat *[n];
  for (nat i = 0; i < m; i++)
  { // inicializar cada hospital como NO lleno
    nat f = m - i - 1;
    insertar(f, hospNOLlenos);
  }
  for (nat i = 0; i < n; i++) // Matriz de preferencia de estudiantes
  {
    asignados[i] = feo; 
    estPref[i] = new nat[m];
    for (nat j = 0; j < m; j++){
      Next[j] = 0;
      estPref[i][ePrefs[i][j]] = j;
    }
  }
  while (!es_vacia_lista(hospNOLlenos))
  {                                // Mientras queden hospitales NO llenos
    nat h = primero(hospNOLlenos); // Obtener hospital NO lleno
    nat est = hPrefs[h][Next[h]];  // Obtener estudiante de la preferencia actual
    if (asignados[est].eid == n)
    {                             // Si el estudiante no esta asignado a un hospital
      asignados[est] = crearPar(h, est); // Asignar estudiante a hospital
      C[h]--;                     // Disminuir el cupo del hospital
      if (C[h] == 0)              // Si el hospital esta lleno
        remover(h, hospNOLlenos); // Eliminarlo de la lista de hospitales NO llenos
    }
    else
    {                        // Si el estudiante ya esta asignado a otro hospital
      nat h2 = asignados[est].hid; // Obtener el hospital asignado
      if (estPref[est][h] < estPref[est][h2])
      {                               // Si h tiene mayor preferencia que h2
        C[h]--;                       // Disminuir el cupo del hospital
        if (C[h] == 0)                // Si el hospital esta lleno
          remover(h, hospNOLlenos);   // Eliminarlo de la lista de hospitales NO llenos
        if (C[h2] == 0)               // Si el hospital estaba lleno
          insertar(h2, hospNOLlenos); // Insertarlo en la lista de hospitales NO llenos
        C[h2]++;                      // Incrementar el cupo del hospital anterior
        asignados[est] = crearPar(h, est); // Asignar estudiante a hospital
      }
    }
    Next[h]++; // Incrementar la preferencia actual del hospital
  }
  delete[] Next;
  for (nat i = 0; i < n; i ++){ 
    delete[] estPref[i];
    if (asignados[i].eid != n)
      insertar_par(asignados[i], devolver);
  }
  delete[] estPref;
  destruir_lista(hospNOLlenos);
  delete [] asignados;
  return devolver;
}