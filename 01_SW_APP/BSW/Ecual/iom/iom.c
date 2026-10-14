
/* ################## Include's ####################### */

    /* Include types */
    #include "libTypes_api.h"
    #include "dataFormat_api.h"
    #include <stdio.h>
    #include <string.h>

    /* Local prototypes */
    #include "iom_api.h"
    #include "iom_cfg.h"

    /* DFA's */

    /* Include external API's */
    #include "mcalm_api.h"


/* ################## Define's ######################### */


/* ################## Global variables ################# */
    __attribute__((section(".Ram_COMM"))) char iom_MsgTX_data[iom_MsgTX_length] = {NULL_CHARACTER};

    /* iom_debounce */
    T_bit iom_debounce_last[E_IOM_TOTAL_DI_SIGNALS];
    T_bit iom_debounce_n_1[E_IOM_TOTAL_DI_SIGNALS];
    T_bit iom_debounce_n_2[E_IOM_TOTAL_DI_SIGNALS];
    T_bit iom_processed[E_IOM_TOTAL_DI_SIGNALS];

    /* iom_StartUpValue */
    T_bit iom_StartupValue[E_IOM_TOTAL_DI_SIGNALS];

/* ################## Local functions / Macros ######### */
    /* Local functions */
        /* Initialize the digital inputs and outputs */
        static inline void iom_InputsInit(void);
        static inline void iom_OutputsInit(void);

        /* Read Inputs */
        static inline T_bit iom_ProcessDebounce(E_IOM_DigitalInput i_input);



//#####################################################
//#####################  SW Code  #####################
//#####################################################

/* ********************************* INIT ********************************* */
void IOM_Init(void) {
    T_u32 i;

    // 1) Initialize swC variables
    for (i = T_U32_MIN; i < E_IOM_TOTAL_DI_SIGNALS; i++) {
        iom_debounce_last[i] = FALSE;
        iom_debounce_n_1[i]  = FALSE;
        iom_debounce_n_2[i]  = FALSE;
        iom_processed[i]     = FALSE;
    }

    // 2) Initialize Inputs
    iom_InputsInit();

    // 3) Disable Outputs
    iom_OutputsInit();
}


void IOM_DeInit(void) {
    IOM_Init();
}


static inline void iom_InputsInit(void) {
    //
    // 1) Read start-up values
    iom_StartupValue[E_IOM__DI_BUTTON_1]      = HAL_GPIO_ReadPin( IOM_PIN_INPUT_BUTTON_1 );
    iom_StartupValue[E_IOM__DI_BUTTON_2]      = HAL_GPIO_ReadPin( IOM_PIN_INPUT_BUTTON_2 );
    iom_StartupValue[E_IOM__DI_SWITCH_1]      = HAL_GPIO_ReadPin( IOM_PIN_INPUT_SWITCH_1 );
    //
    iom_StartupValue[E_IOM__DI_IS_ARC_DRIVER] = HAL_GPIO_ReadPin( IOM_PIN_INPUT_IS_ARC_DRIVER );

    // 2) Fill Input buffer
    iom_processed[E_IOM__DI_BUTTON_1]         = iom_StartupValue[E_IOM__DI_BUTTON_1];
    iom_processed[E_IOM__DI_BUTTON_2]         = iom_StartupValue[E_IOM__DI_BUTTON_2];
    iom_processed[E_IOM__DI_SWITCH_1]         = iom_StartupValue[E_IOM__DI_SWITCH_1];
    //
    iom_processed[E_IOM__DI_IS_ARC_DRIVER]    = iom_StartupValue[E_IOM__DI_IS_ARC_DRIVER];
}

static inline void iom_OutputsInit(void) {
    //
    // 1) Initialize values/Outputs
    IOM_SetOutput__DO_PC13_LED(   IOM_LED_PC13_OFF );
    //
    IOM_SetOutput__DO_ARC_CHANGE( IOM_LOW );
    //
    IOM_SetOutput__DO_SW_TEST_01( IOM_LOW );
    IOM_SetOutput__DO_SW_TEST_02( IOM_LOW );
}



/* ********************************* PERIODIC TASKS ********************************* */



/* ********************************* INPUTS ********************************* */
static inline T_bit iom_ProcessDebounce(E_IOM_DigitalInput i_input) {
    //
    // Check input ID  (in case of wrong ID return a FALSE)
    if ( i_input < E_IOM_TOTAL_DI_SIGNALS ) {
        // 1.1) Information MUX
        if ( i_input == E_IOM__DI_BUTTON_1 ) {
            iom_debounce_last[i_input] = (T_bit)HAL_GPIO_ReadPin( IOM_PIN_INPUT_BUTTON_1 );
        } else if ( i_input == E_IOM__DI_BUTTON_2 ) {
            iom_debounce_last[i_input] = (T_bit)HAL_GPIO_ReadPin( IOM_PIN_INPUT_BUTTON_2 );
        } else if ( i_input == E_IOM__DI_SWITCH_1 ) {
            iom_debounce_last[i_input] = (T_bit)HAL_GPIO_ReadPin( IOM_PIN_INPUT_SWITCH_1 );
        } else if ( i_input == E_IOM__DI_IS_ARC_DRIVER ) {
            iom_debounce_last[i_input] = (T_bit)HAL_GPIO_ReadPin( IOM_PIN_INPUT_IS_ARC_DRIVER );
        } else {  /* Nothing */ }


        // 1.2) Do debouncing
        if ( (!iom_debounce_last[i_input]) && (!iom_debounce_n_1[i_input]) && (!iom_debounce_n_2[i_input]) )  {  iom_processed[i_input] = FALSE;  }
        else if ( iom_debounce_last[i_input] && iom_debounce_n_1[i_input] && iom_debounce_n_2[i_input] )      {  iom_processed[i_input] = TRUE;   }
        else {  /* Nothing */ }

        // 1.3) Update needed variables
        iom_debounce_n_2[i_input] = iom_debounce_n_1[i_input];
        iom_debounce_n_1[i_input] = iom_debounce_last[i_input];
        //
        return( iom_processed[i_input] );
    } else {
        return( FALSE );
    }
}


unsigned char IOM__IsConnected_ARC_DRIVER(void) {
    return( iom_StartupValue[E_IOM__DI_IS_ARC_DRIVER] );
}


/* ********************************* OUTPUTS ********************************* */



/* ********************************* REPORT INFO ********************************* */
void IOM_ReportInputReadings_RAW(void) {
    T_bit dataBOOL[4u] = { FALSE };

    // 1) Get data
    dataBOOL[0u] = HAL_GPIO_ReadPin( IOM_PIN_INPUT_BUTTON_1 );
    dataBOOL[1u] = HAL_GPIO_ReadPin( IOM_PIN_INPUT_BUTTON_2 );
    dataBOOL[2u] = HAL_GPIO_ReadPin( IOM_PIN_INPUT_SWITCH_1 );
    dataBOOL[3u] = HAL_GPIO_ReadPin( IOM_PIN_INPUT_IS_ARC_DRIVER );

    // 2) Report Sensings
    memset(   iom_MsgTX_data, NULL_CHARACTER, sizeof(iom_MsgTX_data) );
    snprintf( iom_MsgTX_data, sizeof(iom_MsgTX_data), "<MCU INPUTS_READ_RAW- But1=%d, But2=%d, Sw1=%d, ArcDrv=%d>", dataBOOL[0u], dataBOOL[1u], dataBOOL[2u], dataBOOL[3u] );
}
