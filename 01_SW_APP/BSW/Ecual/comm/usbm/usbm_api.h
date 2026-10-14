/* Author:   Sergio Martinez Porras
 * Date:     21/03/2021
 */

#ifndef USBM_API_H_
#define USBM_API_H_

    #define USBM_MAJOR_VERSION       1
    #define USBM_MINOR_VERSION       0
    #define USBM_PATCH_VERSION       6


    /* Include's -----------------------------------------------------------------*/
        #include "usbm_cfg.h"


    /* Public Defines ------------------------------------------------------------*/


    /* Enumerates / Structures ---------------------------------------------------*/


    /* Public functions ----------------------------------------------------------*/

        /* Init actions */
        void USBM_Init(void);
        void USBM_DeInit(void);
        void USBM_PostInit(void);

        /* TX/RX functions */
        void USBM_Send(char *msgTX, T_u16 message_Length);
        void USBM_ProcessRXdata(char *msgRX);

#endif /* USBM_API_H_ */
