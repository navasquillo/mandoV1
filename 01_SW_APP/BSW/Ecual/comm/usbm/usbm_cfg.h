/* Author:   Sergio Martinez Porras
 * Date:     21/03/2021
 */


/* Configuration Defines -------------------------------------------------------------------*/

    /* Compilation defines */
        #define USBM_USB_ENABLED
        //#define USBM_TEST_FUNCTIONS_ENABLED


    /* General Options */
        #define usbm_msgRX_length                (35u /*msgh_RxQueue_MsgLength*/)
        #define usbm_msgTX_length                (80u /*msgh_TxQueue_MsgLength*/)


    /* Other */
        #define USBM_PERIOD_TASK_10ms            (10u)
        #define USBM_PERIOD_TASK_100ms           (100u)
