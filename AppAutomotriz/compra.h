/* 
 * File:   compra.h
 * Author: Buho
 *
 * Created on February 8, 2020, 11:34 PM
 */

#ifndef COMPRA_H
#define COMPRA_H

typedef struct {
    int idProducto;
    char *nombre;
    float precio;
} Producto;

typedef struct {
    int idDetalle;
    Producto producto;
    int cantidad;
    float precioTotal;
} Detalle;

extern Detalle listaDetalles[20];
extern int contadorDetalle;


void moduloCompra();
void compraAuto();
void compraRepuestosServicios();
void finalizarCompra();
void imprimirFactura();
Detalle detalleDeCompraProducto(int opcionMenuRepuestosServicios);
void imprimirDetalle(Detalle details[], int sizeDetails);

#endif /* COMPRA_H */

