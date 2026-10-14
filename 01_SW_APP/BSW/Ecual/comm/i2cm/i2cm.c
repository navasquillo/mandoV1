
/* ################## Include's ####################### */

    /* Include types */
    #include "libTypes_api.h"

    /* Local prototypes */
    #include "i2cm_api.h"
    #include "i2cm_cfg.h"

    /* Include external API's */
    #include "mcalm_api.h"
    //
    #include "ssd1306_api.h"


/* ################## Define's ######################### */


/* ################## Global variables ################# */
    extern I2C_HandleTypeDef i2cm_MODULE_DISPLAY;
    extern DMA_HandleTypeDef i2cm_DMA_tx_MODULE_DISPLAY;
    extern DMA_HandleTypeDef i2cm_DMA_rx_MODULE_DISPLAY;
    extern HAL_TickFreqTypeDef uwTickFreq;
    //
    T_u32 i2cm_cfgExtDevices_Cnt_ms = T_U32_MIN;
    T_u32 i2cm_I2C1_Error           = HAL_I2C_ERROR_NONE;


/* ################## Local functions / Macros ######### */



//#####################################################
//#####################  SW Code  #####################
//#####################################################

/* ********************************* INIT ********************************* */
void I2CM_Init(void) {
    // https://electronics.stackexchange.com/questions/272427/stm32-busy-flag-is-set-after-i2c-initialization

    /* 1) Configure the I2C and DMA */
    HAL_I2C_MspInit( &i2cm_MODULE_DISPLAY );

    /* 2) Initialize I2C variables */
    i2cm_cfgExtDevices_Cnt_ms = T_U32_MIN;
}


void I2CM_PostInit(void) {
    // External Device configuration
    if( i2cm_cfgExtDevices_Cnt_ms == T_U32_MIN ) {
        SSD1306_Init();
    }

    i2cm_cfgExtDevices_Cnt_ms += uwTickFreq;
}


void I2CM_DeInit(void) {
    /* 1) De-Initialize I2C Devices */
    // No De-Init for SSD1306 device

    /* 2) Initialize swC variables */
    i2cm_cfgExtDevices_Cnt_ms = T_U32_MIN;

    /* 3) Stop I2C */
    HAL_I2C_MspDeInit( &i2cm_MODULE_DISPLAY );
}



/* ********************************* CHECKS ********************************* */
T_bit I2CM_SSD1306_IsReadyForNewTransference(void) {
    if (HAL_I2C_GetState(&i2cm_MODULE_DISPLAY) == HAL_I2C_STATE_READY) {
        return( TRUE );
    } else {
        return( FALSE );
    }
}



/* ********************************* INTERRUPTS ********************************* */
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c) {
    if (hi2c->Instance == I2C1) {
        SSD1306_UpdateScreenDMA_Step();
    }
}

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c) {
    if (hi2c->Instance == I2C1) {
        /* Nothing (use to process information received via I2C) */
    }
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c) {
    if (hi2c->Instance == I2C1) {
        /* Error Handling */
        i2cm_I2C1_Error = HAL_I2C_GetError(hi2c);
        i2cm_I2C1_Error = i2cm_I2C1_Error;
    }
}

