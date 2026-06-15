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
 *  Archivo:        Archivo fuente del módulo GPTM
 *
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/

/**************************************************************************************************
 *  Archivos de cabecera
 */

#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "NVIC.h"                                                                                   /*  Archivo de cabecera del módulo NVIC */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */
#include "GPTM.h"                                                                                   /*  Archivo de cabecera del módulo GPTM */

/**************************************************************************************************
 *  Variables externas (parámetros)
 */


/**************************************************************************************************
 *  Funciones
 */

/************************************************
 *  Función:        TIMER3_Init
 *
 *  Descripción:    Inicialización y configuración del TIMER 3.
 */



void GPTM3_Init(void){

    SYSCTL_RCGCTIMER_R |= 0X08; //RELOJ Y HABILITA TIMER 3 (p.380)
    while (!(SYSCTL_PRTIMER_R & 0x08));

    TIMER3_CTL_R=0X00000000; //deshabilita para configurar
    TIMER3_CFG_R= 0X00000000; //configura el timer a 32 bits
    TIMER3_TAMR_R= 0X00000012; //configura timer periodico con cuenta hacia arriba
    TIMER3_TAILR_R  = 479; //valor de carga
    TIMER3_TAPR_R= 0X00; //preescalador

    TIMER3_ICR_R= 0X00000001; //limpia interrupcion
    TIMER3_IMR_R |= 0X00000001; //desenmascara interrupcion por timeout
    NVIC_EN1_R |= 1<<(35-32); // establece la interrupcion

    TIMER3_CTL_R |= 0X00000001; // habilita el timer
}
