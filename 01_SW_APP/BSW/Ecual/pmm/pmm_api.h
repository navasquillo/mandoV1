/* Author:   Sergio Martinez Porras
 * Date:     01/04/2024
 */

#ifndef PMM_API_H_
#define PMM_API_H_

    #define PMM_MAJOR_VERSION       1
    #define PMM_MINOR_VERSION       6
    #define PMM_PATCH_VERSION       0


    /* Include's -----------------------------------------------------------------*/
        #include "libTypes_api.h"
        //
        #include "pmm_cfg.h"


    /* Public Defines ------------------------------------------------------------*/


    /* Enumerates / Structures ---------------------------------------------------*/
        typedef enum {
            E_PWM__MOTOR_GAS,
            E_PWM__MOTOR_BRAKE,
            E_PWM__ARC_BRAKE,
            //
            E_PWM__LED_RGB_R,
            E_PWM__LED_RGB_G,
            E_PWM__LED_RGB_B,
            //
            E_PWM__SW_TEST,
            //
            E_PMM_TOTAL_PWM_SIGNALS
        }E_PwmSignals_ID;

    /* Public functions ----------------------------------------------------------*/

        /* Init actions */
        void PMM_Init(void);
        void PMM_DeInit(void);

        /* Periodic PMM tasks */
        void PMM_Task_5ms(void);
        void PMM_Task_100ms(void);

        /* Outputs tasks */
        void PMM_MotorArc_SetDuty(T_u32 duty2set_MotorGas, T_u32 duty2set_MotorBrake, T_u32 duty2set_ArcBrake);
        void PMM_MotorArc_SetFreqDuty(T_u32 freq2set_Hz, T_u32 duty2set_MotorGas, T_u32 duty2set_MotorBrake, T_u32 duty2set_ArcBrake);
        void PMM_LedRgb_SetDuty(T_u32 duty2set_Led_R, T_u32 duty2set_Led_G, T_u32 duty2set_Led_B);
        void PMM_LedRgb_SetFreqDuty(T_u32 freq2set_Hz, T_u32 duty2set_Led_R, T_u32 duty2set_Led_G, T_u32 duty2set_Led_B);

        /* Test functions */
        #ifdef PMM_TEST_FUNCTIONS_ENABLED__MOTOR_ARC
            void PMM_MotorArc_Test01(void);
            void PMM_MotorArc_Test02_FreqDuty_With2Potentiometers(void);
            void PMM_MotorArc_Test03_FreqDuty_With2Potentiometers(void);
        #endif
        //
        #ifdef PMM_TEST_FUNCTIONS_ENABLED__LED_RGB
            void PMM_LedRgb_Test01(void);
            void PMM_LedRgb_Test02(void);
        #endif
#endif /* PMM_API_H_ */
