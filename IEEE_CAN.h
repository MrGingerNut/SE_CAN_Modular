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
 *  Archivo:        Archivo de cabecera del módulo CAN
 *
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/

#ifndef CAN_H                                                                                       /*  Verificar si CAN_H no ha sido definido previamente */
#define CAN_H                                                                                       /*  Definir CAN_H para evitar inclusiones múltiples del mismo archivo */
uint64_t Rx[5];

/**************************************************************************************************
 *  Archivos de cabecera
 */

#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */
#include <stdbool.h>
#include </home/felix/ti/tm4c1294ncpdt.h>

/**************************************************************************************************
 *  Prototipos de funciones
 */

void CAN_Init();                                                                               /*  Inicialización y configuración del ADC_0, SS_3 */
uint64_t CAN_Rx(uint8_t ObjNo);
void CAN_Tx(uint64_t NoObj);
void CAN_Memoria_CtrlMsk(uint16_t Mask, uint8_t DatoL, bool TXIE, bool RXIE, bool RMTEN, uint8_t ObjNo);
void CAN_Memoria_Arb(uint16_t ID, bool TxRx, uint8_t ObjNo);
void CAN_Memoria_Dato(uint64_t Dato, uint8_t NoObj);
void Config_Puertos(void);
void Config_CAN(void);

#endif                                                                                              /*  CAN_H */
