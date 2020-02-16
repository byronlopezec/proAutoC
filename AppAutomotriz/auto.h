/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   auto.h
 * Author: Buho
 *
 * Created on February 6, 2020, 11:50 PM
 */

#ifndef AUTO_H
#define AUTO_H

typedef struct Auto {
    int id;
    char *marca;
    char *color;
    char *tipo;
    float precio;
} Auto;

extern Auto listaAutos[100];
extern int contadorAuto;


void moduloAuto();
void imprimirListaAutos(Auto listaAutos[], int contadorAuto);
char *seleccionarCaracteristicaAuto(char *listaCaracteristica[], int tamanioCaracteristicas, char *nombreCaracteristica);
float calcularPrecioAuto(Auto nuevoAuto);
Auto buscarAutoPorID(int idAuto, Auto listaAutos[], int contadorAutos);


void archivarAutos(Auto lista[100], int sizeAutos);
void cargarAutosDeFichero();

#endif /* AUTO_H */

