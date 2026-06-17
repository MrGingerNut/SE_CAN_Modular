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

#ifndef IEEE_CAN_H_
#define IEEE_CAN_H_

#include <stdbool.h>
#include <stdint.h>
#include "tm4c1294ncpdt.h"
//#include "IEEE_CAN.c"

/**************************************************************************************************
 *  Identificadores de mensajes CAN (11 bits, formato estándar)
 *
 *  Se usa un único mensaje para el modo del sistema.
 *  El maestro transmite; el esclavo recibe.
 */

void CAN_Memoria_Dato(uint64_t Dato, uint8_t NoObj);
void CAN_Memoria_Arb(uint16_t ID, bool TxRx, uint8_t ObjNo);
void CAN_Memoria_CtrlMsk(uint16_t Mask, uint8_t DatoL, bool TXIE, bool RXIE, bool RMTEN, uint8_t ObjNo);
void CAN_Tx(uint64_t NoObj);
uint64_t CAN_Rx(uint8_t ObjNo);

#endif /* IEEE_CAN_H_ */
