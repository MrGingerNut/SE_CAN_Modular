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

#ifndef SSI_H                                                                                       /*  Verificar si SSI_H no ha sido definido previamente */
#define SSI_H                                                                                       /*  Definir SSI_H para evitar inclusiones múltiples del mismo archivo */


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */
#include </home/felix/ti/tm4c1294ncpdt.h>

/**************************************************************************************************
 *  Prototipos de funciones
 */

void SSI0_Init();                                                                               /*  Inicialización y configuración del SSI 0 */
void SSI1_Init();                                                                               /*  Inicialización y configuración del SSI 1*/


#endif                                                                                              /*  SSI_H */
