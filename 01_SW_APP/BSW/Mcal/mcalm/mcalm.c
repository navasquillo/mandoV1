
/* ################## Include's ####################### */

    /* Include types */
    #include "libTypes_api.h"
    #include "stdio.h"
    #include "string.h"

    /* Local prototypes */
    #include "mcalm_api.h"

    /* Include external API's */
    #include "ecualm_api.h"
    #include "iom_api.h"


/* ################## Define's ######################### */
    /* Registers */
    #define REG_RESET_REGISTER                      (RCC->CSR)

    /* Define's */
    #define mcalm_OB_RDP_LEVEL_0                    (0xAAu)
    #define mcalm_OB_RDP_LEVEL_1                    (0xBBu)
    #define mcalm_OB_RDP_LEVEL_2                    (0xCCu)


/* ################## Global variables ################# */
    /* Resets */
        __attribute__((section(".noinit"))) volatile T_u8 mcalm_LogResetReasons[mcalm_NUMBER_RESETS_TO_STORE] = {E_MCALM__NO_reset};
        E_MCALM__ResetReason mcalm_LastResetReason = E_MCALM__NO_reset;

    /* Option Bytes */
        FLASH_OBProgramInitTypeDef mcalm_optionBytes;

    /* OTP */
        uint32_t mcalm_OTP_Data[E_MCALM__OTP_WordsNumber] = {0xFFFFFFFFu};

    /* comm */
        __attribute__((section(".Ram_COMM"))) char mcalm_MsgTX_data[mcalm_MsgTX_length] = {NULL_CHARACTER};


/* ################## Local functions / Macros ######### */
    /* Macros */

    /* Local functions */
        static inline void mcalm_InitVariables(void);
        //
        static inline void mcalm_ReadResetReasons(void);
        //
        static inline void mcalm_OptionBytes_Read(void);
        static inline void mcalm_OptionBytes_Configure(void);
        //
        static inline void mcalm_OTP_FullReading(void);



//#####################################################
//#####################  SW Code  #####################
//#####################################################

/* ********************************* INIT ********************************* */
void MCALM_PeripheralsInit(void) {
    /*IOM_SetOutput__DO_SW_TEST_02( TRUE );*/  // Only for SW Testing

    /* Initialize swC Variables */
    mcalm_InitVariables();

    /* Enable Power to access RTC and Back-Up memory */
    //__HAL_RCC_PWR_CLK_ENABLE();

    /* Read reset reasons */
    mcalm_ReadResetReasons();

    /* Option Bytes */
    mcalm_OptionBytes_Read();
    mcalm_OptionBytes_Configure();

    /* Get OTP data */
    mcalm_OTP_FullReading();

    /*IOM_SetOutput__DO_SW_TEST_02( FALSE );*/  // Only for SW Testing
}


void MCALM_PostInit(void) {
    /* Nothing */
}


static inline void mcalm_InitVariables(void) {
    mcalm_LastResetReason = E_MCALM__NO_reset;
    //
    memset( mcalm_MsgTX_data, NULL_CHARACTER, sizeof(mcalm_MsgTX_data) );
}



/* ********************************* RESETS ********************************* */
void MCALM_ResetSW(void) {
    ECUALM_DeInit();
    //
    HAL_NVIC_SystemReset();
}


static inline void mcalm_ReadResetReasons(void) {

    /*
     *  REF Manual uC (page 123):
     *
     *  The reset source can be identified by checking the reset flags in the Control/Status register,
     *  RCC_CSR (see Section 8.3.10: Control/status register (RCC_CSR)).
     */
    T_u32 resetInfo_regRead = T_U32_MIN;

    // 1) Read Reset reason and clear Reset flags (see page 120 of uC DataSheet)
    resetInfo_regRead   = REG_RESET_REGISTER;
    REG_RESET_REGISTER |= RCC_CSR_RMVF;
    //
    mcalm_LastResetReason = E_MCALM__NO_reset;
    if ((resetInfo_regRead & (RCC_CSR_LSION|RCC_CSR_LSIRDY|RCC_CSR_RMVF|RCC_CSR_BORRSTF|RCC_CSR_PINRSTF|RCC_CSR_PORRSTF|RCC_CSR_SFTRSTF|RCC_CSR_IWDGRSTF|RCC_CSR_WWDGRSTF|RCC_CSR_LPWRRSTF)) != T_U32_MIN) {
        if (resetInfo_regRead & RCC_CSR_LSION)     {   mcalm_LastResetReason = E_MCALM__LSI_on_reset;  }
        if (resetInfo_regRead & RCC_CSR_LSIRDY)    {   mcalm_LastResetReason = E_MCALM__LSI_ready_reset;  }
        if (resetInfo_regRead & RCC_CSR_RMVF)      {   mcalm_LastResetReason = E_MCALM__RMVF_reset; }
        if (resetInfo_regRead & RCC_CSR_BORRSTF)   {   mcalm_LastResetReason = E_MCALM__BOR_reset;  }
        if (resetInfo_regRead & RCC_CSR_PINRSTF)   {   mcalm_LastResetReason = E_MCALM__BUTTON_RST_BOARD_reset;  }
        if (resetInfo_regRead & RCC_CSR_PORRSTF)   {   mcalm_LastResetReason = E_MCALM__POR_reset;  }
        if (resetInfo_regRead & RCC_CSR_SFTRSTF)   {   mcalm_LastResetReason = E_MCALM__SW_reset;  }
        if (resetInfo_regRead & RCC_CSR_IWDGRSTF)  {   mcalm_LastResetReason = E_MCALM__Independent_Watchdog_reset;  }
        if (resetInfo_regRead & RCC_CSR_WWDGRSTF)  {   mcalm_LastResetReason = E_MCALM__Window_Watchdog_reset;  }
        if (resetInfo_regRead & RCC_CSR_LPWRRSTF)  {   mcalm_LastResetReason = E_MCALM__LowPower_reset;  }
    }

    // 2) Update LogResets
    if( mcalm_LastResetReason != E_MCALM__NO_reset ) {
        if( mcalm_LastResetReason == E_MCALM__POR_reset) {
            mcalm_LogResetReasons[7u] = E_MCALM__NO_reset;
            mcalm_LogResetReasons[6u] = E_MCALM__NO_reset;
            mcalm_LogResetReasons[5u] = E_MCALM__NO_reset;
            mcalm_LogResetReasons[4u] = E_MCALM__NO_reset;
            mcalm_LogResetReasons[3u] = E_MCALM__NO_reset;
            mcalm_LogResetReasons[2u] = E_MCALM__NO_reset;
            mcalm_LogResetReasons[1u] = E_MCALM__NO_reset;
            mcalm_LogResetReasons[0u] = E_MCALM__POR_reset;
        } else {
            mcalm_LogResetReasons[7u] = mcalm_LogResetReasons[6u];
            mcalm_LogResetReasons[6u] = mcalm_LogResetReasons[5u];
            mcalm_LogResetReasons[5u] = mcalm_LogResetReasons[4u];
            mcalm_LogResetReasons[4u] = mcalm_LogResetReasons[3u];
            mcalm_LogResetReasons[3u] = mcalm_LogResetReasons[2u];
            mcalm_LogResetReasons[2u] = mcalm_LogResetReasons[1u];
            mcalm_LogResetReasons[1u] = mcalm_LogResetReasons[0u];
            mcalm_LogResetReasons[0u] = mcalm_LastResetReason;
        }
    }
}


E_MCALM__ResetReason MCALM_GetLastResetReason(void) {
    return( mcalm_LastResetReason );
}



/* ********************************* CLOCKS ********************************* */
void HAL_RCC_CSSCallback(void) {
    // After a HSE Clock failure, do a MCU SW Reset
    MCALM_ResetSW();
}



/* ********************************* OPTION BYTES ********************************* */
static inline void mcalm_OptionBytes_Read(void) {
    HAL_FLASHEx_OBGetConfig( &mcalm_optionBytes );
}

static inline void mcalm_OptionBytes_Configure(void) {
    #ifndef DEBUG
        if( (mcalm_optionBytes.RDPLevel == mcalm_OB_RDP_LEVEL_0) || (mcalm_optionBytes.BORLevel != OB_BOR_LEVEL3) ) {
            //
            // 1) Configure Option Bytes
            mcalm_optionBytes.OptionType = (OPTIONBYTE_RDP | OPTIONBYTE_USER | OPTIONBYTE_BOR);
            mcalm_optionBytes.RDPLevel   = mcalm_OB_RDP_LEVEL_1;
            mcalm_optionBytes.USERConfig = (OB_IWDG_SW | OB_STOP_NO_RST | OB_STDBY_NO_RST);
            mcalm_optionBytes.BORLevel   = OB_BOR_LEVEL3;    /* Supply voltage ranges from 2.70 to 3.60 V */

            // 2) Update OptionBytes at uC memory and lock FLASH and Option Bytes
            HAL_FLASH_OB_Unlock();
            HAL_FLASH_Unlock();
            //
            if (HAL_FLASHEx_OBProgram( &mcalm_optionBytes ) == HAL_OK) {
                HAL_FLASH_OB_Launch();  // Apply new Option Bytes and restart MCU
            }
            //
            HAL_FLASH_OB_Lock();
            HAL_FLASH_Lock();

            // 3) Read another time the Option Bytes
            mcalm_OptionBytes_Read();
        }
    #endif
}



/* ********************************* OTP ********************************* */
static inline void mcalm_OTP_FullReading(void) {
    //
    for( uint8_t word_ID=0u; word_ID < E_MCALM__OTP_WordsNumber; word_ID++ ) {
        mcalm_OTP_Data[word_ID] = ((uint32_t*)FLASH_OTP_BASE)[word_ID];
    }
}


uint32_t MCALM_OTP_ReadWord(E_MCALM__OTP_Word_ID word_ID ) {
    return( mcalm_OTP_Data[word_ID] );
}



/* ********************************* FLASH ********************************* */
uint8_t MCALM_IsFlashBusy(void) {
    return( (uint8_t)FLASH_SR_BSY );
}



/* ********************************* REPORT INFO ********************************* */
void MCALM_ReportResetsLog(void) {
    memset(   mcalm_MsgTX_data, NULL_CHARACTER, sizeof(mcalm_MsgTX_data) );
    snprintf( mcalm_MsgTX_data, sizeof(mcalm_MsgTX_data), "<MCU RESET_LOG- %02d %02d %02d %02d %02d %02d %02d %02d>", mcalm_LogResetReasons[0u], mcalm_LogResetReasons[1u], mcalm_LogResetReasons[2u], mcalm_LogResetReasons[3u], mcalm_LogResetReasons[4u], mcalm_LogResetReasons[5u], mcalm_LogResetReasons[6u], mcalm_LogResetReasons[7u] );
}
