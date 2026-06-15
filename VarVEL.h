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
 *  Archivo:        Archivo de cabecera para variables 
 *
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/

#ifndef VARVEL_H_                                                                                   /*  Verificar si SYSCTL_H no ha sido definido previamente */
#define VARVEL_H_                                                                                   /*  Definir SYSCTL_H para evitar inclusiones múltiples del mismo archivo */

extern int sp20[256], sp40[256], sp50[256], sp60[256], sp70[256], sp80[256], sp90[256];
extern volatile uint8_t speed_a, speed_b, seguidor;
extern volatile uint32_t BotonPK;

/**************************************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */
#include <tm4c1294ncpdt.h>

/**************************************************************************************************
 *  Prototipos de funciones
 */


#endif /* VARVEL_H_ */
