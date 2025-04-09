#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tdas/list.h"

//compilar : gcc tdas/*.c tarea1.c -Wno-unused-result -o tarea1
//ejecutar : ./tarea1


typedef struct
{
    char rut[11] ;
    int id ;
    char descripcion[101] ;
    char horaRegistro[10] ; // ej. 10:54:02 
    unsigned short prioridad ; // 1. Alta 2. Media 3. Baja
} ticket ;

void mostrarMenu(){
    puts("===============================================") ;
    puts("     Sistema de Gestion de Soporte Tecnico");
    puts("===============================================") ;
    puts("1) Registrar nuevo ticket") ;
    puts("2) Asignar nueva prioridad a un ticket") ;
    puts("3) Mostrar lista de espera") ;
    puts("4) Atender al siguiente ticket") ;
    puts("5) Mostrar tickets por prioridad") ;
    puts("6) Salir") ;
}

int ticketExiste(List *bajo, List *medio, List *alto, int idTicket){ //Comprueba que el ticket no se repita
    for (void *dato = list_first(bajo) ; dato != NULL ; dato = list_next(bajo)){
        ticket *miniT = (ticket *)dato ;
        if (miniT->id == idTicket){
            return 1 ;}
    }
    for (void *dato = list_first(medio) ; dato != NULL ; dato = list_next(medio)){
        ticket *miniT = (ticket *)dato ;
        if (miniT->id == idTicket){
            return 1 ;}
    }
    for (void *dato = list_first(alto) ; dato != NULL ; dato = list_next(alto)){
        ticket *miniT = (ticket *)dato ;
        if (miniT->id == idTicket){
            return 1 ;}
    }
    return 0 ;
}

void registrarTicket(List *bajo, List *medio, List *alto){ //registra el ticket del usuario
    ticket *nuevoT = malloc(sizeof(ticket)) ;
    if (nuevoT == NULL){
        printf("Error al crear el ticket\n") ;
        return ;}
    
    printf("Ingrese el ID del ticket: ") ;
    scanf("%d", &nuevoT->id) ;
    getchar() ; 

    if (ticketExiste(bajo, NULL, NULL, nuevoT->id)){ //revisar
        printf("El ticket con ID %d ya existe\n", nuevoT->id) ;
        free(nuevoT) ;
        return ;}

    printf("Ingrese una descripción de su problema: ") ;
    fgets(nuevoT->descripcion, 100, stdin) ;
    nuevoT->descripcion[strcspn(nuevoT->descripcion, "\n")] = 0 ;
    
    //registramos hora actual
    time_t tiempo = time(NULL) ;
    struct tm *infoTime = localtime(&tiempo) ;
    strftime(nuevoT->horaRegistro, 10, "%H:%M:%S", infoTime) ;

    char opPrioridad ;
    do{
        printf("Ingrese prioridad de su problema (A = ALTO , M = MEDIO, B = BAJO): ") ;
        scanf(" %c", &opPrioridad) ; getchar() ;
        opPrioridad = toupper(opPrioridad) ;
        if (opPrioridad != 'A' && opPrioridad != 'M' & opPrioridad != 'B')
            printf("Opcion no valida, intente nuevamente.\n") ;
    } while (opPrioridad != 'A' && opPrioridad != 'M' & opPrioridad != 'B') ;

    switch(opPrioridad){
        case 'A':
            nuevoT->prioridad = 1 ;
            list_pushBack(alto, nuevoT) ;
            printf("Ticket registrado con prioridad ALTA\n") ;
            break ;
        case 'M':
            nuevoT->prioridad = 2 ;
            list_pushBack(medio, nuevoT) ;
            printf("Ticket registrado con prioridad MEDIA\n") ;
            break ;
        case 'B':
            nuevoT->prioridad = 3 ;
            list_pushBack(bajo, nuevoT) ;
            printf("Ticket registrado con prioridad BAJA\n\n") ;

    }
}

void asignarPrioridad(List *bajo, List *medio, List *alto){ //CAMBIAR
    int idTicket ;
    printf("Ingrese el ID del ticket a modificar: ") ;
    scanf("%d", &idTicket) ; getchar() ;
    
    //buscar prioridad BAJA (3) para subir a MEDIA (2)
    for (ticket *miniT = (ticket *)list_first(bajo) ; miniT != NULL ; miniT = (ticket *)list_next(bajo)){
        if (miniT->id == idTicket){
            miniT->prioridad = 2 ; //prioridad MEDIA
            list_pushBack(medio, miniT) ;
            list_popCurrent(bajo) ;
            printf("Ticket con ID %d cambiado a prioridad media\n", idTicket) ;
            return ;
        }
    }
    //buscar prioridad MEDIA (2) para subir a ALTA (1)
    for (ticket *miniT = (ticket*)list_first(medio) ; miniT != NULL ; miniT = (ticket*)list_next(medio)){
        if (miniT->id == idTicket){
            miniT->prioridad = 1 ; //prioridad ALTA
            list_pushBack(alto, miniT) ;
            list_popCurrent(medio) ;
            printf("Ticket con ID %d cambiado a prioridad alta\n", idTicket) ;
            return ;
        }
    }
    
    printf("No se encontro el ticket con el ID %d\n", idTicket) ;
}

void mostrarListaEspera(List *bajo, List *medio, List *alto){ //CAMBIADO
    printf("\nTickets en espera:\n") ;

    printf("\n --- PRIORIDAD ALTA --- \n") ;
    for (ticket *miniT = (ticket *)list_first(alto) ; miniT != NULL ; miniT = (ticket *)list_next(alto)){
        printf("ID: %d | Descripcion: %s | Hora: %s | Prioridad: Alta\n", miniT->id, miniT->descripcion, miniT->horaRegistro) ;
    } 
    printf("\n --- PRIORIDAD MEDIA --- \n") ;
    for (ticket *miniT = (ticket *)list_first(medio) ; miniT != NULL ; miniT = (ticket *)list_next(medio)){
        printf("ID: %d | Descripcion: %s | Hora: %s | Prioridad: Media\n", miniT->id, miniT->descripcion, miniT->horaRegistro) ;
    } 
    printf("\n --- PRIORIDAD BAJA --- \n") ;
    for (ticket *miniT = (ticket *)list_first(bajo) ; miniT != NULL ; miniT = (ticket *)list_next(bajo)){
        printf("ID: %d | Descripcion: %s | Hora: %s | Prioridad: Baja\n", miniT->id, miniT->descripcion, miniT->horaRegistro) ;
    } 
}

void siguienteTicket(List *alto, List *medio, List *bajo){ //CAMBIADO
    ticket *miniT = NULL ;
    char confirmacion ;
    const char *prioridad = "" ;
    List *listaAux = NULL ;

    if (list_size(alto) > 0){
        miniT = (ticket *)list_first(alto) ;
        prioridad = "ALTA" ;
        listaAux = alto ;
    } else if (list_size(medio) > 0){
        miniT = (ticket *)list_first(medio) ;
        prioridad = "MEDIA" ;
        listaAux = medio ;
    } else if (list_size(bajo) > 0){
        miniT = (ticket *)list_first(bajo) ;
        prioridad = "BAJA" ;
        listaAux = bajo ;
    } else {
        printf("No hay tickets en espera...\n") ;
        return ;
    }
    printf("\n --- Atendiendo Ticket --- \n") ;
    printf("ID: %d | Descripcion: %s | Hora: %s | Prioridad: %s\n", miniT->id, miniT->descripcion, miniT->horaRegistro, prioridad) ;
    printf("¿Desea atender este ticket? (s/n): ") ;
    scanf(" %c", &confirmacion) ;
    getchar() ;

    if (confirmacion == 's' || confirmacion == 'S'){
        ticket *atendido = (ticket *)list_popFront(listaAux) ; 
        printf("¡ Ticket atendido y removido con exito !\n") ;
        free(atendido) ; //liberar memoria del ticket atendido
    } else if (confirmacion == 'n' || confirmacion == 'N'){ 
        printf("Atencion Cancelada...\n") ;
    } else{
        printf("Opcion no valida. Use 's' o 'n'. \n") ;
    }
}

void buscarTicketID(List *bajo, List *medio, List *alto){ //CAMBIADO
    int idBuscado ;
    printf("Ingrese el ID del ticket a buscar: ") ;
    scanf("%d", &idBuscado) ; getchar() ;

    for (ticket *miniT = (ticket *)list_first(alto) ; miniT != NULL ; miniT = (ticket *)list_next(alto)){
        if (miniT->id == idBuscado){
            printf("\n --- Ticket encontrado --- \n") ;
            printf("ID: %d | Descripcion: %s | Hora: %s | Prioridad: ALTA\n", miniT->id, miniT->descripcion, miniT->horaRegistro) ;
            return ;
        }
    }
    for (ticket *miniT = (ticket *)list_first(medio) ; miniT != NULL ; miniT = (ticket *)list_next(medio)){
        if (miniT->id == idBuscado){
            printf("\n --- Ticket encontrado --- \n") ;
            printf("ID: %d | Descripcion: %s | Hora: %s | Prioridad: MEDIA\n", miniT->id, miniT->descripcion, miniT->horaRegistro) ;
            return ;
        }
    }
    for (ticket *miniT = (ticket *)list_first(bajo) ; miniT != NULL ; miniT = (ticket *)list_next(bajo)){
        if (miniT->id == idBuscado){
            printf("\n --- Ticket encontrado --- \n") ;
            printf("ID: %d | Descripcion: %s | Hora: %s | Prioridad: BAJA\n", miniT->id, miniT->descripcion, miniT->horaRegistro) ;
            return ;
        }
    }
    printf("No se encontro un ticket con la ID %d\n", idBuscado) ;
}

int main()
{
    char opcion ;
    List *priAlta = list_create() ;
    List *priMedia = list_create() ;
    List *priBaja = list_create() ;

    do{
        mostrarMenu() ;
        printf("\n Seleccione una opcion: ") ;
        scanf(" %c", &opcion) ;
        getchar() ; 

        switch (opcion) {
            case '1':
                registrarTicket(priBaja) ;
                break ;
            case '2':
                asignarPrioridad(priBaja, priMedia, priAlta) ;
                break ;
            case '3':
                mostrarListaEspera(priBaja, priMedia, priAlta) ;
                break ;
            case '4':
                siguienteTicket(priAlta, priMedia, priBaja) ;
                break ;
            case '5':
                buscarTicketID(priBaja, priMedia, priAlta) ;
                break ;
            case '6':
                printf("Saliendo del programa...\n") ;
                list_clean(priBaja) ;
                list_clean(priMedia) ;
                list_clean(priAlta) ;
                break ;
            default:
                printf("Opcion no valida. Intente de nuevo...\n") ;}
    }while (opcion != '6') ;

    return 0 ;
}



