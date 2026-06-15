#include <stdbool.h>
#include <stdint.h>
// #include "tm4c1294ncpdt.h"
#include "IEEE_CAN.h"
// #include "driverlib/sysctl.h"

//------------------------------------------------------------------
//%%%%%%%%%%%%%%%%%%%%    PROGRAMA PRINCIPAL    %%%%%%%%%%%%%%%%%%%%
//------------------------------------------------------------------

void main(void){
    Config_Puertos();
    Config_CAN();

    /*****************************************************/
    /*         PRUEBAS SIN FILTROS                      */
    /*****************************************************/

    /*****************************************************/
    /*   ** Recepci�n Sencilla, Transmisi�n Sencilla,   */
    /*      Trama Remota y Respuesta a Trama Remota **   */
    /*****************************************************/


    //Configuraci�n para Recepci�n Sencilla Sin Mascara Localidad #1
    CAN_Memoria_Arb(0xAA,false,0x1);                        //ID, TxRx, Localidad
    CAN_Memoria_CtrlMsk(0xFFF,2,false,true,false,0x1);      //Mask, DLC, TxIE, RxIE, Remote, Localidad

    //Configuraci�n para la Transmisi�n Sencilla Localidad #2
    CAN_Memoria_Arb(0xBB,true,0x2);                         //ID, TxRx, Localidad
    CAN_Memoria_CtrlMsk(0xFFF,2,false,false,false,0x2);     //Mask, DLC, TxIE, RxIE, Remote, Localidad
    CAN_Memoria_Dato(0xBB,0x2);                           //Carga el Campo de Datos de la Transmisi�n Sencilla Localidad #2

    //Configuraci�n para Trama Remota con Recepci�n Localidad #3
    CAN_Memoria_Arb(0xCC,false,0x3);                       //ID, TxRx, Localidad
    CAN_Memoria_CtrlMsk(0xFFF,2,false,true,true,0x3);      //Mask, DLC, TxIE, RxIE, Remote, Localidad

    //Configuraci�n para la Respuesta a Trama Remota Localidad #4
     CAN_Memoria_Arb(0xDD,true,0x4);                       //ID, TxRx, Localidad #4
     CAN_Memoria_CtrlMsk(0xFFF,4,false,false,true,0x4);   //Mask, DLC, TxIE, RxIE, Remote, Localidad #4
     CAN_Memoria_Dato(0x00000000,0x4);                    //Carga el Campo de Datos de la Respuesta a Trama Remota Localidad #4




    /**********************************************/
    /*           PRUEBAS CON FILTROS             */
    /**********************************************/

    /**********************************************/
    /*    TIVA RECEPTORA CON FILTRO               */
    /**********************************************/

/*

    //Configuraci�n para Recepci�n Con Mascara Localidad #1
    CAN_Memoria_Arb(0b10100000111,false,0x1);                   //ID, TxRx, Localidad
    CAN_Memoria_CtrlMsk(0b11100000000,3,false,true,false,0x1);  //Mask, DLC, TxIE, RxIE, Remote, Localidad

    //Configuraci�n para la Transmisi�n Sencilla Localidad #2
    CAN_Memoria_Arb(0b10000000101,true,0x2);                    //ID, TxRx, Localidad
    CAN_Memoria_CtrlMsk(0xFFF,2,false,false,false,0x2);     //Mask, DLC, TxIE, RxIE, Remote, Localidad
    CAN_Memoria_Dato(0x01,0x2);                            //Carga el Campo de Datos de la Tranmisi�n Sencilla Localidad #2

    //Configuraci�n para Trama Remota con Recepci�n Localidad #3
    CAN_Memoria_Arb(0b10101110000,false,0x3);                       //ID, TxRx, Localidad
    CAN_Memoria_CtrlMsk(0xFFF,2,false,true,true,0x3);      //Mask, DLC, TxIE, RxIE, Remote, Localidad

     //Configuraci�n para la Respuesta a Trama Remota Localidad #4
     CAN_Memoria_Arb(0xDD,true,0x4);                       //ID, TxRx, Localidad #4
     CAN_Memoria_CtrlMsk(0xFFF,4,false,false,true,0x4);   //Mask, DLC, TxIE, RxIE, Remote, Localidad #4
     CAN_Memoria_Dato(0x00000000,0x4);                    //Carga el Campo de Datos de la Respuesta a Trama Remota Localidad #4


*/

    /**********************************************/
    /*           PRUEBAS CON FILTROS             */
    /**********************************************/

    /**********************************************/
    /*    TIVA TRANSMISORA CON FILTRO             */
    /**********************************************/


     /*

    //Configuraci�n para Recepci�n Sencilla Sin Mascara Localidad #1
    CAN_Memoria_Arb(0b10000000101,false,0x1);                        //ID, TxRx, Localidad
    CAN_Memoria_CtrlMsk(0xFFF,2,false,true,false,0x1);      //Mask, DLC, TxIE, RxIE, Remote, Localidad

   //Configuraci�n para la Transmisi�n Sencilla Localidad #2
   CAN_Memoria_Arb(0b10101011111,true,0x2);                    //ID, TxRx, Localidad
   CAN_Memoria_CtrlMsk(0xFFF,2,false,false,false,0x2);     //Mask, DLC, TxIE, RxIE, Remote, Localidad
   CAN_Memoria_Dato(0x010A,0x2);

   //Configuraci�n para la Transmisi�n Sencilla Localidad #3
   CAN_Memoria_Arb(0b10100110011,true,0x3);                    //ID, TxRx, Localidad
   CAN_Memoria_CtrlMsk(0xFFF,2,false,false,false,0x3);     //Mask, DLC, TxIE, RxIE, Remote, Localidad
   CAN_Memoria_Dato(0x020B,0x3);

    //Configuraci�n para la Respuesta a Trama Remota Localidad #4
    CAN_Memoria_Arb(0b10101110000,true,0x4);                       //ID, TxRx, Localidad #4
    CAN_Memoria_CtrlMsk(0xFFF,4,false,false,true,0x4);   //Mask, DLC, TxIE, RxIE, Remote, Localidad #4
    CAN_Memoria_Dato(0xDD00DD00,0x4);                    //Carga el Campo de Datos de la Respuesta a Trama Remota Localidad #4

*/

    while(1){

        /*****************************************************/
        /*          EJEMPLO TRANSMISI�N SENCILLA            */
        /*          ACTUALIZANDO CONTADOR                   */
        /*****************************************************/

        /*
        for ( i = 0; i < 500000; i++) {}
        W++;
        CAN_Memoria_Dato(W,0x02);
        CAN_Tx(0x2);
*/

}
}
