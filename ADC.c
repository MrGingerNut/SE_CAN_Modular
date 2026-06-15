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
 *  Archivo:        Archivo fuente del módulo ADC
 *
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/

/**************************************************************************************************
 *  Archivos de cabecera
 */

#include "ADC.h"                                                                                    /*  Archivo de cabecera del módulo ADC */
#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "NVIC.h"                                                                                   /*  Archivo de cabecera del módulo NVIC */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */


/**************************************************************************************************
 *  Variables externas (parámetros)
 */


/**************************************************************************************************
 *  Funciones
 */

/************************************************
 *  Función:        ADC0_SS2_Init
 *
 *  Descripción:    Inicialización y configuración del ADC_0, SS_2.
 */

//void ADC0_SS2_Init(void) {
//
//    /********************************************
//     *  Inicialización y configuración del ADC
//     */
//
//    /** 1.  Habilitar la señal de reloj del ADC y esperar a que se estabilice el reloj. */
//    SYSCTL_RCGCADC_R |= 0x1;                                                                        /*  R0: ADC Module 0 Run Mode Clock Gating Control -> Enabled */
//    while (!(SYSCTL_PRADC_R & 0x1)) {}                                                              /*  R0: ADC Module 0 Peripheral Ready -> ADC module 0 is ready for access */
//
//    ADC0_PC_R = 0x01;         // 7)Configura para 125Ksamp/s (p.1159)
//
//    /********************************************
//     *  Configuración del secuenciador de muestras (SS)
//     */
//
//
//        //
//        //
//        //
//        //
//        //
//    /** 1.  Asegurar que el secuenciador de muestras está deshabilitado. */
//    ADC0_SSPRI_R = 0x0123;                                          //SS2 con la mas alta prioridad
//    ADC0_ACTSS_R &= ~0x0004;
//
//    /** 2.  Configurar el evento de disparo para el SS. */
//    ADC0_EMUX_R = 0x0000;                                           // Se configura SS2 para disparar muestreo por software (default) (p.1091)
//    ADC0_SAC_R = 0x0;                                               // Se configura para no tener sobremuestreo por hardware(default)(p. 1105)
//    ADC0_CTL_R = 0x0;                                               // Se configura con referencias internas (default VDDA and GNDA) (p. 1107)
//    ADC0_SSOP2_R = 0x0000;                                          // Se configure para salvar los resultados del ADC en FIFO (default)(p. 1134)
//    ADC0_SSTSH2_R = 0x000;                                          // Se configure el ADC para un periodo de 4  S&H (default) (p. 1139)
//
//    /** 3.  Para cada muestra en el SS, configurar la fuente de entrada de la señal analógica. */
//    ADC0_SSMUX2_R = 0x0089;                                         // Se configura entradas 1-muestra=AIN9 2�muestra=AIN8 3�muestra=AIN7 (p.1128)
//    ADC0_SSEMUX2_R &= ~0x0011;                                      // Canales del SS2 para 1�muestra 2�muestra y 3�muestra en AIN(15:0) (p.1137)
//
//    /** 5.  Para cada muestra en el SS, configurar los bits de control correspondientes, asegurando
//     *      que el bit END de la última muestra esté habilitado. */
//    ADC0_SSCTL2_R = 0x0060;                                         /* Si: sensor de temperatura, Habilitacion de INR3,
//                                                                     * Fin de secuencia; No:muestra diferencial (p.1142)*/
//
//    /** 6.  Si se utiliza interrupción, desenmascarar la interrupción local. */
//    ADC0_IM_R = 0x0004;                                             // Habilita interrupcion SS2 (p. 1081)
//
//    /** 7.  Habilitar el SS. */
//    ADC0_ACTSS_R |= 0x0004;                                         // Habilita SS2 (p. 1076)
//
//    /********************************************
//     *  Interrupción
//     */
//
//    /** Establecer el nivel de prioridad de la IRQ. */
//    //NVIC_PRI3_R = ((NVIC_PRI3_R & ~0xE0000000) | (1 << 29));                                        /*  IRQ_15 (ADC0 SS1) => INTD: Interrupt Priority -> Cleared and set 1 */
//
//    /** Habilitación de la IRQ en el NVIC. */
//    NVIC_EN0_R |= (1<<16);
//
//    /********************************************
//     *  Habilitación del PLL
//     *  NOTA:   Si se utiliza el PIOSC de 16MHz como fuente de reloj, es necesario habilitar y
//     *          deshabilitar el PLL.
//     */
//
//    /** 1.  Habilitar el PLL y esperar a que esté retroalimentado. */                                                           /*  PLL => LOCK: Lock -> PLL powered and locked */
//    SYSCTL_PLLFREQ0_R |= SYSCTL_PLLFREQ0_PLLPWR;                                            // Encender PLL
//    while((SYSCTL_PLLSTAT_R&0x01)==0);                                                      // Espera a que el PLL fije su frecuencia
//    //SYSCTL_PLLFREQ0_R &= ~SYSCTL_PLLFREQ0_PLLPWR;                                           // Apagar PLL
//    ADC0_ISC_R = 0x0004;                                                                    // Se recomienda Limpia la bandera RIS del ADC0
//    ADC0_PSSI_R = 0x0004;                                                                   // Inicia conversion del SS2
//
//    /** 2.  Habilitar el PIOSC. */
//    ADC0_CC_R = ((ADC0_CC_R & ~0x000F) | 0x0001);                                                   /*  ADC0 => CS: Clock Source -> Alternate clock source as defined by ALTCLKCFG (default: PIOSC) */
//
//    /** 3.  Deshabilitar el PLL. */
//    SYSCTL_PLLFREQ0_R &= ~(1 << 23);                                                                /*  PLL => PLLPWR: PLL Power -> Disabled */
//}

void ADC0_SS2_Init(void) { // Rutina de configuracion del ADC0 para dos muestras

    SYSCTL_RCGCGPIO_R |= (1 << 9); // 1) Habilita reloj para Puerto E
    while((SYSCTL_PRGPIO_R & ((1 << 9))) == 0); // Se espera a que el reloj se estabilice (p.499)

    GPIO_PORTE_AHB_DIR_R = 0x00;    // 2) PE5-4 entradas (analogica)
    GPIO_PORTE_AHB_AFSEL_R |= 0x30; // 3) Habilita Funcion Alterna en PE5-4 (p. 770)
    GPIO_PORTE_AHB_DEN_R &= ~0x30;  // 4) Deshabilita Funcion Digital en PE5-4 (p 781)
    GPIO_PORTE_AHB_AMSEL_R |= 0x30; // 5) Habilita Funcion Analogica de PE5-4 (p. 786)

    SYSCTL_RCGCADC_R |= 0x01;       // 6) Habilita reloj para ADC0(p. 396)
    while((SYSCTL_PRADC_R & 0x01) == 0); // Se espera a que el reloj se estabilice

    ADC0_PC_R = 0x01;         // 7)Configura para 125Ksamp/s (p.1159)
    ADC0_SSPRI_R = 0x0123;    // 8)SS3 con la mas alta prioridad
    ADC0_ACTSS_R &= ~0x0004;  // 9) Deshabilita SS2 antes de cambiar configuracion de registros (p. 1076)
    ADC0_EMUX_R = 0x0000;     // 10) Se configura SS2 para disparar muestreo por software (default) (p.1091)
    ADC0_SAC_R = 0x0;         // 11) Se configura para no tener sobremuestreo por hardware(default)(p. 1105)
    ADC0_CTL_R = 0x0;         //12) Se configura con referencias internas (default VDDA and GNDA) (p. 1107)
    ADC0_SSOP2_R = 0x0000;    // 13) Se configure para salvar los resultados del ADC en FIFO (default)(p. 1134)
    ADC0_SSTSH2_R = 0x000;    // 14) Se configure el ADC para un periodo de 4  S&H (default) (p. 1139)
    ADC0_SSMUX2_R = 0x0089;    // 15) Se configura entradas 1�muestra=AIN9 2�muestra=AIN8 3�muestra=AIN7 (p.1128)
    ADC0_SSEMUX2_R &= ~0x0011; // 16) Canales del SS2 para 1�muestra 2�muestra y 3�muestra en AIN(15:0) (p.1137)
    ADC0_SSCTL2_R = 0x0060;    // 17) Si: sensor de temperatura, Habilitacion de INR3, Fin de secuencia; No:muestra diferencial (p.1142)
    ADC0_IM_R = 0x0004;      // 18) habilita interrupcion SS2 (p. 1081)
    ADC0_ACTSS_R |= 0x0004;    // 19) Habilita SS2 (p. 1076)

    SYSCTL_PLLFREQ0_R |= SYSCTL_PLLFREQ0_PLLPWR;  // encender PLL
    while((SYSCTL_PLLSTAT_R&0x01)==0);            // espera a que el PLL fije su frecuencia
    SYSCTL_PLLFREQ0_R &= ~SYSCTL_PLLFREQ0_PLLPWR; // apagar PLL

    NVIC_EN0_R |= (1<<16);
    ADC0_ISC_R = 0x0004;// Se recomienda Limpia la bandera RIS del ADC0
    ADC0_PSSI_R = 0x0004;//Inicia conversion del SS2

}
