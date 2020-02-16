#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "cliente.h"
#include "shared.h"
#include "fichero.h"

char *menuModuloCliente[] = {
    "Nuevo Cliente",
    "Modificar Cliente",
    "Eliminar Cliente",
    "Listar Clientes",
    "Retroceder"
};

// Variables Globales externas
Cliente listaCliente[100] = {0};
int contadorCliente = 0;

void moduloCliente() {
    //Cliente

    int opcionMenuCliente = -1;

    do {
        system("clear");
        puts(" ---- CLIENTE ----");
        opcionMenuCliente = seleccionarOpcionMenu(menuModuloCliente, 5);

        switch (opcionMenuCliente) {
            case 1:
                system("clear");
                Cliente auxCliente = NuevoCliente(contadorCliente);
                if (auxCliente.cedula == 0) break;
                listaCliente[contadorCliente++] = auxCliente;
                archivarClientes(listaCliente, contadorCliente);
                puts("Registro Ingresado con exito!!!");
                clean_stdin();
                break;
            case 4:
                system("clear");
                imprimirListaClientes(listaCliente, contadorCliente);
                clean_stdin();
                break;
        }
    } while (opcionMenuCliente != 5);
}

void imprimirListaClientes(Cliente listaClientes[], int sizeListaClientes) {

    puts("\t\t\t ** Lista Clientes **");
    puts("_________________________________________________________________________________________________________");
    printf("| %2s | %20s \t | %10s \t | %10s \t | %20s \t |\n", "ID_CLIENT", "NOMBRES", "CEDULA/RUC", "TELEFONO", "DIRECCION");
    puts("=========================================================================================================");
    for (int i = 0; i < sizeListaClientes; i++) {
        printf("|     %02d    | %20s \t | %10d \t | %10s \t | %20s \t \n",
                listaClientes[i].id, listaClientes[i].nombres,
                listaClientes[i].cedula, listaClientes[i].telefono,
                listaClientes[i].direccion);
    }
}

Cliente buscarClienteByID(Cliente listaClientes[], int sizeListaClientes, int idCliente) {

    Cliente clienteEncontrado = {0};
    for (int i = 0; i < sizeListaClientes; i++) {
        if (idCliente == listaClientes[i].id) {
            clienteEncontrado = listaClientes[i];
            break;
        }
    }
    return clienteEncontrado;
}

Cliente NuevoCliente(int contCliAux) {
    Cliente cliAux = {0};
    cliAux.id = contCliAux;

    int registrarCliente = NO;

    do {
        printf("INGRESE LA INFORMACION DEL CLIENTE \n\n");
        printf("CEDULA/RUC: ");
        clean_stdin_dontStop();
        scanf("%d", &cliAux.cedula);

        printf("NOMBRE Y APELLIDO: ");
        clean_stdin_dontStop();
        scanf("%[^\n]", &cliAux.nombres);

        printf("TELEFONO: ");
        clean_stdin_dontStop();
        scanf("%s", &cliAux.telefono);

        printf("DIRECCION: ");
        clean_stdin_dontStop();
        scanf("%[^\n]", &cliAux.direccion);

        printf("\nConfirmar Registro?, 1 [SI], 0 [Cancelar y Salir], cualquier tecla [Modificar]: ");
        clean_stdin_dontStop();
        scanf("%d", &registrarCliente);
        if (registrarCliente == 1) registrarCliente = SI;
        if (registrarCliente == 0) {
            cliAux.cedula = 0;
        }
    } while (registrarCliente = NO);
    return (cliAux);
}

Cliente *eliminarCliente(int idCliente, Cliente *listaClientes, int sizeListaClientes) {

    Cliente auxNuevaListaClientes[] = {0};
    for (int i = 0; i < sizeListaClientes; i++) {
        if (listaClientes[i].id != idCliente)
            auxNuevaListaClientes[i] = listaClientes[i];
    }

    return auxNuevaListaClientes;
}
