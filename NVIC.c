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
 *  Archivo:        Archivo fuente del módulo NVIC
 *
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/

/**************************************************************************************************
 *  Archivos de cabecera
 */
#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "NVIC.h"                                                                                   /*  Archivo de cabecera del módulo NVIC */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */
#include "VarVEL.h"
#include "UART.h"
//#include "IEEE_CAN.h"
#include <tm4c1294ncpdt.h>

/**************************************************************************************************
 *  Variables externas (parámetros)
 */
volatile int a = 0, b = 0;
volatile char dato;
volatile uint32_t eje_x = 2048, eje_y = 2048; // variables para la direccion de los joysticks y contador de interrupcion de PH
volatile uint8_t cuenta; // variable para saber si esta en modo automatico o remoto

/**************************************************************************************************
 *  Funciones
 */

/************************************************
 *  Función:        ADC0_Handler
 *
 *  Descripción:    Rutina de Servicio de Interrupción del ADC.
 */

void ADC0_Handler(void){

    ADC0_ISC_R = 0x0004;  // Limpia la bandera RIS del ADC0

    eje_x = (ADC0_SSFIFO2_R & 0xFFF);// se lee el primer resultado correspondiente al potenciometro 1 pe4
    eje_y = (ADC0_SSFIFO2_R & 0xFFF);// se lee el segundo resultado correspondiente al potenciometro 2 pe5

    ADC0_PSSI_R = 0x0004;//Inicia conversion del SS2

    if(eje_y > 3800 && eje_x < 300){ // da la vuelta
        //GPIO_PORTK_DATA_R = vuelta; //gira ambos motores sentido contrario
//        while((UART7_FR_R & 0x20) != 0);
        UART7_DR_R = 'q';
    }
    else if(eje_y > 3800 && eje_x > 3800){ // da la vuelta
        //GPIO_PORTK_DATA_R = vuelta; //gira ambos motores sentido contrario
//        while((UART7_FR_R & 0x20) != 0);
        UART7_DR_R = 'e';
    }
    else if(eje_x > 3800 ){ // giro derecha
        //GPIO_PORTK_DATA_R = derecha; // gira el motor A hacia adelante
//        while((UART7_FR_R & 0x20) != 0);
        UART7_DR_R = 'd';
    }
    else if(eje_x < 300){ //giro izquierda
        //GPIO_PORTK_DATA_R = izquierda; // gira el motor B hacia adelante
//        while((UART7_FR_R & 0x20) != 0);
         UART7_DR_R = 'a';
    }
    else if(eje_y > 3800){ //avanza
        //GPIO_PORTK_DATA_R = adelante; //gira ambos motores
//        while((UART7_FR_R & 0x20) != 0);
                 UART7_DR_R = 'w';
    }
    else{ // uy quieto
//        GPIO_PORTK_DATA_R = uyquieto; // idle
    }

}

/************************************************
 *  Función:        GPIOL_Handler
 *
 *  Descripción:    Ruitna de Servicio de Interrupción del GPIO L.
 */

void GPIOK_Handler(void){

    GPIO_PORTK_ICR_R = 0x01; // bandera 0 de confirmaci�n
    BotonPK++;

    if(BotonPK % 2 == 0){
//        while((UART7_FR_R & 0x20) != 0);
        UART7_DR_R = 'r';
    }
    else {
//        while((UART7_FR_R & 0x20) != 0);
        UART7_DR_R = 'p';
    }

}

/************************************************
 *  Función:        GPIOL_Handler
 *
 *  Descripción:    Ruitna de Servicio de Interrupción del GPIO L.
 */

void GPIOL_Handler(void){

    GPIO_PORTL_ICR_R = 0x1F;

    seguidor = GPIO_PORTL_DATA_R & 0x1F;

    switch(seguidor){

        case 0b11111: // fuera de linea giro fuerte pa la izquierda
            speed_a = 90; //motor derecho
            speed_b = 40; //motor izquierdo
            break;
        case 0b11110: // linea muy a la derecha
            speed_a = 50; //motor derecho
            speed_b = 90; //motor izquierdo
            break;
        case 0b11100: // linea a la derecha
            speed_a = 50; //motor derecho
            speed_b = 80; //motor izquierdo
            break;
        case 0b11101: // linea desplazada a la derecha
            speed_a = 60; //motor derecho
            speed_b = 80; //motor izquierdo
            break;
        case 0b11011: // linea al centro
            speed_a = 80; //motor derecho
            speed_b = 80; //motor izquierdo
            break;
        case 0b11001: // linea ligerametne a la derecha
            speed_a = 70; //motor derecho
            speed_b = 80; //motor izquierdo
            break;
        case 0b10111: // linea desplazada a la izquierda
            speed_a = 80; //motor derecho
            speed_b = 60; //motor izquierdo
            break;
        case 0b10011: // linea ligeramente a la izquierda
            speed_a = 80; //motor derecho
            speed_b = 70; //motor izquierdo
            break;
        case 0b01111: // linea muy a la izquierda
            speed_a = 90; //motor derecho
            speed_b = 50; //motor izquierdo
            break;
        case 0b00111: // linea a la izquierda
            speed_a = 80; //motor derecho
            speed_b = 50; //motor izquierdo
            break;
        case 0b00011: // giro cerrado izquierdo
            speed_a = 90; //motor derecho
            speed_b = 40; //motor izquierdo
            break;
        case 0b11000: // giro cerrado derecha
            speed_a = 40; //motor derecho
            speed_b = 90; //motor izquierdo
            break;
        case 0b00000: // linea desplazada a la derecha
            speed_a = 0; //motor derecho
            speed_b = 0; //motor izquierdo
            break;
    }
}

/************************************************
 *  Función:        GPTM_Handler
 *
 *  Descripción:    Ruitna de Servicio de Interrupción del GPTM 3.
 */

void TIMER3_Handler(void) {

    TIMER3_ICR_R= 0X00000001 ;

//    if(SSI0_SR_R & SSI_SR_TNF){

    switch(speed_a){

        case 0:
            SSI0_DR_R = 0X1100 | (0 & 0xFF);
            break;
        case 20:
            SSI0_DR_R = 0x1100 | (sp20[a] & 0xFF); // envia dato.
            a = (a + 1) & 0xFF;
            break;
        case 40:
            SSI0_DR_R = 0x1100 | (sp40[a] & 0xFF); // envia dato.
            a = (a + 1) & 0xFF;
            break;
        case 50:
            SSI0_DR_R = 0x1100 | (sp50[a] & 0xFF); // envia dato.
            a = (a + 1) & 0xFF;
            break;
        case 60:
            SSI0_DR_R = 0x1100 | (sp60[a] & 0xFF); // envia dato.
            a = (a + 1) & 0xFF;
            break;
        case 70:
            SSI0_DR_R = 0x1100 | (sp70[a] & 0xFF); // envia dato.
            a = (a + 1) & 0xFF;
            break;
        case 80:
            SSI0_DR_R = 0x1100 | (sp80[a] & 0xFF); // envia dato.
            a = (a + 1) & 0xFF;
            break;
        case 90:
            SSI0_DR_R = 0x1100 | (sp90[a] & 0xFF); // envia dato.
            a = (a + 1) & 0xFF;
            break;
        case 100:
            SSI0_DR_R = 0X1100 | (255 & 0xFF);
            break;

    }

//    if(SSI1_SR_R & SSI_SR_TNF){

    switch(speed_b){

        case 0:
            SSI1_DR_R = 0X1100 | (0 & 0xFF);
            break;
        case 20:
            SSI1_DR_R = 0x1100 | (sp20[b] & 0xFF); // envia dato.
            b = (b + 1) & 0xFF;
            break;
        case 40:
            SSI1_DR_R = 0x1100 | (sp40[b] & 0xFF); // envia dato.
            b = (b + 1) & 0xFF;
            break;
        case 50:
            SSI1_DR_R = 0x1100 | (sp50[b] & 0xFF); // envia dato.
            b = (b + 1) & 0xFF;
            break;
        case 60:
            SSI1_DR_R = 0x1100 | (sp60[b] & 0xFF); // envia dato.
            b = (b + 1) & 0xFF;
            break;
        case 70:
            SSI1_DR_R = 0x1100 | (sp70[b] & 0xFF); // envia dato.
            b = (b + 1) & 0xFF;
            break;
        case 80:
            SSI1_DR_R = 0x1100 | (sp80[b] & 0xFF); // envia dato.
            b = (b + 1) & 0xFF;
            break;
        case 90:
            SSI1_DR_R = 0x1100 | (sp90[b] & 0xFF); // envia dato.
            b = (b + 1) & 0xFF;
            break;
        case 100:
            SSI1_DR_R = 0X1100 | (255 & 0xFF);
            break;
    }
}

/************************************************
 *  Función:        UART7_Handler
 *
 *  Descripción:    Ruitna de Servicio de Interrupción del UART 7.
 */

 void UART7_Handler(void){

    if(UART7_MIS_R & 0x10){ // esto para recibir

          dato = (char)(UART7_DR_R & 0xFF);

          if(dato == 'r'){ //remoto
              GPIO_PortL_Disable();
              cuenta = 1;
              speed_a = 0;
              speed_b = 0;
          }

          else if(dato == 'p'){ //automatico
              GPIO_PortL_Init();
              cuenta = 0;
          }

          else if(dato == 'w' && cuenta ==1){ // forward pa delante
              speed_a = 80;
              speed_b = 80;
          }
          else if(dato == 'a' && cuenta ==1){ // left pa la izquierda
              speed_a = 70;
              speed_b = 0;
          }
          else if(dato == 'd' && cuenta ==1){ // right pa la derecha
              speed_a = 0;
              speed_b = 70;
          }
          else if(dato == 'q' && cuenta ==1){ // q de pa delante a la izquierda
              speed_a = 70;
              speed_b = 50;
          }
          else if(dato == 'e' && cuenta ==1){ // e de pa delante a la derecha
              speed_a = 50;
              speed_b = 70;
          }
          else if(dato == 'u' && cuenta == 1){ // u de uy quietoe
              speed_a = 0;
              speed_b = 0;
          }

          UART7_ICR_R = 0x10;
      }

//    if(UART7_MIS_R & 0X20){ // esto para transmitir ???
//
//        UART7_ICR_R = 0X20;
//    }

}
