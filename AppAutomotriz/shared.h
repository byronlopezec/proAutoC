/* 
 * File:   shared.h
 * Author: Buho
 *
 * Created on February 7, 2020, 11:09 PM
 */

#ifndef SHARED_H
#define SHARED_H

#define SI 1
#define NO 0

void clean_stdin();
void clean_stdin_dontStop(void);
char * getDate();
int seleccionarOpcionMenu(char *menu[], int numeroOpcionesMenu);

#endif /* SHARED_H */

