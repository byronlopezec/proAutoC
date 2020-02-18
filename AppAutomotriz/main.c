/* 
 * File:   main.c
 * Author: Grupo 2
 *
 * Created on 26 de noviembre de 2019, 13:05
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "shared.h"
#include "cliente.h"
#include "auto.h"
#include "compra.h"
#include "factura.h"
#include "fichero.h"

char *menuModuloPrincipal[] = {
    "MODULO CLIENTE",
    "MODULO AUTO",
    "MODULO COMPRAS",
    "SALIR"
};

int main(void) {
    system("COLOR 71");
    int opcionMenuPrincipal = -1;
    cargarClientesDeFichero();
    cargarAutosDeFichero();
    cargarFacturasDeFichero();

    do {
        system("clear");
        puts("--------------------------BIENVENIDO A SU CONCESIONARIA-------------");

        opcionMenuPrincipal = seleccionarOpcionMenu(menuModuloPrincipal, 4);

        switch (opcionMenuPrincipal) {
            case 1:
                moduloCliente();
                break;
            case 2:
                moduloAuto();
                break;
            case 3:
                moduloCompra();
                break;
            case 4:
                printf("Gracias por usar nuestro software");
                break;
            default:
                puts("Opcion invalida!");
                clean_stdin();
                break;
        }

    } while (opcionMenuPrincipal != 4);
    return (0);
}

