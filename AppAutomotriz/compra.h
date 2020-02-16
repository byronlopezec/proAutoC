/* 
 * File:   compra.h
 * Author: Buho
 *
 * Created on February 8, 2020, 11:34 PM
 */

#ifndef COMPRA_H
#define COMPRA_H

struct Producto {
    int idProducto;
    char *nombre;
    float precio;
};

struct Detalle {
    int idDetalle;
    struct Producto producto;
    int cantidad;
    float precioTotal;
};

extern struct Detalle listaDetalles[20];
extern int contadorDetalle;


void moduloCompra();
void compraAuto();
void compraRepuestosServicios();
void finalizarCompra();
void imprimirFactura();
struct Detalle detalleDeCompraProducto(int opcionMenuRepuestosServicios);
void imprimirDetalle(struct Detalle details[], int sizeDetails);

#endif /* COMPRA_H */

