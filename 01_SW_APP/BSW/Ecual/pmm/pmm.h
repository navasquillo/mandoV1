/* Author:   Sergio Martinez Porras
 * Date:     01/04/2024
 */


/* ################## Include's ####################### */
    #include "stdint.h"

/* ################## Structures ######### */
    // 1) LedRgb Module
    typedef struct {
        T_u32 Freq_Hz;
        T_u32 Duty_1decimal_Led_R;
        T_u32 Duty_1decimal_Led_G;
        T_u32 Duty_1decimal_Led_B;
        T_u32 Duty_1decimal_Ch4;
    }S_PMM_LedRgb_RequestData;

    typedef struct {
        uint32_t  FreqRegValue;         //  ARR Register
        uint32_t  DutyRegValue_Led_R;   // CCR1 Register
        uint32_t  DutyRegValue_Led_G;   // CCR2 Register
        uint32_t  DutyRegValue_Led_B;   // CCR3 Register
        uint32_t  DutyRegValue_CCR4;    // CCR4 Register
    }S_PMM_LedRgb_RegDataDMA;

    typedef struct {
        S_PMM_LedRgb_RequestData RequestData;
        T_u32                    FreqTicks;
        S_PMM_LedRgb_RegDataDMA  RegData;
    }S_PMM_LedRgb_Module;


    // 2) MotorArc Module
    typedef struct {
        T_u32 Freq_Hz;
        T_u32 Duty_1decimal_MotorGas;
        T_u32 Duty_1decimal_MotorBrake;
        T_u32 Duty_1decimal_ArcBrake;
        T_u32 Duty_1decimal_Ch4;
    }S_PMM_MotorArc_RequestData;

    typedef struct {
        uint32_t  FreqRegValue;             //  ARR Register
        uint32_t  DutyRegValue_MotorGas;    // CCR1 Register
        uint32_t  DutyRegValue_MotorBrake;  // CCR2 Register
        uint32_t  DutyRegValue_ArcBrake;    // CCR3 Register
        uint32_t  DutyRegValue_CCR4;        // CCR4 Register
    }S_PMM_MotorArc_RegDataDMA;

    typedef struct {
        S_PMM_MotorArc_RequestData RequestData;
        T_u32                      FreqTicks;
        S_PMM_MotorArc_RegDataDMA  RegData;
    }S_PMM_MotorArc_Module;



/* ################## Local functions / Macros ######### */
    /* Macros */
        #define pmm_CalculateFreqRegValue(freq_ticks, out_FreqRegValue) {  \
            if( freq_ticks != T_U32_MIN ) {  \
                out_FreqRegValue = (freq_ticks - 1u);  \
            } else {  \
                out_FreqRegValue = T_U32_MIN;  \
            }  \
        }

        #define pmm_CalculateDutyRegValue(freq_ticks, valueDuty, out_DutyRegValue ) {  \
            if( valueDuty != T_U32_MIN ) {  \
                out_DutyRegValue = (T_u32)( (freq_ticks * (T_u32)valueDuty) / pmm_MAX_DUTY);  \
            } else {  \
                out_DutyRegValue = T_U32_MIN;  \
            }  \
        }


        /* Local functions */
        void Pmm_MotorArc_Init(void);
        void Pmm_MotorArc_DeInit(void);
        void Pmm_MotorArc_Task5ms(void);
        //
        //
        void Pmm_LedRgb_Init(void);
        void Pmm_LedRgb_DeInit(void);
        void Pmm_LedRgb_Task5ms(void);
