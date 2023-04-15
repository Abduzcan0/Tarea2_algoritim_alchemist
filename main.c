#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hashmap.h"
#include "stack.h"
#define barrita "\n======================================\n"
#define MINMAPCAPACITY 10
#define MAXCHAR 20

typedef struct jugadores {
    char nombre[MAXCHAR + 1];
    char (*items)[MAXCHAR + 1];
    size_t cantItems;
    size_t puntosHabilidad;
    stack *historial;
} tipoJugador;

void crearPerfil(HashMap *mapProfiles){
    tipoJugador *perfil = NULL;
    perfil = (tipoJugador*) malloc(sizeof(tipoJugador));
    printf("Ingrese el nombre del jugador %ld.\n", mapProfiles->size + 1);
    scanf("%20[^\n]s", perfil->nombre);
    while (getchar() != '\n');
    perfil->items = malloc(sizeof(char*));
    perfil->cantItems = 0;
    perfil->puntosHabilidad = 0;
    perfil->historial = createStack();
    insertMap(mapProfiles, perfil->nombre, perfil);
}


void mostrarPerfilJugador(HashMap *mapProfiles){
    printf("Ingrese el nombre a buscar.\n");
    tipoJugador *perfil = NULL;
    perfil = (tipoJugador*) malloc(sizeof(tipoJugador));
    scanf("%20[^\n]s", perfil->nombre);
    while (getchar() != '\n');
    perfil = searchMap(mapProfiles, perfil->nombre);
    printf("Nombre del jugador: %s\n", perfil->nombre);
    printf("Cantidad de puntos de habilidad del jugador: %ld\n", perfil->puntosHabilidad);
    if (perfil->cantItems == 0)
    {
        printf("El jugador %s no posee items.\n", perfil->nombre);
        return;
    }
    for (long i = 0; i < perfil->cantItems; i++)
        printf("%s", perfil->items[i]);
}

/*
void agregarItemJugador(HashMap *map){
    
}

void eliminarItemJugador(HashMap *map){
    
}

void agregarPuntosHabilidad(HashMap *map){
    
}

void mostrarJugadoresConMismoItem(HashMap *map){
    
}

void desacerUltimaOpcionJugador(HashMap *map){
    
}

void exportarDatosJugadores(HashMap *map){
    
}

void importarDatosJugadores(HashMap *map){
    
}
*/
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
            /* case 3: 
                {
                    agregarItemJugador();
                    break;
                }
            case 4: 
                {
                    eliminarItemJugador();
                    break;
                }
            case 5: 
                {
                    agregarPuntosHabilidad();
                    break;
                }
            case 6: 
                    mostrarJugadoresConMismoItem();
                    break;
            case 7: 
                {
                    desacerUltimaOpcionJugador();
                    break;
                }
            case 8: 
                {
                    exportarDatosJugadores();
                    break;
                }
            case 9:
                {
                    importarDatosJugadores();
                    break;
                }*/
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