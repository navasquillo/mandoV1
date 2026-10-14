
/* ################## Include's ####################### */

    /* Include types */
    #include "libTypes_api.h"

    /* Local prototypes */
    #include "pmm_api.h"
    #include "pmm.h"


/* ################## Define's ######################### */


/* ################## Global variables ################# */


/* ################## Local functions / Macros ######### */
    /* Macros */

    /* Local functions */



//#####################################################
//#####################  SW Code  #####################
//#####################################################

/* ********************************* INIT ********************************* */
void PMM_Init(void) {
    Pmm_MotorArc_Init();
    Pmm_LedRgb_Init();
}

void PMM_DeInit(void) {
    Pmm_MotorArc_DeInit();
    Pmm_LedRgb_DeInit();
}



/* ********************************* PERIODIC TASKS ********************************* */
void PMM_Task_5ms(void) {
    //Pmm_MotorArc_Task5ms();
}

void PMM_Task_100ms(void) {
    //Pmm_LedRgb_Task100ms();
}



/* ********************************* UPDATE TASKS ********************************* */
