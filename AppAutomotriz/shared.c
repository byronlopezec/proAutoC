#include <stdio.h>
#include <time.h>

#include "auto.h"

char * getDate() {
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];
    char * fecha;
    strftime(output, 128, "%d/%m/%y %H:%M:%S", tlocal);
    fecha = output;
    return fecha;

}

void clean_stdin_dontStop(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void clean_stdin(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
    printf("\nContinuar...");
    getchar();
}

int seleccionarOpcionMenu(char *menu[], int numeroOpcionesMenu) {

    int opcionMenu;
    for (int i = 0; i < numeroOpcionesMenu; i++) {
        printf("\n%d. %s", i + 1, menu[i]);
    }
    printf("\nSeleccione una opcion: ");
    fflush(stdin);
    scanf("%d", &opcionMenu);

    return opcionMenu;

}