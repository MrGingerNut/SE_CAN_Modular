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
 *  Archivo:        Archivo fuente del módulo CAN
 *
 *  Tarjeta de desarrollo:  EK-TM4C1294XL Evaluation board
 ***********************************************/

/**************************************************************************************************
 *  Archivos de cabecera
 */
#include "GPIO.h"                                                                                   /*  Archivo de cabecera del módulo GPIO */
#include "NVIC.h"                                                                                   /*  Archivo de cabecera del módulo NVIC */
#include "SYSCTL.h"                                                                                 /*  Archivo de cabecera del módulo SYSCTL */
#include "IEEE_CAN.h"                                                                                 /*  Archivo de cabecera del módulo CAN */
#include <tm4c1294ncpdt.h>

/**************************************************************************************************
 *  Variables externas (parámetros)
 */
volatile int q;

/**************************************************************************************************
 *  Funciones
 */

/************************************************
 *  Función:        CAN_Init
 *
 *  Descripción:    Inicialización y configuración del protocolo CAN.
 */

void CAN_Init(void){
    SYSCTL_RCGCCAN_R=0x1;                       //Reloj modulo 0 CAN
    while((SYSCTL_PRCAN_R&0x1)==0){}
                                                //Bit Rate= 1 Mbps      CAN clock=16 [Mhz]
    CAN0_CTL_R=0x41;                            //Deshab. modo prueba, Hab. cambios en la config. y hab. inicializacion
    CAN0_BIT_R=0x4900;                          //TSEG2=4   TSEG1=9    SJW=0    BRP=0
                                                //Lenght Bit time=[TSEG2+TSEG1+3]*tq
                                                //               =[(Phase2-1)+(Prop+Phase1-1)+3]*tq
    CAN0_CTL_R&=~0x41;                          //Hab. cambios en la config. y deshab. inicializacion
    CAN0_CTL_R|=0x02;                           //Hab de interrupcion en el modulo CAN
    NVIC_EN1_R|=((1<<(38-32)) & 0xFFFFFFFF);    //(TM4C1294NCPDT)
}

/************************************************
 *  Función:        CAN_Error
 *
 *  Descripción:    Detecta error en el CAN.
 */

void CAN_Error(void){
    static int ent=0;
    if(CAN0_STS_R&0x80){
        if(ent){
            NVIC_APINT_R|=0x4;                      //Reinicio de todo el sistema
        }else{
            CAN0_CTL_R=0x41;                        //Hab. cambios en la config. y hab. inicializacion
            CAN0_CTL_R|=0x80;                       //Hab. modo prueba
            CAN0_TST_R|=0x4;                        //Hab. Modo silencio
            CAN0_CTL_R&=~0x41;                      //Hab. cambios en la config. y deshab. inicializacion
            for(q=0;q<4000;q++);
            CAN0_CTL_R=0x41;                        //Hab. cambios en la config. y hab. inicializacion
            CAN0_TST_R&=~0x4;                       //Deshab. Modo silencio
            CAN0_CTL_R&=~0x41;                      //Hab. cambios en la config. y deshab. inicializacion
            ent++;
        }
    }
}

/************************************************
 *  Función:        CAN_Memoria_Dato
 *
 *  Descripción:    ESCRITURA DE MENSAJE A MEMORIA CAN
 *  Dato: Mensaje de 8 Bytes a escribir en localidad NoObj
 *  NoObj: Localidad de memoria donde se guaradarán el mensaje
 */

//ARB bits, Data lenght code, data bytes
void CAN_Memoria_Dato(uint64_t Dato, uint8_t NoObj){
    CAN0_IF1CMSK_R=0x83;                    //WRNRD: Tx datos de CANIF->CAN message object (MNUM)
                                            //DATAA: Tx bytes 0-3 en el mensaje objeto->CANIFNDAn
                                            //DATAB: Tx bytes 4-7 en el mensaje objeto->CANIFNDAn
    //-------------------Escritura de datos---------------------//
    CAN0_IF1DA1_R = Dato & 0x000000000000FFFF;          //Byte 0-1
    CAN0_IF1DA2_R = (Dato & 0x00000000FFFF0000)>>16;    //Byte 2-3
    CAN0_IF1DB1_R = (Dato & 0x0000FFFF00000000)>>32;    //Byte 4-5
    CAN0_IF1DB2_R = (Dato & 0xFFFF000000000000)>>48;    //Byte 6-7
    CAN0_IF1CRQ_R = NoObj;                  //No. del identificador para indicar la prioridad
    while(CAN0_IF1CRQ_R & 0x8000);          //Espera a que se termine una acción de escritura al espaciod e memoria NoObj
}

/************************************************
 *  Función:        CAN_Memoria_Arb
 *
 *  Descripción:    ESCRITURA DE DATOS DE ARBITRAJE A MEMORIA CAN
 *                  ID: Identificador del mensaje 11 bitsCT
 *                  TxRx: (True) Transmisión de datos (False) Recepción de datos
 *                  NoObj: Localidad de memoria donde se guaradarán los datos
 */

void CAN_Memoria_Arb(uint16_t ID, bool TxRx, uint8_t ObjNo){
    CAN0_IF1CMSK_R=0xA0;                    //WRNRD: Tx datos de CANIF->CAN message object (MNUM)
                                            //ARB: Tx ID+DIR+XTD+MSGVAL del message object a los registros de interfaz
    CAN0_IF1ARB2_R=0x8000|(ID<<2);          //MSGVAL hab, XTD: 11 bit Standard, DIR: Rx y ID
    if(TxRx){
        CAN0_IF1ARB2_R|=0x2000;             //DIR para Tx
    }
    CAN0_IF1CRQ_R = ObjNo;                  //No. del identificador para indicar la prioridad
    while(CAN0_IF1CRQ_R & 0x8000);          //Espera a que se termine una acción de escritura al espaciod e memoria NoObj
}

/************************************************
 *  Función:        CAN_Memoria_CtrlMsk
 *
 *  Descripción:    ESCRITURA DE DATOS DE CONTROL Y ENMASCARAMIENTO A MEMORIA CAN    %%%%%%%%
 *                  Mask: Enmascaramiento (Filtro) del mensaje
 *                  DatoL: Longitud del mensaje a enviar/recibir en número de bytes
 *                  TXIE: (True) Interrupción al transmitir dato de este NoObj (False) Sin interrupción
 *                  RXIE: (True) Interrupción al recibir dato en este NoObj (False) Sin interrupción
 *                  RMTEN: (True) Transmisión de trama remota (False) Transmisión de trama de datos
 *                  NoObj: Localidad de memoria donde se guaradarán los datos
 */

void CAN_Memoria_CtrlMsk(uint16_t Mask, uint8_t DatoL, bool TXIE, bool RXIE, bool RMTEN, uint8_t ObjNo){
    CAN0_IF1CMSK_R=0xD0;                    //WRNRD: Tx datos de CANIF->CAN message object (MNUM)
                                            //MASK: Tx IDMASK+DIR+MXTD del mensaje objeto->registros de interfaz
                                            //CONTROL: Datos de control IFnMCTL->registros de interfaz
    CAN0_IF1MCTL_R=(0x80|DatoL);            //DLC: Num bytes en el data frame, EOB (end of Buffer): Mensaje único
    if(RMTEN){
        CAN0_IF1MCTL_R|=0x200;            //RMTEN: Hab de trama remota
    }
    if(RXIE){
        CAN0_IF1MCTL_R|=0x400;            //RXIE: Hab de interrupción al recibir un mensaje en este NoObj
    }
    if(TXIE){
        CAN0_IF1MCTL_R|=0x800;            //TXIE:  Hab de interrupción al transmitir el mensaje en este NoObj
    }
    if(Mask){
      CAN0_IF1MSK1_R=0x0;
      CAN0_IF1MSK2_R=Mask<<2;                //Aplicación del enmascaramiento
      CAN0_IF1MCTL_R|=0x1000;                //UMASK: Hab de enmsacaramiento
    }
    CAN0_IF1CRQ_R = ObjNo;                  //No. del identificador para indicar la prioridad
    while(CAN0_IF1CRQ_R & 0x8000);          //Espera a que se termine una acción de escritura al espaciod e memoria NoObj
}

/************************************************
 *  Función:        CAN_Tx
 *
 *  Descripción:    TRNSMISIÓN DE DATOS CAN
 *                  NoObj: Localidad de memoria de donde se tomará el mensaje a transmitir
 */

void CAN_Tx(uint64_t NoObj){
    CAN0_IF1CMSK_R = 0x84;                  //WRNRD: Tx datos de CANIF->CAN message object (MNUM)
                                            //Hab NEWDAT/TXRQST: Como WRNRD=1; una Tx es solicitada
    CAN0_IF1CRQ_R = NoObj;                  //No. del identificador para indicar la prioridad
    while(CAN0_IF1CRQ_R & 0x8000);          //Espera a que se termine una acción de escritura a memoria
}

/************************************************
 *  Función:        CAN_Rx
 *
 *  Descripción:    RECEPCIÓN DE DATOS CAN
 *                  NoObj: Localidad de memoria de donde se tomará el mensaje a transmitir
 *                  return: Dato de 8 bytes alojado en la memoria del controlador CAN o error
 */

uint64_t CAN_Rx(uint8_t ObjNo){
    uint64_t Dato=0;
    CAN0_IF1CMSK_R = 0x13;                 //Hab CONTROL, DATAA, DATAB
    CAN0_IF1CRQ_R = ObjNo;                 //No. de identificador para alojar el objeto mensaje
    while(CAN0_IF1CRQ_R & 0x8000);         //Espera a que se termine una acción de lectura/escritura
    if(CAN0_IF1MCTL_R & 0x8000){           //Si NEWDAT bit está hab, hay un nuevo dato en los registros de datos
        //------------Obtención de los nuevos datos-----------------//
            Dato|=(0x00000000000000FF & CAN0_IF1DA1_R);         //Byte 0
        if((CAN0_IF1MCTL_R & 0xF)>= 2){
            Dato|=(0x000000000000FF00 & CAN0_IF1DA1_R);         //Byte 1
        }
        if((CAN0_IF1MCTL_R & 0xF)>= 3){
            Dato|=(0x0000000000FF0000 & (CAN0_IF1DA2_R<<16));   //Byte 2
        }
        if((CAN0_IF1MCTL_R & 0xF)>= 4){
            Dato|=(0x00000000FF000000 & (CAN0_IF1DA2_R<<16));   //Byte 3
        }
        if((CAN0_IF1MCTL_R & 0xF)>= 5){
            Dato|=(0x000000FF00000000 & ((uint64_t)(CAN0_IF1DB1_R)<<32));   //Byte 4
        }
        if((CAN0_IF1MCTL_R & 0xF)>= 6){
            Dato|=(0x0000FF0000000000 & ((uint64_t)(CAN0_IF1DB1_R)<<32));   //Byte 5
        }
        if((CAN0_IF1MCTL_R & 0xF)>= 7){
            Dato|=(0x00FF000000000000 & ((uint64_t)(CAN0_IF1DB2_R)<<48));   //Byte 6
        }
        if((CAN0_IF1MCTL_R & 0xF)>= 8){
            Dato|=(0xFF00000000000000 & ((uint64_t)(CAN0_IF1DB2_R)<<48));   //Byte 7
        }
        CAN0_IF1CMSK_R |= 0x4;             //Hab NEWDAT para limpiar el NEWDAT de IFnMCTL
    }
    if(CAN0_IF1MCTL_R & 0x4000){           //Si MSGLST bit está hab, hubo un mensaje perdido
        CAN0_IF1MCTL_R &= ~0x4000;         //Limpieza del MSGLST bit
        return 0xFFFFFF;                   //Indicador de un error
    }
    CAN0_IF1CMSK_R |= 0x8;                 //Hab CLRINTPND para limpiar el INTPND de IFnMCTL
    CAN0_IF1CRQ_R =ObjNo;                  //No. de identificador para ejecutar las acciones anteriores
    return Dato;
}


void Inter_CAN0(void){
    uint8_t NoInt;
    NoInt=CAN0_INT_R;                           //Lectura del apuntador de interrupciones
     CAN0_STS_R&=~0x10;                         //Limpieza del bit de recepcion
    if(NoInt==0x1){
        Rx[0]=CAN_Rx(NoInt);                //Recepción de datos
        //Leds();
    }
    if(NoInt==0x3){
        Rx[1]=CAN_Rx(NoInt);                //Recepciónn de datos
        //Leds();
    }
}

void Config_Puertos(void){                      //(TM4C1294NCPDT)
    SYSCTL_RCGCGPIO_R|=0x01;
    //Reloj Puerto A
    while((SYSCTL_PRGPIO_R&0x01)==0){}
    GPIO_PORTA_AHB_AFSEL_R=0x3;                 //PA0 y PA1 funci�n alterna
    GPIO_PORTA_AHB_PCTL_R=0x77;                 //Funci�n CAN a los pines PA0-PA1
    GPIO_PORTA_AHB_DEN_R=0x3;
    SYSCTL_RCGCGPIO_R |= 0X1100;    // Habilita reloj para puerto J y N
    while((SYSCTL_PRGPIO_R & 0x1100)==0){}

    GPIO_PORTJ_AHB_DIR_R &= ~0x01;       // (c) PJ0 dirección entrada - boton SW1
    GPIO_PORTJ_AHB_DEN_R |= 0x01;        //     PJ0 se habilita
    GPIO_PORTJ_AHB_PUR_R |= 0x01;        //     habilita weak pull-up on PJ1
    GPIO_PORTJ_AHB_IS_R &= ~0x01;        // (d) PJ1 es sensible por flanco
    GPIO_PORTJ_AHB_IBE_R &= ~0x01;       //     PJ1 no es sensible a dos flancos
    GPIO_PORTJ_AHB_IEV_R &= ~0x01;       //     PJ1 detecta eventos de flanco de bajada
    GPIO_PORTJ_AHB_ICR_R = 0x01;         // (e) limpia la bandera 0
    GPIO_PORTJ_AHB_IM_R |= 0x01;         // (f) Se desenmascara la interrupcion PJ0 y se envia al controlador de interrupciones
    NVIC_PRI12_R = (NVIC_PRI12_R&0x00FFFFFF)|0x00000000; // (g) prioridad 0 (pag 159)         //(h) habilita la interrupción 51 en NVIC (Pag. 154)
    NVIC_EN1_R|=((1<<(51-32)) & 0xFFFFFFFF);

    //Para LEDS
    GPIO_PORTN_DIR_R |= 0X01;   // PN0 como salida
    GPIO_PORTN_DEN_R |= 0X01;   // Habilita PN0
    GPIO_PORTN_DATA_R &= ~0x01;     // Se apaga PN0
}


//--------------------------------------------------------------------
//%%%%%%%%%%%%%%%%%%%%    INICIALIZACI�N CAN0     %%%%%%%%%%%%%%%%%%%%
//--------------------------------------------------------------------
void Config_CAN(void){
    SYSCTL_RCGCCAN_R=0x1;                       //Reloj modulo 0 CAN
    while((SYSCTL_PRCAN_R&0x1)==0){}
                                                //Bit Rate= 1 Mbps      CAN clock=16 [Mhz]
    CAN0_CTL_R=0x41;                            //Deshab. modo prueba, Hab. cambios en la config. y hab. inicializacion
    CAN0_BIT_R=0x4900;                          //TSEG2=4   TSEG1=9    SJW=0    BRP=0
                                                //Lenght Bit time=[TSEG2+TSEG1+3]*tq
                                                //               =[(Phase2-1)+(Prop+Phase1-1)+3]*tq
    CAN0_CTL_R&=~0x41;                          //Hab. cambios en la config. y deshab. inicializacion
    CAN0_CTL_R|=0x02;                            //Hab de interrupci�n en el m�dulo CAN
    NVIC_EN1_R|=((1<<(38-32)) & 0xFFFFFFFF);    //(TM4C1294NCPDT)

}



