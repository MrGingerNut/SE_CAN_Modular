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
 *  Archivo:        Archivo de cabecera del módulo SPI
 *
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


#ifndef NVIC_H                                                                                      /*  Verificar si NVIC_H no ha sido definido previamente */
#define NVIC_H                                                                                      /*  Definir NVIC_H para evitar inclusiones múltiples del mismo archivo */

/**************************************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */
#include </home/felix/ti/tm4c1294ncpdt.h>

/**************************************************************************************************
 *  Prototipos de funciones
 */

void UART0_Handler(void);                                                                           /*  Rutina de servicio de interrupción (ISR) del UART0 */
void GPIO_PortJ_Handler(void);                                                                      /*  Rutina de servicio de interrupción (ISR) del GPIO PortJ */


#endif                                                                                              /*  NVIC_H */
