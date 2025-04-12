 # Tarea-1
Tarea 1. Estructura de Datos 2025

## Sistema de Gestión de Soporte Técnico

DESCRIPCION :

Este programa permite gestionar los tickets de un soporte tecnico con diferentes niveles de prioridad (alta, media, baja), los usuarios pueden registrar nuevos tickets, modificiar la prioridad, consultar la lista de espera, atender tickets por el orden de prioridad y buscar tickets por ID. Esta herramienta esta diseñada para organizar eficientemente la atencion en el soporte tecnico, asegurandose que los problemas mas urgentes se resuelvan primero.

1. Como compilar y ejecutar :
   El programa fue diseñado en el lenguaje C, puede ser ejecutado en Visual Studio Code, con una extension de C/C++ de Microsoft. Los pasos a seguir para empezar a trabajar con el programa son :
   - Tener instalado Visual Studio Code (https://code.visualstudio.com/)
   - Instalar la extencion de C/C++ Extension Pack ubicada en Visual Studio Code
   - Instalar (si no se tiene) un compilador de C (como gcc). Si se esta en Windows se recomienda descargar MinGW (https://www.mingw-w64.org/)
   Los pasos para compilar y ejecutar el programa son:
   * Abrir el proyecto :
      - Descargar el archivo .zip que contiene el programa y descomprimirlo en una carpeta local
      - Abrir Visual Studio Code
      - Seleccionar 'File > Open folder' , luego abrir la carpeta donde se descomprimio el proyecto
   * Compilar y ejecutar el proyecto :
      - Abrir el archivo principal, en este caso "tarea1"
      - Abrir una terminal, 'Terminal > New Terminal' y en esta compila el programa con el siguiente comando:

              gcc tdas/*.c tarea1.c -Wno-unused-result -o tarea1

      - Una vez compilado usar este comando para ejecutar el programa :

              ./tarea1

2. Funcionalidades :
   * Funcionando correctamente:
     - Registro de tickets con ID, descripcion y prioridad
     - Modificacion de prioridad en un ticket
     - Mostrar los tickets agrupados por prioridad y orden de llegada (hora)
     - Atender al siguiente ticket, respetando prioridad y el orden de llegada
     - Busqueda de ticket segun la ID
     - Limpieza de memoria de los tickets al salir del programa
       
   * Problemas conocidos:
     - El sistema no carga ni guarda tickets desde archivos externos (CSV o txt)
     - Al escribir numeros de mas de dos digitos al elegir el menu, toma el primero para cumplir funcion requerida
     - Al ingresar letras en la ID del ticket, se salta el ingreso de descripcion del problema, guarda la ID 'ingresada' como si fuera descripcion y coloca una ID random
     - En la descripcion al ingresar solo numeros no salta un error
       
   * A mejorar:
     - Implementar carga y guardado de tickets desde otros archivos
     - Una interfaz de usuario mas agradable :)
     - Errores de prueba variados
       
3. Ejemplo de Uso :
   
   Paso 1: Registro de ticket
   
      Se registra un nuevo cliente, ingresando un numero de ID para reconocer su ticket, la descripcion y la prioridad de su problema.
   
         Ingrese el ID del ticket: 001
         Ingrese una descripcion a su problema: Se ha dañado la pantalla de la computadora
         Ingrese prioridad a su problema (A = ALTO, M = MEDIO, B = BAJO): M
            Ticket registrado con prioridad MEDIA
      El sistema registra el nuevo ticket con ID '001', la descripcion del problema y la prioridad, en este caso 'MEDIA', tambien se guarda la hora de ingreso del ticket automaticamente. La prioridad puede cambiarse al regresar al menu con la opcion 2).
   
   Paso 2 : Mostrar lista de espera
   
      Si hay muchos tickets se puede saber el orden que estos tienen para ser atendidos.
   
         Tickets en espera:
         --- Prioridad Alta ---
         ID: 009 | Descripcion: Daño grave a los componentes con cortocircuito | Hora: 15:39:45 | Prioridad: Alta
         --- Prioridad Media ---
         ID: 001 | Descripcion: Se ha dañado la pantalla de la computadora | Hora: 13:29:53 | Prioridad: Media
         --- Prioridad Baja ---
         ID: 010| Descripcion: No conecta el cargador al computador | Hora: 15:58:03 | Prioridad: Baja
      Se ordena segun prioridad y se atiende segun quien llego primero, muestra la ID, descripcion, la hora y la prioridad del ticket. Tambien existe la opcion de mostrar un ticket especifico para ver sus datos, escribiendo la ID del ticket que se busca.

    Paso 3: Atender ticket
      Al seleccionar esta opcion se tomara el primer ticket, segun que prioridad tenga y a que hora haya llegado.
   
         --- Atendiendo Ticket ---
         ID: 009 | Descripcion: Daño grave a los componentes con cortocircuito | Hora: 15:39:45 | Prioridad: Alta
      Se mostrara el primer ticket a atender, con su ID, descripcion, hora y prioridad. Se preguntara si se desea atender el ticket mostrado en pantalla con las opciones (s = si / n = no), si se responde con 's' el ticket debe atenderse y se elimina automaticamente de la lista de espera, si se responde que 'n' se cancela la operacion. No importa si se responde con una letra mayuscula o minuscula.
   
         Desea atender este ticket? (s/n): s
            Ticket atendido y removido con exito !
         Desea atender este ticket? (s/n): n
            Atencion Cancelada...
   En el menu al seleccionar la opcion 6) se sale del menu y termina el programa

         ....
         5) Mostrar ticket por ID
         6) Salir 
       
            Seleccione una opcion: 6
         Saliendo del programa...









      
   
