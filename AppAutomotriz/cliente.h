/* 
 * File:   cliente.h
 * Author: Buho
 *
 * Created on February 6, 2020, 11:35 PM
 */

#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct {
    int id;
    int cedula;
    char nombres[20];
    char telefono[13];
    char direccion[20];
} Cliente;

extern Cliente listaCliente[100];
extern int contadorCliente;

Cliente NuevoCliente(int contCliAux);
void imprimirListaClientes(Cliente listaClientes[], int sizeListaClientes);
Cliente buscarClienteByID(Cliente listaClientes[], int sizeListaClientes, int idCliente);
void moduloCliente();

Cliente *eliminarCliente(int idCliente, Cliente *listaClientes, int sizeListaClientes);

void cargarClientes();
#endif /* CLIENTE_H */

