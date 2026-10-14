/*
 * File: Gatell.c
 *
 * Code generated for Simulink model 'Gatell'.
 *
 * Model version                  : 1.75
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Fri Dec 19 18:16:44 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "Gatell.h"

/* Named constants for Chart: '<Root>/Gatell' */
#define IN_DEBOUNCE_1                  ((uint8_T)1U)
#define IN_DEBOUNCE_2                  ((uint8_T)2U)
#define IN_DEBOUNCE_3                  ((uint8_T)3U)
#define IN_DEBOUNCE_4                  ((uint8_T)4U)
#define IN_DEBOUNCE_BR_1               ((uint8_T)1U)
#define IN_DEBOUNCE_BR_2               ((uint8_T)2U)
#define IN_DEBOUNCE_CH_1               ((uint8_T)1U)
#define IN_DEBOUNCE_CH_2               ((uint8_T)2U)
#define IN_DEBOUNCE_OFF                ((uint8_T)1U)
#define IN_DEBOUNCE_ON                 ((uint8_T)2U)
#define IN_EN_ST                       ((uint8_T)1U)
#define IN_E_Eixida                    ((uint8_T)1U)
#define IN_E_Fondo                     ((uint8_T)2U)
#define IN_E_Frenada_Mapa_1            ((uint8_T)3U)
#define IN_E_Frenada_Mapa_2            ((uint8_T)4U)
#define IN_E_Frenada_Mapa_3            ((uint8_T)5U)
#define IN_E_Frenada_Mapa_4            ((uint8_T)6U)
#define IN_E_Mitat                     ((uint8_T)7U)
#define IN_LED_OFF                     ((uint8_T)2U)
#define IN_LED_ON                      ((uint8_T)3U)
#define IN_MAPA_FRENO_1                ((uint8_T)5U)
#define IN_MAPA_FRENO_2                ((uint8_T)6U)
#define IN_MAPA_FRENO_3                ((uint8_T)7U)
#define IN_MAPA_FRENO_4                ((uint8_T)8U)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_NO_BRAKE_PULSAT             ((uint8_T)3U)
#define IN_POTENCIA_DINAMICA_OFF       ((uint8_T)3U)
#define IN_POTENCIA_DINAMICA_ON        ((uint8_T)4U)
#define IN_SI_BRAKE_PULSAT             ((uint8_T)4U)

/* user code (top of source file) */
#include "pmm_api.h"
#include "iom_api.h"
#include "m2b.h"
#if defined MANDO_DS

extern TIM_HandleTypeDef pmm_RGB_MOTOR_MODULE;

#elif defined MANDO_DIFALCO

extern TIM_HandleTypeDef pmm_MOTOR_MODULE;
extern TIM_HandleTypeDef pmm_RGB_MODULE;

#endif

/* Exported block signals */
uint32_T mes_gatellFiltratFinalSim;    /* '<Root>/mes_gatellFiltratFinalSim' */
uint32_T pwmRoig;                      /* '<Root>/Gatell' */
uint32_T pwmVerd;                      /* '<Root>/Gatell' */
uint32_T pwmGas;                       /* '<Root>/Gatell' */
uint32_T pwmFreno;                     /* '<Root>/Gatell' */
uint32_T pwmBlau;                      /* '<Root>/Gatell' */
uint32_T diffGatell;                   /* '<Root>/Gatell' */
uint32_T tempsVolta;                   /* '<Root>/Gatell' */
uint32_T flashWrite_mapaFreno;         /* '<Root>/Gatell' */
uint32_T flashWrite_potenciaDin;       /* '<Root>/Gatell' */
uint32_T pwmArcFreno;                  /* '<Root>/Gatell' */
boolean_T flashWrite_IsUpdatedMapaFreno;/* '<Root>/Gatell' */
boolean_T flashWrite_IsUpdatedPotenciaDin;/* '<Root>/Gatell' */

/* Block signals and states (auto storage) */
DW DW_l;
extern real_T rt_roundd_snf(real_T u);

/* Forward declaration for local functions */
static void MAPES_FRENO(const boolean_T *Switch2);
static void POTENCIA_DINAMICA(const boolean_T *Switch3);
static void enter_internal_E_Eixida(void);
static void enter_internal_E_Fondo(void);
static void enter_internal_E_Frenada_Mapa_1(void);
static void enter_internal_E_Mitat(void);
static void E_Fondo(void);
static void E_Frenada_Mapa_2(void);
static void E_Frenada_Mapa_3(void);
static void GATELL(void);
real_T rt_roundd_snf(real_T u)
{
    real_T y;
    if (fabs(u) < 4.503599627370496E+15) {
        if (u >= 0.5) {
            y = floor(u + 0.5);
        } else if (u > -0.5) {
            y = u * 0.0;
        } else {
            y = ceil(u - 0.5);
        }
    } else {
        y = u;
    }

    return y;
}

/* Function for Chart: '<Root>/Gatell' */
static void MAPES_FRENO(const boolean_T *Switch2)
{
    uint64_T tmp;

    /* During 'MAPES_FRENO': '<S1>:174' */
    switch (DW_l.is_MAPES_FRENO) {
      case IN_DEBOUNCE_1:
        /* During 'DEBOUNCE_1': '<S1>:181' */
        if (DW_l.debounceBoto >= DEBOUNCE_BOTO) {
            /* Transition: '<S1>:176' */
            DW_l.is_MAPES_FRENO = IN_MAPA_FRENO_2;

            /* Entry Internal 'MAPA_FRENO_2': '<S1>:244' */
            /* Transition: '<S1>:250' */
            DW_l.is_MAPA_FRENO_2 = IN_EN_ST;

            /* Entry 'EN_ST': '<S1>:305' */
            flashWrite_mapaFreno = 2U;
            flashWrite_IsUpdatedMapaFreno = true;
            DW_l.fondo = false;
            DW_l.blinkLedPC13 = 0U;
            IOM_SetOutput__DO_PC13_LED(IOM_HIGH);
        } else {
            tmp = DW_l.debounceBoto + 1ULL;
            if (tmp > 4294967295ULL) {
                tmp = 4294967295ULL;
            }

            DW_l.debounceBoto = (uint32_T)tmp;
        }
        break;

      case IN_DEBOUNCE_2:
        /* During 'DEBOUNCE_2': '<S1>:246' */
        if (DW_l.debounceBoto >= DEBOUNCE_BOTO) {
            /* Transition: '<S1>:245' */
            DW_l.is_MAPES_FRENO = IN_MAPA_FRENO_3;

            /* Entry 'MAPA_FRENO_3': '<S1>:182' */
            flashWrite_mapaFreno = 3U;
            flashWrite_IsUpdatedMapaFreno = true;
            DW_l.fondo = false;
            IOM_SetOutput__DO_PC13_LED(IOM_LOW);
        } else {
            tmp = DW_l.debounceBoto + 1ULL;
            if (tmp > 4294967295ULL) {
                tmp = 4294967295ULL;
            }

            DW_l.debounceBoto = (uint32_T)tmp;
        }
        break;

      case IN_DEBOUNCE_3:
        /* During 'DEBOUNCE_3': '<S1>:317' */
        if (DW_l.debounceBoto >= DEBOUNCE_BOTO) {
            /* Transition: '<S1>:318' */
            DW_l.is_MAPES_FRENO = IN_MAPA_FRENO_4;

            /* Entry Internal 'MAPA_FRENO_4': '<S1>:321' */
            /* Transition: '<S1>:322' */
            DW_l.is_MAPA_FRENO_4 = IN_EN_ST;

            /* Entry 'EN_ST': '<S1>:326' */
            flashWrite_mapaFreno = 4U;
            flashWrite_IsUpdatedMapaFreno = true;
            DW_l.fondo = false;
            DW_l.blinkLedPC13 = 0U;
            IOM_SetOutput__DO_PC13_LED(IOM_HIGH);
            DW_l.tempsRectaLlarga = 0U;
        } else {
            tmp = DW_l.debounceBoto + 1ULL;
            if (tmp > 4294967295ULL) {
                tmp = 4294967295ULL;
            }

            DW_l.debounceBoto = (uint32_T)tmp;
        }
        break;

      case IN_DEBOUNCE_4:
        /* During 'DEBOUNCE_4': '<S1>:183' */
        if (DW_l.debounceBoto >= DEBOUNCE_BOTO) {
            /* Transition: '<S1>:178' */
            DW_l.is_MAPES_FRENO = IN_MAPA_FRENO_1;

            /* Entry 'MAPA_FRENO_1': '<S1>:180' */
            flashWrite_mapaFreno = 1U;
            flashWrite_IsUpdatedMapaFreno = true;
            DW_l.fondo = false;
            IOM_SetOutput__DO_PC13_LED(IOM_HIGH);
        } else {
            tmp = DW_l.debounceBoto + 1ULL;
            if (tmp > 4294967295ULL) {
                tmp = 4294967295ULL;
            }

            DW_l.debounceBoto = (uint32_T)tmp;
        }
        break;

      case IN_MAPA_FRENO_1:
        /* Inport: '<Root>/flashRead_GatellMinLow' incorporates:
         *  Inport: '<Root>/mes_adcFreno'
         */
        /* During 'MAPA_FRENO_1': '<S1>:180' */
        if ((*Switch2) && (DW_l.Switch4 < flashRead_GatellMinLow) && ((int32_T)
                rt_roundd_snf((real_T)mes_adcFreno / 40.0) < 21) && ((int32_T)
                rt_roundd_snf((real_T)mes_adcFreno / 40.0) >= 1)) {
            /* Transition: '<S1>:177' */
            DW_l.is_MAPES_FRENO = IN_DEBOUNCE_1;

            /* Entry 'DEBOUNCE_1': '<S1>:181' */
            DW_l.debounceBoto = 0U;
        } else {
            flashWrite_IsUpdatedMapaFreno = false;
        }
        break;

      case IN_MAPA_FRENO_2:
        /* Inport: '<Root>/flashRead_GatellMinLow' incorporates:
         *  Inport: '<Root>/mes_adcFreno'
         */
        /* During 'MAPA_FRENO_2': '<S1>:244' */
        if ((*Switch2) && (DW_l.Switch4 < flashRead_GatellMinLow) && ((int32_T)
                rt_roundd_snf((real_T)mes_adcFreno / 40.0) < 21) && ((int32_T)
                rt_roundd_snf((real_T)mes_adcFreno / 40.0) >= 1)) {
            /* Transition: '<S1>:247' */
            /* Exit Internal 'MAPA_FRENO_2': '<S1>:244' */
            DW_l.is_MAPA_FRENO_2 = IN_NO_ACTIVE_CHILD;
            DW_l.is_MAPES_FRENO = IN_DEBOUNCE_2;

            /* Entry 'DEBOUNCE_2': '<S1>:246' */
            DW_l.debounceBoto = 0U;
        } else {
            switch (DW_l.is_MAPA_FRENO_2) {
              case IN_EN_ST:
                /* During 'EN_ST': '<S1>:305' */
                /* Transition: '<S1>:306' */
                flashWrite_IsUpdatedMapaFreno = false;
                DW_l.is_MAPA_FRENO_2 = IN_LED_ON;

                /* Entry 'LED_ON': '<S1>:261' */
                DW_l.blinkLedPC13 = 0U;
                IOM_SetOutput__DO_PC13_LED(IOM_HIGH);
                break;

              case IN_LED_OFF:
                /* During 'LED_OFF': '<S1>:262' */
                if (DW_l.blinkLedPC13 >= 50U) {
                    /* Transition: '<S1>:263' */
                    DW_l.is_MAPA_FRENO_2 = IN_LED_ON;

                    /* Entry 'LED_ON': '<S1>:261' */
                    DW_l.blinkLedPC13 = 0U;
                    IOM_SetOutput__DO_PC13_LED(IOM_HIGH);
                } else {
                    tmp = DW_l.blinkLedPC13 + 1ULL;
                    if (tmp > 4294967295ULL) {
                        tmp = 4294967295ULL;
                    }

                    DW_l.blinkLedPC13 = (uint32_T)tmp;
                }
                break;

              default:
                /* During 'LED_ON': '<S1>:261' */
                if (DW_l.blinkLedPC13 >= 50U) {
                    /* Transition: '<S1>:255' */
                    DW_l.is_MAPA_FRENO_2 = IN_LED_OFF;

                    /* Entry 'LED_OFF': '<S1>:262' */
                    DW_l.blinkLedPC13 = 0U;
                    IOM_SetOutput__DO_PC13_LED(IOM_LOW);
                } else {
                    tmp = DW_l.blinkLedPC13 + 1ULL;
                    if (tmp > 4294967295ULL) {
                        tmp = 4294967295ULL;
                    }

                    DW_l.blinkLedPC13 = (uint32_T)tmp;
                }
                break;
            }
        }
        break;

      case IN_MAPA_FRENO_3:
        /* Inport: '<Root>/flashRead_GatellMinLow' incorporates:
         *  Inport: '<Root>/mes_adcFreno'
         */
        /* During 'MAPA_FRENO_3': '<S1>:182' */
        if ((*Switch2) && (DW_l.Switch4 < flashRead_GatellMinLow) && ((int32_T)
                rt_roundd_snf((real_T)mes_adcFreno / 40.0) < 21) && ((int32_T)
                rt_roundd_snf((real_T)mes_adcFreno / 40.0) >= 1)) {
            /* Transition: '<S1>:319' */
            DW_l.is_MAPES_FRENO = IN_DEBOUNCE_3;

            /* Entry 'DEBOUNCE_3': '<S1>:317' */
            DW_l.debounceBoto = 0U;
        } else {
            flashWrite_IsUpdatedMapaFreno = false;
        }
        break;

      default:
        /* Inport: '<Root>/flashRead_GatellMinLow' incorporates:
         *  Inport: '<Root>/mes_adcFreno'
         */
        /* During 'MAPA_FRENO_4': '<S1>:321' */
        if ((*Switch2) && (DW_l.Switch4 < flashRead_GatellMinLow) && ((int32_T)
                rt_roundd_snf((real_T)mes_adcFreno / 40.0) < 21) && ((int32_T)
                rt_roundd_snf((real_T)mes_adcFreno / 40.0) >= 1)) {
            /* Transition: '<S1>:179' */
            /* Exit Internal 'MAPA_FRENO_4': '<S1>:321' */
            DW_l.is_MAPA_FRENO_4 = IN_NO_ACTIVE_CHILD;
            DW_l.is_MAPES_FRENO = IN_DEBOUNCE_4;

            /* Entry 'DEBOUNCE_4': '<S1>:183' */
            DW_l.debounceBoto = 0U;
        } else {
            switch (DW_l.is_MAPA_FRENO_4) {
              case IN_EN_ST:
                /* During 'EN_ST': '<S1>:326' */
                /* Transition: '<S1>:323' */
                flashWrite_IsUpdatedMapaFreno = false;
                DW_l.is_MAPA_FRENO_4 = IN_LED_ON;

                /* Entry 'LED_ON': '<S1>:327' */
                DW_l.blinkLedPC13 = 0U;
                IOM_SetOutput__DO_PC13_LED(IOM_HIGH);
                break;

              case IN_LED_OFF:
                /* During 'LED_OFF': '<S1>:328' */
                if (DW_l.blinkLedPC13 >= 25U) {
                    /* Transition: '<S1>:325' */
                    DW_l.is_MAPA_FRENO_4 = IN_LED_ON;

                    /* Entry 'LED_ON': '<S1>:327' */
                    DW_l.blinkLedPC13 = 0U;
                    IOM_SetOutput__DO_PC13_LED(IOM_HIGH);
                } else {
                    tmp = DW_l.blinkLedPC13 + 1ULL;
                    if (tmp > 4294967295ULL) {
                        tmp = 4294967295ULL;
                    }

                    DW_l.blinkLedPC13 = (uint32_T)tmp;
                }
                break;

              default:
                /* During 'LED_ON': '<S1>:327' */
                if (DW_l.blinkLedPC13 >= 25U) {
                    /* Transition: '<S1>:324' */
                    DW_l.is_MAPA_FRENO_4 = IN_LED_OFF;

                    /* Entry 'LED_OFF': '<S1>:328' */
                    DW_l.blinkLedPC13 = 0U;
                    IOM_SetOutput__DO_PC13_LED(IOM_LOW);
                } else {
                    tmp = DW_l.blinkLedPC13 + 1ULL;
                    if (tmp > 4294967295ULL) {
                        tmp = 4294967295ULL;
                    }

                    DW_l.blinkLedPC13 = (uint32_T)tmp;
                }
                break;
            }
        }
        break;
    }
}

/* Function for Chart: '<Root>/Gatell' */
static void POTENCIA_DINAMICA(const boolean_T *Switch3)
{
    uint64_T tmp;

    /* During 'POTENCIA_DINAMICA': '<S1>:109' */
    switch (DW_l.is_POTENCIA_DINAMICA) {
      case IN_DEBOUNCE_OFF:
        /* During 'DEBOUNCE_OFF': '<S1>:133' */
        if (DW_l.debounceBoto >= DEBOUNCE_BOTO) {
            /* Transition: '<S1>:134' */
            DW_l.is_POTENCIA_DINAMICA = IN_POTENCIA_DINAMICA_ON;

            /* Entry 'POTENCIA_DINAMICA_ON': '<S1>:118' */
            flashWrite_potenciaDin = 2U;
            flashWrite_IsUpdatedPotenciaDin = true;

            /* Entry Internal 'POTENCIA_DINAMICA_ON': '<S1>:118' */
            /* Transition: '<S1>:526' */
            if (TIPO_MANDO) {
                /* Transition: '<S1>:518' */
                /* Transition: '<S1>:521' */
                /*  Mando Difalco */
                /* Desactivar LED blau */
                pwmBlau = PWM_0;

                /* Transition: '<S1>:523' */
            } else {
                /* Transition: '<S1>:524' */
                /*  Mando DS */
                /* Desactivar LED blau */
                pwmBlau = IOM_LOW;
            }

            /* Transition: '<S1>:528' */
        } else {
            tmp = DW_l.debounceBoto + 1ULL;
            if (tmp > 4294967295ULL) {
                tmp = 4294967295ULL;
            }

            DW_l.debounceBoto = (uint32_T)tmp;
            pwmBlau = IOM_HIGH;

            /* Transition: '<S1>:549' */
            if (TIPO_MANDO) {
                /* Transition: '<S1>:542' */
                /* Transition: '<S1>:544' */
                /*  Mando Difalco */
                /* Desactivar LED blau */
                pwmBlau = PWM_MAX;

                /* Transition: '<S1>:546' */
            } else {
                /* Transition: '<S1>:547' */
                /*  Mando DS */
                /* Desactivar LED blau */
            }

            /* Transition: '<S1>:540' */
        }
        break;

      case IN_DEBOUNCE_ON:
        /* During 'DEBOUNCE_ON': '<S1>:130' */
        if (DW_l.debounceBoto >= DEBOUNCE_BOTO) {
            /* Transition: '<S1>:125' */
            DW_l.is_POTENCIA_DINAMICA = IN_POTENCIA_DINAMICA_OFF;

            /* Entry 'POTENCIA_DINAMICA_OFF': '<S1>:120' */
            flashWrite_potenciaDin = 1U;
            flashWrite_IsUpdatedPotenciaDin = true;

            /* Entry Internal 'POTENCIA_DINAMICA_OFF': '<S1>:120' */
            /* Transition: '<S1>:538' */
            if (TIPO_MANDO) {
                /* Transition: '<S1>:531' */
                /* Transition: '<S1>:533' */
                /*  Mando Difalco */
                /* Desactivar LED blau */
                pwmBlau = PWM_0;

                /* Transition: '<S1>:535' */
            } else {
                /* Transition: '<S1>:536' */
                /*  Mando DS */
                /* Desactivar LED blau */
                pwmBlau = IOM_LOW;
            }

            /* Transition: '<S1>:529' */
        } else {
            tmp = DW_l.debounceBoto + 1ULL;
            if (tmp > 4294967295ULL) {
                tmp = 4294967295ULL;
            }

            DW_l.debounceBoto = (uint32_T)tmp;

            /* Transition: '<S1>:272' */
            if (((DW_l.debounceBoto == 0U) && (DW_l.debounceBoto <= 8U)) ||
                    ((DW_l.debounceBoto > 16U) && (DW_l.debounceBoto <= 24U)) ||
                ((DW_l.debounceBoto > 32U) && (DW_l.debounceBoto <= 40U))) {
                /* Transition: '<S1>:276' */
                /* Transition: '<S1>:497' */
                if (TIPO_MANDO) {
                    /* Transition: '<S1>:488' */
                    /* Transition: '<S1>:491' */
                    pwmBlau = PWM_MAX;

                    /* Transition: '<S1>:493' */
                } else {
                    /* Transition: '<S1>:494' */
                    pwmBlau = IOM_HIGH;
                }

                /* Transition: '<S1>:496' */
                /* Transition: '<S1>:283' */
            } else {
                /* Transition: '<S1>:486' */
                if (TIPO_MANDO) {
                    /* Transition: '<S1>:478' */
                    /* Transition: '<S1>:481' */
                    pwmBlau = PWM_0;

                    /* Transition: '<S1>:479' */
                } else {
                    /* Transition: '<S1>:482' */
                    pwmBlau = IOM_LOW;
                }

                /* Transition: '<S1>:487' */
            }

            /* Transition: '<S1>:285' */
        }
        break;

      case IN_POTENCIA_DINAMICA_OFF:
        /* Inport: '<Root>/flashRead_GatellMinLow' incorporates:
         *  Inport: '<Root>/mes_adcFreno'
         */
        /* During 'POTENCIA_DINAMICA_OFF': '<S1>:120' */
        if ((*Switch3) && (DW_l.Switch4 < flashRead_GatellMinLow) && ((int32_T)
                rt_roundd_snf((real_T)mes_adcFreno / 40.0) < 21) && ((int32_T)
                rt_roundd_snf((real_T)mes_adcFreno / 40.0) >= 1)) {
            /* Transition: '<S1>:122' */
            DW_l.is_POTENCIA_DINAMICA = IN_DEBOUNCE_OFF;

            /* Entry 'DEBOUNCE_OFF': '<S1>:133' */
            DW_l.debounceBoto = 0U;
        } else {
            flashWrite_IsUpdatedPotenciaDin = false;
        }
        break;

      default:
        /* Inport: '<Root>/flashRead_GatellMinLow' incorporates:
         *  Inport: '<Root>/mes_adcFreno'
         */
        /* During 'POTENCIA_DINAMICA_ON': '<S1>:118' */
        if ((*Switch3) && (DW_l.Switch4 < flashRead_GatellMinLow) && ((int32_T)
                rt_roundd_snf((real_T)mes_adcFreno / 40.0) < 21) && ((int32_T)
                rt_roundd_snf((real_T)mes_adcFreno / 40.0) >= 1)) {
            /* Transition: '<S1>:121' */
            DW_l.is_POTENCIA_DINAMICA = IN_DEBOUNCE_ON;

            /* Entry 'DEBOUNCE_ON': '<S1>:130' */
            DW_l.debounceBoto = 0U;

            /* Entry Internal 'DEBOUNCE_ON': '<S1>:130' */
            /* Transition: '<S1>:499' */
            if (TIPO_MANDO) {
                /* Transition: '<S1>:506' */
                /* Transition: '<S1>:508' */
                /*  Mando Difalco */
                /* Desactivar LED blau */
                pwmBlau = PWM_MAX;

                /* Transition: '<S1>:501' */
            } else {
                /* Transition: '<S1>:503' */
                /*  Mando DS */
                /* Desactivar LED blau */
                pwmBlau = IOM_HIGH;
            }

            /* Transition: '<S1>:509' */
            if (((DW_l.debounceBoto == 0U) && (DW_l.debounceBoto <= 8U)) ||
                    ((DW_l.debounceBoto > 16U) && (DW_l.debounceBoto <= 24U)) ||
                ((DW_l.debounceBoto > 32U) && (DW_l.debounceBoto <= 40U))) {
                /* Transition: '<S1>:276' */
                /* Transition: '<S1>:497' */
                if (TIPO_MANDO) {
                    /* Transition: '<S1>:488' */
                    /* Transition: '<S1>:491' */
                    /*  Mando Difalco */
                    /* Desactivar LED blau */
                    pwmBlau = PWM_MAX;

                    /* Transition: '<S1>:493' */
                } else {
                    /* Transition: '<S1>:494' */
                    /*  Mando DS */
                    /* Desactivar LED blau */
                    pwmBlau = IOM_HIGH;
                }

                /* Transition: '<S1>:496' */
                /* Transition: '<S1>:283' */
            } else {
                /* Transition: '<S1>:486' */
                if (TIPO_MANDO) {
                    /* Transition: '<S1>:478' */
                    /* Transition: '<S1>:481' */
                    /*  Mando Difalco */
                    /* Desactivar LED blau */
                    pwmBlau = PWM_0;

                    /* Transition: '<S1>:479' */
                } else {
                    /* Transition: '<S1>:482' */
                    /*  Mando DS */
                    /* Desactivar LED blau */
                    pwmBlau = IOM_LOW;
                }

                /* Transition: '<S1>:487' */
            }

            /* Transition: '<S1>:285' */
        } else {
            flashWrite_IsUpdatedPotenciaDin = false;
        }
        break;
    }
}

/* Function for Chart: '<Root>/Gatell' */
static void enter_internal_E_Eixida(void)
{
    uint64_T tmp;

    /* Entry Internal 'E_Eixida': '<S1>:555' */
    /* Transition: '<S1>:594' */
    /* reset temps de recta fondo */
    DW_l.tempsGasFondo = 0U;

    /* Transition: '<S1>:589' */
    /* Activacio outptus: E_Mitat */
    IOM_SetOutput__DO_RELAY(IOM_LOW);
    DW_l.gatellFiltratFinalAnterior = DW_l.Switch4;

    /* Transition: '<S1>:588' */
    if (TIPO_MANDO) {
        /* Transition: '<S1>:595' */
        /* Transition: '<S1>:571' */
        /*  Mando Difalco */
        /* Desactivar LED blau,  pot din desactivada */
        pwmBlau = PWM_0;

        /* Transition: '<S1>:558' */
    } else {
        /* Transition: '<S1>:598' */
        /*  Mando DS */
        /* Desactivar LED blau,  pot din desactivada */
        pwmBlau = IOM_LOW;
    }

    /* Inport: '<Root>/DI_SWITCH_1' */
    /* Transition: '<S1>:574' */
    if (IOM_ReadInput__DI_SWITCH_1()) {
        /* Inport: '<Root>/indexStart' */
        /* Transition: '<S1>:675' */
        /* Transition: '<S1>:670' */
        /*  Gestio PWM Motor: E_Eixida. Asegurar un punt de eixida mínim en qualsevol corba Mapa2 */
        tmp = indexStart + 1ULL;
        if (tmp > 4294967295ULL) {
            tmp = 4294967295ULL;
        }

        /* Inport: '<Root>/mes_valorsCalculatsMapa2' */
        pwmFreno = mes_valorsCalculatsMapa2[(int32_T)tmp - 1];

        /* Inport: '<Root>/indexStart' */
        tmp = indexStart + 1ULL;
        if (tmp > 4294967295ULL) {
            tmp = 4294967295ULL;
        }

        /* Inport: '<Root>/mes_valorsCalculatsMapa2' */
        pwmGas = mes_valorsCalculatsMapa2[(int32_T)tmp - 1];

        /* Transition: '<S1>:684' */
        /* Gestio PWM Leds: E_Eixida Mapa2 */
        pwmRoig = PWM_0;

        /* Inport: '<Root>/indexStart' */
        tmp = indexStart + 1ULL;
        if (tmp > 4294967295ULL) {
            tmp = 4294967295ULL;
        }

        /* Inport: '<Root>/mes_valorsCalculatsMapa2' */
        pwmVerd = mes_valorsCalculatsMapa2[(int32_T)tmp - 1];

        /* Transition: '<S1>:685' */
    } else {
        /* Inport: '<Root>/indexStart' */
        /* Transition: '<S1>:561' */
        /*  Gestio PWM Motor: E_Eixida. Asegurar un punt de eixida mínim en qualsevol corba Mapa1 */
        tmp = indexStart + 1ULL;
        if (tmp > 4294967295ULL) {
            tmp = 4294967295ULL;
        }

        /* Inport: '<Root>/mes_valorsCalculatsMapa1' */
        pwmFreno = mes_valorsCalculatsMapa1[(int32_T)tmp - 1];

        /* Inport: '<Root>/indexStart' */
        tmp = indexStart + 1ULL;
        if (tmp > 4294967295ULL) {
            tmp = 4294967295ULL;
        }

        /* Inport: '<Root>/mes_valorsCalculatsMapa1' */
        pwmGas = mes_valorsCalculatsMapa1[(int32_T)tmp - 1];

        /* Transition: '<S1>:563' */
        /* Gestio PWM Leds: E_Eixida Mapa1 */
        pwmRoig = PWM_0;

        /* Inport: '<Root>/indexStart' */
        tmp = indexStart + 1ULL;
        if (tmp > 4294967295ULL) {
            tmp = 4294967295ULL;
        }

        /* Inport: '<Root>/mes_valorsCalculatsMapa1' */
        pwmVerd = mes_valorsCalculatsMapa1[(int32_T)tmp - 1];
    }

    /* End of Inport: '<Root>/DI_SWITCH_1' */
    /* Transition: '<S1>:567' */
    /* Guardar la última mostra */
}

/* Function for Chart: '<Root>/Gatell' */
static void enter_internal_E_Fondo(void)
{
    uint64_T tmp;

    /* Entry Internal 'E_Fondo': '<S1>:10' */
    /* Transition: '<S1>:311' */
    /* reset temps de recta fondo */
    DW_l.tempsGasFondo = 0U;
    if (TIPO_MANDO) {
        /* Transition: '<S1>:391' */
        /* Transition: '<S1>:393' */
        /*  Mando Difalco */
        /* Activar led blau: E_Fondo */
        pwmBlau = PWM_MAX;

        /* Transition: '<S1>:396' */
    } else {
        /* Transition: '<S1>:395' */
        /*  Mando DS */
        /* Activar led blau: E_Fondo */
        pwmBlau = IOM_HIGH;
    }

    /* Transition: '<S1>:102' */
    /*  Activacio outputs: E_Fondo */
    IOM_SetOutput__DO_RELAY(IOM_HIGH);
    DW_l.fondo = true;

    /* Transition: '<S1>:192' */
    /*  Gestio PWM Motor: E_Fondo */
    pwmFreno = PWM_MAX;
    pwmGas = PWM_MAX;

    /* Transition: '<S1>:41' */
    /* Gestio PWM Leds: E_Fondo */
    pwmRoig = PWM_0;
    pwmVerd = PWM_0;

    /* Transition: '<S1>:309' */
    /* reset temps de recta fondo */
    tmp = DW_l.tempsGasFondo + 1ULL;
    if (tmp > 4294967295ULL) {
        tmp = 4294967295ULL;
    }

    DW_l.tempsGasFondo = (uint32_T)tmp;
    if (DW_l.tempsGasFondo > DW_l.tempsRectaLlarga) {
        /* Transition: '<S1>:382' */
        /* Transition: '<S1>:386' */
        /*  Guarfadar el temps de la recta llarga */
        DW_l.tempsRectaLlarga = DW_l.tempsGasFondo;

        /* Transition: '<S1>:387' */
    } else {
        /* Transition: '<S1>:384' */
    }

    /* Transition: '<S1>:389' */
}

/* Function for Chart: '<Root>/Gatell' */
static void enter_internal_E_Frenada_Mapa_1(void)
{
    uint32_T x;

    /* Entry Internal 'E_Frenada_Mapa_1': '<S1>:7' */
    /* Transition: '<S1>:372' */
    /* reset temps de recta fondo */
    DW_l.tempsGasFondo = 0U;

    /* Transition: '<S1>:68' */
    /*  Apagar rele: E_Frenada_Mapa_1 */
    IOM_SetOutput__DO_RELAY(IOM_LOW);
    if (TIPO_MANDO) {
        /* Transition: '<S1>:432' */
        /* Transition: '<S1>:433' */
        /*  Mando Difalco */
        /* Desactivar LED blau: E_Frenada_Mapa_1 */
        pwmBlau = PWM_0;

        /* Transition: '<S1>:434' */
    } else {
        /* Transition: '<S1>:439' */
        /*  Mando DS */
        /* Desactivar LED blau: E_Frenada_Mapa_1 */
        pwmBlau = IOM_LOW;
    }

    /* Inport: '<Root>/mes_adcSupply12v_mV' */
    /* Transition: '<S1>:440' */
    if (mes_adcSupply12v_mV <= 6000U) {
        /* Transition: '<S1>:612' */
        /* Transition: '<S1>:616' */
        /*  Gestio PWM Motor: E_Frenada_Mapa_1 */
        pwmFreno = PWM_MAX;
        pwmGas = PWM_0;

        /* Transition: '<S1>:617' */
        /*  Gestio PWM Leds: E_Frenada */
        pwmRoig = PWM_MAX;
        pwmVerd = PWM_0;

        /* Transition: '<S1>:618' */
    } else {
        /* Inport: '<Root>/mes_adcFreno' */
        /* Transition: '<S1>:66' */
        /*  Gestio PWM Motor: E_Frenada_Mapa_1 */
        pwmFreno = mes_adcFreno >> 2;
        x = mes_adcFreno - (pwmFreno << 2);
        if ((x > 0U) && (x >= 2U)) {
            pwmFreno++;
        }

        pwmGas = PWM_0;

        /* Inport: '<Root>/mes_adcFreno' */
        /* Transition: '<S1>:188' */
        /*  Gestio PWM Leds: E_Frenada */
        pwmRoig = mes_adcFreno >> 2;
        x = mes_adcFreno - (pwmRoig << 2);
        if ((x > 0U) && (x >= 2U)) {
            pwmRoig++;
        }

        pwmVerd = PWM_0;
    }

    /* End of Inport: '<Root>/mes_adcSupply12v_mV' */
    /* Transition: '<S1>:619' */
}

/* Function for Chart: '<Root>/Gatell' */
static void enter_internal_E_Mitat(void)
{
    uint64_T tmp;
    uint32_T qY;

    /* Entry Internal 'E_Mitat': '<S1>:9' */
    /* Transition: '<S1>:374' */
    /* reset temps de recta fondo */
    DW_l.tempsGasFondo = 0U;

    /* Transition: '<S1>:45' */
    /* Activacio outptus: E_Mitat */
    IOM_SetOutput__DO_RELAY(IOM_LOW);
    DW_l.gatellFiltratFinalAnterior = DW_l.Switch4;
    qY = DW_l.Switch4 - /*MW:OvSatOk*/ DW_l.gatellFiltratFinalAnterior;
    if (qY > DW_l.Switch4) {
        qY = 0U;
    }

    if ((qY >= DIFF_GATELL) && (flashWrite_potenciaDin == 2U)) {
        /* Transition: '<S1>:200' */
        /* Potencia dinamica. Intent de copia del TicTac */
        if (TIPO_MANDO) {
            /* Transition: '<S1>:405' */
            /* Transition: '<S1>:403' */
            /*  Mando Difalco */
            /* Activar LED blau,  pot din activat */
            pwmBlau = PWM_MAX;

            /* Transition: '<S1>:404' */
        } else {
            /* Transition: '<S1>:402' */
            /*  Mando DS */
            /* Activar LED blau,  pot din activat */
            pwmBlau = IOM_HIGH;
        }

        /* Transition: '<S1>:210' */
        /*  Incrementar el PWM del motor eixa diferencia */
        qY = DW_l.Switch4 - /*MW:OvSatOk*/ DW_l.gatellFiltratFinalAnterior;
        if (qY > DW_l.Switch4) {
            qY = 0U;
        }

        diffGatell = qY;

        /* Inport: '<Root>/flashRead_GatellMinHigh' */
        qY = DW_l.Switch4 - /*MW:OvSatOk*/ flashRead_GatellMinHigh;
        if (qY > DW_l.Switch4) {
            qY = 0U;
        }

        /* Inport: '<Root>/indexStart' */
        tmp = 1ULL + indexStart;
        if (tmp > 4294967295ULL) {
            tmp = 4294967295ULL;
        }

        tmp = (uint64_T)qY + (uint32_T)tmp;
        if (tmp > 4294967295ULL) {
            tmp = 4294967295ULL;
        }

        tmp = (uint64_T)(uint32_T)tmp + diffGatell;
        if (tmp > 4294967295ULL) {
            tmp = 4294967295ULL;
        }

        /* Inport: '<Root>/indexStart' */
        qY = 1500U - /*MW:OvSatOk*/ indexStart;
        if (qY > 1500U) {
            qY = 0U;
        }

        if ((uint32_T)tmp >= qY) {
            /* Transition: '<S1>:213' */
            /* Protecció a overflow */
            /* Transition: '<S1>:215' */
            /*  Gestio PWM Motor: E_Fondo amb overflow del index calculat */
            pwmFreno = PWM_MAX;
            pwmGas = PWM_MAX;

            /* Transition: '<S1>:660' */
            /* Transition: '<S1>:216' */
        } else {
            /* Inport: '<Root>/DI_SWITCH_1' */
            /* Transition: '<S1>:657' */
            if (IOM_ReadInput__DI_SWITCH_1()) {
                /* Transition: '<S1>:655' */
                /* Transition: '<S1>:654' */
                /*  Gestio PWM Motor: E_Mitat amb potència dinàmica activat Mapa2 */
                pwmFreno = PWM_MAX;

                /* Inport: '<Root>/flashRead_GatellMinHigh' */
                qY = DW_l.Switch4 - /*MW:OvSatOk*/ flashRead_GatellMinHigh;
                if (qY > DW_l.Switch4) {
                    qY = 0U;
                }

                /* Inport: '<Root>/indexStart' */
                tmp = 1ULL + indexStart;
                if (tmp > 4294967295ULL) {
                    tmp = 4294967295ULL;
                }

                tmp = (uint64_T)qY + (uint32_T)tmp;
                if (tmp > 4294967295ULL) {
                    tmp = 4294967295ULL;
                }

                tmp = (uint64_T)(uint32_T)tmp + diffGatell;
                if (tmp > 4294967295ULL) {
                    tmp = 4294967295ULL;
                }

                /* Inport: '<Root>/mes_valorsCalculatsMapa2' */
                pwmGas = mes_valorsCalculatsMapa2[(int32_T)tmp - 1];

                /* Transition: '<S1>:216' */
            } else {
                /* Transition: '<S1>:207' */
                /*  Gestio PWM Motor: E_Mitat amb potència dinàmica activat Mapa1 */
                pwmFreno = PWM_MAX;

                /* Inport: '<Root>/flashRead_GatellMinHigh' */
                qY = DW_l.Switch4 - /*MW:OvSatOk*/ flashRead_GatellMinHigh;
                if (qY > DW_l.Switch4) {
                    qY = 0U;
                }

                /* Inport: '<Root>/indexStart' */
                tmp = 1ULL + indexStart;
                if (tmp > 4294967295ULL) {
                    tmp = 4294967295ULL;
                }

                tmp = (uint64_T)qY + (uint32_T)tmp;
                if (tmp > 4294967295ULL) {
                    tmp = 4294967295ULL;
                }

                tmp = (uint64_T)(uint32_T)tmp + diffGatell;
                if (tmp > 4294967295ULL) {
                    tmp = 4294967295ULL;
                }

                /* Inport: '<Root>/mes_valorsCalculatsMapa1' */
                pwmGas = mes_valorsCalculatsMapa1[(int32_T)tmp - 1];
            }
        }

        /* Transition: '<S1>:208' */
    } else {
        /* Transition: '<S1>:422' */
        if (TIPO_MANDO) {
            /* Transition: '<S1>:414' */
            /* Transition: '<S1>:415' */
            /*  Mando Difalco */
            /* Desactivar LED blau,  pot din desactivada */
            pwmBlau = PWM_0;

            /* Transition: '<S1>:416' */
        } else {
            /* Transition: '<S1>:421' */
            /*  Mando DS */
            /* Desactivar LED blau,  pot din desactivada */
            pwmBlau = IOM_LOW;
        }

        /* Inport: '<Root>/DI_SWITCH_1' */
        /* Transition: '<S1>:423' */
        if (IOM_ReadInput__DI_SWITCH_1()) {
            /* Inport: '<Root>/flashRead_GatellMinHigh' */
            /* Transition: '<S1>:651' */
            /* Transition: '<S1>:649' */
            /*  Gestio PWM Motor: E_Mitat pas normal Mapa2 */
            qY = DW_l.Switch4 - /*MW:OvSatOk*/ flashRead_GatellMinHigh;
            if (qY > DW_l.Switch4) {
                qY = 0U;
            }

            /* Inport: '<Root>/indexStart' */
            tmp = 1ULL + indexStart;
            if (tmp > 4294967295ULL) {
                tmp = 4294967295ULL;
            }

            tmp = (uint64_T)qY + (uint32_T)tmp;
            if (tmp > 4294967295ULL) {
                tmp = 4294967295ULL;
            }

            /* Inport: '<Root>/mes_valorsCalculatsMapa2' */
            pwmFreno = mes_valorsCalculatsMapa2[(int32_T)tmp - 1];

            /* Inport: '<Root>/flashRead_GatellMinHigh' */
            qY = DW_l.Switch4 - /*MW:OvSatOk*/ flashRead_GatellMinHigh;
            if (qY > DW_l.Switch4) {
                qY = 0U;
            }

            /* Inport: '<Root>/indexStart' */
            tmp = 1ULL + indexStart;
            if (tmp > 4294967295ULL) {
                tmp = 4294967295ULL;
            }

            tmp = (uint64_T)qY + (uint32_T)tmp;
            if (tmp > 4294967295ULL) {
                tmp = 4294967295ULL;
            }

            /* Inport: '<Root>/mes_valorsCalculatsMapa2' */
            pwmGas = mes_valorsCalculatsMapa2[(int32_T)tmp - 1];

            /* Transition: '<S1>:653' */
        } else {
            /* Inport: '<Root>/flashRead_GatellMinHigh' */
            /* Transition: '<S1>:190' */
            /*  Gestio PWM Motor: E_Mitat pas normal Mapa1 */
            qY = DW_l.Switch4 - /*MW:OvSatOk*/ flashRead_GatellMinHigh;
            if (qY > DW_l.Switch4) {
                qY = 0U;
            }

            /* Inport: '<Root>/indexStart' */
            tmp = 1ULL + indexStart;
            if (tmp > 4294967295ULL) {
                tmp = 4294967295ULL;
            }

            tmp = (uint64_T)qY + (uint32_T)tmp;
            if (tmp > 4294967295ULL) {
                tmp = 4294967295ULL;
            }

            /* Inport: '<Root>/mes_valorsCalculatsMapa1' */
            pwmFreno = mes_valorsCalculatsMapa1[(int32_T)tmp - 1];

            /* Inport: '<Root>/flashRead_GatellMinHigh' */
            qY = DW_l.Switch4 - /*MW:OvSatOk*/ flashRead_GatellMinHigh;
            if (qY > DW_l.Switch4) {
                qY = 0U;
            }

            /* Inport: '<Root>/indexStart' */
            tmp = 1ULL + indexStart;
            if (tmp > 4294967295ULL) {
                tmp = 4294967295ULL;
            }

            tmp = (uint64_T)qY + (uint32_T)tmp;
            if (tmp > 4294967295ULL) {
                tmp = 4294967295ULL;
            }

            /* Inport: '<Root>/mes_valorsCalculatsMapa1' */
            pwmGas = mes_valorsCalculatsMapa1[(int32_T)tmp - 1];
        }
    }

    /* Inport: '<Root>/DI_SWITCH_1' */
    /* Transition: '<S1>:662' */
    if (IOM_ReadInput__DI_SWITCH_1()) {
        /* Transition: '<S1>:661' */
        /* Transition: '<S1>:664' */
        /* Gestio PWM Leds: E_Mitat Mapa2 */
        pwmRoig = PWM_0;

        /* Inport: '<Root>/flashRead_GatellMinHigh' */
        qY = DW_l.Switch4 - /*MW:OvSatOk*/ flashRead_GatellMinHigh;
        if (qY > DW_l.Switch4) {
            qY = 0U;
        }

        /* Inport: '<Root>/indexStart' */
        tmp = 1ULL + indexStart;
        if (tmp > 4294967295ULL) {
            tmp = 4294967295ULL;
        }

        tmp = (uint64_T)qY + (uint32_T)tmp;
        if (tmp > 4294967295ULL) {
            tmp = 4294967295ULL;
        }

        /* Inport: '<Root>/mes_valorsCalculatsMapa2' */
        pwmVerd = mes_valorsCalculatsMapa2[(int32_T)tmp - 1];

        /* Transition: '<S1>:666' */
    } else {
        /* Transition: '<S1>:48' */
        /* Gestio PWM Leds: E_Mitat Mapa1 */
        pwmRoig = PWM_0;

        /* Inport: '<Root>/flashRead_GatellMinHigh' */
        qY = DW_l.Switch4 - /*MW:OvSatOk*/ flashRead_GatellMinHigh;
        if (qY > DW_l.Switch4) {
            qY = 0U;
        }

        /* Inport: '<Root>/indexStart' */
        tmp = 1ULL + indexStart;
        if (tmp > 4294967295ULL) {
            tmp = 4294967295ULL;
        }

        tmp = (uint64_T)qY + (uint32_T)tmp;
        if (tmp > 4294967295ULL) {
            tmp = 4294967295ULL;
        }

        /* Inport: '<Root>/mes_valorsCalculatsMapa1' */
        pwmVerd = mes_valorsCalculatsMapa1[(int32_T)tmp - 1];
    }

    /* Transition: '<S1>:202' */
    /* Guardar la última mostra */
}

/* Function for Chart: '<Root>/Gatell' */
static void E_Fondo(void)
{
    boolean_T out;
    uint32_T y;
    uint32_T x;
    boolean_T guard1 = false;
    uint64_T tmp;

    /* Inport: '<Root>/mes_adcSupply12v_mV' incorporates:
     *  Inport: '<Root>/mandoArc'
     */
    /* During 'E_Fondo': '<S1>:10' */
    /* Transition: '<S1>:610' */
    /* Transition: '<S1>:609' */
    if ((mes_adcSupply12v_mV <= VOLTAGE_LOW) && (!mandoArc)) {
        guard1 = true;
    } else {
        /* Inport: '<Root>/mes_adcFreno' */
        y = mes_adcFreno / 40U;
        x = mes_adcFreno - y * 40U;
        if ((x > 0U) && (x >= 20U)) {
            y++;
        }

        if ((int32_T)y <= 20) {
            guard1 = true;
        } else {
            out = false;
        }
    }

    /* End of Inport: '<Root>/mes_adcSupply12v_mV' */
    if (guard1) {
        out = true;
    }

    if (out) {
        /* Transition: '<S1>:604' */
        /* Transition: '<S1>:608' */
        DW_l.is_GATELL = IN_E_Frenada_Mapa_1;
        enter_internal_E_Frenada_Mapa_1();
    } else {
        /* Inport: '<Root>/flashRead_GatellMaxLow' */
        tmp = flashRead_GatellMaxLow + 15ULL;
        if (tmp > 4294967295ULL) {
            tmp = 4294967295ULL;
        }

        if ((DW_l.Switch4 < (uint32_T)tmp) && (flashWrite_mapaFreno == 4U) &&
                (DW_l.tempsGasFondo >= (uint32_T)rt_roundd_snf(0.8 * (real_T)
                DW_l.tempsRectaLlarga))) {
            /* Transition: '<S1>:24' */
            /* Transition: '<S1>:350' */
            DW_l.is_GATELL = IN_E_Frenada_Mapa_4;

            /* Entry Internal 'E_Frenada_Mapa_4': '<S1>:329' */
            /* Transition: '<S1>:380' */
            /* reset temps de recta fondo */
            DW_l.tempsGasFondo = 0U;

            /* Inport: '<Root>/flashRead_GatellMaxLow' */
            /* Transition: '<S1>:338' */
            /*  Inicialitzar el valor guardat */
            DW_l.minGatellFiltratFinal = flashRead_GatellMaxLow;
            DW_l.fondo = false;

            /* Transition: '<S1>:339' */
            /*  Apagar rele i led: E_Frenada_Mapa_3 */
            IOM_SetOutput__DO_RELAY(IOM_LOW);
            if (TIPO_MANDO) {
                /* Transition: '<S1>:459' */
                /* Transition: '<S1>:462' */
                /*  Mando Difalco */
                /* Desactivar LED blau: E_Frenada_Mapa_4 */
                pwmBlau = PWM_0;

                /* Transition: '<S1>:460' */
            } else {
                /* Transition: '<S1>:463' */
                /*  Mando DS */
                /* Desactivar LED blau: E_Frenada_Mapa_4 */
                pwmBlau = IOM_LOW;
            }

            /* Transition: '<S1>:467' */
            /* Transition: '<S1>:341' */
            /*  Gestio PWM Motor: E_Frenada_Mapa_4 */
            pwmFreno = PWM_MAX;
            pwmGas = PWM_0;

            /* Transition: '<S1>:342' */
            /*  Gestio PWM: E_Frenada_Mapa_4 */
            pwmRoig = PWM_MAX;
            pwmVerd = PWM_0;
            if (DW_l.Switch4 < DW_l.minGatellFiltratFinal) {
                /* Transition: '<S1>:343' */
                /* Breakpoint ací E_Frenada_Mapa_4 */
                /* Transition: '<S1>:345' */
                /*  Guardar el valor mínim */
                DW_l.minGatellFiltratFinal = DW_l.Switch4;

                /* Transition: '<S1>:346' */
            } else {
                /* Transition: '<S1>:344' */
            }

            /* Transition: '<S1>:347' */
        } else {
            /* Inport: '<Root>/flashRead_GatellMaxLow' */
            tmp = flashRead_GatellMaxLow + 15ULL;
            if (tmp > 4294967295ULL) {
                tmp = 4294967295ULL;
            }

            if ((DW_l.Switch4 < (uint32_T)tmp) && (flashWrite_mapaFreno == 3U))
            {
                /* Transition: '<S1>:348' */
                DW_l.is_GATELL = IN_E_Frenada_Mapa_3;

                /* Entry Internal 'E_Frenada_Mapa_3': '<S1>:8' */
                /* Transition: '<S1>:378' */
                /* reset temps de recta fondo */
                DW_l.tempsGasFondo = 0U;

                /* Inport: '<Root>/flashRead_GatellMaxLow' */
                /* Transition: '<S1>:53' */
                /*  Inicialitzar el valor guardat */
                DW_l.minGatellFiltratFinal = flashRead_GatellMaxLow;
                DW_l.fondo = false;

                /* Transition: '<S1>:105' */
                /*  Apagar rele i led: E_Frenada_Mapa_3 */
                IOM_SetOutput__DO_RELAY(IOM_LOW);
                if (TIPO_MANDO) {
                    /* Transition: '<S1>:450' */
                    /* Transition: '<S1>:453' */
                    /*  Mando Difalco */
                    /* Desactivar LED blau: E_Frenada_Mapa_3 */
                    pwmBlau = PWM_0;

                    /* Transition: '<S1>:451' */
                } else {
                    /* Transition: '<S1>:454' */
                    /*  Mando DS */
                    /* Desactivar LED blau: E_Frenada_Mapa_3 */
                    pwmBlau = IOM_LOW;
                }

                /* Inport: '<Root>/mes_adcFreno' */
                /* Transition: '<S1>:458' */
                /* Transition: '<S1>:194' */
                /*  Gestio PWM Motor: E_Frenada_Mapa_3 */
                pwmFreno = mes_adcFreno >> 2;
                y = mes_adcFreno - (pwmFreno << 2);
                if ((y > 0U) && (y >= 2U)) {
                    pwmFreno++;
                }

                pwmGas = PWM_0;

                /* Inport: '<Root>/mes_adcFreno' */
                /* Transition: '<S1>:51' */
                /*  Gestio PWM: E_Frenada_Mapa_3 */
                pwmRoig = mes_adcFreno >> 2;
                y = mes_adcFreno - (pwmRoig << 2);
                if ((y > 0U) && (y >= 2U)) {
                    pwmRoig++;
                }

                pwmVerd = PWM_0;
                if (DW_l.Switch4 < DW_l.minGatellFiltratFinal) {
                    /* Transition: '<S1>:164' */
                    /* Breakpoint ací E_Frenada_Mapa_3 */
                    /* Transition: '<S1>:166' */
                    /*  Guardar el valor mínim */
                    DW_l.minGatellFiltratFinal = DW_l.Switch4;

                    /* Transition: '<S1>:167' */
                } else {
                    /* Transition: '<S1>:150' */
                }

                /* Transition: '<S1>:169' */
            } else {
                /* Inport: '<Root>/flashRead_GatellMaxLow' */
                tmp = flashRead_GatellMaxLow + 15ULL;
                if (tmp > 4294967295ULL) {
                    tmp = 4294967295ULL;
                }

                if (DW_l.Switch4 < (uint32_T)tmp) {
                    /* Transition: '<S1>:264' */
                    DW_l.is_GATELL = IN_E_Mitat;
                    enter_internal_E_Mitat();
                } else {
                    /* Transition: '<S1>:32' */
                    /* Transition: '<S1>:192' */
                    pwmFreno = PWM_MAX;
                    pwmGas = PWM_MAX;

                    /* Transition: '<S1>:41' */
                    pwmRoig = PWM_0;
                    pwmVerd = PWM_0;

                    /* Transition: '<S1>:309' */
                    tmp = DW_l.tempsGasFondo + 1ULL;
                    if (tmp > 4294967295ULL) {
                        tmp = 4294967295ULL;
                    }

                    DW_l.tempsGasFondo = (uint32_T)tmp;
                    if (DW_l.tempsGasFondo > DW_l.tempsRectaLlarga) {
                        /* Transition: '<S1>:382' */
                        /* Transition: '<S1>:386' */
                        DW_l.tempsRectaLlarga = DW_l.tempsGasFondo;

                        /* Transition: '<S1>:387' */
                    } else {
                        /* Transition: '<S1>:384' */
                    }

                    /* Transition: '<S1>:389' */
                }
            }
        }
    }
}

/* Function for Chart: '<Root>/Gatell' */
static void E_Frenada_Mapa_2(void)
{
    uint32_T x;
    uint64_T tmp;

    /* During 'E_Frenada_Mapa_2': '<S1>:225' */
    tmp = (uint64_T)DW_l.minGatellFiltratFinal + HISTERESI_FRENO;
    if (tmp > 4294967295ULL) {
        tmp = 4294967295ULL;
    }

    /* Inport: '<Root>/flashRead_GatellMinHigh' */
    if ((DW_l.Switch4 > (uint32_T)tmp) && (DW_l.Switch4 >=
            flashRead_GatellMinHigh)) {
        /* Transition: '<S1>:223' */
        DW_l.is_GATELL = IN_E_Mitat;
        enter_internal_E_Mitat();
    } else {
        /* Inport: '<Root>/mes_adcFreno' */
        /* Transition: '<S1>:236' */
        /* Transition: '<S1>:237' */
        pwmFreno = mes_adcFreno >> 2;
        x = mes_adcFreno - (pwmFreno << 2);
        if ((x > 0U) && (x >= 2U)) {
            pwmFreno++;
        }

        pwmGas = PWM_0;

        /* Inport: '<Root>/mes_adcFreno' */
        /* Transition: '<S1>:238' */
        pwmRoig = mes_adcFreno >> 2;
        x = mes_adcFreno - (pwmRoig << 2);
        if ((x > 0U) && (x >= 2U)) {
            pwmRoig++;
        }

        pwmVerd = PWM_0;
        if (DW_l.Switch4 < DW_l.minGatellFiltratFinal) {
            /* Transition: '<S1>:239' */
            /* Breakpoint ací: E_Frenada_Mapa_2 */
            /* Transition: '<S1>:241' */
            DW_l.minGatellFiltratFinal = DW_l.Switch4;

            /* Transition: '<S1>:242' */
        } else {
            /* Transition: '<S1>:240' */
        }

        /* Transition: '<S1>:243' */
    }

    /* End of Inport: '<Root>/flashRead_GatellMinHigh' */
}

/* Function for Chart: '<Root>/Gatell' */
static void E_Frenada_Mapa_3(void)
{
    uint32_T x;
    uint64_T tmp;

    /* During 'E_Frenada_Mapa_3': '<S1>:8' */
    /* Transition: '<S1>:353' */
    tmp = (uint64_T)DW_l.minGatellFiltratFinal + HISTERESI_FRENO;
    if (tmp > 4294967295ULL) {
        tmp = 4294967295ULL;
    }

    /* Inport: '<Root>/flashRead_GatellMinHigh' */
    if ((DW_l.Switch4 > (uint32_T)tmp) && (DW_l.Switch4 >=
            flashRead_GatellMinHigh)) {
        /* Transition: '<S1>:14' */
        DW_l.is_GATELL = IN_E_Mitat;
        enter_internal_E_Mitat();
    } else {
        /* Inport: '<Root>/mes_adcFreno' */
        /* Transition: '<S1>:49' */
        /* Transition: '<S1>:194' */
        pwmFreno = mes_adcFreno >> 2;
        x = mes_adcFreno - (pwmFreno << 2);
        if ((x > 0U) && (x >= 2U)) {
            pwmFreno++;
        }

        pwmGas = PWM_0;

        /* Inport: '<Root>/mes_adcFreno' */
        /* Transition: '<S1>:51' */
        pwmRoig = mes_adcFreno >> 2;
        x = mes_adcFreno - (pwmRoig << 2);
        if ((x > 0U) && (x >= 2U)) {
            pwmRoig++;
        }

        pwmVerd = PWM_0;
        if (DW_l.Switch4 < DW_l.minGatellFiltratFinal) {
            /* Transition: '<S1>:164' */
            /* Breakpoint ací E_Frenada_Mapa_3 */
            /* Transition: '<S1>:166' */
            DW_l.minGatellFiltratFinal = DW_l.Switch4;

            /* Transition: '<S1>:167' */
        } else {
            /* Transition: '<S1>:150' */
        }

        /* Transition: '<S1>:169' */
    }

    /* End of Inport: '<Root>/flashRead_GatellMinHigh' */
}

/* Function for Chart: '<Root>/Gatell' */
static void GATELL(void)
{
    boolean_T out;
    uint32_T y;
    uint32_T x;
    boolean_T guard2 = false;
    uint64_T tmp;

    /* During 'GATELL': '<S1>:108' */
    switch (DW_l.is_GATELL) {
      case IN_E_Eixida:
        /* Inport: '<Root>/flashRead_GatellMinLow' */
        /* During 'E_Eixida': '<S1>:555' */
        if (DW_l.Switch4 < flashRead_GatellMinLow) {
            /* Transition: '<S1>:13' */
            DW_l.is_GATELL = IN_E_Frenada_Mapa_1;
            enter_internal_E_Frenada_Mapa_1();
        } else {
            /* Inport: '<Root>/flashRead_GatellMinHigh' */
            tmp = flashRead_GatellMinHigh + 15ULL;
            if (tmp > 4294967295ULL) {
                tmp = 4294967295ULL;
            }

            if (DW_l.Switch4 >= (uint32_T)tmp) {
                /* Transition: '<S1>:556' */
                DW_l.is_GATELL = IN_E_Mitat;
                enter_internal_E_Mitat();
            } else {
                /* Transition: '<S1>:566' */
                /* Transition: '<S1>:588' */
                if (TIPO_MANDO) {
                    /* Transition: '<S1>:595' */
                    /* Transition: '<S1>:571' */
                    pwmBlau = PWM_0;

                    /* Transition: '<S1>:558' */
                } else {
                    /* Transition: '<S1>:598' */
                    pwmBlau = IOM_LOW;
                }

                /* Inport: '<Root>/DI_SWITCH_1' */
                /* Transition: '<S1>:574' */
                if (IOM_ReadInput__DI_SWITCH_1()) {
                    /* Inport: '<Root>/indexStart' */
                    /* Transition: '<S1>:675' */
                    /* Transition: '<S1>:670' */
                    tmp = indexStart + 1ULL;
                    if (tmp > 4294967295ULL) {
                        tmp = 4294967295ULL;
                    }

                    /* Inport: '<Root>/mes_valorsCalculatsMapa2' */
                    pwmFreno = mes_valorsCalculatsMapa2[(int32_T)tmp - 1];

                    /* Inport: '<Root>/indexStart' */
                    tmp = indexStart + 1ULL;
                    if (tmp > 4294967295ULL) {
                        tmp = 4294967295ULL;
                    }

                    /* Inport: '<Root>/mes_valorsCalculatsMapa2' */
                    pwmGas = mes_valorsCalculatsMapa2[(int32_T)tmp - 1];

                    /* Transition: '<S1>:684' */
                    pwmRoig = PWM_0;

                    /* Inport: '<Root>/indexStart' */
                    tmp = indexStart + 1ULL;
                    if (tmp > 4294967295ULL) {
                        tmp = 4294967295ULL;
                    }

                    /* Inport: '<Root>/mes_valorsCalculatsMapa2' */
                    pwmVerd = mes_valorsCalculatsMapa2[(int32_T)tmp - 1];

                    /* Transition: '<S1>:685' */
                } else {
                    /* Inport: '<Root>/indexStart' */
                    /* Transition: '<S1>:561' */
                    tmp = indexStart + 1ULL;
                    if (tmp > 4294967295ULL) {
                        tmp = 4294967295ULL;
                    }

                    /* Inport: '<Root>/mes_valorsCalculatsMapa1' */
                    pwmFreno = mes_valorsCalculatsMapa1[(int32_T)tmp - 1];

                    /* Inport: '<Root>/indexStart' */
                    tmp = indexStart + 1ULL;
                    if (tmp > 4294967295ULL) {
                        tmp = 4294967295ULL;
                    }

                    /* Inport: '<Root>/mes_valorsCalculatsMapa1' */
                    pwmGas = mes_valorsCalculatsMapa1[(int32_T)tmp - 1];

                    /* Transition: '<S1>:563' */
                    pwmRoig = PWM_0;

                    /* Inport: '<Root>/indexStart' */
                    tmp = indexStart + 1ULL;
                    if (tmp > 4294967295ULL) {
                        tmp = 4294967295ULL;
                    }

                    /* Inport: '<Root>/mes_valorsCalculatsMapa1' */
                    pwmVerd = mes_valorsCalculatsMapa1[(int32_T)tmp - 1];
                }

                /* Transition: '<S1>:567' */
                DW_l.gatellFiltratFinalAnterior = DW_l.Switch4;
            }
        }
        break;

      case IN_E_Fondo:
        E_Fondo();
        break;

      case IN_E_Frenada_Mapa_1:
        /* Inport: '<Root>/flashRead_GatellMinHigh' incorporates:
         *  Inport: '<Root>/mandoArc'
         *  Inport: '<Root>/mes_adcSupply12v_mV'
         */
        /* During 'E_Frenada_Mapa_1': '<S1>:7' */
        if ((DW_l.Switch4 >= flashRead_GatellMinHigh) && ((mes_adcSupply12v_mV >
              VOLTAGE_HIGH) || mandoArc)) {
            /* Inport: '<Root>/mes_adcFreno' */
            y = mes_adcFreno / 40U;
            x = mes_adcFreno - y * 40U;
            if ((x > 0U) && (x >= 20U)) {
                y++;
            }

            if ((int32_T)y > 20) {
                out = true;
            } else {
                guard2 = true;
            }
        } else {
            guard2 = true;
        }

        if (guard2) {
            out = false;
        }

        if (out) {
            /* Transition: '<S1>:12' */
            DW_l.is_GATELL = IN_E_Eixida;
            enter_internal_E_Eixida();
        } else {
            /* Inport: '<Root>/mes_adcSupply12v_mV' */
            /* Transition: '<S1>:64' */
            if (mes_adcSupply12v_mV <= 6000U) {
                /* Transition: '<S1>:612' */
                /* Transition: '<S1>:616' */
                pwmFreno = PWM_MAX;
                pwmGas = PWM_0;

                /* Transition: '<S1>:617' */
                pwmRoig = PWM_MAX;
                pwmVerd = PWM_0;

                /* Transition: '<S1>:618' */
            } else {
                /* Inport: '<Root>/mes_adcFreno' */
                /* Transition: '<S1>:66' */
                pwmFreno = mes_adcFreno >> 2;
                y = mes_adcFreno - (pwmFreno << 2);
                if ((y > 0U) && (y >= 2U)) {
                    pwmFreno++;
                }

                pwmGas = PWM_0;

                /* Inport: '<Root>/mes_adcFreno' */
                /* Transition: '<S1>:188' */
                pwmRoig = mes_adcFreno >> 2;
                y = mes_adcFreno - (pwmRoig << 2);
                if ((y > 0U) && (y >= 2U)) {
                    pwmRoig++;
                }

                pwmVerd = PWM_0;
            }

            /* Transition: '<S1>:619' */
        }
        break;

      case IN_E_Frenada_Mapa_2:
        E_Frenada_Mapa_2();
        break;

      case IN_E_Frenada_Mapa_3:
        E_Frenada_Mapa_3();
        break;

      case IN_E_Frenada_Mapa_4:
        /* During 'E_Frenada_Mapa_4': '<S1>:329' */
        /* Transition: '<S1>:25' */
        /* Transition: '<S1>:354' */
        tmp = (uint64_T)DW_l.minGatellFiltratFinal + HISTERESI_FRENO;
        if (tmp > 4294967295ULL) {
            tmp = 4294967295ULL;
        }

        /* Inport: '<Root>/flashRead_GatellMinHigh' */
        if ((DW_l.Switch4 > (uint32_T)tmp) && (DW_l.Switch4 >=
                flashRead_GatellMinHigh)) {
            /* Transition: '<S1>:14' */
            DW_l.is_GATELL = IN_E_Mitat;
            enter_internal_E_Mitat();
        } else {
            /* Transition: '<S1>:340' */
            /* Transition: '<S1>:341' */
            pwmFreno = PWM_MAX;
            pwmGas = PWM_0;

            /* Transition: '<S1>:342' */
            pwmRoig = PWM_MAX;
            pwmVerd = PWM_0;
            if (DW_l.Switch4 < DW_l.minGatellFiltratFinal) {
                /* Transition: '<S1>:343' */
                /* Breakpoint ací E_Frenada_Mapa_4 */
                /* Transition: '<S1>:345' */
                DW_l.minGatellFiltratFinal = DW_l.Switch4;

                /* Transition: '<S1>:346' */
            } else {
                /* Transition: '<S1>:344' */
            }

            /* Transition: '<S1>:347' */
        }
        break;

      default:
        /* Inport: '<Root>/mes_adcSupply12v_mV' incorporates:
         *  Inport: '<Root>/mandoArc'
         */
        /* Inport: '<Root>/flashRead_GatellFreMapa2' */
        /* During 'E_Mitat': '<S1>:9' */
        /* Transition: '<S1>:606' */
        if ((mes_adcSupply12v_mV <= VOLTAGE_LOW) && (!mandoArc)) {
            guard2 = true;
        } else {
            /* Inport: '<Root>/mes_adcFreno' */
            y = mes_adcFreno / 40U;
            x = mes_adcFreno - y * 40U;
            if ((x > 0U) && (x >= 20U)) {
                y++;
            }

            if ((int32_T)y <= 20) {
                guard2 = true;
            } else {
                out = false;
            }
        }

        if (guard2) {
            out = true;
        }

        if (out) {
            /* Transition: '<S1>:604' */
            /* Transition: '<S1>:608' */
            DW_l.is_GATELL = IN_E_Frenada_Mapa_1;
            enter_internal_E_Frenada_Mapa_1();
        } else if ((DW_l.Switch4 < flashRead_GatellFreMapa2) &&
                   (flashWrite_mapaFreno == 2U) && DW_l.fondo) {
            /* Transition: '<S1>:16' */
            /* Transition: '<S1>:314' */
            /* [tempsGasFondo >= (0.8 *tempsRectaLlarga)] */
            DW_l.is_GATELL = IN_E_Frenada_Mapa_2;

            /* Entry Internal 'E_Frenada_Mapa_2': '<S1>:225' */
            /* Transition: '<S1>:376' */
            /* reset temps de recta fondo */
            DW_l.tempsGasFondo = 0U;

            /* Inport: '<Root>/flashRead_GatellMaxLow' */
            /* Transition: '<S1>:234' */
            /*  Inicialitzar el valor guardat */
            DW_l.minGatellFiltratFinal = flashRead_GatellMaxLow;
            DW_l.fondo = false;

            /* Transition: '<S1>:235' */
            /*  Apagar rele i led: E_Frenada_Mapa_2 */
            IOM_SetOutput__DO_RELAY(IOM_LOW);
            if (TIPO_MANDO) {
                /* Transition: '<S1>:441' */
                /* Transition: '<S1>:444' */
                /*  Mando Difalco */
                /* Desactivar LED blau: E_Frenada_Mapa_2 */
                pwmBlau = PWM_0;

                /* Transition: '<S1>:442' */
            } else {
                /* Transition: '<S1>:445' */
                /*  Mando DS */
                /* Desactivar LED blau: E_Frenada_Mapa_2 */
                pwmBlau = IOM_LOW;
            }

            /* Inport: '<Root>/mes_adcFreno' */
            /* Transition: '<S1>:449' */
            /* Transition: '<S1>:237' */
            /*  Gestio PWM Motor: E_Frenada_Mapa_2 */
            pwmFreno = mes_adcFreno >> 2;
            y = mes_adcFreno - (pwmFreno << 2);
            if ((y > 0U) && (y >= 2U)) {
                pwmFreno++;
            }

            pwmGas = PWM_0;

            /* Inport: '<Root>/mes_adcFreno' */
            /* Transition: '<S1>:238' */
            /*  Gestio PWM: E_Frenada_Mapa_2 */
            pwmRoig = mes_adcFreno >> 2;
            y = mes_adcFreno - (pwmRoig << 2);
            if ((y > 0U) && (y >= 2U)) {
                pwmRoig++;
            }

            pwmVerd = PWM_0;
            if (DW_l.Switch4 < DW_l.minGatellFiltratFinal) {
                /* Transition: '<S1>:239' */
                /* Breakpoint ací: E_Frenada_Mapa_2 */
                /* Transition: '<S1>:241' */
                /*  Guardar el valor mínim */
                DW_l.minGatellFiltratFinal = DW_l.Switch4;

                /* Transition: '<S1>:242' */
            } else {
                /* Transition: '<S1>:240' */
            }

            /* Transition: '<S1>:243' */
        } else {
            /* Inport: '<Root>/flashRead_GatellMaxHigh' */
            tmp = flashRead_GatellMaxHigh + 15ULL;
            if (tmp > 4294967295ULL) {
                tmp = 4294967295ULL;
            }

            if (DW_l.Switch4 >= (uint32_T)tmp) {
                /* Transition: '<S1>:15' */
                DW_l.is_GATELL = IN_E_Fondo;
                enter_internal_E_Fondo();
            } else {
                /* Inport: '<Root>/flashRead_GatellMinLow' */
                tmp = flashRead_GatellMinLow + 15ULL;
                if (tmp > 4294967295ULL) {
                    tmp = 4294967295ULL;
                }

                if (DW_l.Switch4 < (uint32_T)tmp) {
                    /* Transition: '<S1>:557' */
                    DW_l.is_GATELL = IN_E_Eixida;
                    enter_internal_E_Eixida();
                } else {
                    /* Transition: '<S1>:46' */
                    y = DW_l.Switch4 - /*MW:OvSatOk*/
                        DW_l.gatellFiltratFinalAnterior;
                    if (y > DW_l.Switch4) {
                        y = 0U;
                    }

                    if ((y >= DIFF_GATELL) && (flashWrite_potenciaDin == 2U)) {
                        /* Transition: '<S1>:200' */
                        /* Potencia dinamica. Intent de copia del TicTac */
                        if (TIPO_MANDO) {
                            /* Transition: '<S1>:405' */
                            /* Transition: '<S1>:403' */
                            pwmBlau = PWM_MAX;

                            /* Transition: '<S1>:404' */
                        } else {
                            /* Transition: '<S1>:402' */
                            pwmBlau = IOM_HIGH;
                        }

                        /* Transition: '<S1>:210' */
                        y = DW_l.Switch4 - /*MW:OvSatOk*/
                            DW_l.gatellFiltratFinalAnterior;
                        if (y > DW_l.Switch4) {
                            y = 0U;
                        }

                        diffGatell = y;

                        /* Inport: '<Root>/flashRead_GatellMinHigh' */
                        y = DW_l.Switch4 - /*MW:OvSatOk*/
                            flashRead_GatellMinHigh;
                        if (y > DW_l.Switch4) {
                            y = 0U;
                        }

                        /* Inport: '<Root>/indexStart' */
                        tmp = 1ULL + indexStart;
                        if (tmp > 4294967295ULL) {
                            tmp = 4294967295ULL;
                        }

                        tmp = (uint64_T)y + (uint32_T)tmp;
                        if (tmp > 4294967295ULL) {
                            tmp = 4294967295ULL;
                        }

                        tmp = (uint64_T)(uint32_T)tmp + diffGatell;
                        if (tmp > 4294967295ULL) {
                            tmp = 4294967295ULL;
                        }

                        /* Inport: '<Root>/indexStart' */
                        y = 1500U - /*MW:OvSatOk*/ indexStart;
                        if (y > 1500U) {
                            y = 0U;
                        }

                        if ((uint32_T)tmp >= y) {
                            /* Transition: '<S1>:213' */
                            /* Protecció a overflow */
                            /* Transition: '<S1>:215' */
                            pwmFreno = PWM_MAX;
                            pwmGas = PWM_MAX;

                            /* Transition: '<S1>:660' */
                            /* Transition: '<S1>:216' */
                        } else {
                            /* Inport: '<Root>/DI_SWITCH_1' */
                            /* Transition: '<S1>:657' */
                            if (IOM_ReadInput__DI_SWITCH_1()) {
                                /* Transition: '<S1>:655' */
                                /* Transition: '<S1>:654' */
                                pwmFreno = PWM_MAX;

                                /* Inport: '<Root>/flashRead_GatellMinHigh' */
                                y = DW_l.Switch4 - /*MW:OvSatOk*/
                                    flashRead_GatellMinHigh;
                                if (y > DW_l.Switch4) {
                                    y = 0U;
                                }

                                /* Inport: '<Root>/indexStart' */
                                tmp = 1ULL + indexStart;
                                if (tmp > 4294967295ULL) {
                                    tmp = 4294967295ULL;
                                }

                                tmp = (uint64_T)y + (uint32_T)tmp;
                                if (tmp > 4294967295ULL) {
                                    tmp = 4294967295ULL;
                                }

                                tmp = (uint64_T)(uint32_T)tmp + diffGatell;
                                if (tmp > 4294967295ULL) {
                                    tmp = 4294967295ULL;
                                }

                                /* Inport: '<Root>/mes_valorsCalculatsMapa2' */
                                pwmGas = mes_valorsCalculatsMapa2[(int32_T)tmp -
                                    1];

                                /* Transition: '<S1>:216' */
                            } else {
                                /* Transition: '<S1>:207' */
                                pwmFreno = PWM_MAX;

                                /* Inport: '<Root>/flashRead_GatellMinHigh' */
                                y = DW_l.Switch4 - /*MW:OvSatOk*/
                                    flashRead_GatellMinHigh;
                                if (y > DW_l.Switch4) {
                                    y = 0U;
                                }

                                /* Inport: '<Root>/indexStart' */
                                tmp = 1ULL + indexStart;
                                if (tmp > 4294967295ULL) {
                                    tmp = 4294967295ULL;
                                }

                                tmp = (uint64_T)y + (uint32_T)tmp;
                                if (tmp > 4294967295ULL) {
                                    tmp = 4294967295ULL;
                                }

                                tmp = (uint64_T)(uint32_T)tmp + diffGatell;
                                if (tmp > 4294967295ULL) {
                                    tmp = 4294967295ULL;
                                }

                                /* Inport: '<Root>/mes_valorsCalculatsMapa1' */
                                pwmGas = mes_valorsCalculatsMapa1[(int32_T)tmp -
                                    1];
                            }
                        }

                        /* Transition: '<S1>:208' */
                    } else {
                        /* Transition: '<S1>:422' */
                        if (TIPO_MANDO) {
                            /* Transition: '<S1>:414' */
                            /* Transition: '<S1>:415' */
                            pwmBlau = PWM_0;

                            /* Transition: '<S1>:416' */
                        } else {
                            /* Transition: '<S1>:421' */
                            pwmBlau = IOM_LOW;
                        }

                        /* Inport: '<Root>/DI_SWITCH_1' */
                        /* Transition: '<S1>:423' */
                        if (IOM_ReadInput__DI_SWITCH_1()) {
                            /* Inport: '<Root>/flashRead_GatellMinHigh' */
                            /* Transition: '<S1>:651' */
                            /* Transition: '<S1>:649' */
                            y = DW_l.Switch4 - /*MW:OvSatOk*/
                                flashRead_GatellMinHigh;
                            if (y > DW_l.Switch4) {
                                y = 0U;
                            }

                            /* Inport: '<Root>/indexStart' */
                            tmp = 1ULL + indexStart;
                            if (tmp > 4294967295ULL) {
                                tmp = 4294967295ULL;
                            }

                            tmp = (uint64_T)y + (uint32_T)tmp;
                            if (tmp > 4294967295ULL) {
                                tmp = 4294967295ULL;
                            }

                            /* Inport: '<Root>/mes_valorsCalculatsMapa2' */
                            pwmFreno = mes_valorsCalculatsMapa2[(int32_T)tmp - 1];

                            /* Inport: '<Root>/flashRead_GatellMinHigh' */
                            y = DW_l.Switch4 - /*MW:OvSatOk*/
                                flashRead_GatellMinHigh;
                            if (y > DW_l.Switch4) {
                                y = 0U;
                            }

                            /* Inport: '<Root>/indexStart' */
                            tmp = 1ULL + indexStart;
                            if (tmp > 4294967295ULL) {
                                tmp = 4294967295ULL;
                            }

                            tmp = (uint64_T)y + (uint32_T)tmp;
                            if (tmp > 4294967295ULL) {
                                tmp = 4294967295ULL;
                            }

                            /* Inport: '<Root>/mes_valorsCalculatsMapa2' */
                            pwmGas = mes_valorsCalculatsMapa2[(int32_T)tmp - 1];

                            /* Transition: '<S1>:653' */
                        } else {
                            /* Inport: '<Root>/flashRead_GatellMinHigh' */
                            /* Transition: '<S1>:190' */
                            y = DW_l.Switch4 - /*MW:OvSatOk*/
                                flashRead_GatellMinHigh;
                            if (y > DW_l.Switch4) {
                                y = 0U;
                            }

                            /* Inport: '<Root>/indexStart' */
                            tmp = 1ULL + indexStart;
                            if (tmp > 4294967295ULL) {
                                tmp = 4294967295ULL;
                            }

                            tmp = (uint64_T)y + (uint32_T)tmp;
                            if (tmp > 4294967295ULL) {
                                tmp = 4294967295ULL;
                            }

                            /* Inport: '<Root>/mes_valorsCalculatsMapa1' */
                            pwmFreno = mes_valorsCalculatsMapa1[(int32_T)tmp - 1];

                            /* Inport: '<Root>/flashRead_GatellMinHigh' */
                            y = DW_l.Switch4 - /*MW:OvSatOk*/
                                flashRead_GatellMinHigh;
                            if (y > DW_l.Switch4) {
                                y = 0U;
                            }

                            /* Inport: '<Root>/indexStart' */
                            tmp = 1ULL + indexStart;
                            if (tmp > 4294967295ULL) {
                                tmp = 4294967295ULL;
                            }

                            tmp = (uint64_T)y + (uint32_T)tmp;
                            if (tmp > 4294967295ULL) {
                                tmp = 4294967295ULL;
                            }

                            /* Inport: '<Root>/mes_valorsCalculatsMapa1' */
                            pwmGas = mes_valorsCalculatsMapa1[(int32_T)tmp - 1];
                        }
                    }

                    /* Inport: '<Root>/DI_SWITCH_1' */
                    /* Transition: '<S1>:662' */
                    if (IOM_ReadInput__DI_SWITCH_1()) {
                        /* Transition: '<S1>:661' */
                        /* Transition: '<S1>:664' */
                        pwmRoig = PWM_0;

                        /* Inport: '<Root>/flashRead_GatellMinHigh' */
                        y = DW_l.Switch4 - /*MW:OvSatOk*/
                            flashRead_GatellMinHigh;
                        if (y > DW_l.Switch4) {
                            y = 0U;
                        }

                        /* Inport: '<Root>/indexStart' */
                        tmp = 1ULL + indexStart;
                        if (tmp > 4294967295ULL) {
                            tmp = 4294967295ULL;
                        }

                        tmp = (uint64_T)y + (uint32_T)tmp;
                        if (tmp > 4294967295ULL) {
                            tmp = 4294967295ULL;
                        }

                        /* Inport: '<Root>/mes_valorsCalculatsMapa2' */
                        pwmVerd = mes_valorsCalculatsMapa2[(int32_T)tmp - 1];

                        /* Transition: '<S1>:666' */
                    } else {
                        /* Transition: '<S1>:48' */
                        pwmRoig = PWM_0;

                        /* Inport: '<Root>/flashRead_GatellMinHigh' */
                        y = DW_l.Switch4 - /*MW:OvSatOk*/
                            flashRead_GatellMinHigh;
                        if (y > DW_l.Switch4) {
                            y = 0U;
                        }

                        /* Inport: '<Root>/indexStart' */
                        tmp = 1ULL + indexStart;
                        if (tmp > 4294967295ULL) {
                            tmp = 4294967295ULL;
                        }

                        tmp = (uint64_T)y + (uint32_T)tmp;
                        if (tmp > 4294967295ULL) {
                            tmp = 4294967295ULL;
                        }

                        /* Inport: '<Root>/mes_valorsCalculatsMapa1' */
                        pwmVerd = mes_valorsCalculatsMapa1[(int32_T)tmp - 1];
                    }

                    /* Transition: '<S1>:202' */
                    DW_l.gatellFiltratFinalAnterior = DW_l.Switch4;
                }
            }
        }

        /* End of Inport: '<Root>/flashRead_GatellFreMapa2' */
        break;
    }
}

/* Model step function */
void Gatell_step(void)
{
    boolean_T rtb_Switch;
    boolean_T Switch3;
    uint64_T tmp;

    /* Switch: '<Root>/Switch4' incorporates:
     *  Constant: '<Root>/Constant4'
     *  Inport: '<Root>/mes_gatellFiltratFinal'
     *  Inport: '<Root>/mes_gatellFiltratFinalSim'
     */
    if (TEST_VALOR_GATELL) {
        DW_l.Switch4 = mes_gatellFiltratFinal;
    } else {
        DW_l.Switch4 = mes_gatellFiltratFinalSim;
    }

    /* End of Switch: '<Root>/Switch4' */

    /* Switch: '<Root>/Switch' incorporates:
     *  Constant: '<Root>/Constant'
     *  Inport: '<Root>/DI_BUTTON_1'
     *  Logic: '<Root>/Logical Operator'
     */
    if (TIPO_MANDO) {
        rtb_Switch = !IOM_ReadInput__DI_BUTTON_1();
    } else {
        rtb_Switch = IOM_ReadInput__DI_BUTTON_1();
    }

    /* End of Switch: '<Root>/Switch' */

    /* Switch: '<Root>/Switch3' incorporates:
     *  Constant: '<Root>/Constant3'
     */
    Switch3 = ((!MARCA_MANDO) && rtb_Switch);

    /* Switch: '<Root>/Switch2' incorporates:
     *  Constant: '<Root>/Constant2'
     */
    if (!MARCA_MANDO) {
        /* Switch: '<Root>/Switch1' incorporates:
         *  Constant: '<Root>/Constant1'
         *  Inport: '<Root>/DI_BUTTON_2'
         *  Logic: '<Root>/Logical Operator1'
         */
        if (TIPO_MANDO) {
            rtb_Switch = !IOM_ReadInput__DI_BUTTON_2();
        } else {
            rtb_Switch = IOM_ReadInput__DI_BUTTON_2();
        }

        /* End of Switch: '<Root>/Switch1' */
    }

    /* End of Switch: '<Root>/Switch2' */

    /* Delay: '<Root>/mapaFreno' incorporates:
     *  Inport: '<Root>/flashRead_mapaFreno'
     */
    if (DW_l.icLoad != 0) {
        DW_l.mapaFreno_DSTATE = flashRead_mapaFreno;
    }

    /* Delay: '<Root>/potenciaDin' incorporates:
     *  Inport: '<Root>/flashRead_potenciaDin'
     */
    if (DW_l.icLoad_n != 0) {
        DW_l.potenciaDin_DSTATE = flashRead_potenciaDin;
    }

    /* Chart: '<Root>/Gatell' incorporates:
     *  Delay: '<Root>/mapaFreno'
     *  Delay: '<Root>/potenciaDin'
     *  Inport: '<Root>/flashRead_GatellMaxHigh'
     *  Inport: '<Root>/flashRead_GatellMinHigh'
     *  Inport: '<Root>/mes_adcFreno'
     */
    /* Gateway: Gatell */
    /* During: Gatell */
    if (DW_l.is_active_c2_Gatell == 0U) {
        /* Entry: Gatell */
        DW_l.is_active_c2_Gatell = 1U;

        /* Entry Internal: Gatell */
        /* Entry Internal 'MAPES_FRENO': '<S1>:174' */
        switch (DW_l.mapaFreno_DSTATE) {
          case 2U:
            /* Transition: '<S1>:294' */
            DW_l.is_MAPES_FRENO = IN_MAPA_FRENO_2;

            /* Entry Internal 'MAPA_FRENO_2': '<S1>:244' */
            /* Transition: '<S1>:250' */
            DW_l.is_MAPA_FRENO_2 = IN_EN_ST;

            /* Entry 'EN_ST': '<S1>:305' */
            flashWrite_mapaFreno = 2U;
            flashWrite_IsUpdatedMapaFreno = true;
            DW_l.fondo = false;
            DW_l.blinkLedPC13 = 0U;
            IOM_SetOutput__DO_PC13_LED(IOM_HIGH);
            break;

          case 3U:
            /* Transition: '<S1>:297' */
            DW_l.is_MAPES_FRENO = IN_MAPA_FRENO_3;

            /* Entry 'MAPA_FRENO_3': '<S1>:182' */
            flashWrite_mapaFreno = 3U;
            flashWrite_IsUpdatedMapaFreno = true;
            DW_l.fondo = false;
            IOM_SetOutput__DO_PC13_LED(IOM_LOW);
            break;

          case 4U:
            /* Transition: '<S1>:320' */
            DW_l.is_MAPES_FRENO = IN_MAPA_FRENO_4;

            /* Entry Internal 'MAPA_FRENO_4': '<S1>:321' */
            /* Transition: '<S1>:322' */
            DW_l.is_MAPA_FRENO_4 = IN_EN_ST;

            /* Entry 'EN_ST': '<S1>:326' */
            flashWrite_mapaFreno = 4U;
            flashWrite_IsUpdatedMapaFreno = true;
            DW_l.fondo = false;
            DW_l.blinkLedPC13 = 0U;
            IOM_SetOutput__DO_PC13_LED(IOM_HIGH);
            DW_l.tempsRectaLlarga = 0U;
            break;

          default:
            /* Transition: '<S1>:298' */
            DW_l.is_MAPES_FRENO = IN_MAPA_FRENO_1;

            /* Entry 'MAPA_FRENO_1': '<S1>:180' */
            flashWrite_mapaFreno = 1U;
            flashWrite_IsUpdatedMapaFreno = true;
            DW_l.fondo = false;
            IOM_SetOutput__DO_PC13_LED(IOM_HIGH);
            break;
        }

        /* Entry Internal 'POTENCIA_DINAMICA': '<S1>:109' */
        if (DW_l.potenciaDin_DSTATE == 1U) {
            /* Transition: '<S1>:299' */
            DW_l.is_POTENCIA_DINAMICA = IN_POTENCIA_DINAMICA_OFF;

            /* Entry 'POTENCIA_DINAMICA_OFF': '<S1>:120' */
            flashWrite_potenciaDin = 1U;
            flashWrite_IsUpdatedPotenciaDin = true;

            /* Entry Internal 'POTENCIA_DINAMICA_OFF': '<S1>:120' */
            /* Transition: '<S1>:538' */
            if (TIPO_MANDO) {
                /* Transition: '<S1>:531' */
                /* Transition: '<S1>:533' */
                /*  Mando Difalco */
                /* Desactivar LED blau */
                pwmBlau = PWM_0;

                /* Transition: '<S1>:535' */
            } else {
                /* Transition: '<S1>:536' */
                /*  Mando DS */
                /* Desactivar LED blau */
                pwmBlau = IOM_LOW;
            }

            /* Transition: '<S1>:529' */
        } else {
            /* Transition: '<S1>:119' */
            DW_l.is_POTENCIA_DINAMICA = IN_POTENCIA_DINAMICA_ON;

            /* Entry 'POTENCIA_DINAMICA_ON': '<S1>:118' */
            flashWrite_potenciaDin = 2U;
            flashWrite_IsUpdatedPotenciaDin = true;

            /* Entry Internal 'POTENCIA_DINAMICA_ON': '<S1>:118' */
            /* Transition: '<S1>:526' */
            if (TIPO_MANDO) {
                /* Transition: '<S1>:518' */
                /* Transition: '<S1>:521' */
                /*  Mando Difalco */
                /* Desactivar LED blau */
                pwmBlau = PWM_0;

                /* Transition: '<S1>:523' */
            } else {
                /* Transition: '<S1>:524' */
                /*  Mando DS */
                /* Desactivar LED blau */
                pwmBlau = IOM_LOW;
            }

            /* Transition: '<S1>:528' */
        }

        /* Entry Internal 'GATELL': '<S1>:108' */
        if ((DW_l.Switch4 > flashRead_GatellMinHigh) && (DW_l.Switch4 <
                flashRead_GatellMaxHigh)) {
            /* Transition: '<S1>:26' */
            DW_l.tempsRectaLlarga = 0U;
            DW_l.is_GATELL = IN_E_Mitat;
            enter_internal_E_Mitat();
        } else if (DW_l.Switch4 >= flashRead_GatellMaxHigh) {
            /* Transition: '<S1>:27' */
            DW_l.tempsRectaLlarga = 0U;
            DW_l.is_GATELL = IN_E_Fondo;
            enter_internal_E_Fondo();
        } else {
            /* Transition: '<S1>:11' */
            DW_l.tempsRectaLlarga = 0U;
            DW_l.is_GATELL = IN_E_Frenada_Mapa_1;
            enter_internal_E_Frenada_Mapa_1();
        }

        /* Entry Internal 'BOTON_FRENO': '<S1>:636' */
        /* Transition: '<S1>:637' */
        DW_l.is_BOTON_FRENO = IN_NO_BRAKE_PULSAT;

        /* Entry 'NO_BRAKE_PULSAT': '<S1>:642' */
        pwmArcFreno = PWM_MAX;

        /* Entry Internal 'BOTON_CHANGE': '<S1>:626' */
        /* Transition: '<S1>:627' */
        DW_l.is_BOTON_CHANGE = IN_NO_BRAKE_PULSAT;

        /* Entry 'NO_BRAKE_PULSAT': '<S1>:632' */
        IOM_SetOutput__DO_ARC_CHANGE(IOM_HIGH);
    } else {
        MAPES_FRENO(&rtb_Switch);
        POTENCIA_DINAMICA(&Switch3);
        GATELL();

        /* During 'TEMPS_VOLTA': '<S1>:357' */
        /* Transition: '<S1>:360' */
        if (DW_l.tempsGasFondo >= (uint32_T)rt_roundd_snf(0.95 * (real_T)
                DW_l.tempsRectaLlarga)) {
            /* Transition: '<S1>:362' */
            /* Transition: '<S1>:366' */
            tempsVolta = DW_l.tempsVoltaLocal;
            DW_l.tempsVoltaLocal = 0U;

            /* Transition: '<S1>:368' */
        } else {
            /* Transition: '<S1>:364' */
            tmp = DW_l.tempsVoltaLocal + 1ULL;
            if (tmp > 4294967295ULL) {
                tmp = 4294967295ULL;
            }

            DW_l.tempsVoltaLocal = (uint32_T)tmp;
        }

        /* During 'BOTON_FRENO': '<S1>:636' */
        switch (DW_l.is_BOTON_FRENO) {
          case IN_DEBOUNCE_BR_1:
            /* During 'DEBOUNCE_BR_1': '<S1>:644' */
            if (DW_l.debounceBoto >= DEBOUNCE_2_BOTO) {
                /* Transition: '<S1>:639' */
                DW_l.is_BOTON_FRENO = IN_SI_BRAKE_PULSAT;

                /* Entry 'SI_BRAKE_PULSAT': '<S1>:643' */
                pwmArcFreno = PWM_0;
            } else {
                tmp = DW_l.debounceBoto + 1ULL;
                if (tmp > 4294967295ULL) {
                    tmp = 4294967295ULL;
                }

                DW_l.debounceBoto = (uint32_T)tmp;
            }
            break;

          case IN_DEBOUNCE_BR_2:
            /* During 'DEBOUNCE_BR_2': '<S1>:645' */
            if (DW_l.debounceBoto >= DEBOUNCE_2_BOTO) {
                /* Transition: '<S1>:640' */
                DW_l.is_BOTON_FRENO = IN_NO_BRAKE_PULSAT;

                /* Entry 'NO_BRAKE_PULSAT': '<S1>:642' */
                pwmArcFreno = PWM_MAX;
            } else {
                tmp = DW_l.debounceBoto + 1ULL;
                if (tmp > 4294967295ULL) {
                    tmp = 4294967295ULL;
                }

                DW_l.debounceBoto = (uint32_T)tmp;
            }
            break;

          case IN_NO_BRAKE_PULSAT:
            /* During 'NO_BRAKE_PULSAT': '<S1>:642' */
            if (Switch3 && ((int32_T)rt_roundd_snf((real_T)mes_adcFreno / 40.0) >=
                            21)) {
                /* Transition: '<S1>:638' */
                DW_l.is_BOTON_FRENO = IN_DEBOUNCE_BR_1;

                /* Entry 'DEBOUNCE_BR_1': '<S1>:644' */
                DW_l.debounceBoto = 0U;
            }
            break;

          default:
            /* During 'SI_BRAKE_PULSAT': '<S1>:643' */
            if ((!Switch3) && ((int32_T)rt_roundd_snf((real_T)mes_adcFreno /
                    40.0) >= 21)) {
                /* Transition: '<S1>:641' */
                DW_l.is_BOTON_FRENO = IN_DEBOUNCE_BR_2;

                /* Entry 'DEBOUNCE_BR_2': '<S1>:645' */
                DW_l.debounceBoto = 0U;
            }
            break;
        }

        /* During 'BOTON_CHANGE': '<S1>:626' */
        switch (DW_l.is_BOTON_CHANGE) {
          case IN_DEBOUNCE_CH_1:
            /* During 'DEBOUNCE_CH_1': '<S1>:634' */
            if (DW_l.debounceBoto >= DEBOUNCE_2_BOTO) {
                /* Transition: '<S1>:629' */
                DW_l.is_BOTON_CHANGE = IN_SI_BRAKE_PULSAT;

                /* Entry 'SI_BRAKE_PULSAT': '<S1>:633' */
                IOM_SetOutput__DO_ARC_CHANGE(IOM_LOW);
            } else {
                tmp = DW_l.debounceBoto + 1ULL;
                if (tmp > 4294967295ULL) {
                    tmp = 4294967295ULL;
                }

                DW_l.debounceBoto = (uint32_T)tmp;
            }
            break;

          case IN_DEBOUNCE_CH_2:
            /* During 'DEBOUNCE_CH_2': '<S1>:635' */
            if (DW_l.debounceBoto >= DEBOUNCE_2_BOTO) {
                /* Transition: '<S1>:630' */
                DW_l.is_BOTON_CHANGE = IN_NO_BRAKE_PULSAT;

                /* Entry 'NO_BRAKE_PULSAT': '<S1>:632' */
                IOM_SetOutput__DO_ARC_CHANGE(IOM_HIGH);
            } else {
                tmp = DW_l.debounceBoto + 1ULL;
                if (tmp > 4294967295ULL) {
                    tmp = 4294967295ULL;
                }

                DW_l.debounceBoto = (uint32_T)tmp;
            }
            break;

          case IN_NO_BRAKE_PULSAT:
            /* During 'NO_BRAKE_PULSAT': '<S1>:632' */
            if (rtb_Switch && ((int32_T)rt_roundd_snf((real_T)mes_adcFreno /
                    40.0) >= 21)) {
                /* Transition: '<S1>:628' */
                DW_l.is_BOTON_CHANGE = IN_DEBOUNCE_CH_1;

                /* Entry 'DEBOUNCE_CH_1': '<S1>:634' */
                DW_l.debounceBoto = 0U;
            }
            break;

          default:
            /* During 'SI_BRAKE_PULSAT': '<S1>:633' */
            if ((!rtb_Switch) && ((int32_T)rt_roundd_snf((real_T)mes_adcFreno /
                    40.0) >= 21)) {
                /* Transition: '<S1>:631' */
                DW_l.is_BOTON_CHANGE = IN_DEBOUNCE_CH_2;

                /* Entry 'DEBOUNCE_CH_2': '<S1>:635' */
                DW_l.debounceBoto = 0U;
            }
            break;
        }
    }

    /* End of Chart: '<Root>/Gatell' */

    /* Update for Delay: '<Root>/mapaFreno' */
    DW_l.icLoad = 0U;
    DW_l.mapaFreno_DSTATE = flashWrite_mapaFreno;

    /* Update for Delay: '<Root>/potenciaDin' */
    DW_l.icLoad_n = 0U;
    DW_l.potenciaDin_DSTATE = flashWrite_potenciaDin;
}

/* Model initialize function */
void Gatell_initialize(void)
{
    /* InitializeConditions for Delay: '<Root>/mapaFreno' */
    DW_l.icLoad = 1U;

    /* InitializeConditions for Delay: '<Root>/potenciaDin' */
    DW_l.icLoad_n = 1U;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
