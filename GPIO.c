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
 *  Archivo:        Archivo fuente del módulo GPIO
 *
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/

/**************************************************************************************************
 *  Archivos de cabecera
 */

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
 *  Función:        GPIO_PortE_Init
 *
 *  Descripción:    Inicialización y configuración del puerto GPIO E (PE4, PE5).
 */

void GPIO_PortE_Init(void) {

    /** 1.  Habilitar la señal de reloj del GPIO y esperar a que se estabilice el reloj. */
    SYSCTL_RCGCGPIO_R |= (1 << 4);
    while((SYSCTL_PRGPIO_R & ((1 << 4))) == 0);
    /** 2.  Configurar la dirección de los pines del puerto GPIO. */
    GPIO_PORTE_AHB_DIR_R = 0x00;
    /** 3.  Habilitar las funciones alternas de hardware de los pines de los puertos GPIO. (p.770) */
    GPIO_PORTE_AHB_AFSEL_R |= 0x30;
    /** 4.  Deshabilitar las funciones digitales de los pines del puerto GPIO. (p.781) */
    GPIO_PORTE_AHB_DEN_R &= ~0x30;
    /** 5.  Habilitar las funciones analógica de los pines del puerto GPIO. (p. 786) */
    GPIO_PORTE_AHB_AMSEL_R |= 0x30;

}

/************************************************
 *  Función:        GPIO_PortK_Init
 *
 *  Descripción:    Inicialización y configuración del puerto GPIO K.
 */

void GPIO_PortK_Init(void) {

    /** 1.  Habilitar la señal de reloj del GPIO y esperar a que se estabilice el reloj. */
    SYSCTL_RCGCGPIO_R |= (1 << 8) | (1 << 9)    | (1 << 12);  // J, K, N
    while ((SYSCTL_PRGPIO_R & ((1 << 8) | (1 << 9) | (1 << 12))) == 0){}; // reloj listo?
    /** 2.  Configurar la dirección de los pines del puerto GPIO. */
    GPIO_PORTK_DIR_R |= 0x0F;
    /** 3.  Habilitar las funciones alternas de hardware de los pines de los puertos GPIO. (p.770) */
    //GPIO_PORTE_AHB_AFSEL_R |= 0x30;
    /** 4.  Deshabilitar las funciones digitales de los pines del puerto GPIO. (p.781) */
    GPIO_PORTK_DEN_R |= 0x0F;
    /** 5.  Habilitar las funciones analógica de los pines del puerto GPIO. (p. 786) */
    //GPIO_PORTE_AHB_AMSEL_R |= 0x30;

}

/************************************************
 *  Función:        GPIO_PortN_Init
 *
 *  Descripción:    Inicialización y configuración del puerto GPIO N.
 */

void GPIO_PortN_Init(void) {

    /** 1.  Habilitar la señal de reloj del GPIO y esperar a que se estabilice el reloj. */
    SYSCTL_RCGCGPIO_R |= 0x1000;                                                                    /*  R12: GPIO PortN Run Mode Clock Gating Control -> Enabled */
    while (!(SYSCTL_PRGPIO_R & 0x1000)) {}                                                          /*  R12: GPIO PortN Peripheral Ready -> GPIO PortN is ready for access */

    /** 2.  Configurar la dirección de los pines del puerto GPIO. */
    GPIO_PORTN_DIR_R |= 0x03;                                                                       /*  PortN[1,0] => DIR: GPIO Data direction -> Output */

    /** 3.  Deshabilitar las funciones alternas de hardware de los pines de los puertos GPIO. */

    /** 4.  Configurar los modos de controlador extendidos. */

    /** 5.  Configurar el driver de 4mA de los pines del puerto GPIO. */

    /** 6.  Configurar el driver de 8mA de los pines del puerto GPIO. */

    /** 7.  Configurar el driver de 12mA de los pines del puerto GPIO. */

    /** 8.  Configurar como open drain y las resistencias de pull-up / pull-down. */

    /** 9.  Habilitar las funciones digitales de los pines del puerto GPIO. */
    GPIO_PORTN_DEN_R |= 0x03;                                                                       /*  PortN[1,0] => DEN: Digital Enable -> Enabled */

    /** 10. Si se utiliza interrupción, configurar la sensibilidad y el tipo de evento. Además de
     *      desenmascarar la interrupción local. */

}

/************************************************
 *  Función:        GPIO_PortL_Init
 *
 *  Descripción:    Inicialización y configuración del puerto GPIO L.
 */

void GPIO_PortL_Init(void){

    SYSCTL_RCGCGPIO_R |= (1 << 10);
    while((SYSCTL_PRGPIO_R & ((1 << 10))) == 0);                                // Se espera a que el reloj se estabilice (p.499)

    GPIO_PORTL_DIR_R &= ~0x1F;
    GPIO_PORTL_DEN_R |= 0x1F;
    GPIO_PORTL_PUR_R |= 0x1F;

    GPIO_PORTL_IS_R &= ~0x1F;                                                   // (d) PH0 es sensible por flanco
    GPIO_PORTL_IBE_R |= 0x1F;                                                   // PH0 no es sensible a dos flancos
//    GPIO_PORTL_IEV_R &= ~0x1F; // PH0 detecta eventos de flanco de bajada
    GPIO_PORTL_ICR_R = 0x1F;                                                    // (e) limpia la bandera 0
    GPIO_PORTL_IM_R |= 0x1F;                                                    // (f) Se desenmascara la interrupcion PH0 y se envia al controlador de interrupciones

    NVIC_PRI13_R = (NVIC_PRI13_R & 0xFFFF00FF) | 0x00000000;
    NVIC_EN1_R |= (1 << (53 - 32));
}

/************************************************
 *  Función:        GPIO_PortL_Init
 *
 *  Descripción:    Desactivación del puerto GPIO L.
 */

void GPIO_PortL_Disable(void){ // Rutina de configuracion del GPIOH

    NVIC_EN1_R &= ~(1 << (53 - 32)); // deshabilitar el nvic

    GPIO_PORTL_IM_R &= ~0x1F; // (f) Se enmascara la interrupcion PH0 y se envia al controlador de interrupciones
    GPIO_PORTL_ICR_R = 0x1F; // (e) limpia la banderas pendientes

    SYSCTL_RCGCGPIO_R &= ~(1 << 10); //quitarle el reloj

}
