/* Author:   Sergio Martinez Porras
 * Date:     01/04/2024
 */


/* Configuration Defines -------------------------------------------------------------------*/

    /* Compilation defines */
        //#define PMM_TEST_FUNCTIONS_ENABLED__MOTOR_ARC
        //#define PMM_TEST_FUNCTIONS_ENABLED__LED_RGB


    /* General Options */
        // Frequency
        #define pmm_DEFAULT_FREQ_HZ                     (1000u)        // Default Frequency =  1.0 kHz

        // Duty Cycle
        #define pmm_OFF_DUTY                            (0u)           // OFF Duty      =   0.0%
        #define pmm_ON_DUTY                             (1000u)        // ON Duty       = 100.0%
        #define pmm_MIN_DUTY                            (0u)           // Min Duty      =   0.0%
        #define pmm_MAX_DUTY                            (1000u)        // Max Duty      = 100.0%
        //
        #define pmm_DEFAULT_DUTY                        (pmm_OFF_DUTY)


    /* Motor configurations */
        #define pmm_MOTOR_ARC__MODULE                   htim1
        #define pmm_MOTOR_ARC__MODULE_CLK               (mcalm_TIM1_FREQ / (mcalm_TIM1_PRESCALER  + 1))   // 4 MHz = 84 MHz / (20+1)
        #define pmm_MOTOR_ARC__MODULE_OUTPUT_FREQ_MIN   (62u)           // 62 Hz
        #define pmm_MOTOR_ARC__MODULE_OUTPUT_FREQ_MAX   (4000u)         // 4 kHz to have 0.1% Duty Cycle resolution
        #define pmm_MOTOR_ARC__MODULE_OUTPUT_FREQ_DEF   (4000u)         // 4 kHz
        #define pmm_MOTOR_GAS__CHANNEL                  TIM_CHANNEL_1
        #define pmm_MOTOR_BRAKE__CHANNEL                TIM_CHANNEL_2   /* Independent PWM channel for MOTOR_BRAKE */
        #define pmm_ARC_BRAKE__CHANNEL                  TIM_CHANNEL_3

    /* Led RGB configurations */
        #define pmm_LED_RGB__MODULE                     htim5
        #define pmm_LED_RGB__MODULE_CLK                 (mcalm_TIM5_FREQ / (mcalm_TIM5_PRESCALER + 1))    // 2 MHz = 84 MHz / (41+1)
        #define pmm_LED_RGB__MODULE_OUTPUT_FREQ_MIN     (31u)           // 31 Hz
        #define pmm_LED_RGB__MODULE_OUTPUT_FREQ_MAX     (2000u)         // 2 kHz to have 0.1% Duty Cycle resolution
        #define pmm_LED_RGB__MODULE_OUTPUT_FREQ_DEF     (2000u)         // 2 kHz
        #define pmm_LED_RGB__R_CHANNEL                  TIM_CHANNEL_1
        #define pmm_LED_RGB__G_CHANNEL                  TIM_CHANNEL_2
        #define pmm_LED_RGB__B_CHANNEL                  TIM_CHANNEL_3


    /* Test functions */
        #define PMM_TEST02__DUTY_MIN                    (583u)   // 583u = 58.3%
        #define PMM_TEST02__VOUT_MIN_mV                 (7000u)
