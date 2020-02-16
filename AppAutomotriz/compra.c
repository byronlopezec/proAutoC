#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "string.h"


#include "cliente.h"
#include "shared.h"
#include "compra.h"
#include "factura.h"
#include "auto.h"
#include "fichero.h"


char * menuModuloCompra[] = {
    "Compra Auto",
    "Compra Repuestos y Servicios",
    "Finalizar Compra",
    "Factura",
    "Salir"
};

char * menuRepuestosYServicios[] = {
    "Filtros $5.00",
    "Suspension $69.00",
    "Sistema de encendido $350.00",
    "Sistema electrico $500.00",
    "Embrague $70.00",
    "Transmision $555.00",
    "Servicio Enderezado y Pintura $1000.00",
    "Servicio Mecanica Correctiva $500.00",
    "Servicio Alineacion $300.00",
    "Retroceder"
};

// Constantes Lista de Repuestos y Servicios de Taller
const Producto listaProductos[9] = {
    {1, "Filtros", 5.00},
    {2, "Suspension", 69.00},
    {3, "Sistema de encendido", 350.00},
    {4, "Sistema electrico", 500.00},
    {5, "Embrague", 70.00},
    {6, "Transmision", 555.00},
    {7, "Servicio Enderezado y Pintura", 1000.00},
    {8, "Servicio Mecanica Correctiva", 500.00},
    {9, "Servicio Alineacion", 300.00}
};

int contadorDetalle = 0;
Detalle listaDetalles[20] = {0};

int contadorFactura = 0;
Factura listaFacturas[100] = {0};

void moduloCompra() {

    int opcionMenuCompra = -1;

    do {
        system("clear");
        puts("\t-----Modulo Compra------");

        opcionMenuCompra = seleccionarOpcionMenu(menuModuloCompra, 5);

        switch (opcionMenuCompra) {
            case 1:
                compraAuto();
                break;

            case 2:
                system("clear");
                puts("-------- Compra Repuestos y Servicios --------");
                compraRepuestosServicios();
                break;

            case 3:
                //-------- Finalizar Compra --------
                finalizarCompra();
                break;

            case 4:
                system("clear");
                puts("-------- Factura --------");
                moduloFacturacion();
                break;

            case 5:
                break;

            default:
                puts(" ** Opcion Invalida!!! **");
                break;
        }

    } while (opcionMenuCompra != 5);
}

void compraAuto() {

    Auto autoSeleccionado = {0};
    Detalle auxDetalle = {0};
    int registrarDetalle = -1;
    int opcionId_auto;
    int salirCompraAuto = NO;

    do {
        opcionId_auto = -2;
        system("clear");
        puts("\t\t\t ** COMPRA AUTO ** ");

        if (contadorAuto == 0) {
            puts("No existe autos disponibles!!");
            clean_stdin();
            break;
        }

        imprimirListaAutos(listaAutos, contadorAuto);
        printf("Ingrese ID del auto a comprar (digite -1 para cancelar): ");
        fflush(stdin);
        scanf("%d", &opcionId_auto);

        if (opcionId_auto == -1) break;

        autoSeleccionado = buscarAutoPorID(opcionId_auto, listaAutos, contadorAuto);

        if (autoSeleccionado.id == 0 && autoSeleccionado.marca == NULL) {
            printf("\n Id_auto %d no encontrado!!!! -> Ingresar un ID entre [1-%d]", opcionId_auto, contadorAuto);
            clean_stdin();
            continue;
        }

        auxDetalle.idDetalle = contadorDetalle;
        auxDetalle.producto.idProducto = autoSeleccionado.id;
        auxDetalle.producto.nombre = autoSeleccionado.marca;
        auxDetalle.producto.precio = autoSeleccionado.precio;
        auxDetalle.cantidad = 1;
        auxDetalle.precioTotal = auxDetalle.cantidad * autoSeleccionado.precio;

        Detalle auxListDetails[1] = {auxDetalle};
        imprimirDetalle(auxListDetails, 1);

        printf("\nComprar Auto? (1 [SI],0 [Salir y Cancelar], \n[Precione Cualquier tecla para seguir modificando]): ");
        fflush(stdin);
        scanf("%d", &registrarDetalle);

        if (registrarDetalle == 0) {
            puts("Compra Cancelada!... Regresando...");
            clean_stdin();
            break;
        }

        if (registrarDetalle == 1) {
            listaDetalles[contadorDetalle++] = auxDetalle;
            puts("Compra exitosa!... Regresando...");
            clean_stdin();
            break;
        }
        if (registrarDetalle != 1 && registrarDetalle != 0) {
            clean_stdin();
            continue;
        }

    } while (salirCompraAuto == NO);

}

void imprimirDetalle( Detalle details[], int sizeDetails) {
    puts(" \t\t\t\t*** Detalles *** ");
    puts("_______________________________________________________________________________");
    printf("| %4s \t |%15s \t | %4s  | %8s \t | %8s\n", "ID_DETAIL", "NOMBRE", "CANT", "PRECIO_U", "SUB_TOTAL");
    puts("===============================================================================");
    for (int i = 0; i < sizeDetails; i++) {
        printf("|   %02d   \t |%15s \t |  %02d   | $ %.2f \t | $ %.2f\n",
                details[i].idDetalle, details[i].producto.nombre,
                details[i].cantidad, details[i].producto.precio, details[i].precioTotal);
    }
}

void compraRepuestosServicios() {

    Detalle listaDetalles[10] = {0}; // inicializando a null;
    int opcionMenuRepuestosServicios = -1;
    do {

        system("clear");
        puts("\t\t\t ** Comprar Repuestos y Servicios **");
        opcionMenuRepuestosServicios = seleccionarOpcionMenu(menuRepuestosYServicios, 10);
        Detalle auxDetalle = {0};

        if (opcionMenuRepuestosServicios < 1 || 9 < opcionMenuRepuestosServicios) continue;

        auxDetalle = detalleDeCompraProducto(opcionMenuRepuestosServicios);
        if (auxDetalle.idDetalle == opcionMenuRepuestosServicios) {
            listaDetalles[opcionMenuRepuestosServicios - 1] = auxDetalle;
        }
    } while (opcionMenuRepuestosServicios != 10);
}

Detalle detalleDeCompraProducto(int opcionMenuRepuestosServicios) {

    int auxCantidad = -1;
    Producto temProducto = listaProductos[opcionMenuRepuestosServicios - 1];
    Detalle auxDetalle = {0};

    do {

        system("clear");
        puts(menuRepuestosYServicios[opcionMenuRepuestosServicios - 1]);
        printf("Ingrese una cantidad (digite 0 para cancelar): ");
        fflush(stdin);
        scanf("%d", &auxCantidad);

        if (auxCantidad == 0) break;

        if (0 > auxCantidad || auxCantidad > 100) {
            printf("\nIncorrecto!!!! -> Cantidad permitida [1-100] %d", auxCantidad);
            clean_stdin();
        }

    } while (0 > auxCantidad || auxCantidad > 100);

    if (auxCantidad == 0) return auxDetalle;

    printf("\n%s, Cantidad: %d, Total:  %.2f", temProducto.nombre, auxCantidad, temProducto.precio * auxCantidad);

    auxDetalle.idDetalle = opcionMenuRepuestosServicios;
    auxDetalle.producto = temProducto;
    auxDetalle.cantidad = auxCantidad;
    auxDetalle.precioTotal = temProducto.precio * auxCantidad;

    printf("\nCodigo Detalle: %d, Producto: %s, Cantidad: %d, Total:  %.2f", auxDetalle.idDetalle, auxDetalle.producto.nombre, auxDetalle.cantidad, auxDetalle.precioTotal);
    clean_stdin();

    return auxDetalle;
}

void finalizarCompra() {

    int salir = NO;
    int opcionIdCliente = -1;
    int asociarCliente = -1;

    Cliente clienteEncontrado = {0};
    Factura auxFactura = {0};

    do {
        system("clear");
        if (contadorDetalle == 0) {
            printf("\n No existe ninguna compra en proceso....");
            clean_stdin();
            break;
        }
        puts("\t\t\t\t======= ** Finalizar Compra  ** =========");
        imprimirDetalle(listaDetalles, contadorDetalle);
        puts("\n ______ Asociar cliente _________");
        imprimirListaClientes(listaCliente, contadorCliente);
        printf("\nSeleccione un ID CLIENTE: ");
        scanf("%d", &opcionIdCliente);

        clienteEncontrado = buscarClienteByID(listaCliente, contadorCliente, opcionIdCliente);

        if (clienteEncontrado.id == 0 && clienteEncontrado.cedula == 0) {
            puts("Cliente no encontrado...");
            clean_stdin();
            continue;
        }

        Cliente auxListClientes[1] = {clienteEncontrado};
        imprimirListaClientes(auxListClientes, 1);

        printf("\n Asociar Cliente? (1 [SI],0 [Salir y Cancelar], cualquier tecla [modificar]): ");
        fflush(stdin);
        scanf("%d", &asociarCliente);

        if (asociarCliente == 0) {
            puts("Asociacion Cliente Cancelado!... Regresando...");
            clean_stdin();
            break;
        }

        if (asociarCliente == 1) {

            auxFactura.id = contadorFactura;
            auxFactura.cliente = clienteEncontrado;
            for (int i = 0; i < contadorDetalle; i++) {
                auxFactura.listaDetalles[i] = listaDetalles[i];
            }
            auxFactura.sizeDetalles = contadorDetalle;
            auxFactura.precioFinalPagar = calcularPrecioFinalDetalles(listaDetalles, contadorDetalle);
            strlcpy(auxFactura.fecha, getDate(), 20);
            listaFacturas[contadorFactura++] = auxFactura;
/*
            archivarFacturas(listaFacturas, contadorFactura);
*/

            // -- Limpiar Detalles
            memset(listaDetalles, 0, sizeof ( listaDetalles));
            contadorDetalle = 0;

            puts("\nCompra realizada con exito!!... Imprimiendo Factura!!...");
            clean_stdin();
            imprimirFactura(listaFacturas[contadorFactura - 1]);

            break;
        }
        if (asociarCliente != 1 && asociarCliente != 0) {
            clean_stdin();
            continue;
        }

    } while (salir == NO);
}
