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
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/


/**************************************************************************************************
 *  Archivos de cabecera
 */
#include <stdint.h>                                                                                 /*  Tipos enteros con tamaños fijos */
#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "NVIC.h"                                                                                   /*  Archivo de cabecera del módulo NVIC */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */
#include "UART.h"                                                                                   /*  Archivo de cabecera del módulo UART */
#include "ADC.h"                                                                                    /*  Archivo de cabecera del módulo ADC */
//#include "GPTM.h"                                                                                   /*  Archivo de cabecera del módulo GPTM */
//#include "SSI.h"                                                                                    /*  Archivo de cabecera del módulo SPI */
#include "VarVEL.h"

/**************************************************************************************************
 *  Variables globales
 */
int i=0;
int sp20[256], sp40[256], sp50[256], sp60[256], sp70[256], sp80[256], sp90[256];
volatile uint8_t speed_a=0, speed_b=0, seguidor;

/**************************************************************************************************
 *  Función principal
 */

int main(void) {

    GPIO_PortE_Init();                                                                              /*  Inicialización y configuración del puerto GPIO E */
//    GPIO_PortL_Init();
//    GPIO_PortK_Init();                                                                              /*  Inicialización y configuración del puerto GPIO K */
    UART7_Init();                                                                                   /*  Inicialización y configuración del UART7 */
    SSI0_Init();                                                                                    /*  Inicialización y configuración del SSI0 */
    SSI1_Init();                                                                                    /*  Inicialización y configuración del SSI1 */
//    ADC0_SS2_Init();                                                                                /*  Inicialización y configuración del ADC0 SS2 */
    GPTM3_Init();                                                                                   /*  Inicialización y configuración del GPTM 3 */

for(i=0; i<256;i++){
        if(i < 51){
            sp20[i] = 255;
        } else {
            sp20[i] = 0;
        }

        if(i < 102){
            sp40[i] = 255;
        } else {
            sp40[i] = 0;
        }
        if(i < 127){
            sp50[i] = 255;
        } else {
            sp50[i] = 0;
        }
        if(i < 153){
            sp60[i] = 255;
        } else {
            sp60[i] = 0;
        }
        if(i < 180){
            sp70[i] = 255;
        } else {
            sp70[i] = 0;
        }
        if(i < 204){
            sp80[i] = 255;
        } else {
            sp80[i] = 0;
        }
        if(i < 231){
            sp90[i] = 255;
        } else {
            sp90[i] = 0;
        }
    }

    while (1);
}
