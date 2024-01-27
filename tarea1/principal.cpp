
/**
Módulo principal de la tarea 3.

Intérprete de comandos para probar los módulos.

Cada comando tiene un nombre y una lista (posiblemente vacía) de parámetros.
Se asume que los comandos están bien formados. Esto implica que:
- el nombre es uno de los descritos más abajo;
- la cantidad y tipo de los parámetros cumplen con lo requerido;
- se cumplen las precondiciones de las operaciones invocadas.

Descripción de los comandos:
leer_instancia
  - Lee de la entrada la cantidad de hospitales y la cantidad de estudiantes.
  Los valores quedan almacenados en las variables "n" y "m" de forma correspondiente.
  Cada estudiante se corresponde con un índice entre 0 y n-1.
  Cada hospital se corresponde con un índice entre 0 y m-1.
  - Lee una lista de cupos ofrecidos por cada hospital. El valor en la posición i se corresponde con
  los cupos libres del hospital i y queda almacenado en C[i].
  - Lee de la entrada m permutaciones de n estudiantes. La permutación i se corresponde con la lista
  de preferencias del hospital i. La lista queda almacenada en hPrefs[i].
  - Lee de la entrada n permutaciones de m hospitales. La permutación j se corresponde con la lista
  de preferencias del estudiante j. La lista queda almacenada en ePrefs[j].
imprimir_instancia
  Imprime los datos que definen la instancia: "n", "m", "C", y las matrices de preferencias
  hPrefs y ePrefs.
asignar_residencias
  Ejecuta la función asignarResidencias y almacena la lista de parejas resultado en "a".
asignar_residencias_stress
  Ejecuta la función asignarResidenciasStress y alamacena la lista de parejas resultado en "a".
  Imprime la asignación almacenada en a.
imprimir_asignacion
  Imprime la asignación almacenada en a, si la asignación es vacía retorna el mensaje
  "La asignación es vacía". Los pares se imprimen ordenados de forma creciente por índice
  de estudiante. Si un estudiante e_i quedó libre se imprime la pareja (e_i, libre).
Fin
  Termina el programa.
# comentario
  Imprime el resto de la línea.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "include/asignacion.h"
#include "include/asignacion_residencias.h"
#include <iostream>
#include <cstring>
#include <climits>


/* Ejemplo de instancia de entrada
m n
c0 c1 .... cm-1 // cupos hospitales 
p0 p1 ... pn-1 // lista de preferencias de h0 
...
p0 p1 ... pn-1 // lista de preferencias de hm-1 
p0 p1 ... pm-1 // lista de preferencias de e0 
... 
p0 p1 ... pm-1 // lista de preferencias de en-1 
*/
static void leer_instancia(nat &m, nat* &cupos, nat &n, nat ** &hPrefs, nat ** &ePrefs);

static void crear_instancia_stress(nat &m, nat* &cupos, nat &n, nat ** &hPrefs, nat ** &ePrefs);

static void imprimir_instancia(nat m, nat* C, nat n, nat** hPrefs, nat** ePrefs);

static void liberar_memoria(nat m, nat n, nat* &C, nat** &hPrefs, nat** &ePrefs, Asignacion &a);
/* Estructura para identificar el nombre de comando */
enum enum_cmd_t {
  cmd_fin,
  cmd_leer_instancia,
  cmd_imprimir_instancia,
  cmd_asignar_residencias,
  cmd_asignar_residencias_stress,
  cmd_imprimir_asignacion,
  cmd_comentario,
  no_reconocido
};
const int cant_com = no_reconocido;

struct enum_nombre_cmd {
  const enum_cmd_t enum_cmd;
  const char *nombre_cmd;
};

/*
  Asociación entre nombre de comando y enumerado.
 */
const enum_nombre_cmd cmds[] = {
    {cmd_fin, "Fin"},
    {cmd_leer_instancia, "leer_instancia"},
    {cmd_imprimir_instancia, "imprimir_instancia"},
    {cmd_asignar_residencias, "asignar_residencias"},
    {cmd_asignar_residencias_stress, "asignar_residencias_stress"},
    {cmd_imprimir_asignacion, "imprimir_asignacion"},
    {cmd_comentario, "#"}
};

/*
  Devuelve el identificador de comando leido desde la entrada estándar.
 */
enum_cmd_t identificador_comando();

/*
  Incrementa el contador de comandos y muestra el prompt.
 */
void mostrar_prompt(int &cont_comandos);

/* Devuelve en `str_numero' la conversión de ´nat' a  string. */
void nat_a_string(char *str_numero, nat nat);

int main( int argc, const char* argv[] )
{
    const int MAX_LINEA = 100;
    char restolinea[MAX_LINEA];

    int cont_comandos = 0;
    bool salir = false;

    nat m,n = 0;
    nat* C = NULL;
    nat ** hPrefs = NULL; 
    nat ** ePrefs = NULL;

    Asignacion a = NULL;

    while (!salir) {

        mostrar_prompt(cont_comandos);
        enum_cmd_t enum_com = identificador_comando();
        // procesar el comando
        switch (enum_com) {

            case cmd_leer_instancia: {
                leer_instancia(m, C, n, hPrefs, ePrefs);
                break;
            }

            case cmd_imprimir_instancia: {
                imprimir_instancia(m, C, n, hPrefs, ePrefs);
                break;
            }

            case cmd_asignar_residencias: {
                a = asignarResidencias(m, C, n, hPrefs, ePrefs);
                break;
            }

            case cmd_imprimir_asignacion: {
                if (a == NULL || n == 0)
                    printf("La asignación es vacía. \n");
                else
                    imprimir_asignacion(a, n);
                break;
            }

            case cmd_asignar_residencias_stress: {
                crear_instancia_stress(m, C, n, hPrefs, ePrefs);
                a = asignarResidencias(m, C, n, hPrefs, ePrefs);
                if (a == NULL || n == 0)
                    printf("La asignación es vacía. \n");
                else
                    imprimir_asignacion(a, n);
                break;
            }

            case cmd_fin: {
                salir = true;
                printf("Fin.\n");
                break;
            }

            case cmd_comentario: {
                fgets(restolinea, MAX_LINEA, stdin);
                printf("%s", restolinea);
                ungetc('\n', stdin);
                break;
            }

            default:
                printf("Comando No Reconocido.\n");
                break;
            } // switch
        fgets(restolinea, MAX_LINEA, stdin);
    } // while

    //Liberar memoria
    liberar_memoria(m, n, C, hPrefs, ePrefs, a);
}

// FIN MAIN

static void leer_instancia(nat &m, nat* &cupos, nat &n, nat ** &hPrefs, nat ** &ePrefs){
    int cant_scanf = scanf("%u %u", &m, &n);
    assert(cant_scanf == 2);
    (void)cant_scanf; // para evitar el warning al compilar con -NDEBUG

    cupos = new nat[m];
    for(nat i = 0; i < m; i++) {
        char strnum[10];
        int cant_scanf = scanf("%s", strnum);
        assert(cant_scanf == 1);
        (void)(cant_scanf);
        cupos[i] = atoi(strnum);
    }

    hPrefs = new nat*[m];
    for(nat i = 0; i < m; i++) {
        hPrefs[i] = new nat[n];
        for(nat j = 0; j < n; j++) {
            char strnum[10];
            int cant_scanf = scanf("%s", strnum);
            assert(cant_scanf == 1);
            (void)(cant_scanf);
            hPrefs[i][j] = atoi(strnum);
        }
    }

    ePrefs = new nat*[n];
    for(nat i = 0; i < n; i++) {
        ePrefs[i] = new nat[m];
        for(nat j = 0; j < m; j++) {
            char strnum[10];
            int cant_scanf = scanf("%s", strnum);
            assert(cant_scanf == 1);
            (void)(cant_scanf);
            ePrefs[i][j] = atoi(strnum);
        }
    }
}

static void crear_instancia_stress(nat &m, nat* &cupos, nat &n, nat ** &hPrefs, nat ** &ePrefs) {
    nat dir = 0;
    int cant_scanf = scanf("%u %u %u", &m, &n, &dir);
    assert(cant_scanf == 3);
    (void)cant_scanf; // para evitar el warning al compilar con -NDEBUG

    cupos = new nat[m];
    for(nat i = 0; i < m; i++) {
        cupos[i] = n/m;
    }

    hPrefs = new nat*[m];
    for(nat i = 0; i < m; i++) {
        hPrefs[i] = new nat[n];
        for(nat j = 0; j < n; j++) {
            hPrefs[i][j] = j;
        }
    }

    ePrefs = new nat*[n];
    for(nat i = 0; i < n; i++) {
        ePrefs[i] = new nat[m];
        for(nat j = 0; j < m; j++) {
            if (dir == 0) {
                ePrefs[i][j] = j;
            } else {
                ePrefs[i][j] = m - j - 1;
            }
        }
    }
}

static void imprimir_instancia(nat m, nat* C, nat n, nat** hPrefs, nat** ePrefs){ 
    printf("Cantidad hospitales: %u\n", m);
    printf("Cupos hospitales: "); 
    for(nat i = 0; i < m; i++) {
        printf("%u ", C[i]);
    }
    printf("\n");

    printf("Cantidad estudiantes: %u\n", n); 

    printf("Preferencias hospitales\n");
    for(nat i = 0; i < m; i++) {
        printf("Preferencias hospital h%u: ", i);
        for(nat j = 0; j < n; j++) {
            printf("%u ", hPrefs[i][j]);
        }
        printf("\n");
    }

    printf("Preferencias estudiantes\n");
    for(nat i = 0; i < n; i++) {
        printf("Preferencias estudiante e%u: ", i);
        for(nat j = 0; j < m; j++) {
            printf("%u ", ePrefs[i][j]);
        }
        printf("\n");
    }
}


enum_cmd_t identificador_comando() {
  enum_cmd_t res = no_reconocido;

  const int MAX_NOMBRE = 50;
  char nom_com[MAX_NOMBRE];
  int cant_scanf = scanf("%s", nom_com);
  assert(cant_scanf == 1);
  (void)cant_scanf; // para evitar el warning al compilar con -NDEBUG
  bool encontrado = false;
  int i = cmd_fin; // = 0
  while ((!encontrado) && (i < cant_com)) {
    if (0 == strcmp(nom_com, cmds[i].nombre_cmd)) {
      res = cmds[i].enum_cmd;
      encontrado = true;
    } else {
      i++;
    }
  }
  return res;
} // identificador_comando

/*
  Incrementa el contador de comandos y muestra el prompt.
 */
void mostrar_prompt(int &cont_comandos) {
  cont_comandos++;
  printf("%u>", cont_comandos);
} // mostrar_prompt

/* Devuelve en `str_numero' la conversión de ´nat' a  string. */
void nat_a_string(char *str_numero, nat nat) {
  if (nat == UINT_MAX)
    strcpy(str_numero, "NO");
  else
    sprintf(str_numero, "%u", nat);
} // nat_a_string

static void liberar_memoria(nat m, nat n, nat* &C, nat** &hPrefs, nat** &ePrefs, Asignacion &a) {
    //Liberar memoria
    if (C != NULL)
        delete [] C;
    if (hPrefs != NULL) {
        for(nat i = 0; i < m; i++) delete [] hPrefs[i];
        delete [] hPrefs; 
    }
    if (ePrefs != NULL) {
        for(nat i = 0; i < n; i++) delete [] ePrefs[i]; 
        delete [] ePrefs;
    }
    destruir_asignacion(a);
}