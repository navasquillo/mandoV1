
/* ################## Include's ####################### */

    /* Include types */
    #include "libTypes_api.h"

    /* Local prototypes */
    #include "pmm_api.h"
    #include "pmm_cfg.h"
    #include "pmm.h"

    /* DFA's */

    /* Include external API's */
    #include "mcalm_api.h"
    #include "mcalm_cfg.h"


/* ################## Define's ######################### */


/* ################## Global variables ################# */
    // External variables
    extern TIM_HandleTypeDef pmm_LED_RGB__MODULE;

    // swC variables
    volatile S_PMM_LedRgb_Module  pmm_LedRgb_Module;


/* ################## Local functions / Macros ######### */
    /* Macros */

    /* Local functions */
        static inline void pmm_LedRgb_PwmOutputsInit(void);
        static inline void pmm_LedRgb_UpdatePwmOutputs(void);



//#####################################################
//#####################  SW Code  #####################
//#####################################################

/* ********************************* INIT ********************************* */
void Pmm_LedRgb_Init(void) {
    //
    // 1) Initialize swC variables
    // Requests
    pmm_LedRgb_Module.RequestData.Freq_Hz             = pmm_LED_RGB__MODULE_OUTPUT_FREQ_DEF;
    pmm_LedRgb_Module.RequestData.Duty_1decimal_Led_R = pmm_OFF_DUTY;
    pmm_LedRgb_Module.RequestData.Duty_1decimal_Led_G = pmm_OFF_DUTY;
    pmm_LedRgb_Module.RequestData.Duty_1decimal_Led_B = pmm_OFF_DUTY;
    pmm_LedRgb_Module.RequestData.Duty_1decimal_Ch4   = pmm_OFF_DUTY;
    pmm_LedRgb_Module.FreqTicks                       = T_U32_MIN;
    //
    // Register Data
    pmm_LedRgb_Module.RegData.FreqRegValue        = T_U32_MIN;
    pmm_LedRgb_Module.RegData.DutyRegValue_Led_R  = T_U32_MIN;
    pmm_LedRgb_Module.RegData.DutyRegValue_Led_G  = T_U32_MIN;
    pmm_LedRgb_Module.RegData.DutyRegValue_Led_B  = T_U32_MIN;
    pmm_LedRgb_Module.RegData.DutyRegValue_CCR4   = T_U32_MIN;

    // 2) Initialize PWM_Output Timers
    pmm_LedRgb_PwmOutputsInit();
}


void Pmm_LedRgb_DeInit(void) {
    //
    // 1) Stop PWM_Output Signals
    HAL_TIM_PWM_Stop( &pmm_LED_RGB__MODULE,   pmm_LED_RGB__R_CHANNEL );
    HAL_TIM_PWM_Stop( &pmm_LED_RGB__MODULE,   pmm_LED_RGB__G_CHANNEL );
    HAL_TIM_PWM_Stop( &pmm_LED_RGB__MODULE,   pmm_LED_RGB__B_CHANNEL );

    // 2) De-Initialize Timer
    HAL_TIM_Base_DeInit( &pmm_LED_RGB__MODULE );
}


static inline void pmm_LedRgb_PwmOutputsInit(void) {
    /*
    TIM5 configuration:
     - PWM Generation CH1 / CH2 / CH3
     - Counter Mode: Up
     - Auto-reload preload:     Enable
     - Capture/Compare preload: Enable
     - Trigger Event Selection: Reset
    */

    // 1) Start PWM  ( ----- Very important to set it firstly! ----- )
    HAL_TIM_PWM_Start( &pmm_LED_RGB__MODULE,  pmm_LED_RGB__R_CHANNEL );
    HAL_TIM_PWM_Start( &pmm_LED_RGB__MODULE,  pmm_LED_RGB__G_CHANNEL );
    HAL_TIM_PWM_Start( &pmm_LED_RGB__MODULE,  pmm_LED_RGB__B_CHANNEL );

    // 2) Set PWM Configuration (initial Frequency and Duty Cycle)
    pmm_LED_RGB__MODULE.Init.RepetitionCounter = 0u;
    __HAL_TIM_SET_COUNTER( &pmm_LED_RGB__MODULE, T_U32_MIN );
    //
    PMM_LedRgb_SetFreqDuty( pmm_LED_RGB__MODULE_OUTPUT_FREQ_DEF, pmm_OFF_DUTY, pmm_OFF_DUTY, pmm_OFF_DUTY );
}



/* ********************************* PERIODIC TASKS ********************************* */
void Pmm_LedRgb_Task5ms(void) {
    //
}



/* ********************************* UPDATE TASKS ********************************* */
void PMM_LedRgb_SetDuty(T_u32 duty2set_Led_R, T_u32 duty2set_Led_G, T_u32 duty2set_Led_B) {
    if ( (duty2set_Led_R <= pmm_MAX_DUTY) && (duty2set_Led_G <= pmm_MAX_DUTY) && (duty2set_Led_B <= pmm_MAX_DUTY) ) {
        pmm_LedRgb_Module.RequestData.Duty_1decimal_Led_R = duty2set_Led_R;
        pmm_LedRgb_Module.RequestData.Duty_1decimal_Led_G = duty2set_Led_G;
        pmm_LedRgb_Module.RequestData.Duty_1decimal_Led_B = duty2set_Led_B;
        //
        pmm_CalculateDutyRegValue( pmm_LedRgb_Module.FreqTicks,  pmm_LedRgb_Module.RequestData.Duty_1decimal_Led_R,    pmm_LedRgb_Module.RegData.DutyRegValue_Led_R );
        pmm_CalculateDutyRegValue( pmm_LedRgb_Module.FreqTicks,  pmm_LedRgb_Module.RequestData.Duty_1decimal_Led_G,    pmm_LedRgb_Module.RegData.DutyRegValue_Led_G );
        pmm_CalculateDutyRegValue( pmm_LedRgb_Module.FreqTicks,  pmm_LedRgb_Module.RequestData.Duty_1decimal_Led_B,    pmm_LedRgb_Module.RegData.DutyRegValue_Led_B );
        //
        pmm_LedRgb_UpdatePwmOutputs();
    }
}

void PMM_LedRgb_SetFreqDuty(T_u32 freq2set_Hz, T_u32 duty2set_Led_R, T_u32 duty2set_Led_G, T_u32 duty2set_Led_B) {
    if( (freq2set_Hz >= pmm_LED_RGB__MODULE_OUTPUT_FREQ_MIN) && (freq2set_Hz <= pmm_LED_RGB__MODULE_OUTPUT_FREQ_MAX) ) {
        if ( (duty2set_Led_R <= pmm_MAX_DUTY) && (duty2set_Led_G <= pmm_MAX_DUTY) && (duty2set_Led_B <= pmm_MAX_DUTY) ) {
            pmm_LedRgb_Module.RequestData.Freq_Hz             = freq2set_Hz;
            pmm_LedRgb_Module.RequestData.Duty_1decimal_Led_R = duty2set_Led_R;
            pmm_LedRgb_Module.RequestData.Duty_1decimal_Led_G = duty2set_Led_G;
            pmm_LedRgb_Module.RequestData.Duty_1decimal_Led_B = duty2set_Led_B;
            //
            pmm_LedRgb_Module.FreqTicks =  pmm_LED_RGB__MODULE_CLK / pmm_LedRgb_Module.RequestData.Freq_Hz;
            pmm_CalculateFreqRegValue( pmm_LedRgb_Module.FreqTicks,  pmm_LedRgb_Module.RegData.FreqRegValue );
            pmm_CalculateDutyRegValue( pmm_LedRgb_Module.FreqTicks,  pmm_LedRgb_Module.RequestData.Duty_1decimal_Led_R,  pmm_LedRgb_Module.RegData.DutyRegValue_Led_R );
            pmm_CalculateDutyRegValue( pmm_LedRgb_Module.FreqTicks,  pmm_LedRgb_Module.RequestData.Duty_1decimal_Led_G,  pmm_LedRgb_Module.RegData.DutyRegValue_Led_G );
            pmm_CalculateDutyRegValue( pmm_LedRgb_Module.FreqTicks,  pmm_LedRgb_Module.RequestData.Duty_1decimal_Led_B,  pmm_LedRgb_Module.RegData.DutyRegValue_Led_B );
            //
            pmm_LedRgb_UpdatePwmOutputs();
        }
    }
}

static inline void pmm_LedRgb_UpdatePwmOutputs(void) {
    __HAL_TIM_SET_AUTORELOAD( &pmm_LED_RGB__MODULE, pmm_LedRgb_Module.RegData.FreqRegValue );
    pmm_LED_RGB__MODULE.Instance->CCR1 = pmm_LedRgb_Module.RegData.DutyRegValue_Led_R;
    pmm_LED_RGB__MODULE.Instance->CCR2 = pmm_LedRgb_Module.RegData.DutyRegValue_Led_G;
    pmm_LED_RGB__MODULE.Instance->CCR3 = pmm_LedRgb_Module.RegData.DutyRegValue_Led_B;
}



/* ********************************* TEST FUNCTIONS ********************************* */
#ifdef PMM_TEST_FUNCTIONS_ENABLED__LED_RGB
    void PMM_LedRgb_Test01(void) {
        #if 1
            static T_u32 freq_Hz = 200u;
            //
            if( freq_Hz < 4000u ) {
                freq_Hz += 100u;
            } else {
                freq_Hz = 200u;
            }
            //
            PMM_LedRgb_SetFreqDuty( freq_Hz, 255u, 505u, 805u );
        #else
            static T_u32 duty = pmm_MIN_DUTY;
            //
            if( duty < 10u ) {
                duty += 1u;
            }
            else if( duty < (pmm_MAX_DUTY-100u) ) {
                duty += 100u;
            }
            else if( duty < pmm_MAX_DUTY ) {
                duty += 10u;
            } else {
                duty = pmm_MIN_DUTY;
            }
            //
            PMM_LedRgb_SetFreqDuty( pmm_LED_RGB__MODULE_OUTPUT_FREQ_DEF, duty, duty, duty );
        #endif
    }

    void PMM_LedRgb_Test02(void) {
        static T_u32 freq_Hz = 200u;
        static T_u32 duty    = pmm_MIN_DUTY;
        //
        if( freq_Hz < 5200u ) {
            freq_Hz += 50u;
            duty    += 1u;
        } else {
            freq_Hz = 200u;
            duty    = 0u;
        }
        //
        PMM_LedRgb_SetFreqDuty( freq_Hz, 255u, 505u, 805u );
    }
#endif
