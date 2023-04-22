#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hashmap.h"
#include "stack.h"
#define barrita "\n======================================\n"
#define barrita2 "\n--------------------------------------\n"
#define MINMAPCAPACITY 10
#define MAXCHAR 20

typedef struct{
    int *indicadorUltimaAccion;//1 agregar item,2 eliminar item,3 agregar puntos
    char (*ultimoItem)[MAXCHAR + 1];
    int *ultimosPuntos;
    int cantAcciones;
    int capacidadHistorial;
}tipoHistorial;

typedef struct{
    char nombre[MAXCHAR + 1];
    char (*items)[MAXCHAR + 1];
    long cantItems;
    long puntosHabilidad;
    tipoHistorial *historial;
} tipoJugador;

tipoHistorial* alargarHistorial(tipoHistorial* historial)
{
    historial->capacidadHistorial *= 2;
    historial->indicadorUltimaAccion = realloc(historial->indicadorUltimaAccion, sizeof(int) * historial->capacidadHistorial);
    historial->ultimoItem= realloc(historial->ultimoItem, sizeof(char[MAXCHAR + 1]) * historial->capacidadHistorial);
    historial->ultimosPuntos = realloc(historial->ultimosPuntos, sizeof(int) * historial->capacidadHistorial);
    return historial;
}

void crearPerfil(HashMap *mapProfiles){
    tipoJugador *perfil = NULL;
    perfil = (tipoJugador*) malloc(sizeof(tipoJugador));
    printf("Ingrese el nombre del jugador %ld.\n", mapProfiles->size + 1);
    scanf("%20[^\n]s", perfil->nombre);
    while (getchar() != '\n');
    perfil->items = malloc(sizeof(char*));
    perfil->cantItems = 0;
    perfil->puntosHabilidad = 0;
    perfil->historial = (tipoHistorial*) malloc(sizeof(tipoHistorial));
    perfil->historial->indicadorUltimaAccion = (int *) malloc(sizeof(int));
    perfil->historial->ultimoItem = malloc(sizeof(char*));
    perfil->historial->ultimosPuntos = (int *) malloc(sizeof(int));
    perfil->historial->cantAcciones = 0;
    perfil->historial->capacidadHistorial = 1;
    if (mapProfiles->size == mapProfiles->capacity)
        enlarge(mapProfiles);
    insertMap(mapProfiles, perfil->nombre, perfil);
}

void mostrarPerfilJugador(HashMap *mapProfiles){
    printf("Ingrese el nombre a buscar.\n");
    tipoJugador *perfil = NULL;
    perfil = (tipoJugador*) malloc(sizeof(tipoJugador));
    scanf("%20[^\n]s", perfil->nombre);
    while (getchar() != '\n');
    perfil = searchMap(mapProfiles, perfil->nombre);
    if (perfil == NULL)
    {
        printf("No existe el jugador %s en nuestros registros.", perfil->nombre);
        return;
    }
    printf("Nombre del jugador: %s\n", mapProfiles->buckets[mapProfiles->current]->key);
    printf("Cantidad de puntos de habilidad del jugador: %ld\n", perfil->puntosHabilidad);
    if (perfil->cantItems == 0)
    {
        printf("El jugador %s no posee items.\n", perfil->nombre);
        return;
    }
    for (long i = 0; i < perfil->cantItems; i++)
        printf("El item %ld del jugador %s es: %s\n", i + 1, perfil->nombre,perfil->items[i]);
}


void agregarItemJugador(HashMap *map){

    char item[MAXCHAR + 1];
    char jugador[MAXCHAR + 1];
    tipoJugador *perfil = NULL;
    perfil = (tipoJugador*) malloc(sizeof(tipoJugador));

    printf("Ingrese el nombre del jugador.\n");
    scanf("%20[^\n]s",jugador);
    while (getchar() != '\n');
   
    perfil = searchMap(map, jugador);
    
    if(perfil != NULL){
        printf("Ingrese el nombre del item a agregar.\n");
        scanf("%20[^\n]s", item);
        while (getchar() != '\n');
        perfil->historial->indicadorUltimaAccion[perfil->historial->cantAcciones] = 1;
        strcpy(perfil->historial->ultimoItem[perfil->historial->cantAcciones], item);
        perfil->items = realloc(perfil->items, sizeof(char[MAXCHAR + 1]) * perfil->cantItems + 1);
        strcpy(perfil->items[perfil->cantItems],item);
        perfil->cantItems++;
        perfil->historial->cantAcciones++;
        if (perfil->historial->cantAcciones == perfil->historial->capacidadHistorial)
            perfil->historial = alargarHistorial(perfil->historial);
        map->buckets[map->current]->value = perfil;
    }else{
        printf("No existe el jugador %s\n",jugador);
    }
    
}

void eliminarItemJugador(HashMap *map){

    char item[MAXCHAR + 1];
    char jugador[MAXCHAR + 1];
    tipoJugador *perfil = NULL;
    perfil = (tipoJugador*) malloc(sizeof(tipoJugador));
    size_t verificador;
    bool seguir = false;
    
    do{
        printf("Ingrese el nombre del jugador.\n");
        scanf("%20[^\n]s", jugador);
        while (getchar() != '\n');
        perfil = searchMap(map, jugador);
        if (perfil == NULL){
            printf("No existe el jugador mencionado.");
            return;
        }else{
            printf("Ingrese el item a borrar.\n");
            scanf("%20[^\n]s", item);
            while (getchar() != '\n');
            long auxItems = perfil->cantItems;
            
            for (long i = 0; i <= auxItems-1; i++){
                if (strcmp(perfil->items[i], item) == 0){
                    if (i == auxItems - 1){
                        perfil->cantItems--;
                        break;
                    }else{
                        for (long j = 0; j <= auxItems-2; j++){
                            strcpy(perfil->items[j], perfil->items[j+1]);
                        }
                        perfil->cantItems--;
                    }
                }
            }
        }
        perfil->historial->indicadorUltimaAccion[perfil->historial->cantAcciones] = 2;
        perfil->historial->cantAcciones++;
        if (perfil->historial->cantAcciones == perfil->historial->capacidadHistorial)
            perfil->historial = alargarHistorial(perfil->historial);
        printf("¿Desea eliminar otro item? Ingrese '0' para finalizar.");
        scanf("%zu", &verificador);
        if (verificador == 0){
            seguir = false;
        }else
        {
            seguir = true;
        }
    }while(seguir);
    return;
}

void agregarPuntosHabilidad(HashMap *map){
    
    long puntosHabilidad=0;
    char jugador[MAXCHAR + 1];
    tipoJugador *perfil = NULL;
    perfil = (tipoJugador*) malloc(sizeof(tipoJugador));
    
    printf("Ingrese el nombre del jugador para agregarle puntos.\n");
    scanf("%20[^\n]s",jugador);
    while (getchar() != '\n');
    
    perfil = searchMap(map,jugador);
     
    if(perfil!=NULL){
        
        printf("Ingrese la cantidad de puntos de habilidad a agregar.\n");
        scanf("%ld",&puntosHabilidad);
        perfil->historial->indicadorUltimaAccion[perfil->historial->cantAcciones] = 3;
        perfil->puntosHabilidad+=puntosHabilidad;
        perfil->historial->cantAcciones++;
        if (perfil->historial->cantAcciones == perfil->historial->capacidadHistorial)
        perfil->historial = alargarHistorial(perfil->historial);
    }else{
        printf("No existe el jugador %s\n",jugador);
    }
}

void mostrarJugadoresConMismoItem(HashMap *map){
    char item[MAXCHAR + 1];
    printf("Ingrese el nombre del item.\n");
    scanf("%20[^\n]s", item);
    Pair* pos = firstMap(map);
    tipoJugador* perfil = (tipoJugador*) malloc(sizeof(tipoJugador)); 
    bool hayJugadores = false;
    
    while(pos!=NULL){
        perfil=pos->value;
        for (long i = 0; i <= perfil->cantItems-1; i++){
            if (hayJugadores == false){
                if (strcmp(perfil->items[i],item)==0){
                    hayJugadores = true;
                    printf("Se mostraran los jugadores que tengan el item %s.\n", item);
                    printf("%s.\n", perfil->nombre);
                    break;
                }
            }else{
                if (strcmp(perfil->items[i],item)==0){
                    printf("%s.\n", perfil->nombre);
                    break;
                }
            }
        }
        pos = nextMap(map);
    }
    if (hayJugadores == false) printf("No hay jugadores que tengan el item %s.\n", item);
    return;
}
/*
void desacerUltimaOpcionJugador(HashMap *map){
    
}

void exportarJugadores(HashMap *map){
    
}

void importarJugadores(HashMap *map){
    
}
*/
void mostrarTodosLosJugadores(HashMap *mapProfiles){
    puts(barrita);
    printf("Datos de todos los jugadores");
    puts(barrita);
    Pair* pos = firstMap(mapProfiles);
    long cont = 0;
    tipoJugador *perfil = NULL;
    perfil = (tipoJugador*) malloc(sizeof(tipoJugador));
    
    while (pos != NULL)
    {
        perfil = pos->value;
        printf("Nombre del jugador: %s\n", perfil->nombre);
        printf("Cantidad de puntos de habilidad del jugador: %ld\n", perfil->puntosHabilidad);
        if (perfil->cantItems == 0)
        {
            printf("El jugador %s no posee items.\n", perfil->nombre);
        }
        else
        {
            for (long i = 0; i < perfil->cantItems; i++)
            printf("El item %ld del jugador %s es: %s", i + 1, perfil->nombre,perfil->items[i]);
        }
        pos = nextMap(mapProfiles);
        puts(barrita2);
    }
}

int main(void) {

    HashMap *mapProfiles = createMap(MINMAPCAPACITY);
    int opcionMenu = -1;
    
    printf("Bienvenido al control de pacientes.\n");
        
    while (opcionMenu != 0){
        puts(barrita);
        printf("Elija una opción del menú.\n");
        puts(barrita);
        printf("1. Crear perfil de jugador/a\n");
        printf("2. Mostrar perfil de jugador/a\n");
        printf("3. Agregar item a jugador/a\n");
        printf("4. Eliminar item de jugador/a\n");
        printf("5. Agregar puntos de habilidad a el/la jugador/a\n");
        printf("6. Mostrar jugador@s con item específico\n");
        printf("7. Deshacer última acción de jugador/a\n");
        printf("8. Exportar datos de jugadores a archivo de texto\n");
        printf("9. Cargar datos de jugadores desde un archivo de texto \n");
        printf("0.- Salir del juego\n");
        printf("Indique la opcion: \n");
        scanf("%d", &opcionMenu);
        while(getchar() != '\n');
        switch(opcionMenu){
            case 1:
                {
                    crearPerfil(mapProfiles);
                    break;
                } 
            case 2:
                {
                    mostrarPerfilJugador(mapProfiles);
                    break;
                }
            case 3: 
                {
                    agregarItemJugador(mapProfiles);
                    break;
                }
            case 4: 
                {
                    eliminarItemJugador(mapProfiles);
                    break;
                }
            case 5: 
                {
                    agregarPuntosHabilidad(mapProfiles);
                    break;
                }
            case 6: 
                    mostrarJugadoresConMismoItem(mapProfiles);
                    break;
            /*case 7: 
                {
                    desacerUltimaOpcionJugador(mapProfiles);
                    break;
                }
            case 8: 
                {
                    exportarJugadores(mapProfiles);
                    break;
                }
            case 9:
                {
                    importarJugadores(mapProfiles);
                    break;*/
            case 11:
                {
                    mostrarTodosLosJugadores(mapProfiles);
                    break;
                }
            case 0: 
                {
                    printf("\nSaliste del juego.");
                    return 0;
                }
            default: 
                {
                    printf("No ingreso opción válida.");
                    break;
                }
        }
    }
    return 0;
}