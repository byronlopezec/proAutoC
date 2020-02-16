/* 
 * File:   factura.h
 * Author: Buho
 *
 * Created on February 9, 2020, 11:34 AM
 */

#ifndef FACTURA_H
#define FACTURA_H

typedef struct {
    int id;
    Cliente cliente;
    int sizeDetalles;
    char fecha[20];
    float precioFinalPagar;
    Detalle listaDetalles[20];
} Factura;

extern int contadorFactura;
extern Factura listaFacturas[100];


void moduloFacturacion();
float calcularPrecioFinalDetalles(Detalle listaDetalles[], int contadorDetalle);

//void archivarFacturas(Factura lista[100], int sizeFacturas);
//void cargarFacturasDeFichero();

#endif /* FACTURA_H */

