
/* ################## Include's ####################### */

    /* Include types */
    #include "libTypes_api.h"
    #include "dataFormat_api.h"
    #include <stdio.h>
    #include <string.h>

    /* Local prototypes */
    #include "usbm_api.h"
    #include "usbm_cfg.h"

    /* Include external API's */
    #include "usbd_cdc_if.h"


/* ################## Define's ######################### */


/* ################## Global variables ################# */
    // External
        extern USBD_HandleTypeDef hUsbDeviceFS;
        extern T_u8 UserRxBufferFS[APP_RX_DATA_SIZE];
        extern T_u8 UserTxBufferFS[APP_TX_DATA_SIZE];

    // RX / TX
        __attribute__((section(".Ram_COMM"))) char  usbm_dataTX[usbm_msgTX_length];


/* ################## Local functions / Macros ######### */
    #ifdef USBM_TEST_FUNCTIONS_ENABLED
        static inline void usbm_Test_MsgTX(void):
    #endif



//#####################################################
//#####################  SW Code  #####################
//#####################################################

/* ********************************* INIT ********************************* */
void USBM_Init(void) {
    // 1) Restart variables
    memset( UserRxBufferFS,  NULL_CHARACTER,  sizeof(UserRxBufferFS) );  // Clean RX buffer
    memset( UserTxBufferFS,  NULL_CHARACTER,  sizeof(UserTxBufferFS) );  // Clean TX buffer
    memset( usbm_dataTX,     NULL_CHARACTER,  sizeof(usbm_dataTX) );     // Clean TX buffer

    // 2) Init USB
    USBD_Interface_fops_FS.Init();
    USBD_CDC_ReceivePacket( &hUsbDeviceFS );    // Allow receive messages via USB
}


void USBM_DeInit(void) {
    USBD_Interface_fops_FS.DeInit();
}


void USBM_PostInit(void) {
    #ifdef USBM_TEST_FUNCTIONS_ENABLED
        usbm_Test_MsgTX();
    #endif
}



/* ********************************* OTHER TASKS ********************************* */
void USBM_Send(char *msgTX, T_u16 message_Length) {
    (void)CDC_Transmit_FS( (uint8_t *)msgTX, (uint16_t)message_Length );
}


void USBM_ProcessRXdata(char* msgRX) {
    #ifdef USBM_USB_ENABLED
        uint8_t  usbm_ProcessData = FALSE;
        uint16_t i;
        //
        // 1) Check message format
        if( msgRX[0u] == '[' ) {         // PcLapCounter messages
            for( i=1u; i<usbm_msgRX_length; i++ ) {
                if( msgRX[i] == ']' ) {
                    usbm_ProcessData = TRUE;
                    break;
                }
            }
        }
        else if( msgRX[0u] == '<' ) {    // Internal messages
            for( i=1u; i<usbm_msgRX_length; i++ ) {
                if( msgRX[i] == '>' ) {
                    usbm_ProcessData = TRUE;
                    break;
                }
            }
        } else { /* Nothing */ }

        // 2) Process message
        if( usbm_ProcessData ) {
            /* Function to process received message (swC B2H) */
        } else { /* Nothing */ }
    #endif
}



/* ********************************* REPORT INFO ********************************* */



/* ********************************* TEST FUNCTIONS ********************************* */
#ifdef USBM_TEST_FUNCTIONS_ENABLED
    static inline void usbm_Test_MsgTX(void) {
        static uint16_t cnt = T_U16_MIN;
        //
        snprintf(  usbm_dataTX, sizeof(usbm_dataTX), "Hello USB World--%d!", cnt );
        USBM_Send( usbm_dataTX, sizeof(usbm_dataTX) );
        cnt++;
    }
#endif
