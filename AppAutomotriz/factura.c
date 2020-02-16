#include "stdio.h"
#include "stdlib.h"
//------------------
#include "cliente.h"
#include "shared.h"
#include "compra.h"
#include "factura.h"
//--------------------------------

#define IVA 0.12

void moduloFacturacion() {

    system("clear");
    imprimirTablaFacturas(listaFacturas, contadorFactura);


    clean_stdin();
}

float calcularPrecioFinalDetalles(Detalle listaDetalles[], int contadorDetalle) {

    float totalPrecioAPagar = 0.0;

    for (int i = 0; i < contadorDetalle; i++) {
        totalPrecioAPagar += listaDetalles[i].precioTotal; // i = i +a; --> i+=a;
    }
    totalPrecioAPagar += (IVA * totalPrecioAPagar);

    return totalPrecioAPagar;
}

void imprimirTablaFacturas(Factura listaFacturas[], int sizeListaFacturas) {

    int opcionIdFactura = -1;
    do {
        system("clear");
        puts(" \t\t\t\t*** F A C T U R A S *** ");
        puts("_______________________________________________________________________________________________");
        printf("| %4s | %10s | %20s | %10s | %10s | %10s \n", "ID_FACTURA", "C.I. CLIEN", "NOMBRE CLIENTE", "      FECHA      ", "CANT. DET.", "TOTAL");
        puts("===============================================================================================");
        for (int i = 0; i < sizeListaFacturas; i++) {
            printf("|     %02d     | %10d | %20s | %17s |     %02d     | $ %.2f\n",
                    listaFacturas[i].id,
                    listaFacturas[i].cliente.cedula,
                    listaFacturas[i].cliente.nombres,
                    listaFacturas[i].fecha,
                    listaFacturas[i].sizeDetalles,
                    listaFacturas[i].precioFinalPagar);
        }
        printf("\n Ingrese un ID FACTURA ( -1 [CANCELAR] ]): ");
        fflush(stdin);
        scanf("%d", &opcionIdFactura);

        if (opcionIdFactura == -1) break;

        Factura auxFactura = buscarFacturaByID(listaFacturas, contadorFactura, opcionIdFactura);

        if (auxFactura.sizeDetalles != 0) {
            imprimirFactura(auxFactura);
            continue;
        }

        printf("\n Factura con el ID: %d no existe!!", opcionIdFactura);
    } while (opcionIdFactura == -1);
}

void imprimirFactura(Factura factura) {

    system("clear");
    puts("\t\t\t\t **** F A C T U R A **** ");
    printf("===============================================================================\n");
    printf(" PRO AUT GRUPO 2 S.A \t\t\t\tRUC: 1751201234001\n");
    printf(" GRUPO 2 S.A \t\t\t\t AUT.SRI: 1234567890\n");
    printf(" \t\t\t\t\t\t NO. %03d-%03d-1751201234\n", factura.id, factura.cliente);
    puts(" DIRECCION: EPN-ESFOT \t\t\t\t FECHA AUTORIZACION: 18-02-2020");
    puts("__ CLIENTE ____________________________________________________________________");
    printf(" NOMBRES: %s \t\t\t\t R.U.C/C.I.: %d\n", factura.cliente.nombres, factura.cliente.cedula);
    printf(" DIRECCION : %s \t\t\t\t TELEFONO: %s\n", factura.cliente.direccion, factura.cliente.telefono);
    printf(" FECHA EMISION: %10s \t\t\t  _____________________\n", factura.fecha);
    imprimirDetalle(factura.listaDetalles, factura.sizeDetalles);
    puts("_______________________________________________________________________________");
    printf(" %46s SUB TOTAL 0%c IVA | $ %.2f \n", " ", '%', (factura.precioFinalPagar / 1.12));
    printf(" %46s IVA 12%c          | $ %.2f \n", " ", '%', (factura.precioFinalPagar * 0.12));
    printf(" %46s TOTAL A PAGAR    | $ %.2f \n", " ", factura.precioFinalPagar);
    puts(" \t _______________________________");
    puts(" \t\tRECIBI CONFORME");
    printf("===============================================================================\n");

    clean_stdin();
}

Factura buscarFacturaByID(Factura facturas[], int sizeFacturas, int idFactura) {

    Factura facturaEncontrada = {0};
    for (int i = 0; i < sizeFacturas; i++) {
        if (idFactura == facturas[i].id) {
            facturaEncontrada = facturas[i];
            break;
        }
    }
    return facturaEncontrada;
}

void archivarFacturas(Factura lista[100], int sizeFacturas) {

    FILE *archivo;
    archivo = fopen("facturas.db", "w");

    if (archivo) {
        fwrite(lista, sizeof (Factura), sizeFacturas, archivo);
        fclose(archivo);
    }
}

void cargarFacturasDeFichero() {

    FILE *archivo = fopen("facturas.db", "r");
    Factura auxFactura = {0};
    if (archivo != NULL) {
        fread(&auxFactura, sizeof (Factura), 1, archivo);
        while (!feof(archivo)) {
            if (auxFactura.sizeDetalles != 0) {
                listaFacturas[contadorFactura++] = auxFactura;
            }
            fread(&auxFactura, sizeof (Factura), 1, archivo);
        }
    } else {
        printf("Error al abrir el archivo \n");
        exit(1);
    }
    fclose(archivo);
}