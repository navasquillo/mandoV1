
/* ################## Include's ####################### */

    /* Include types */
    #include "libTypes_api.h"

    /* Local prototypes */
    #include "ecualm_api.h"

    /* Include external API's */
    #include "iom_api.h"
    #include "adm_api.h"
    #include "pmm_api.h"
    //
    #include "usbm_api.h"
    #include "i2cm_api.h"


/* ################## Define's ######################### */


/* ################## Global variables ################# */


/* ################## Local functions / Macros ######### */



//#####################################################
//#####################  SW Code  #####################
//#####################################################

/* ********************************* INIT ********************************* */
void ECUALM_Init(void) {
    /* Inputs / Outputs */
    IOM_Init();
    ADM_Init();
    //
    PMM_Init();

    /* Communications */
    #ifdef USBM_USB_ENABLED
        USBM_Init();
    #endif
    //
    I2CM_Init();
}


void ECUALM_DeInit(void) {
    /* Inputs / Outputs */
    IOM_DeInit();
    ADM_DeInit();
    //
    PMM_DeInit();

    /* Communications */
    #ifdef USBM_USB_ENABLED
        USBM_DeInit();
    #endif
    //
    I2CM_DeInit();
}


void ECUALM_PostInit(void) {
    /* Inputs */

    /* Communications */

    /* Outputs */

}



/* ********************************* REPORT INFO ********************************* */



/* ********************************* TEST FUNCTIONS ********************************* */


