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
 *  Archivo:        Archivo fuente del módulo SPI
 *
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/

/**************************************************************************************************
 *  Archivos de cabecera
 */


#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "NVIC.h"                                                                                   /*  Archivo de cabecera del módulo NVIC */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */
#include "SSI.h"                                                                                 /*  Archivo de cabecera del módulo SPI */

/**************************************************************************************************
 *  Variables externas (parámetros)
 */


/**************************************************************************************************
 *  Funciones
 */

/************************************************
 *  Función:        SSI0_Init
 *
 *  Descripción:    Inicialización y configuración del SPI0.
 */

void SSI0_Init(void){

    SYSCTL_RCGCSSI_R |= SYSCTL_RCGCSSI_R0; // Activa reloj al SSI0
    while ((SYSCTL_PRSSI_R & SYSCTL_PRSSI_R0) == 0); // Espera a que este listo
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0; // Activa reloj del GPIO A
    while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R0) == 0); // Espera a que este listo // 0b00111100

    GPIO_PORTA_AHB_AFSEL_R |= 0x3C; // Seleciona la función alterna de PA[2:5].
    GPIO_PORTA_AHB_PCTL_R = (GPIO_PORTA_AHB_PCTL_R & 0XFF0000FF) | 0x00FFFF00; // Configura las terminales de PA a su función de SSI0.
    GPIO_PORTA_AHB_AMSEL_R = 0x00; // Deshabilita la función analogica
    GPIO_PORTA_AHB_DIR_R = (GPIO_PORTA_AHB_DIR_R & ~0x3C) | 0x1C; // Configura al puerto como salida
    GPIO_PORTA_AHB_DEN_R |= 0x3C; // Habilita la función digital del puerto

    SSI0_CR1_R = 0x00; // Selecciona modo maestro/deshabilita SSI0. (p. 1247)
    SSI0_CPSR_R = 0x02; // preescalador (CPSDVSR) del reloj SSI (p. 1252)
    // configura para Freescale SPI; 16bit; 4 Mbps; SPO = 0; SPH = 0 (p. 1245)
    SSI0_CR0_R = (0x0100 | SSI_CR0_FRF_MOTO | SSI_CR0_DSS_16) & ~(SSI_CR0_SPO | SSI_CR0_SPH);
    SSI0_CR1_R |= SSI_CR1_SSE; // Habilita SSI0.
}

/************************************************
 *  Función:        SSI1_Init
 *
 *  Descripción:    Inicialización y configuración del SPI 1.
 */

void SSI1_Init(void){

    SYSCTL_RCGCSSI_R |= SYSCTL_RCGCSSI_R1; // Activa reloj al SSI1
    while ((SYSCTL_PRSSI_R & SYSCTL_PRSSI_R1) == 0); // Espera a que este listo

    SYSCTL_RCGCGPIO_R |= (1 << 1) | (1 << 4); // 1) Habilita reloj para Puerto E y B
    while((SYSCTL_PRGPIO_R & ((1 << 1) | (1 << 4))) == 0); // Se espera a que el reloj se estabilice (p.499)

    GPIO_PORTB_AHB_AFSEL_R |= 0x30; // Seleciona la función alterna de PB[4:5].
    GPIO_PORTE_AHB_AFSEL_R |= 0X10; // Seleciona la función alterna de PE[4:5].

    GPIO_PORTB_AHB_PCTL_R = (GPIO_PORTB_AHB_PCTL_R & 0XFF00FFFF) | 0x00FF0000; // Configura las terminales de PA a su función de SSI0.
    GPIO_PORTE_AHB_PCTL_R = (GPIO_PORTE_AHB_PCTL_R & 0XFFF0FFFF) | 0x000F0000; // Configura las terminales de PA a su función de SSI0.

    GPIO_PORTB_AHB_AMSEL_R  &= ~0x30; // Deshabilita la función analogica
    GPIO_PORTE_AHB_AMSEL_R  &= ~0x10; // Deshabilita la función analogica

    GPIO_PORTB_AHB_DIR_R = 0x30; // Configura al puerto como salida
    GPIO_PORTE_AHB_DIR_R = 0x10; // Configura al puerto como salida

    GPIO_PORTB_AHB_DEN_R |= 0x30; // Habilita la función digital del puerto
    GPIO_PORTE_AHB_DEN_R |= 0x10; // Habilita la función digital del puerto

    SSI1_CR1_R = 0x00; // Selecciona modo maestro/deshabilita SSI0. (p. 1247)
    SSI1_CPSR_R = 0x02; // preescalador (CPSDVSR) del reloj SSI (p. 1252)
    // configura para Freescale SPI; 16bit; 4 Mbps; SPO = 0; SPH = 0 (p. 1245)
    SSI1_CR0_R = (0x0100 | SSI_CR0_FRF_MOTO | SSI_CR0_DSS_16) & ~(SSI_CR0_SPO | SSI_CR0_SPH);
    SSI1_CR1_R |= SSI_CR1_SSE; // Habilita SSI1.
}
