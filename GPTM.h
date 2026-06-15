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


#ifndef GPTM_H                                                                                      /*  Verificar si GPTM_H no ha sido definido previamente */
#define GPTM_H                                                                                      /*  Definir GPTM_H para evitar inclusiones múltiples del mismo archivo */


/**************************************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */
#include </home/felix/ti/tm4c1294ncpdt.h>

/************************************************
 *  Bit fields
 */
    //  Bit fields in the TIMER_RIS register                                                            pp.996
#define TIMER_RIS_TBTORIS           0x00000100                                                      /*  GPTM Timer B Time-Out Raw Interrupt */
#define TIMER_RIS_TATORIS           0x00000001                                                      /*  GPTM Timer A Time-Out Raw Interrupt */


/**************************************************************************************************
 *  Prototipos de funciones
 */

void GPTM3_Init();                               /*  Inicialización y configuración del temporizador GPTM0 (subtimer A) en modo one-shot */
void TIMER3_Handler();                               /*  Inicialización y configuración del temporizador GPTM0 (subtimer B) en modo one-shot */


#endif                                                                                              /*  GPTM_H */
