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
 *  Archivo:        Archivo fuente del módulo UART
 *
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/

/**************************************************************************************************
 *  Archivos de cabecera
 */

#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "NVIC.h"                                                                                   /*  Archivo de cabecera del módulo NVIC */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */
#include "UART.h"                                                                                   /*  Archivo de cabecera del módulo GPTM */

/**************************************************************************************************
 *  Variables externas (parámetros)
 */


/**************************************************************************************************
 *  Funciones
 */

/************************************************
 *  Función:        UART7_Init
 *
 *  Descripción:    Inicialización y configuración del UART7.
 */

void UART7_Init(void){

    SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R7;
    SYSCTL_RCGCGPIO_R |= (1 << 2);

    while((SYSCTL_PRUART_R & SYSCTL_PRUART_R7) == 0);
    while((SYSCTL_PRGPIO_R & (1 << 2)) == 0);

    UART7_CTL_R = 0x00;  // Deshabilita UART completamente

    SYSCTL_ALTCLKCFG_R = (SYSCTL_ALTCLKCFG_R & ~SYSCTL_ALTCLKCFG_ALTCLK_M) | SYSCTL_ALTCLKCFG_ALTCLK_PIOSC;
    UART7_CC_R = (UART7_CC_R & ~UART_CC_CS_M) | UART_CC_CS_PIOSC;

    UART7_IBRD_R = 104;
    UART7_FBRD_R = 10;

    UART7_LCRH_R = (UART_LCRH_WLEN_8 | UART_LCRH_FEN);

    UART7_IFLS_R &= (UART7_IFLS_R & ~0X3F) | 0X00;
    UART7_ICR_R = 0xFFFF;
    UART7_IM_R |= 0x30;  // Solo interrupción RX

    UART7_CTL_R &= ~0x20;
    UART7_CTL_R |= 0x01;

//    while((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R0)==0);

    // Configura GPIO PC4-PC5 para UART7
    GPIO_PORTC_AHB_AFSEL_R |= 0x30;
    GPIO_PORTC_AHB_DEN_R |= 0x30;
    GPIO_PORTC_AHB_PCTL_R = (GPIO_PORTC_AHB_PCTL_R & 0xFF00FFFF) | 0x00110000;
    GPIO_PORTC_AHB_AMSEL_R &= ~0x30;

    UART7_CTL_R = UART_CTL_UARTEN | UART_CTL_TXE | UART_CTL_RXE;  // Habilita UART, TX, RX

    NVIC_PRI15_R = (NVIC_PRI15_R & 0xFFFFFF00) | 0x00;
    NVIC_EN1_R |= 1 << (60 - 32);
}
