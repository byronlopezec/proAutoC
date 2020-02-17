#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "shared.h"
#include "auto.h"

// ----- MODELOS DE AUTO
char* marcasAuto[] = {"TOYOTA", "CHEVROLET", "MAZDA", "KIA", "MERCEDES BENZ"};
const int sizeMarcasAutos = 5;
// ---- TIPOS DE AUTO
char *tiposAuto[] = {"CUPE", "HATCHBACK", "DESCAPOTABLE", "ROADSTER", "FAMILIAR"};
const int sizeTiposAuto = 5;
// ---- COLORES DE AUTO
char *coloresAuto[] = {"BLANCO", "PLOMO", "ROJO", "AZUL MARINO", "PLATEADO"};
const int sizeColoresAuto = 5;

const float precioMinimoAuto = 10000.00;
const float precioVariaTipo = 2000.00;
const float precioVariaMarca = 300.00;
const float precioVariaColor = 100.00;

char *menuModuloAuto[] = {
    "Nuevo Auto",
    "Modificar Auto",
    "Eliminar Auto",
    "Listar Auto",
    "Retroceder"
};
char *menuNuevoAuto[] = {
    "MARCA",
    "TIPO",
    "COLOR",
    "PRECIO",
    "RETROCEDER"
};


// Variables Externas usadas en otros archivos
Auto listaAutos[100] = {0};
int contadorAuto = 0;

void moduloAuto() {
    int opcionMenuAuto = -1, opcionMenuNuevoAuto = -1, registrar = -1;


    do {
        system("clear");
        puts("----- MODULO AUTO ------");
        opcionMenuAuto = seleccionarOpcionMenu(menuModuloAuto, 5);
        Auto auxAuto = {0};

        switch (opcionMenuAuto) {
            case 1:
                do {
                    system("clear");
                    printf("-----NUEVO VEHICULO------");
                    opcionMenuNuevoAuto = seleccionarOpcionMenu(menuNuevoAuto, 5);

                    switch (opcionMenuNuevoAuto) {
                        case 1:
                            auxAuto.marca = seleccionarCaracteristicaAuto(marcasAuto, sizeMarcasAutos, "Marca");
                            break;

                        case 2:
                            auxAuto.tipo = seleccionarCaracteristicaAuto(tiposAuto, sizeTiposAuto, "Tipo");
                            break;
                        case 3:
                            auxAuto.color = seleccionarCaracteristicaAuto(coloresAuto, sizeColoresAuto, "Color");
                            break;

                        case 4:
                            system("clear");
                            puts("*** Precio Nuevo Auto ***");
                            auxAuto.precio = calcularPrecioAuto(auxAuto);

                            printf("\nMarca: %s", auxAuto.marca);
                            printf("\nTipo: %s", auxAuto.tipo);
                            printf("\nColor: %s", auxAuto.color);
                            printf("\nPrecio: $ %.2f \n______\n", auxAuto.precio);

                            printf("\nRegistrar Auto? (1 [SI],0 [Salir y Cancelar], \n[Precione Cualquier tecla para seguir modificando]): ");
                            fflush(stdin);
                            scanf("%d", &registrar);

                            if (registrar == 1) {
                                if (auxAuto.marca == NULL || auxAuto.color == NULL || auxAuto.tipo == NULL) {
                                    puts("\nDebe completar todos los campos para registrar Auto--Error!!!");
                                    clean_stdin();
                                    break;
                                }
                                auxAuto.id = contadorAuto;
                                listaAutos[contadorAuto++] = auxAuto;
                                archivarAutos(listaAutos, contadorAuto);
                                puts("\nRegistro exitoso!!!");
                                clean_stdin();
                                opcionMenuNuevoAuto = 5;
                                break;
                            }
                            if (registrar == 0) {
                                opcionMenuNuevoAuto = 5;
                                puts("Registro Cancelado...");
                                clean_stdin();
                            }

                            break;

                    }
                } while (opcionMenuNuevoAuto != 5);
                break;

            case 2:
                printf("\n\t\t\t ** MODIFICAR AUTO **\n");
                modificarAuto();

                break;
            case 3:
                system("clear");
                puts("\n\t\t\t ** ELIMINAR AUTO **");
                int opcionIDauto = -1;
                imprimirListaAutos(listaAutos, contadorAuto);
                printf("\n Seleccione ID del auto: ");
                fflush(stdin);
                scanf("%d", &opcionIDauto);
                eliminarDatosAuto(listaAutos, &contadorAuto, opcionIDauto);
                archivarAutos(listaAutos, contadorAuto);
                clean_stdin();
                break;
            case 4:

                imprimirListaAutos(listaAutos, contadorAuto);
                clean_stdin();
                break;
        }
    } while (opcionMenuAuto != 5);
}

void eliminarDatosAuto(Auto autos[], int* contadorAuto, int idAuto) {
    for (int p = idAuto; p<*contadorAuto - 1; p++) {
        autos[p] = autos[p + 1];
        autos[p].marca = autos[p + 1].marca;
        autos[p].tipo = autos[p + 1].tipo;
        autos[p].color = autos[p + 1].color;
        autos[p].precio = autos[p + 1].precio;
    }
    *contadorAuto = *contadorAuto - 1;
}

void modificarAuto() {

    int opcionIDauto = -1;
    Auto auxAuto = {0};

    system("clear");
    puts("\t\t\t *** MODIFICAR AUTO ***");
    imprimirListaAutos(listaAutos, contadorAuto);
    printf("\n Seleccione ID del auto: ");
    clean_stdin_dontStop();
    scanf("%d", &opcionIDauto);

    auxAuto = buscarAutoPorID(opcionIDauto, listaAutos, contadorAuto);

    if (auxAuto.marca != NULL) {

        auxAuto.marca = seleccionarCaracteristicaAuto(marcasAuto, sizeMarcasAutos, "Marca");
        auxAuto.tipo = seleccionarCaracteristicaAuto(tiposAuto, sizeTiposAuto, "Tipo");
        auxAuto.color = seleccionarCaracteristicaAuto(coloresAuto, sizeColoresAuto, "Color");
        system("clear");
        puts("*** Precio Auto ***");
        auxAuto.precio = calcularPrecioAuto(auxAuto);

        printf("\n Modifcar auto %d ", opcionIDauto);
        printf("\nMarca: %s", auxAuto.marca);
        printf("\nTipo: %s", auxAuto.tipo);
        printf("\nColor: %s", auxAuto.color);
        printf("\nPrecio: $ %.2f \n______\n", auxAuto.precio);

        for (int i = 0; i < contadorAuto; i++) {
            if (auxAuto.id == listaAutos[i].id) {
                listaAutos[i] = auxAuto;
                archivarAutos(listaAutos, contadorAuto);
                printf("\n Auto %d modificado exitosamente!!!", listaAutos[i].id);
                clean_stdin();
                break;
            }
        }
    }
}

Auto buscarAutoPorID(int idAuto, Auto listaAutos[], int contadorAutos) {

    Auto autoEncontrado = {0};
    for (int i = 0; i < contadorAutos; i++) {
        if (idAuto == listaAutos[i].id) {
            autoEncontrado = listaAutos[i];
            break;
        }
    }
    return autoEncontrado;
}

float calcularPrecioAuto(Auto nuevoAuto) {
    float precioAuto = precioMinimoAuto;

    int posicionMarca = 0; // $ 200
    int posicionTipo = 0; // $ 1000
    int posicionColor = 0; // $100

    // Caracteristicas --Marcas,--Color, --Tipo
    for (int i = 0; i < sizeMarcasAutos; i++) {
        if (nuevoAuto.marca == marcasAuto[i]) {
            posicionMarca = i;
            break;
        }
    }
    // Caracteristicas --Marcas,--Color, --Tipo
    for (int i = 0; i < sizeTiposAuto; i++) {
        if (nuevoAuto.tipo == tiposAuto[i]) {
            posicionTipo = i;
            break;
        }
    }
    // Caracteristicas --Marcas,--Color, --Tipo
    for (int i = 0; i < sizeColoresAuto; i++) {
        if (nuevoAuto.color == coloresAuto[i]) {
            posicionColor = i;
            break;
        }
    }

    precioAuto = precioAuto + posicionColor * precioVariaColor + posicionMarca * precioVariaMarca + posicionTipo * precioVariaTipo;

    return precioAuto;
};

char *seleccionarCaracteristicaAuto(char *listaCaracteristica[], int tamanioCaracteristicas, char *nombreCaracteristica) {
    int opcion = -1;
    int salir = NO; // 1 SI, 0 NO

    do {
        system("clear");
        printf("====== Seleccionar %s =======\n", nombreCaracteristica);

        for (int i = 0; i < tamanioCaracteristicas; i++) {
            printf("%d.%s\n", i + 1, listaCaracteristica[i]);
        }
        printf("%d.REGRESAR", tamanioCaracteristicas + 1);
        printf("\n\nSeleccione %s del auto: ", nombreCaracteristica);
        fflush(stdin); //vaciar buffer, prevenir error de scanf
        scanf("%d", &opcion);

        if (opcion < 1 || tamanioCaracteristicas + 1 < opcion) continue;
        salir = SI;

    } while (salir == NO);

    if (opcion == tamanioCaracteristicas + 1) return ""; //regresar
    printf("\n Su marca de auto seleccionado es: %s", listaCaracteristica[opcion - 1]);
    clean_stdin();
    return (listaCaracteristica[opcion - 1]);
}

void imprimirListaAutos(Auto listaAutos[], int contadorAuto) {
    system("clear");
    puts(" \t\t\t\t*** AUTOS REGISTRADOS *** ");
    puts("_____________________________________________________________________________________________");
    printf("| %2s \t |%15s \t | %12s \t | %12s \t | %9s\n", "ID", "MARCA", "TIPO", "COLOR", "PRECIO");
    puts("=============================================================================================");
    for (int j = 0; j < contadorAuto; j++) {
        printf("| %02d \t |%15s \t | %12s \t | %12s \t | $ %.2f\n", listaAutos[j].id, listaAutos[j].marca, listaAutos[j].tipo, listaAutos[j].color, listaAutos[j].precio);
    }
    puts("---------------------------------------------------------------------------------------------");

}

void archivarAutos(Auto lista[100], int sizeAutos) {

    FILE *archivo;
    archivo = fopen("autos.db", "w");

    if (archivo) {
        fwrite(lista, sizeof (Auto), sizeAutos, archivo);
        fclose(archivo);
    }
}

void cargarAutosDeFichero() {

    FILE *archivo = fopen("autos.db", "r");
    Auto auxAuto = {0};
    if (archivo != NULL) {
        fread(&auxAuto, sizeof (Auto), 1, archivo);
        while (!feof(archivo)) {
            if (auxAuto.marca != NULL) {
                listaAutos[contadorAuto++] = auxAuto;
            }
            fread(&auxAuto, sizeof (Auto), 1, archivo);
        }
    } else {
        printf("Error al abrir el archivo \n");
        exit(1);
    }
    fclose(archivo);
}
