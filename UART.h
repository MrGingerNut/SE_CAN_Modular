/**************************************************************************************************
 *  Universidad Nacional Autónoma de México (UNAM)
 *  Facultad de Ingeniería | Departamento de Electrónica
 *
 *  Asignatura:     Sistemas Embebidos
 *  Profesor:       Dr. Saúl de la Rosa Nieves
 *
 *  Tema:           CAN y Periféricos
 *  Descripción:
 *
 *  Archivo:        Archivo de cabecera del módulo GPTM
 *
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


#ifndef UART_H                                                                                      /*  Verificar si UART_H no ha sido definido previamente */
#define UART_H                                                                                      /*  Definir UART_H para evitar inclusiones múltiples del mismo archivo */


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */
#include </home/felix/ti/tm4c1294ncpdt.h>

/**************************************************************************************************
 *  Prototipos de funciones
 */

void UART7_Init();                                                                                  /*  Inicialización y configuración del UART0 */


#endif                                                                                              /*  UART_H */
