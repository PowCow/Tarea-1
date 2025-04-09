#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arraylist.c"
#include "arraylist.h"

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
        ticket *t = (ticket *)get(bajo, k) ;
        if (t->id == idTicket){
            return 1 ;}}
    for (int k = 0 ; k < get_size(medio) ; k++){
        ticket *t = (ticket *)get(medio, k) ;
        if (t->id == idTicket){
            return 1 ;}}
    for (int k = 0 ; k < get_size(alto) ; k++){
        ticket *t = (ticket *)get(alto, k) ;
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
        ticket *t = (ticket *)get(bajo, k) ;
        if (t->id == idTicket){
            t->prioridad = 2 ;
            pushBack(medio, t) ;
            remove(bajo, k) ;
            printf("Ticket con ID %d cambiado a prioridad media\n", idTicket) ;
            return ;}}

    for (int k = 0; k < get_size(medio); k++){
        ticket *t = (ticket *)get(medio, k) ;
        if (t->id == idTicket){
            t->prioridad = 1 ;
            pushBack(alto, t) ;
            remove(medio, k) ; //ojo con el indice
            printf("Ticket con ID %d cambiado a prioridad alta\n", idTicket) ;
            return ; }}
    
    printf("No se encontró el ticket con el ID %d\n", idTicket) ;
}

void mostrarListaEspera(List *bajo, List *medio, List *alto){
    printf("Tickets en espera:\n") ;

    for (int k = 0 ; k < get_size(bajo) ; k++){
        ticket *t = (ticket *)get(bajo, k) ;
        printf("ID: %d | Descripción: %s | Hora: %s | Prioridad: Baja\n", t->id, t->descripcion, t->horaRegistro) ;
    } 
    for (int k = 0 ; k < get_size(medio) ; k++){
        ticket *t = (ticket *)get(medio, k) ;
        printf("ID: %d | Descripción: %s | Hora: %s | Prioridad: Media\n", t->id, t->descripcion, t->horaRegistro) ;
    } 
    for (int k = 0 ; k < get_size(alto) ; k++){
        ticket *t = (ticket *)get(alto, k) ;
        printf("ID: %d | Descripción: %s | Hora: %s | Prioridad: Alta\n", t->id, t->descripcion, t->horaRegistro) ;
    } 
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
                // Implementar la lógica para atender el siguiente ticket
                break ;
            case '5':
                // Implementar la lógica para mostrar tickets por prioridad
                break ;
            case '6':
                printf("Saliendo del programa...\n") ;
                break ;
            default:
                printf("Opción no válida. Intente de nuevo.\n") ;}
    }while (opcion != '6') ;

    return 0 ;
} 
