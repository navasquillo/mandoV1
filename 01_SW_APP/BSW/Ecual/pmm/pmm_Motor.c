
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
    //
    #ifdef PMM_TEST_FUNCTIONS_ENABLED__MOTOR_ARC
        #include "iom_api.h"
    #endif


/* ################## Define's ######################### */


/* ################## Global variables ################# */
    // External variables
    extern TIM_HandleTypeDef pmm_MOTOR_ARC__MODULE;
    //
    #ifdef PMM_TEST_FUNCTIONS_ENABLED__MOTOR_ARC
        extern uint32_t mes_potenciaTransformat;
        extern uint32_t mes_corbaTransformat;
        extern uint32_t mes_adcSupply12v;
    #endif

    // swC variables
    volatile S_PMM_MotorArc_Module  pmm_MotorArc_Module;
    //
    #ifdef PMM_TEST_FUNCTIONS_ENABLED__MOTOR_ARC
        T_u32 pmm_Test_motorFreq_Hz;
        T_u32 pmm_Test_motorDuty;
    #endif


/* ################## Local functions / Macros ######### */
    /* Macros */

    /* Local functions */
        static inline void pmm_MotorArc_PwmOutputsInit(void);
        static inline void pmm_MotorArc_UpdatePwmOutputs(void);



//#####################################################
//#####################  SW Code  #####################
//#####################################################

/* ********************************* INIT ********************************* */
void Pmm_MotorArc_Init(void) {
    //
    // 1) Initialize swC variables
    // Requests
    pmm_MotorArc_Module.RequestData.Freq_Hz                  = pmm_MOTOR_ARC__MODULE_OUTPUT_FREQ_DEF;
    pmm_MotorArc_Module.RequestData.Duty_1decimal_MotorGas   = pmm_OFF_DUTY;
    pmm_MotorArc_Module.RequestData.Duty_1decimal_MotorBrake = pmm_OFF_DUTY;
    pmm_MotorArc_Module.RequestData.Duty_1decimal_ArcBrake   = pmm_OFF_DUTY;
    pmm_MotorArc_Module.RequestData.Duty_1decimal_Ch4        = pmm_OFF_DUTY;
    pmm_MotorArc_Module.FreqTicks                            = T_U32_MIN;
    //
    // Register Data
    pmm_MotorArc_Module.RegData.FreqRegValue             = T_U16_MIN;
    pmm_MotorArc_Module.RegData.DutyRegValue_MotorGas    = T_U16_MIN;
    pmm_MotorArc_Module.RegData.DutyRegValue_MotorBrake  = T_U16_MIN;
    pmm_MotorArc_Module.RegData.DutyRegValue_ArcBrake    = T_U16_MIN;
    pmm_MotorArc_Module.RegData.DutyRegValue_CCR4        = T_U16_MIN;
    //
    #ifdef PMM_TEST_FUNCTIONS_ENABLED__MOTOR_ARC
        pmm_Test_motorFreq_Hz = T_U32_MIN;
        pmm_Test_motorDuty    = T_U32_MIN;
    #endif

    // 2) Initialize PWM_Output Timers
    pmm_MotorArc_PwmOutputsInit();
}


void Pmm_MotorArc_DeInit(void) {
    //
    // 1) Stop PWM_Output Signals
    HAL_TIM_PWM_Stop( &pmm_MOTOR_ARC__MODULE,   pmm_MOTOR_GAS__CHANNEL );
    HAL_TIM_PWM_Stop( &pmm_MOTOR_ARC__MODULE,   pmm_MOTOR_BRAKE__CHANNEL );
    HAL_TIM_PWM_Stop( &pmm_MOTOR_ARC__MODULE,   pmm_ARC_BRAKE__CHANNEL );

    // 2) De-Initialize Timer
    HAL_TIM_Base_DeInit( &pmm_MOTOR_ARC__MODULE );
}


static inline void pmm_MotorArc_PwmOutputsInit(void) {
    /*
    TIM1 configuration:
     - PWM Generation CH1 / CH2 / CH3
     - Counter Mode: Up
     - Repetition Counter: 0
     - Auto-reload preload: Enable
     - Capture/Compare preload: Enable
     - Trigger Event Selection: Reset
    */

    // 1) Start PWM  ( ----- Very important to set it firstly! ----- )
    HAL_TIM_PWM_Start( &pmm_MOTOR_ARC__MODULE,  pmm_MOTOR_GAS__CHANNEL );
    HAL_TIM_PWM_Start( &pmm_MOTOR_ARC__MODULE,  pmm_MOTOR_BRAKE__CHANNEL );
    HAL_TIM_PWM_Start( &pmm_MOTOR_ARC__MODULE,  pmm_ARC_BRAKE__CHANNEL );

    // 2) Set PWM Configuration (initial Frequency and Duty Cycle)
    pmm_MOTOR_ARC__MODULE.Init.RepetitionCounter = 0u;
    __HAL_TIM_SET_COUNTER( &pmm_MOTOR_ARC__MODULE, T_U16_MIN );
    //
    PMM_MotorArc_SetFreqDuty( pmm_MOTOR_ARC__MODULE_OUTPUT_FREQ_DEF, pmm_OFF_DUTY, pmm_OFF_DUTY, pmm_OFF_DUTY );
}



/* ********************************* PERIODIC TASKS ********************************* */
void Pmm_MotorArc_Task5ms(void) {
    //
}



/* ********************************* UPDATE TASKS ********************************* */
void PMM_MotorArc_SetDuty(T_u32 duty2set_MotorGas, T_u32 duty2set_MotorBrake, T_u32 duty2set_ArcBrake) {
    if ( (duty2set_MotorGas <= pmm_MAX_DUTY) && (duty2set_MotorBrake <= pmm_MAX_DUTY) && (duty2set_ArcBrake <= pmm_MAX_DUTY) ) {
        pmm_MotorArc_Module.RequestData.Duty_1decimal_MotorGas   = duty2set_MotorGas;
        pmm_MotorArc_Module.RequestData.Duty_1decimal_MotorBrake = duty2set_MotorBrake;
        pmm_MotorArc_Module.RequestData.Duty_1decimal_ArcBrake   = duty2set_ArcBrake;
        //
        pmm_CalculateDutyRegValue(  pmm_MotorArc_Module.FreqTicks,  pmm_MotorArc_Module.RequestData.Duty_1decimal_MotorGas,     pmm_MotorArc_Module.RegData.DutyRegValue_MotorGas );
        pmm_CalculateDutyRegValue(  pmm_MotorArc_Module.FreqTicks,  pmm_MotorArc_Module.RequestData.Duty_1decimal_MotorBrake,   pmm_MotorArc_Module.RegData.DutyRegValue_MotorBrake );
        pmm_CalculateDutyRegValue(  pmm_MotorArc_Module.FreqTicks,  pmm_MotorArc_Module.RequestData.Duty_1decimal_ArcBrake,     pmm_MotorArc_Module.RegData.DutyRegValue_ArcBrake );
        //
        pmm_MotorArc_UpdatePwmOutputs();
    }
}

void PMM_MotorArc_SetFreqDuty(T_u32 freq2set_Hz, T_u32 duty2set_MotorGas, T_u32 duty2set_MotorBrake, T_u32 duty2set_ArcBrake) {
    if( (freq2set_Hz >= pmm_MOTOR_ARC__MODULE_OUTPUT_FREQ_MIN) && (freq2set_Hz <= pmm_MOTOR_ARC__MODULE_OUTPUT_FREQ_MAX) ) {
        if ( (duty2set_MotorGas <= pmm_MAX_DUTY) && (duty2set_MotorBrake <= pmm_MAX_DUTY) && (duty2set_ArcBrake <= pmm_MAX_DUTY) ) {
            pmm_MotorArc_Module.RequestData.Freq_Hz                  = freq2set_Hz;
            pmm_MotorArc_Module.RequestData.Duty_1decimal_MotorGas   = duty2set_MotorGas;
            pmm_MotorArc_Module.RequestData.Duty_1decimal_MotorBrake = duty2set_MotorBrake;
            pmm_MotorArc_Module.RequestData.Duty_1decimal_ArcBrake   = duty2set_ArcBrake;
            //
            pmm_MotorArc_Module.FreqTicks = pmm_MOTOR_ARC__MODULE_CLK / pmm_MotorArc_Module.RequestData.Freq_Hz;
            pmm_CalculateFreqRegValue(  pmm_MotorArc_Module.FreqTicks,  pmm_MotorArc_Module.RegData.FreqRegValue );
            pmm_CalculateDutyRegValue(  pmm_MotorArc_Module.FreqTicks,  pmm_MotorArc_Module.RequestData.Duty_1decimal_MotorGas,     pmm_MotorArc_Module.RegData.DutyRegValue_MotorGas );
            pmm_CalculateDutyRegValue(  pmm_MotorArc_Module.FreqTicks,  pmm_MotorArc_Module.RequestData.Duty_1decimal_MotorBrake,   pmm_MotorArc_Module.RegData.DutyRegValue_MotorBrake );
            pmm_CalculateDutyRegValue(  pmm_MotorArc_Module.FreqTicks,  pmm_MotorArc_Module.RequestData.Duty_1decimal_ArcBrake,     pmm_MotorArc_Module.RegData.DutyRegValue_ArcBrake );
            //
            pmm_MotorArc_UpdatePwmOutputs();
        }
    }
}

static inline void pmm_MotorArc_UpdatePwmOutputs(void) {
    __HAL_TIM_SET_AUTORELOAD( &pmm_MOTOR_ARC__MODULE, pmm_MotorArc_Module.RegData.FreqRegValue );
    pmm_MOTOR_ARC__MODULE.Instance->CCR1 = pmm_MotorArc_Module.RegData.DutyRegValue_MotorGas;
    pmm_MOTOR_ARC__MODULE.Instance->CCR2 = pmm_MotorArc_Module.RegData.DutyRegValue_MotorBrake;
    pmm_MOTOR_ARC__MODULE.Instance->CCR3 = pmm_MotorArc_Module.RegData.DutyRegValue_ArcBrake;
}



/* ********************************* TEST FUNCTIONS ********************************* */
#ifdef PMM_TEST_FUNCTIONS_ENABLED__MOTOR_ARC
    void PMM_MotorArc_Test01(void) {
        #if 1
            static T_u32 freq_Hz = 200u;
            //
            if( freq_Hz < 4000u ) {
                freq_Hz += 100u;
            } else {
                freq_Hz = 200u;
            }
            //
            PMM_MotorArc_SetFreqDuty( freq_Hz, 255u, 505u, 805u );
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
            PMM_MotorArc_SetFreqDuty( pmm_MOTOR_ARC__MODULE_OUTPUT_FREQ_DEF, duty, (1000u-duty), 105u );
        #endif
    }

    void PMM_MotorArc_Test02_FreqDuty_With2Potentiometers(void) {
        T_u32 freqStepValue;
        //
        // 1.1) Set Frequency
        if( IOM_ReadInput__DI_SWITCH_1() ) {
            // Range 200 Hz to 1200 Hz  --> 10 Hz/step
            freqStepValue         = (1200u - 200u) / pmm_MAX_DUTY;
            pmm_Test_motorFreq_Hz = (mes_potenciaTransformat * freqStepValue) + 200u;
        }
        else {
            // Range 1000 Hz to 4000 Hz  --> 30 Hz/step
            freqStepValue         = (4000u - 1000u) / pmm_MAX_DUTY;
            pmm_Test_motorFreq_Hz = (mes_potenciaTransformat * freqStepValue) + 1000u;
        }

        // 1.2) Set Duty
        pmm_Test_motorDuty = (mes_corbaTransformat * 10u);

        // 2) Update PWM Output
        PMM_MotorArc_SetFreqDuty( pmm_Test_motorFreq_Hz, pmm_Test_motorDuty, pmm_ON_DUTY, 105u );
    }


    void PMM_MotorArc_Test03_FreqDuty_With2Potentiometers(void) {
        T_u32 freqStepValue;
        float dutyStepValue_F;
        //
        // 1.1) Set Frequency
        // Range 200 Hz to 5200 Hz  --> 50 Hz/step
        freqStepValue         = (5200u - 200u) / pmm_MAX_DUTY;
        pmm_Test_motorFreq_Hz = (mes_potenciaTransformat * freqStepValue) + 200u;

        // 1.2) Set Duty
        if( IOM_ReadInput__DI_SWITCH_1() ) {
            // 1.2.1) Duty between PMM_TEST02__DUTY_MIN and 100%
            T_u32 value        = pmm_MAX_DUTY - PMM_TEST02__DUTY_MIN;
            dutyStepValue_F    = (float)value / (float)pmm_MAX_DUTY;
            pmm_Test_motorDuty = ((float)mes_corbaTransformat * dutyStepValue_F) + (float)PMM_TEST02__DUTY_MIN;
        }
        else {
            // 1.2.2) Read VCC and calculate minimum Duty Cycle to have PMM_TEST02__VOUT_MIN_mV at the Output (Motor)
            T_u32 value             = PMM_TEST02__VOUT_MIN_mV * pmm_MAX_DUTY;
            float minDutyOutput9V_F = ((float)value / (float)mes_adcSupply12v);    // ( ((PMM_TEST02__VOUT_MIN_mV mV * 100%) / adcSupply12v)
            dutyStepValue_F         = (100.00F - minDutyOutput9V_F) / (float)pmm_MAX_DUTY;
            pmm_Test_motorDuty      = ((float)mes_corbaTransformat * dutyStepValue_F) + minDutyOutput9V_F;
        }

        // 2) Update PWM Output
        PMM_MotorArc_SetFreqDuty( pmm_Test_motorFreq_Hz, pmm_Test_motorDuty, pmm_ON_DUTY, 105u );
    }
#endif
