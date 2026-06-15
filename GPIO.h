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
 *  Archivo:        Archivo de cabecera del módulo GPIO
 *
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


#ifndef GPIO_H                                                                                      /*  Verificar si GPIO_H no ha sido definido previamente */
#define GPIO_H                                                                                      /*  Definir GPIO_H para evitar inclusiones múltiples del mismo archivo */


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */
#include <tm4c1294ncpdt.h>


/**************************************************************************************************
 *  Prototipos de funciones
 */

void GPIO_PortE_Init();                                                                             /*  Inicialización y configuración del puerto GPIO E */
void GPIO_PortK_Init();                                                                             /*  Inicialización y configuración del puerto GPIO K */
void GPIO_PortN_Init();
void GPIO_PortL_Init();
void GPIO_PortL_Disable();

#endif                                                                                              /*  GPIO_H */
