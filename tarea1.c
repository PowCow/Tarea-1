#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "tdas/list.h"

typedef struct
{
    int id ; // ej. 1234
    char descripcion[201] ; //ej. "No enciende la pantalla"
    char horaRegistro[10] ; // ej. 10:54:02 
    unsigned short prioridad ; // 1. Alta 2. Media 3. Baja
} ticket ; //guarda la info del ticket

void mostrarMenu(){
    puts("===============================================") ;
    puts("     Sistema de Gestion de Soporte Tecnico");
    puts("===============================================") ;
    puts("1) Registrar nuevo ticket") ;
    puts("2) Asignar nueva prioridad a un ticket") ;
    puts("3) Mostrar lista de espera") ;
    puts("4) Atender ticket") ;
    puts("5) Mostrar ticket por ID") ;
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
    ticket *nuevoT = malloc(sizeof(ticket)) ; //reservamos memoria para el ticket
    if (nuevoT == NULL){
        printf("Error al crear el ticket\n") ;
        return ;}
    
    printf("Ingrese el ID del ticket: ") ;
    scanf("%d", &nuevoT->id) ;
    getchar() ; 

    if (ticketExiste(bajo, medio, alto, nuevoT->id)){ //verificamos si el ticket ya existe
        printf("El ticket con ID %d ya existe\n", nuevoT->id) ;
        free(nuevoT) ; //se libera memoria si ya existia el ticket
        return ;}

    printf("Ingrese una descripcion de su problema: ") ;
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
        if (opPrioridad != 'A' && opPrioridad != 'M' && opPrioridad != 'B')
            printf("Opcion no valida, intente nuevamente.\n") ;
    } while (opPrioridad != 'A' && opPrioridad != 'M' && opPrioridad != 'B') ;

    switch(opPrioridad){
        case 'A':
            nuevoT->prioridad = 1 ;
            list_pushBack(alto, nuevoT) ;
            printf(" Ticket registrado con prioridad ALTA\n\n") ;
            break ;
        case 'M':
            nuevoT->prioridad = 2 ;
            list_pushBack(medio, nuevoT) ;
            printf(" Ticket registrado con prioridad MEDIA\n\n") ;
            break ;
        case 'B':
            nuevoT->prioridad = 3 ;
            list_pushBack(bajo, nuevoT) ;
            printf(" Ticket registrado con prioridad BAJA\n\n") ;

    }
}

void asignarPrioridad(List *bajo, List *medio, List *alto){ //Asigna prioridad al ticket
    int idTicket ;
    printf("Ingrese el ID del ticket a modificar: ") ;
    scanf("%d", &idTicket) ; getchar() ;

    ticket *tEncontrado = NULL ;
    List *listaAux = NULL ;
    unsigned short newPrioridad = 0 ;

    //buscar lista ALTA
    for (ticket *miniT = (ticket *)list_first(alto) ; miniT != NULL ; miniT = (ticket *)list_next(alto)){ 
        if (miniT->id == idTicket){
            tEncontrado = miniT ;
            listaAux = alto ;
            newPrioridad = 1 ;
            break ;}
    }
    if (!tEncontrado){ //buscar lista MEDIA
        for (ticket *miniT = (ticket *)list_first(medio) ; miniT != NULL ; miniT = (ticket *)list_next(medio)){
            if (miniT->id == idTicket){
                tEncontrado = miniT ;
                listaAux = medio ;
                newPrioridad = 2 ;
                break ;}
        }
    }
    if (!tEncontrado){ //buscar lista BAJA
        for (ticket *miniT = (ticket *)list_first(bajo) ; miniT != NULL ; miniT = (ticket *)list_next(bajo)){
            if (miniT->id == idTicket){
                tEncontrado = miniT ;
                listaAux = bajo ;
                newPrioridad = 3 ;
                break ;}
        }
    }
    if (!tEncontrado){ //no hay ticket
        printf("No se encontro el ticket con la ID %d\n", idTicket) ; return ;
    }
    //muestra informacion actual
    printf("\n Ticket Encontrado - Prioridad Actual : %s\n", (newPrioridad == 1) ? "ALTA" : (newPrioridad == 2) ? "MEDIA" : "BAJA") ;
    printf("ID: %d | Descripcion: %s\n", tEncontrado->id, tEncontrado->descripcion) ;

    //solicita nueva prioridad
    char nuevaPrioridad;
    do {
        printf("\nSeleccione nueva prioridad (A = Alta, M = Media, B = Baja): ") ;
        scanf(" %c", &nuevaPrioridad) ; getchar();
        nuevaPrioridad = toupper(nuevaPrioridad) ; //cambia las letras a mayusculas
    } while(nuevaPrioridad != 'A' && nuevaPrioridad != 'M' && nuevaPrioridad != 'B') ;

    // Determinar lista destino
    List *listaDestino = NULL ;
    unsigned short nuevaPrioridadNum = 0 ;

    switch(nuevaPrioridad) {
        case 'A':
            listaDestino = alto ;
            nuevaPrioridadNum = 1 ;
            break ;
        case 'M': 
            listaDestino = medio ;
            nuevaPrioridadNum = 2 ;
            break ;
        case 'B':
            listaDestino = bajo ;
            nuevaPrioridadNum = 3 ;
            break ;
    }

    if (nuevaPrioridadNum == newPrioridad) {
        printf("El ticket ya tiene prioridad %s\n", (newPrioridad == 1) ? "ALTA" : (newPrioridad == 2) ? "MEDIA" : "BAJA") ;
        return;
    }

    // Mover el ticket a la nueva lista por prioridad
    list_pushBack(listaDestino, tEncontrado) ;
    list_popCurrent(listaAux) ;
    tEncontrado->prioridad = nuevaPrioridadNum ;

    printf("Prioridad cambiada a %s\n", (nuevaPrioridadNum == 1) ? "ALTA" : (nuevaPrioridadNum == 2) ? "MEDIA" : "BAJA") ;
}

void mostrarListaEspera(List *bajo, List *medio, List *alto){ //muestra los tickets que esperan ser atendidos
    printf("\nTickets en espera:\n") ;

    printf("\n --- PRIORIDAD ALTA --- \n") ; //muestra todos los tickets con prioridad alta
    for (ticket *miniT = (ticket *)list_first(alto) ; miniT != NULL ; miniT = (ticket *)list_next(alto)){
        printf("ID: %d | Descripcion: %s | Hora: %s | Prioridad: Alta\n", miniT->id, miniT->descripcion, miniT->horaRegistro) ;
    } 
    printf("\n --- PRIORIDAD MEDIA --- \n") ; //muestra todos los tickets con prioridad media
    for (ticket *miniT = (ticket *)list_first(medio) ; miniT != NULL ; miniT = (ticket *)list_next(medio)){
        printf("ID: %d | Descripcion: %s | Hora: %s | Prioridad: Media\n", miniT->id, miniT->descripcion, miniT->horaRegistro) ;
    } 
    printf("\n --- PRIORIDAD BAJA --- \n") ; //muestra todos los tickets con prioridad baja
    for (ticket *miniT = (ticket *)list_first(bajo) ; miniT != NULL ; miniT = (ticket *)list_next(bajo)){
        printf("ID: %d | Descripcion: %s | Hora: %s | Prioridad: Baja\n", miniT->id, miniT->descripcion, miniT->horaRegistro) ;
    } 
    printf("\n") ;
}

void siguienteTicket(List *alto, List *medio, List *bajo){ //muestra el ticket a atender
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
    printf("ID: %d | Descripcion: %s | Hora: %s | Prioridad: %s\n\n", miniT->id, miniT->descripcion, miniT->horaRegistro, prioridad) ;
    printf("Desea atender este ticket? (s/n): ") ;
    scanf(" %c", &confirmacion) ;
    getchar() ;

    if (confirmacion == 's' || confirmacion == 'S'){
        ticket *atendido = (ticket *)list_popFront(listaAux) ; 
        printf("\n Ticket atendido y removido con exito !\n\n") ;
        free(atendido) ; //liberar memoria del ticket atendido
    } else if (confirmacion == 'n' || confirmacion == 'N'){ 
        printf("\n Atencion Cancelada...\n\n") ;
    } else{
        printf("\n Opcion no valida. Use 's' o 'n'. \n\n") ;
    }
}

void buscarTicketID(List *bajo, List *medio, List *alto){ //busca un ticket especifico por ID
    int idBuscado ;
    printf("Ingrese el ID del ticket a buscar: ") ;
    scanf("%d", &idBuscado) ; getchar() ;

    for (ticket *miniT = (ticket *)list_first(alto) ; miniT != NULL ; miniT = (ticket *)list_next(alto)){
        if (miniT->id == idBuscado){
            printf("\n --- Ticket encontrado --- \n") ;
            printf("ID: %d | Descripcion: %s | Hora: %s | Prioridad: ALTA\n\n", miniT->id, miniT->descripcion, miniT->horaRegistro) ;
            return ;
        }
    }
    for (ticket *miniT = (ticket *)list_first(medio) ; miniT != NULL ; miniT = (ticket *)list_next(medio)){
        if (miniT->id == idBuscado){
            printf("\n --- Ticket encontrado --- \n") ;
            printf("ID: %d | Descripcion: %s | Hora: %s | Prioridad: MEDIA\n\n", miniT->id, miniT->descripcion, miniT->horaRegistro) ;
            return ;
        }
    }
    for (ticket *miniT = (ticket *)list_first(bajo) ; miniT != NULL ; miniT = (ticket *)list_next(bajo)){
        if (miniT->id == idBuscado){
            printf("\n --- Ticket encontrado --- \n") ;
            printf("ID: %d | Descripcion: %s | Hora: %s | Prioridad: BAJA\n\n", miniT->id, miniT->descripcion, miniT->horaRegistro) ;
            return ;
        }
    }
    printf("No se encontro un ticket con la ID %d\n\n", idBuscado) ;
}

int main()
{
    char opcion ; //guarda la opcion del menu
    //crea listas para cada prioridad
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
                registrarTicket(priBaja, priMedia, priAlta) ;
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
            default: //no se selecciona una opcion valida, se intenta de nuevo
                printf("Opcion no valida. Intente de nuevo...\n") ;}
    }while (opcion != '6') ;

    return 0 ;
}



