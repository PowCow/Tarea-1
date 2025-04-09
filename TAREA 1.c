#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arraylist.c"
#include <string.h>
#include "arraylist.h"
#include "list.h"
#define List_h
#ifndef ARRAYLIST_H
#define ARRAYLIST_H

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
    puts("       Sistema de Gestión de Soporte Técnico");
    puts("===============================================") ;
    puts("1) Registrar nuevo ticket") ;
    puts("2) Asignar nueva prioridad a un ticket") ;
    puts("3) Mostrar lista de espera") ;
    puts("4) Atender al siguiente ticket") ;
    puts("5) Mostrar tickets por prioridad") ;
    puts("6) Salir") ;
}

int ticketExiste(List *bajo, List *medio, List *alto, int idTicket){
    for (int k = 0 ; k < get_size(bajo) ; k++){
        ticket *t = (ticket *)bajo->data[k] ;
        if (t->id == idTicket){
            return 1 ;}}
    for (int k = 0 ; k < get_size(medio) ; k++){
        ticket *t = (ticket *)medio->data[k] ;
        if (t->id == idTicket){
            return 1 ;}}
    for (int k = 0 ; k < get_size(alto) ; k++){
        ticket *t = (ticket *)alto->data[k] ;
        if (t->id == idTicket){
            return 1 ;}}
    return 0 ;
}

void registrarTicket(List *bajo){
    ticket *nuevoT = malloc(sizeof(ticket)) ;
    if (nuevoT == NULL){
        printf("Error al crear el ticket\n") ;
        return ;}
    
    printf("Ingrese el ID del ticket: ") ;
    scanf("%d", &nuevoT->id) ;
    getchar() ; 

    if (ticketExiste(bajo, NULL, NULL, nuevoT->id)){
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
    
    nuevoT->prioridad = 3 ;
    pushBack(bajo, nuevoT) ;
}

void asignarPrioridad(List *bajo, List *medio, List *alto){
    int idTicket ;
    printf("Ingrese el ID del ticket a modificar: ") ;
    scanf("%d", &idTicket) ;

    for (int k = 0; k < get_size(bajo); k++){
        ticket *t = (ticket *)bajo->data[k] ;
        if (t->id == idTicket){
            t->prioridad = 2 ;
            pushBack(medio, t) ;
            popCurrent(bajo) ;
            printf("Ticket con ID %d cambiado a prioridad media\n", idTicket) ;
            return ;}}

    for (int k = 0; k < get_size(medio); k++){
        ticket *t = (ticket *)medio->data[k] ;
        if (t->id == idTicket){
            t->prioridad = 1 ;
            pushBack(alto, t) ;
            popCurrent(medio) ; //ojo con el indice
            printf("Ticket con ID %d cambiado a prioridad alta\n", idTicket) ;
            return ; }}
    
    printf("No se encontró el ticket con el ID %d\n", idTicket) ;
}

void mostrarListaEspera(List *bajo, List *medio, List *alto){
    printf("Tickets en espera:\n") ;

    for (int k = 0 ; k < get_size(bajo) ; k++){
        ticket *t = (ticket *)bajo->data[k] ;
        printf("ID: %d | Descripción: %s | Hora: %s | Prioridad: Baja\n", t->id, t->descripcion, t->horaRegistro) ;
    } 
    for (int k = 0 ; k < get_size(medio) ; k++){
        ticket *t = (ticket *)medio->data[k] ;
        printf("ID: %d | Descripción: %s | Hora: %s | Prioridad: Media\n", t->id, t->descripcion, t->horaRegistro) ;
    } 
    for (int k = 0 ; k < get_size(alto) ; k++){
        ticket *t = (ticket *)alto->data[k] ;
        printf("ID: %d | Descripción: %s | Hora: %s | Prioridad: Alta\n", t->id, t->descripcion, t->horaRegistro) ;
    } 
}

void siguienteTicket(List *alto, List *medio, List *bajo){
    ticket *miniT = NULL ;
    char confirmacion ;

    if (get_size(alto) > 0){
        miniT = (ticket *)alto->data[0] ;
        printf("\n --- Atendiendo ticket --- \n") ;
        printf("¿Está seguro de atender el ticket con la ID %d? (s/n): ", miniT->id) ;
        scanf(" %c", &confirmacion) ; getchar() ;
        if (confirmacion == 's' || confirmacion == 'S'){
            popCurrent(alto) ;
            printf("ID: %d | Descripción: %s | Hora: %s | Prioridad: Alta\n", miniT->id, miniT->descripcion, miniT->horaRegistro) ;
        } else if (confirmacion == 'n' || confirmacion == 'N') {
            printf("Atención cancelada.\n") ;
        } else{
            printf("Seleccione una opción mencionada\n") ;
        }
        return ;
        
    }else if (get_size(medio) > 0){
        miniT = (ticket *)medio->data[0] ;
        printf("\n --- Atendiendo ticket --- \n") ;
        printf("¿Está seguro de atender el ticket con la ID %d? (s/n): ", miniT->id) ;
        scanf(" %c", &confirmacion) ; getchar() ;
        if (confirmacion == 's' || confirmacion =='S'){
            popCurrent(medio) ;
            printf("ID: %d | Descripción: %s | Hora: %s | Prioridad: Media\n", miniT->id, miniT->descripcion, miniT->horaRegistro) ;
        } else if (confirmacion == 'n' || confirmacion == 'N'){
            printf("Atención cancelada.\n") ;
        } else{
            printf("Seleccione una opción mencionada\n") ;
        }
        return ;

    }else if (get_size(bajo) > 0){
        miniT = (ticket *)bajo->data[0] ;  
        printf("\n --- Atendiendo ticket --- \n") ;
        printf("¿Está seguro de atender el ticket con la ID %d? (s/n): ", miniT->id) ;
        scanf(" %c", &confirmacion) ; getchar() ;
        if (confirmacion == 's' || confirmacion == 'S'){
            popCurrent(bajo) ;
            printf("ID: %d | Descripción: %s | Hora: %s | Prioridad: Baja\n", miniT->id, miniT->descripcion, miniT->horaRegistro) ;
        } else if (confirmacion == 'n' || confirmacion == 'N'){
            printf("Atención cancelada.\n") ;
        } else{
            printf("Seleccione una opción mencionada\n") ;
        }
        return ;
    }else{
        printf("No hay tickets en espera...\n") ;
        return ;
    }
}

void buscarTicketID(List *bajo, List *medio, List *alto){
    int idBuscado ;
    printf("Ingrese el ID del ticket a buscar: ") ;
    scanf("%d", &idBuscado) ; getchar() ;

    for (int k = 0 ; k < get_size(alto) ; k++){
        ticket *miniT = (ticket *)alto->data[k] ;
        if (miniT->id == idBuscado){
            printf("\n --- Ticket Encontrado --- \n") ;
            printf("ID: %d | Descripción: %s | Hora: %s | Prioridad: Alta\n", miniT->id, miniT->descripcion, miniT->horaRegistro) ;
            return ;
        }
    }
    for (int k = 0 ; k < get_size(medio) ; k++){
        ticket *miniT = (ticket *)medio->data[k] ;
        if (miniT->id == idBuscado){
            printf("\n --- Ticket Encontrado --- \n") ;
            printf("ID: %d | Descripción: %s | Hora: %s | Prioridad: Media\n", miniT->id, miniT->descripcion, miniT->horaRegistro) ;
            return ;
        } 
    }
    for (int k = 0 ; k < get_size(bajo) ; k++){
        ticket *miniT = (ticket *)bajo->data[k] ;
        if (miniT->id == idBuscado){
            printf("\n --- Ticket Encontrado --- \n") ;
            printf("ID: %d | Descripción: %s | Hora: %s | Prioridad: Baja\n", miniT->id, miniT->descripcion, miniT->horaRegistro) ;
            return ;
        }
    }
    printf("No se encontró un ticket con la ID %d\n", idBuscado) ;
}

int main()
{
    char opcion ;
    List *priAlta = create_list() ;
    List *priMedia = create_list() ;
    List *priBaja = create_list() ;

    do{
        mostrarMenu() ;
        printf("Seleccione una opción: ") ;
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
                break ;
            default:
                printf("Opción no válida. Intente de nuevo.\n") ;}
    }while (opcion != '6') ;

    return 0 ;
}
#endif

