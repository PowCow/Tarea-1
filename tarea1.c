void asignarPrioridad(List *bajo, List *medio, List *alto){ //Asigna prioridad al ticket, empieza en bajo
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
