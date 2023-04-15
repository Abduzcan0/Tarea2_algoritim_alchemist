#include <stdio.h>
#include "hashmap.h"
#include "stack.h"
#define barrita "\n======================================\n"

typedef struct jugadores {
    char *nombre;
    char **items;
    size_t cantItems;
    size_t puntosHabilidad;
    stack *historial;
} tipoJugador;

void crearPerfil(HashMap *map){
    
}

void mostrarPerfilJugador(HashMap *map){
    
}

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

int main(void) {

    HashMap *map;
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
                    crearPerfil();
                    break;
                } 
            case 2:
                {
                    mostrarPerfilJugador();
                    break;
                }
            case 3: 
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