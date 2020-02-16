#include "stdio.h"
#include "stdlib.h"

#include "auto.h"
#include "cliente.h"
#include "fichero.h"
#include "factura.h"

void archivarClientes(Cliente lista[100], int sizeClientes) {

    FILE *archivo;
    archivo = fopen("clientes.db", "w");

    if (archivo) {
        fwrite(lista, sizeof (Cliente), sizeClientes, archivo);
        fclose(archivo);
    }
}

void cargarClientesDeFichero() {

    FILE *archivo = fopen("clientes.db", "r");
    Cliente auxCliente = {0};
    if (archivo != NULL) {
        fread(&auxCliente, sizeof (Cliente), 1, archivo);
        while (!feof(archivo)) {
            if (auxCliente.cedula != 0) {
                listaCliente[contadorCliente++] = auxCliente;
            }
            fread(&auxCliente, sizeof (Cliente), 1, archivo);
        }
    } else {
        printf("Error al abrir el archivo \n");
        exit(1);
    }
    fclose(archivo);
}

