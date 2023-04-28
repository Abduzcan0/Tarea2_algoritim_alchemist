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
#define MAXLONGITUDTIPOLONG 10
#define CANTINICIALITEMS 10
#define CAPACIDADHISTORIALINICIAL 10
#define ELEM1SIZE sizeof(stack*)
#define ELEM2SIZE sizeof(char*)
#define ELEM3SIZE sizeof(long)

typedef struct{
    stack *indicadorUltimaAccion; //1 agregar item,2 eliminar item,3 agregar puntos
    stack *ultimoItem;
    stack *ultimosPuntos;
}tipoHistorial;

typedef struct{
    char nombre[MAXCHAR + 1];
    char (*items)[MAXCHAR + 1];
    long cantItems;
    long puntosHabilidad;
    tipoHistorial *historial;
} tipoJugador;

void crearPerfil(HashMap *mapProfiles){
    tipoJugador *perfil = NULL;
    perfil = (tipoJugador*) malloc(sizeof(tipoJugador));
    long size = sizeMap(mapProfiles);
    long capacity = capacityMap(mapProfiles);
    printf("Ingrese el nombre del jugador %ld.\n", size + 1);
    scanf("%20[^\n]s", perfil->nombre);
    while (getchar() != '\n');
    perfil->items = malloc(sizeof(char[MAXCHAR + 1]));
    perfil->cantItems = 0;
    perfil->puntosHabilidad = 0;
    perfil->historial = (tipoHistorial*) malloc(sizeof(tipoHistorial));
    perfil->historial->indicadorUltimaAccion = (stack*) malloc(sizeof(stack) * CAPACIDADHISTORIALINICIAL);    
    perfil->historial->indicadorUltimaAccion = createStack(perfil->historial->indicadorUltimaAccion, ELEM1SIZE, ELEM3SIZE);
    perfil->historial->ultimoItem = (stack*) malloc(sizeof(stack) * CAPACIDADHISTORIALINICIAL);
    perfil->historial->ultimoItem = createStack(perfil->historial->ultimoItem, ELEM1SIZE, ELEM2SIZE);
    perfil->historial->ultimosPuntos = (stack*) malloc(sizeof(stack) * CAPACIDADHISTORIALINICIAL);
    perfil->historial->ultimosPuntos = createStack(perfil->historial->ultimosPuntos, ELEM1SIZE, ELEM2SIZE);
    if (size >= capacity)
        enlarge(mapProfiles);
    insertMap(mapProfiles, perfil->nombre, perfil);
}

void mostrarPerfilJugador(HashMap *mapProfiles){
    printf("Ingrese el nombre a buscar.\n");
    tipoJugador *perfilAux = NULL;
    tipoJugador *perfil = NULL;
    perfilAux = (tipoJugador*) malloc(sizeof(tipoJugador));
    perfil = (tipoJugador*) malloc(sizeof(tipoJugador));
    scanf("%20[^\n]s", perfil->nombre);
    while (getchar() != '\n');
    perfilAux = searchMap(mapProfiles, perfil->nombre);
    if (perfilAux == NULL)
    {
        printf("No existe el jugador %s en nuestros registros.", perfil->nombre);
        return;
    }
    printf("Nombre del jugador: %s\n", perfilAux->nombre);
    printf("Cantidad de puntos de habilidad del jugador: %ld\n", perfilAux->puntosHabilidad);
    if (perfilAux->cantItems == 0)
    {
        printf("El jugador %s no posee items.\n", perfilAux->nombre);
        return;
    }
    for (long i = 0; i < perfilAux->cantItems; i++)
        printf("El item %ld del jugador %s es: %s\n", i + 1, perfilAux->nombre, perfilAux->items[i]);
}


void agregarItemJugador(HashMap *map){
    char item[MAXCHAR + 1];
    char jugador[MAXCHAR + 1];
    tipoJugador *perfil = NULL;
    perfil = (tipoJugador*) malloc(sizeof(tipoJugador));

    printf("Ingrese el nombre del jugador.\n");
    scanf("%20[^\n]s", jugador);
    while (getchar() != '\n');

    perfil = searchMap(map, jugador);
    
    if(perfil != NULL){
        printf("Ingrese el nombre del item a agregar.\n");
        scanf("%20[^\n]s", item);
        while (getchar() != '\n');
        int indicador = 1;
        pushBackStack(perfil->historial->indicadorUltimaAccion, &indicador, ELEM1SIZE, ELEM3SIZE);
        pushBackStack(perfil->historial->ultimoItem, item, ELEM1SIZE, ELEM2SIZE);
        perfil->items = realloc(perfil->items, sizeof(char[MAXCHAR + 1]) * (perfil->cantItems + 1));
        strcpy(perfil->items[perfil->cantItems], item);
        perfil->cantItems++;
    }else{
        printf("No existe el jugador %s\n", jugador);
    }
}
void eliminarItemJugador(HashMap *map){
    char item[MAXCHAR + 1];
    char jugador[MAXCHAR + 1];
    tipoJugador *perfil = NULL;
    perfil = (tipoJugador*) malloc(sizeof(tipoJugador));
    size_t verificador;
    bool hayItem = false;

    
    printf("Ingrese el nombre del jugador.\n");
    scanf("%20[^\n]s", jugador);
    while (getchar() != '\n');
    perfil = searchMap(map, jugador);
    if (perfil == NULL){
        printf("No existe el jugador mencionado.\n");
        return;
    }else{
        printf("Ingrese el item a borrar.\n");
        scanf("%20[^\n]s", item);
        while (getchar() != '\n');
        long auxItems = perfil->cantItems;
        
        for (long i = 0; i <= auxItems-1; i++){
            if (strcmp(perfil->items[i], item) == 0){
                int indicador = 2;
                pushBackStack(perfil->historial->indicadorUltimaAccion, &indicador, ELEM1SIZE, ELEM3SIZE);
                pushBackStack(perfil->historial->ultimoItem, item, ELEM1SIZE, ELEM2SIZE);
                if (i != auxItems-1){
                    for (long j = i; j <= auxItems-2; j++){
                        strcpy(perfil->items[j], perfil->items[j+1]);
                    }
                }
                perfil->cantItems--;
                hayItem = true;
                break;
            }
        }
    }
    if (hayItem){
        printf("El item %s ha sido eliminado del inventario del jugador %s\n", item, perfil->nombre);
        printf("¿Desea eliminar otro item? Ingrese '0' para finalizar.\n");
        scanf("%zu", &verificador);
        hayItem = false;
    }else{
        printf("No existe el item a eliminar.\n");
    }
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
    if(perfil != NULL){
        printf("Ingrese la cantidad de puntos de habilidad a agregar.\n");
        scanf("%ld",&puntosHabilidad);
        int indicador = 3;
        pushBackStack(perfil->historial->indicadorUltimaAccion, &indicador, ELEM1SIZE, ELEM3SIZE);
        pushBackStack(perfil->historial->ultimosPuntos, &puntosHabilidad, ELEM1SIZE, ELEM2SIZE);
        perfil->puntosHabilidad+=puntosHabilidad;
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

void deshacerUltimaOpcionJugador(HashMap *map){
    char jugador[MAXCHAR + 1];
    tipoJugador *perfil = NULL;
    perfil = (tipoJugador*) malloc(sizeof(tipoJugador));

    printf("Ingrese el nombre del jugador a deshacer su ultima acción.\n");
    scanf("%20[^\n]s",jugador);
    while (getchar() != '\n');
    perfil = searchMap(map, jugador);
    
    if (perfil != NULL){
        int *indicador;
        indicador = (int*) malloc(sizeof(int));
        indicador = (int*) topStack(perfil->historial->indicadorUltimaAccion);
        size_t elemSize = sizeof(stack*);
        size_t elem2Size = sizeof(char*);
        switch(*indicador){
            case 1:
                {
                    popBackStack(perfil->historial->ultimoItem);
                    perfil->cantItems--;
                    popBackStack(perfil->historial->indicadorUltimaAccion);
                    printf("Se ha deshecho la ultima accion del jugador %s.\n", perfil->nombre);
                    break;
                }
            case 2:
                {
                    printf("\n");
                    perfil->cantItems++;
                    char *item;
                    item = (char*) malloc(sizeof(char) * (MAXCHAR + 1));
                    strcpy(item, (char*) topStack(perfil->historial->ultimoItem));
                    strcpy(perfil->items[perfil->cantItems-1], item);
                    popBackStack(perfil->historial->ultimoItem);
                    popBackStack(perfil->historial->indicadorUltimaAccion);
                    printf("Se ha deshecho la ultima accion del jugador %s.\n", perfil->nombre);
                    break;
                }
            case 3: 
                {
                    perfil->puntosHabilidad -= (long) topStack(perfil->historial->ultimosPuntos);
                    popBackStack(perfil->historial->ultimosPuntos);
                    popBackStack(perfil->historial->indicadorUltimaAccion);
                    printf("Se ha deshecho la ultima accion del jugador %s.\n", perfil->nombre);
                    break;
                }
            default: 
                {
                    printf("El jugador %s no ha realizado acciones.\n", perfil->nombre);
                    break;
                }
            }
    }
    else{
         printf("Este jugador no existe.\n");
    }
    return;
}

void exportarJugadores(HashMap *map){

    printf("Ingrese el nombre del archivo .csv donde los jugadores se exportarán.\n");
    char nombreArchivoExport[MAXCHAR + 1];
    scanf("%20[^\n]s", nombreArchivoExport);
    while (getchar() != '\n');


    FILE* file = fopen(nombreArchivoExport, "w");
    fprintf(file, "Nombre,Puntos de habilidad,#items,Item 1,Item 2,Item 3,Item 4,Item 5,Item 6,Item 7,Item 8\n");
    if (file == NULL){
        printf("No existe el archivo");
        return;
    }

    Pair* pos = firstMap(map);
    tipoJugador* perfil = NULL;
    perfil = (tipoJugador *) malloc(sizeof(tipoJugador));
         while (pos != NULL)
        {
            perfil = pos->value;
            fprintf(file,"%s,",perfil->nombre);
            fprintf(file,"%ld", perfil->puntosHabilidad);
            if (perfil->cantItems == 0){
    
                fprintf(file,",0");
    
            }else{
                fprintf(file,",%ld",perfil->cantItems);
                for (long i = 0; i < perfil->cantItems; i++){
                    fprintf(file,",%s",perfil->items[i]);
    
                }
            }
            fprintf(file,"\n");
            pos = nextMap(map);
        }

    
    fclose(file);
}
void importarJugadores(HashMap* map){
    tipoJugador* nuevoJugador;
    char nombreArchivoImport[MAXCHAR + 1];
    long size = sizeMap(map);
    long capacity = capacityMap(map);
    printf("Ingrese el nombre del archivo .csv del que se importarán los jugadores.\n");
    scanf("%20[^\n]s", nombreArchivoImport);
    while(getchar() != '\n');
    FILE* file = fopen(nombreArchivoImport, "r");
    if (file == NULL){
        printf("No existe el archivo");
        return;
    }
    char* titular = (char*) malloc(sizeof(char) * MAXCHAR * 5);
    fscanf(file, "%s[^\n]", titular);
    while (fgetc(file) != '\n');
    int cont = 0;
    char caracterAux;
    bool indicadorFinArchivo = false;
    
    while (!indicadorFinArchivo){
        cont++;
        if (size >= capacity)
        {
            capacity *= 2;
            enlarge(map);
        }
        nuevoJugador = NULL;
        nuevoJugador = (tipoJugador *) calloc(sizeof(tipoJugador), 1);
        fscanf(file, "%[^,]s", nuevoJugador->nombre);
        while (fgetc(file) != ',');
        fscanf(file, "%ld", &nuevoJugador->puntosHabilidad);
        while (fgetc(file) != ',');
        fscanf(file, "%ld", &nuevoJugador->cantItems);
        while (fgetc(file) != ',');
        nuevoJugador->items = realloc(nuevoJugador->items, sizeof(char[MAXCHAR + 1]) * nuevoJugador->cantItems);
        
        if (nuevoJugador->cantItems > 0)
        {
            for (long i = 0; i < nuevoJugador->cantItems - 1; i++)
            {
                fscanf(file, "%[^,]s", nuevoJugador->items[i]);
                while (fgetc(file) != ',');
            }
            fscanf(file, "%s", nuevoJugador->items[nuevoJugador->cantItems - 1]);
            caracterAux = fgetc(file);
            while (caracterAux != '\n' && caracterAux != EOF)
            {
                caracterAux = fgetc(file);
                if (caracterAux == EOF)
                    indicadorFinArchivo = true;
            }
        }
        insertMap(map, nuevoJugador->nombre, nuevoJugador);
        size++;
    }
    fclose(file);
}

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
        cont++;
        perfil = pos->value;
        printf("Nombre del jugador %ld: %s\n", cont, perfil->nombre);
        printf("Cantidad de puntos de habilidad del jugador: %ld\n", perfil->puntosHabilidad);
        if (perfil->cantItems == 0)
        {
            printf("El jugador %s no posee items.\n", perfil->nombre);
        }
        else
        {
            for (long i = 0; i < perfil->cantItems; i++)
            printf("El item %ld del jugador %s es: %s\n", i + 1, perfil->nombre,perfil->items[i]);
        }
        pos = nextMap(mapProfiles);
        puts(barrita2);
    }
}

int main(void){

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
                case 7: 
                    {
                        deshacerUltimaOpcionJugador(mapProfiles);
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
                        break;
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
    }
    return 0;
}