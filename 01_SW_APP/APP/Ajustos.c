/*
 * File: Ajustos.c
 *
 * Code generated for Simulink model 'Ajustos'.
 *
 * Model version                  : 2.57
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Sun Feb 08 13:00:44 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "Ajustos.h"

/* Named constants for Chart: '<Root>/Ajustos' */
#define IN_AJUST_P_FINAL_1             ((uint8_T)1U)
#define IN_AJUST_P_FINAL_2             ((uint8_T)1U)
#define IN_AJUST_P_FINAL_VALOR_1       ((uint8_T)1U)
#define IN_AJUST_P_FINAL_VALOR_2       ((uint8_T)2U)
#define IN_AJUST_P_FINAL_VALOR_3       ((uint8_T)3U)
#define IN_AJUST_P_FINAL_VALOR_4       ((uint8_T)4U)
#define IN_AJUST_P_FINAL_VALOR_RALLY_1 ((uint8_T)5U)
#define IN_AJUST_P_FINAL_VALOR_RALLY_2 ((uint8_T)6U)
#define IN_AJUST_P_SALIDA_1            ((uint8_T)2U)
#define IN_AJUST_P_SALIDA_2            ((uint8_T)2U)
#define IN_AJUST_P_SALIDA_VALOR_1      ((uint8_T)1U)
#define IN_AJUST_P_SALIDA_VALOR_2      ((uint8_T)2U)
#define IN_AJUST_P_SALIDA_VALOR_3      ((uint8_T)3U)
#define IN_AJUST_P_SALIDA_VALOR_4      ((uint8_T)4U)
#define IN_AJUST_P_SALIDA_VALOR_RALLY_1 ((uint8_T)5U)
#define IN_AJUST_P_SALIDA_VALOR_RALLY_2 ((uint8_T)6U)
#define IN_DEBOUNCE_1                  ((uint8_T)1U)
#define IN_DEBOUNCE_1_AJUST_P_FINAL_2  ((uint8_T)7U)
#define IN_DEBOUNCE_1_AJUST_P_FINAL_RAL ((uint8_T)8U)
#define IN_DEBOUNCE_1_AJUST_P_SALIDA_2 ((uint8_T)7U)
#define IN_DEBOUNCE_1_AJUST_P_SALIDA_RA ((uint8_T)8U)
#define IN_DEBOUNCE_1_AJUST_P_SALIDA__m ((uint8_T)9U)
#define IN_DEBOUNCE_2                  ((uint8_T)1U)
#define IN_DEBOUNCE_2_AJUST_P_FINAL_2  ((uint8_T)9U)
#define IN_DEBOUNCE_2_AJUST_P_FINAL_3  ((uint8_T)10U)
#define IN_DEBOUNCE_2_AJUST_P_FINAL_RAL ((uint8_T)11U)
#define IN_DEBOUNCE_2_AJUST_P_SALIDA_2 ((uint8_T)10U)
#define IN_DEBOUNCE_3                  ((uint8_T)1U)
#define IN_DEBOUNCE_3_AJUST_P_SALIDA_2 ((uint8_T)11U)
#define IN_DEBOUNCE_4                  ((uint8_T)1U)
#define IN_DEBOUNCE_4_AJUST_P_FINAL_2  ((uint8_T)12U)
#define IN_DEBOUNCE_4_AJUST_P_SALIDA_2 ((uint8_T)12U)
#define IN_DEBOUNCE_5                  ((uint8_T)1U)
#define IN_DEBOUNCE_8                  ((uint8_T)1U)
#define IN_DEBOUNCE_FINISH_1           ((uint8_T)2U)
#define IN_DEBOUNCE_FINISH_2           ((uint8_T)2U)
#define IN_DEBOUNCE_FINISH_3           ((uint8_T)2U)
#define IN_DEBOUNCE_FINISH_3_g         ((uint8_T)1U)
#define IN_DEBOUNCE_FINISH_4           ((uint8_T)3U)
#define IN_DEBOUNCE_FINISH_5           ((uint8_T)3U)
#define IN_DEBOUNCE_FINISH_AJUST_P_FINA ((uint8_T)4U)
#define IN_DEBOUNCE_FINISH_AJUST_P_FI_c ((uint8_T)4U)
#define IN_DEBOUNCE_FINISH_AJUST_P_SALI ((uint8_T)5U)
#define IN_DEBOUNCE_FINISH_AJUST_P_SA_c ((uint8_T)5U)
#define IN_DEBOUNCE_MENSAJE_P_FINAL_1  ((uint8_T)6U)
#define IN_DEBOUNCE_MENSAJE_P_FINAL_2  ((uint8_T)6U)
#define IN_DEBOUNCE_MENSAJE_P_SALIDA_1 ((uint8_T)7U)
#define IN_DEBOUNCE_MENSAJE_P_SALIDA_2 ((uint8_T)7U)
#define IN_DEBOUNCE_NOK_2              ((uint8_T)3U)
#define IN_DEBOUNCE_NOK_3              ((uint8_T)3U)
#define IN_DEBOUNCE_SUBMENU_1          ((uint8_T)8U)
#define IN_DEBOUNCE_SUBMENU_2          ((uint8_T)9U)
#define IN_DEBOUNCE_SUBMENU_3          ((uint8_T)8U)
#define IN_DEBOUNCE_SUBMENU_4          ((uint8_T)9U)
#define IN_DU                          ((uint8_T)2U)
#define IN_FINISH_1                    ((uint8_T)3U)
#define IN_FINISH_2                    ((uint8_T)4U)
#define IN_FINISH_3                    ((uint8_T)4U)
#define IN_FINISH_3_n                  ((uint8_T)3U)
#define IN_FINISH_4                    ((uint8_T)10U)
#define IN_FINISH_5                    ((uint8_T)10U)
#define IN_FINISH_NOK_2                ((uint8_T)5U)
#define IN_FINISH_NOK_3                ((uint8_T)5U)
#define IN_FRE_MAPA2                   ((uint8_T)2U)
#define IN_INIT                        ((uint8_T)1U)
#define IN_MAPA1                       ((uint8_T)2U)
#define IN_MAPA1_MENU                  ((uint8_T)2U)
#define IN_MAPA2                       ((uint8_T)2U)
#define IN_MAPA2_MENU                  ((uint8_T)3U)
#define IN_MENSAJE_18_INIT             ((uint8_T)2U)
#define IN_MENSAJE_1_INIT1             ((uint8_T)2U)
#define IN_MENSAJE_2_INIT              ((uint8_T)2U)
#define IN_MENSAJE_4_INIT              ((uint8_T)3U)
#define IN_MENSAJE_4_INIT_d            ((uint8_T)2U)
#define IN_MENSAJE_5_INIT              ((uint8_T)3U)
#define IN_MENSAJE_FINISH_1            ((uint8_T)4U)
#define IN_MENSAJE_FINISH_2            ((uint8_T)6U)
#define IN_MENSAJE_FINISH_3            ((uint8_T)6U)
#define IN_MENSAJE_FINISH_3_n          ((uint8_T)4U)
#define IN_MENSAJE_FINISH_4            ((uint8_T)11U)
#define IN_MENSAJE_FINISH_5            ((uint8_T)11U)
#define IN_MENSAJE_P_FINAL_1           ((uint8_T)12U)
#define IN_MENSAJE_P_FINAL_2           ((uint8_T)12U)
#define IN_MENSAJE_P_SALIDA_1          ((uint8_T)13U)
#define IN_MENSAJE_P_SALIDA_2          ((uint8_T)13U)
#define IN_MENSAJE_PosFrenoNok         ((uint8_T)7U)
#define IN_MENSAJE_VALOR_GATELL_1      ((uint8_T)5U)
#define IN_MENSAJE_VALOR_GATELL_2      ((uint8_T)8U)
#define IN_MENSAJE_VALOR_GATELL_3      ((uint8_T)7U)
#define IN_MENSAJE_VALOR_GATELL_3_m    ((uint8_T)5U)
#define IN_NO_ACTIVE_CHILD             ((uint8_T)0U)
#define IN_POS_FONDO                   ((uint8_T)3U)
#define IN_POS_FONDO_MENU              ((uint8_T)4U)
#define IN_POS_FRENO                   ((uint8_T)3U)
#define IN_POS_FRENO_MENU              ((uint8_T)5U)
#define IN_POS_FRE_MAPA2_MENU          ((uint8_T)6U)
#define IN_PosFondoNok                 ((uint8_T)8U)
#define IN_RE_INIT                     ((uint8_T)7U)
#define IN_SALIR                       ((uint8_T)8U)
#define IN_SALIR_k                     ((uint8_T)3U)
#define IN_VISOR_GATELL                ((uint8_T)3U)
#define IN_VISOR_GATELL_MENU           ((uint8_T)9U)

/* user code (top of source file) */
#include "pmm_api.h"
#include "iom_api.h"
#include "m2b.h"

/* Exported block signals */
uint32_T estat;                        /* '<Root>/Ajustos' */
uint32_T mensajePantalla;              /* '<Root>/Ajustos' */
uint32_T flashWrite_ValorInicial1;     /* '<Root>/Ajustos' */
uint32_T flashWrite_ValorFinal1;       /* '<Root>/Ajustos' */
uint32_T flashWrite_ValorInicial2;     /* '<Root>/Ajustos' */
uint32_T flashWrite_ValorFinal2;       /* '<Root>/Ajustos' */
uint32_T flashWrite_deltaGatell;       /* '<Root>/Ajustos' */
uint32_T flashWrite_extraPWM;          /* '<Root>/Ajustos' */
boolean_T mensajePantalla_IsUpdated;   /* '<Root>/Ajustos' */
boolean_T enviarValorGatell;           /* '<Root>/Ajustos' */
boolean_T enviarValorPuntInicial1;     /* '<Root>/Ajustos' */
boolean_T enviarValorPuntFinal1;       /* '<Root>/Ajustos' */
boolean_T enviarValorPuntInicial2;     /* '<Root>/Ajustos' */
boolean_T enviarValorPuntFinal2;       /* '<Root>/Ajustos' */
boolean_T menuAjustos;                 /* '<Root>/Ajustos' */
boolean_T flashWrite_IsUpdatedPosFreno;/* '<Root>/Ajustos' */
boolean_T flashWrite_IsUpdatedPosFondo;/* '<Root>/Ajustos' */
boolean_T flashWrite_IsUpdatedlPosFreMapa2;/* '<Root>/Ajustos' */
boolean_T flashWrite_IsUpdatedValorInicial1;/* '<Root>/Ajustos' */
boolean_T flashWrite_IsUpdatedValorFinal1;/* '<Root>/Ajustos' */
boolean_T flashWrite_IsUpdatedValorInicial2;/* '<Root>/Ajustos' */
boolean_T flashWrite_IsUpdatedValorFinal2;/* '<Root>/Ajustos' */
boolean_T flashWrite_IsUpdatedDeltaGatell;/* '<Root>/Ajustos' */
boolean_T flashWrite_IsUpdatedExtraPWM;/* '<Root>/Ajustos' */
boolean_T enviarVoltajeEixida;         /* '<Root>/Ajustos' */

/* Block signals and states (auto storage) */
DW rtDW;

/* Forward declaration for local functions */
static void VISOR_GATELL_MENU(const boolean_T *Switch1);
static void MAPA1(const boolean_T *Switch1, const boolean_T *Switch2);
static void MAPA1_MENU(const boolean_T *Switch1, const boolean_T *Switch2);
static void MAPA2(const boolean_T *Switch1, const boolean_T *Switch2);
static void MAPA2_MENU(const boolean_T *Switch1, const boolean_T *Switch2);
static void POS_FONDO_MENU(const boolean_T *Switch1);
static void POS_FRENO_MENU(const boolean_T *Switch1);

/* Function for Chart: '<Root>/Ajustos' */
static void VISOR_GATELL_MENU(const boolean_T *Switch1)
{
  uint32_T qY;

  /* Inport: '<Root>/mes_adcFrenoSafe' */
  /* During 'VISOR_GATELL_MENU': '<S1>:942' */
  if ((mes_adcFrenoSafe <= 190U) && (!rtDW.ajustant)) {
    /* Transition: '<S1>:966' */
    /* Exit Internal 'VISOR_GATELL_MENU': '<S1>:942' */
    rtDW.is_VISOR_GATELL_MENU = IN_NO_ACTIVE_CHILD;

    /* Exit Internal 'VISOR_GATELL': '<S1>:945' */
    rtDW.is_VISOR_GATELL = IN_NO_ACTIVE_CHILD;
    rtDW.is_c2_Ajustos = IN_INIT;

    /* Entry 'INIT': '<S1>:964' */
    estat = 0U;
    rtDW.finish = false;
    rtDW.ajustant = false;
    enviarValorGatell = false;
    mensajePantalla = 0U;
    mensajePantalla_IsUpdated = true;
  } else if ((mes_adcFrenoSafe >= 400U) && (!rtDW.ajustant)) {
    /* Transition: '<S1>:968' */
    /* Exit Internal 'VISOR_GATELL_MENU': '<S1>:942' */
    rtDW.is_VISOR_GATELL_MENU = IN_NO_ACTIVE_CHILD;

    /* Exit Internal 'VISOR_GATELL': '<S1>:945' */
    rtDW.is_VISOR_GATELL = IN_NO_ACTIVE_CHILD;
    rtDW.is_c2_Ajustos = IN_POS_FRENO_MENU;

    /* Entry Internal 'POS_FRENO_MENU': '<S1>:967' */
    /* Transition: '<S1>:979' */
    rtDW.is_POS_FRENO_MENU = IN_MENSAJE_2_INIT;

    /* Entry 'MENSAJE_2_INIT': '<S1>:676' */
    estat = 2U;
    rtDW.finish = false;
    rtDW.ajustant = false;
    mensajePantalla = 2U;
    mensajePantalla_IsUpdated = true;
  } else if (rtDW.finish) {
    /* Transition: '<S1>:1056' */
    /* Exit Internal 'VISOR_GATELL_MENU': '<S1>:942' */
    rtDW.is_VISOR_GATELL_MENU = IN_NO_ACTIVE_CHILD;

    /* Exit Internal 'VISOR_GATELL': '<S1>:945' */
    rtDW.is_VISOR_GATELL = IN_NO_ACTIVE_CHILD;
    rtDW.is_c2_Ajustos = IN_RE_INIT;

    /* Entry 'RE_INIT': '<S1>:1055' */
    rtDW.ajustant = false;
  } else {
    switch (rtDW.is_VISOR_GATELL_MENU) {
     case IN_DEBOUNCE_1:
      /* During 'DEBOUNCE_1': '<S1>:944' */
      if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
        /* Transition: '<S1>:957' */
        rtDW.is_VISOR_GATELL_MENU = IN_VISOR_GATELL;

        /* Entry Internal 'VISOR_GATELL': '<S1>:945' */
        /* Transition: '<S1>:946' */
        rtDW.is_VISOR_GATELL = IN_MENSAJE_VALOR_GATELL_1;

        /* Entry 'MENSAJE_VALOR_GATELL_1': '<S1>:951' */
        enviarValorGatell = true;
      } else {
        qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
        if (qY < rtDW.debounceBoto) {
          qY = MAX_uint32_T;
        }

        rtDW.debounceBoto = qY;
      }
      break;

     case IN_MENSAJE_1_INIT1:
      /* During 'MENSAJE_1_INIT1': '<S1>:943' */
      if (*Switch1) {
        /* Transition: '<S1>:956' */
        rtDW.is_VISOR_GATELL_MENU = IN_DEBOUNCE_1;

        /* Entry 'DEBOUNCE_1': '<S1>:944' */
        rtDW.debounceBoto = 0U;
        rtDW.ajustant = true;
      } else {
        mensajePantalla_IsUpdated = false;
      }
      break;

     default:
      /* During 'VISOR_GATELL': '<S1>:945' */
      switch (rtDW.is_VISOR_GATELL) {
       case IN_DEBOUNCE_1:
        /* During 'DEBOUNCE_1': '<S1>:952' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:948' */
          rtDW.is_VISOR_GATELL = IN_MENSAJE_FINISH_1;

          /* Entry 'MENSAJE_FINISH_1': '<S1>:953' */
          mensajePantalla = 11U;
          mensajePantalla_IsUpdated = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_DEBOUNCE_FINISH_1:
        /* During 'DEBOUNCE_FINISH_1': '<S1>:954' */
        if (rtDW.debounceBoto >= 200U) {
          /* Transition: '<S1>:950' */
          rtDW.is_VISOR_GATELL = IN_FINISH_1;

          /* Entry 'FINISH_1': '<S1>:955' */
          rtDW.finish = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_FINISH_1:
        /* During 'FINISH_1': '<S1>:955' */
        break;

       case IN_MENSAJE_FINISH_1:
        /* During 'MENSAJE_FINISH_1': '<S1>:953' */
        /* Transition: '<S1>:949' */
        mensajePantalla_IsUpdated = false;
        rtDW.is_VISOR_GATELL = IN_DEBOUNCE_FINISH_1;

        /* Entry 'DEBOUNCE_FINISH_1': '<S1>:954' */
        rtDW.debounceBoto = 0U;
        break;

       default:
        /* During 'MENSAJE_VALOR_GATELL_1': '<S1>:951' */
        if (*Switch1) {
          /* Transition: '<S1>:947' */
          rtDW.is_VISOR_GATELL = IN_DEBOUNCE_1;

          /* Entry 'DEBOUNCE_1': '<S1>:952' */
          rtDW.debounceBoto = 0U;
          enviarValorGatell = false;
        }
        break;
      }
      break;
    }
  }

  /* End of Inport: '<Root>/mes_adcFrenoSafe' */
}

/* Function for Chart: '<Root>/Ajustos' */
static void MAPA1(const boolean_T *Switch1, const boolean_T *Switch2)
{
  uint32_T qY;

  /* During 'MAPA1': '<S1>:586' */
  switch (rtDW.is_MAPA1) {
   case IN_AJUST_P_FINAL_1:
    /* During 'AJUST_P_FINAL_1': '<S1>:1509' */
    if (*Switch1) {
      /* Transition: '<S1>:1255' */
      /* Exit Internal 'AJUST_P_FINAL_1': '<S1>:1509' */
      rtDW.is_AJUST_P_FINAL_1 = IN_NO_ACTIVE_CHILD;
      rtDW.is_MAPA1 = IN_DEBOUNCE_FINISH_AJUST_P_FINA;

      /* Entry 'DEBOUNCE_FINISH_AJUST_P_FINAL_1': '<S1>:1254' */
      rtDW.debounceBoto = 0U;
      flashWrite_IsUpdatedValorFinal1 = true;
    } else {
      switch (rtDW.is_AJUST_P_FINAL_1) {
       case IN_AJUST_P_FINAL_VALOR_1:
        /* During 'AJUST_P_FINAL_VALOR_1': '<S1>:1535' */
        if (*Switch2) {
          /* Transition: '<S1>:1524' */
          rtDW.is_AJUST_P_FINAL_1 = IN_DEBOUNCE_1_AJUST_P_FINAL_2;

          /* Entry 'DEBOUNCE_1_AJUST_P_FINAL_2': '<S1>:1537' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntFinal1 = false;
        }
        break;

       case IN_AJUST_P_FINAL_VALOR_2:
        /* During 'AJUST_P_FINAL_VALOR_2': '<S1>:1538' */
        if (*Switch2) {
          /* Transition: '<S1>:1522' */
          rtDW.is_AJUST_P_FINAL_1 = IN_DEBOUNCE_2_AJUST_P_FINAL_2;

          /* Entry 'DEBOUNCE_2_AJUST_P_FINAL_2': '<S1>:1541' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntFinal1 = false;
        }
        break;

       case IN_AJUST_P_FINAL_VALOR_3:
        /* During 'AJUST_P_FINAL_VALOR_3': '<S1>:1539' */
        if (*Switch2) {
          /* Transition: '<S1>:1521' */
          rtDW.is_AJUST_P_FINAL_1 = IN_DEBOUNCE_2_AJUST_P_FINAL_3;

          /* Entry 'DEBOUNCE_2_AJUST_P_FINAL_3': '<S1>:1542' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntFinal1 = false;
        }
        break;

       case IN_AJUST_P_FINAL_VALOR_4:
        /* During 'AJUST_P_FINAL_VALOR_4': '<S1>:1540' */
        /* Transition: '<S1>:1529' */
        if (*Switch2) {
          /* Transition: '<S1>:1531' */
          rtDW.is_AJUST_P_FINAL_1 = IN_DEBOUNCE_4_AJUST_P_FINAL_2;

          /* Entry 'DEBOUNCE_4_AJUST_P_FINAL_2': '<S1>:1543' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntFinal1 = false;
        }
        break;

       case IN_AJUST_P_FINAL_VALOR_RALLY_1:
        /* During 'AJUST_P_FINAL_VALOR_RALLY_1': '<S1>:1532' */
        if (*Switch2) {
          /* Transition: '<S1>:1520' */
          rtDW.is_AJUST_P_FINAL_1 = IN_DEBOUNCE_1_AJUST_P_FINAL_RAL;

          /* Entry 'DEBOUNCE_1_AJUST_P_FINAL_RALLY_1': '<S1>:1533' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntFinal1 = false;
        }
        break;

       case IN_AJUST_P_FINAL_VALOR_RALLY_2:
        /* During 'AJUST_P_FINAL_VALOR_RALLY_2': '<S1>:1534' */
        if (*Switch2) {
          /* Transition: '<S1>:1519' */
          rtDW.is_AJUST_P_FINAL_1 = IN_DEBOUNCE_2_AJUST_P_FINAL_RAL;

          /* Entry 'DEBOUNCE_2_AJUST_P_FINAL_RALLY_2': '<S1>:1536' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntFinal1 = false;
        }
        break;

       case IN_DEBOUNCE_1_AJUST_P_FINAL_2:
        /* During 'DEBOUNCE_1_AJUST_P_FINAL_2': '<S1>:1537' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1525' */
          rtDW.is_AJUST_P_FINAL_1 = IN_AJUST_P_FINAL_VALOR_2;

          /* Entry 'AJUST_P_FINAL_VALOR_2': '<S1>:1538' */
          flashWrite_ValorFinal1 = 2U;
          enviarValorPuntFinal1 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_DEBOUNCE_1_AJUST_P_FINAL_RAL:
        /* During 'DEBOUNCE_1_AJUST_P_FINAL_RALLY_1': '<S1>:1533' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1523' */
          rtDW.is_AJUST_P_FINAL_1 = IN_AJUST_P_FINAL_VALOR_RALLY_2;

          /* Entry 'AJUST_P_FINAL_VALOR_RALLY_2': '<S1>:1534' */
          flashWrite_ValorFinal1 = 6U;
          enviarValorPuntFinal1 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_DEBOUNCE_2_AJUST_P_FINAL_2:
        /* During 'DEBOUNCE_2_AJUST_P_FINAL_2': '<S1>:1541' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1526' */
          rtDW.is_AJUST_P_FINAL_1 = IN_AJUST_P_FINAL_VALOR_3;

          /* Entry 'AJUST_P_FINAL_VALOR_3': '<S1>:1539' */
          flashWrite_ValorFinal1 = 3U;
          enviarValorPuntFinal1 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_DEBOUNCE_2_AJUST_P_FINAL_3:
        /* During 'DEBOUNCE_2_AJUST_P_FINAL_3': '<S1>:1542' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1527' */
          rtDW.is_AJUST_P_FINAL_1 = IN_AJUST_P_FINAL_VALOR_4;

          /* Entry 'AJUST_P_FINAL_VALOR_4': '<S1>:1540' */
          flashWrite_ValorFinal1 = 4U;
          enviarValorPuntFinal1 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_DEBOUNCE_2_AJUST_P_FINAL_RAL:
        /* During 'DEBOUNCE_2_AJUST_P_FINAL_RALLY_2': '<S1>:1536' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1518' */
          rtDW.is_AJUST_P_FINAL_1 = IN_AJUST_P_FINAL_VALOR_1;

          /* Entry 'AJUST_P_FINAL_VALOR_1': '<S1>:1535' */
          flashWrite_ValorFinal1 = 1U;
          enviarValorPuntFinal1 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       default:
        /* During 'DEBOUNCE_4_AJUST_P_FINAL_2': '<S1>:1543' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1530' */
          /* Transition: '<S1>:1528' */
          rtDW.is_AJUST_P_FINAL_1 = IN_AJUST_P_FINAL_VALOR_RALLY_1;

          /* Entry 'AJUST_P_FINAL_VALOR_RALLY_1': '<S1>:1532' */
          flashWrite_ValorFinal1 = 5U;
          enviarValorPuntFinal1 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;
      }
    }
    break;

   case IN_AJUST_P_SALIDA_1:
    /* During 'AJUST_P_SALIDA_1': '<S1>:1474' */
    if (*Switch1) {
      /* Transition: '<S1>:1092' */
      /* Exit Internal 'AJUST_P_SALIDA_1': '<S1>:1474' */
      rtDW.is_AJUST_P_SALIDA_1 = IN_NO_ACTIVE_CHILD;
      rtDW.is_MAPA1 = IN_DEBOUNCE_FINISH_AJUST_P_SALI;

      /* Entry 'DEBOUNCE_FINISH_AJUST_P_SALIDA_1': '<S1>:1093' */
      rtDW.debounceBoto = 0U;
      flashWrite_IsUpdatedValorInicial1 = true;
    } else {
      switch (rtDW.is_AJUST_P_SALIDA_1) {
       case IN_AJUST_P_SALIDA_VALOR_1:
        /* During 'AJUST_P_SALIDA_VALOR_1': '<S1>:1500' */
        if (*Switch2) {
          /* Transition: '<S1>:1488' */
          rtDW.is_AJUST_P_SALIDA_1 = IN_DEBOUNCE_1_AJUST_P_SALIDA_2;

          /* Entry 'DEBOUNCE_1_AJUST_P_SALIDA_2': '<S1>:1502' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntInicial1 = false;
        }
        break;

       case IN_AJUST_P_SALIDA_VALOR_2:
        /* During 'AJUST_P_SALIDA_VALOR_2': '<S1>:1503' */
        if (*Switch2) {
          /* Transition: '<S1>:1486' */
          rtDW.is_AJUST_P_SALIDA_1 = IN_DEBOUNCE_2_AJUST_P_SALIDA_2;

          /* Entry 'DEBOUNCE_2_AJUST_P_SALIDA_2': '<S1>:1506' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntInicial1 = false;
        }
        break;

       case IN_AJUST_P_SALIDA_VALOR_3:
        /* During 'AJUST_P_SALIDA_VALOR_3': '<S1>:1504' */
        if (*Switch2) {
          /* Transition: '<S1>:1485' */
          rtDW.is_AJUST_P_SALIDA_1 = IN_DEBOUNCE_3_AJUST_P_SALIDA_2;

          /* Entry 'DEBOUNCE_3_AJUST_P_SALIDA_2': '<S1>:1507' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntInicial1 = false;
        }
        break;

       case IN_AJUST_P_SALIDA_VALOR_4:
        /* During 'AJUST_P_SALIDA_VALOR_4': '<S1>:1505' */
        /* Transition: '<S1>:1494' */
        if (*Switch2) {
          /* Transition: '<S1>:1496' */
          rtDW.is_AJUST_P_SALIDA_1 = IN_DEBOUNCE_4_AJUST_P_SALIDA_2;

          /* Entry 'DEBOUNCE_4_AJUST_P_SALIDA_2': '<S1>:1508' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntInicial1 = false;
        }
        break;

       case IN_AJUST_P_SALIDA_VALOR_RALLY_1:
        /* During 'AJUST_P_SALIDA_VALOR_RALLY_1': '<S1>:1497' */
        if (*Switch2) {
          /* Transition: '<S1>:1484' */
          rtDW.is_AJUST_P_SALIDA_1 = IN_DEBOUNCE_1_AJUST_P_SALIDA_RA;

          /* Entry 'DEBOUNCE_1_AJUST_P_SALIDA_RALLY_1': '<S1>:1498' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntInicial1 = false;
        }
        break;

       case IN_AJUST_P_SALIDA_VALOR_RALLY_2:
        /* During 'AJUST_P_SALIDA_VALOR_RALLY_2': '<S1>:1499' */
        if (*Switch2) {
          /* Transition: '<S1>:1483' */
          rtDW.is_AJUST_P_SALIDA_1 = IN_DEBOUNCE_1_AJUST_P_SALIDA__m;

          /* Entry 'DEBOUNCE_1_AJUST_P_SALIDA_RALLY_2': '<S1>:1501' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntInicial1 = false;
        }
        break;

       case IN_DEBOUNCE_1_AJUST_P_SALIDA_2:
        /* During 'DEBOUNCE_1_AJUST_P_SALIDA_2': '<S1>:1502' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1490' */
          rtDW.is_AJUST_P_SALIDA_1 = IN_AJUST_P_SALIDA_VALOR_2;

          /* Entry 'AJUST_P_SALIDA_VALOR_2': '<S1>:1503' */
          flashWrite_ValorInicial1 = 2U;
          enviarValorPuntInicial1 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_DEBOUNCE_1_AJUST_P_SALIDA_RA:
        /* During 'DEBOUNCE_1_AJUST_P_SALIDA_RALLY_1': '<S1>:1498' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1487' */
          rtDW.is_AJUST_P_SALIDA_1 = IN_AJUST_P_SALIDA_VALOR_RALLY_2;

          /* Entry 'AJUST_P_SALIDA_VALOR_RALLY_2': '<S1>:1499' */
          flashWrite_ValorInicial1 = 6U;
          enviarValorPuntInicial1 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_DEBOUNCE_1_AJUST_P_SALIDA__m:
        /* During 'DEBOUNCE_1_AJUST_P_SALIDA_RALLY_2': '<S1>:1501' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1489' */
          rtDW.is_AJUST_P_SALIDA_1 = IN_AJUST_P_SALIDA_VALOR_1;

          /* Entry 'AJUST_P_SALIDA_VALOR_1': '<S1>:1500' */
          flashWrite_ValorInicial1 = 1U;
          enviarValorPuntInicial1 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_DEBOUNCE_2_AJUST_P_SALIDA_2:
        /* During 'DEBOUNCE_2_AJUST_P_SALIDA_2': '<S1>:1506' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1492' */
          rtDW.is_AJUST_P_SALIDA_1 = IN_AJUST_P_SALIDA_VALOR_3;

          /* Entry 'AJUST_P_SALIDA_VALOR_3': '<S1>:1504' */
          flashWrite_ValorInicial1 = 3U;
          enviarValorPuntInicial1 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_DEBOUNCE_3_AJUST_P_SALIDA_2:
        /* During 'DEBOUNCE_3_AJUST_P_SALIDA_2': '<S1>:1507' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1491' */
          rtDW.is_AJUST_P_SALIDA_1 = IN_AJUST_P_SALIDA_VALOR_4;

          /* Entry 'AJUST_P_SALIDA_VALOR_4': '<S1>:1505' */
          flashWrite_ValorInicial1 = 4U;
          enviarValorPuntInicial1 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       default:
        /* During 'DEBOUNCE_4_AJUST_P_SALIDA_2': '<S1>:1508' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1495' */
          /* Transition: '<S1>:1493' */
          rtDW.is_AJUST_P_SALIDA_1 = IN_AJUST_P_SALIDA_VALOR_RALLY_1;

          /* Entry 'AJUST_P_SALIDA_VALOR_RALLY_1': '<S1>:1497' */
          flashWrite_ValorInicial1 = 5U;
          enviarValorPuntInicial1 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;
      }
    }
    break;

   case IN_DEBOUNCE_FINISH_4:
    /* During 'DEBOUNCE_FINISH_4': '<S1>:1096' */
    if (rtDW.debounceBoto >= 200U) {
      /* Transition: '<S1>:1097' */
      rtDW.is_MAPA1 = IN_FINISH_4;

      /* Entry 'FINISH_4': '<S1>:1098' */
      rtDW.finish = true;
    } else {
      qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
      if (qY < rtDW.debounceBoto) {
        qY = MAX_uint32_T;
      }

      rtDW.debounceBoto = qY;
    }
    break;

   case IN_DEBOUNCE_FINISH_AJUST_P_FINA:
    /* During 'DEBOUNCE_FINISH_AJUST_P_FINAL_1': '<S1>:1254' */
    if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
      /* Transition: '<S1>:1256' */
      /* Transition: '<S1>:1260' */
      /* Transition: '<S1>:1258' */
      rtDW.is_MAPA1 = IN_MENSAJE_FINISH_4;

      /* Entry 'MENSAJE_FINISH_4': '<S1>:1094' */
      mensajePantalla = 11U;
      mensajePantalla_IsUpdated = true;
    } else {
      flashWrite_IsUpdatedValorFinal1 = false;
      qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
      if (qY < rtDW.debounceBoto) {
        qY = MAX_uint32_T;
      }

      rtDW.debounceBoto = qY;
    }
    break;

   case IN_DEBOUNCE_FINISH_AJUST_P_SALI:
    /* During 'DEBOUNCE_FINISH_AJUST_P_SALIDA_1': '<S1>:1093' */
    if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
      /* Transition: '<S1>:1091' */
      rtDW.is_MAPA1 = IN_MENSAJE_FINISH_4;

      /* Entry 'MENSAJE_FINISH_4': '<S1>:1094' */
      mensajePantalla = 11U;
      mensajePantalla_IsUpdated = true;
    } else {
      flashWrite_IsUpdatedValorInicial1 = false;
      qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
      if (qY < rtDW.debounceBoto) {
        qY = MAX_uint32_T;
      }

      rtDW.debounceBoto = qY;
    }
    break;

   case IN_DEBOUNCE_MENSAJE_P_FINAL_1:
    /* During 'DEBOUNCE_MENSAJE_P_FINAL_1': '<S1>:1085' */
    if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
      /* Transition: '<S1>:1083' */
      rtDW.is_MAPA1 = IN_AJUST_P_FINAL_1;

      /* Entry Internal 'AJUST_P_FINAL_1': '<S1>:1509' */
      /* Transition: '<S1>:1514' */
      rtDW.is_AJUST_P_FINAL_1 = IN_AJUST_P_FINAL_VALOR_1;

      /* Entry 'AJUST_P_FINAL_VALOR_1': '<S1>:1535' */
      flashWrite_ValorFinal1 = 1U;
      enviarValorPuntFinal1 = true;
    } else {
      qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
      if (qY < rtDW.debounceBoto) {
        qY = MAX_uint32_T;
      }

      rtDW.debounceBoto = qY;
    }
    break;

   case IN_DEBOUNCE_MENSAJE_P_SALIDA_1:
    /* During 'DEBOUNCE_MENSAJE_P_SALIDA_1': '<S1>:1081' */
    if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
      /* Transition: '<S1>:1080' */
      rtDW.is_MAPA1 = IN_AJUST_P_SALIDA_1;

      /* Entry Internal 'AJUST_P_SALIDA_1': '<S1>:1474' */
      /* Transition: '<S1>:1479' */
      rtDW.is_AJUST_P_SALIDA_1 = IN_AJUST_P_SALIDA_VALOR_1;

      /* Entry 'AJUST_P_SALIDA_VALOR_1': '<S1>:1500' */
      flashWrite_ValorInicial1 = 1U;
      enviarValorPuntInicial1 = true;
    } else {
      qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
      if (qY < rtDW.debounceBoto) {
        qY = MAX_uint32_T;
      }

      rtDW.debounceBoto = qY;
    }
    break;

   case IN_DEBOUNCE_SUBMENU_1:
    /* During 'DEBOUNCE_SUBMENU_1': '<S1>:1074' */
    if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
      /* Transition: '<S1>:1077' */
      rtDW.is_MAPA1 = IN_MENSAJE_P_FINAL_1;

      /* Entry 'MENSAJE_P_FINAL_1': '<S1>:1076' */
      mensajePantalla = 15U;

      /*  msg15 = Punto Curva Final  */
      mensajePantalla_IsUpdated = true;
    } else {
      qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
      if (qY < rtDW.debounceBoto) {
        qY = MAX_uint32_T;
      }

      rtDW.debounceBoto = qY;
    }
    break;

   case IN_DEBOUNCE_SUBMENU_2:
    /* During 'DEBOUNCE_SUBMENU_2': '<S1>:1102' */
    if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
      /* Transition: '<S1>:1079' */
      rtDW.is_MAPA1 = IN_MENSAJE_P_SALIDA_1;

      /* Entry 'MENSAJE_P_SALIDA_1': '<S1>:1073' */
      mensajePantalla = 14U;

      /*  msg14 = Punto Cuva Salida  */
      mensajePantalla_IsUpdated = true;
    } else {
      qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
      if (qY < rtDW.debounceBoto) {
        qY = MAX_uint32_T;
      }

      rtDW.debounceBoto = qY;
    }
    break;

   case IN_FINISH_4:
    /* During 'FINISH_4': '<S1>:1098' */
    break;

   case IN_MENSAJE_FINISH_4:
    /* During 'MENSAJE_FINISH_4': '<S1>:1094' */
    /* Transition: '<S1>:1095' */
    mensajePantalla_IsUpdated = false;
    rtDW.is_MAPA1 = IN_DEBOUNCE_FINISH_4;

    /* Entry 'DEBOUNCE_FINISH_4': '<S1>:1096' */
    rtDW.debounceBoto = 0U;
    break;

   case IN_MENSAJE_P_FINAL_1:
    /* During 'MENSAJE_P_FINAL_1': '<S1>:1076' */
    if (*Switch2) {
      /* Transition: '<S1>:1078' */
      rtDW.is_MAPA1 = IN_DEBOUNCE_SUBMENU_2;

      /* Entry 'DEBOUNCE_SUBMENU_2': '<S1>:1102' */
      rtDW.debounceBoto = 0U;
    } else if (*Switch1) {
      /* Transition: '<S1>:1084' */
      rtDW.is_MAPA1 = IN_DEBOUNCE_MENSAJE_P_FINAL_1;

      /* Entry 'DEBOUNCE_MENSAJE_P_FINAL_1': '<S1>:1085' */
      rtDW.debounceBoto = 0U;
    } else {
      mensajePantalla_IsUpdated = false;
    }
    break;

   default:
    /* During 'MENSAJE_P_SALIDA_1': '<S1>:1073' */
    if (*Switch2) {
      /* Transition: '<S1>:1075' */
      rtDW.is_MAPA1 = IN_DEBOUNCE_SUBMENU_1;

      /* Entry 'DEBOUNCE_SUBMENU_1': '<S1>:1074' */
      rtDW.debounceBoto = 0U;
    } else if (*Switch1) {
      /* Transition: '<S1>:1082' */
      rtDW.is_MAPA1 = IN_DEBOUNCE_MENSAJE_P_SALIDA_1;

      /* Entry 'DEBOUNCE_MENSAJE_P_SALIDA_1': '<S1>:1081' */
      rtDW.debounceBoto = 0U;
    } else {
      mensajePantalla_IsUpdated = false;
    }
    break;
  }
}

/* Function for Chart: '<Root>/Ajustos' */
static void MAPA1_MENU(const boolean_T *Switch1, const boolean_T *Switch2)
{
  uint32_T qY;

  /* Inport: '<Root>/mes_adcFrenoSafe' */
  /* During 'MAPA1_MENU': '<S1>:978' */
  if ((mes_adcFrenoSafe >= 1200U) && (!rtDW.ajustant)) {
    /* Transition: '<S1>:997' */
    /* Exit Internal 'MAPA1_MENU': '<S1>:978' */
    rtDW.is_MAPA1_MENU = IN_NO_ACTIVE_CHILD;

    /* Exit Internal 'MAPA1': '<S1>:586' */
    /* Exit Internal 'AJUST_P_FINAL_1': '<S1>:1509' */
    rtDW.is_AJUST_P_FINAL_1 = IN_NO_ACTIVE_CHILD;
    rtDW.is_MAPA1 = IN_NO_ACTIVE_CHILD;

    /* Exit Internal 'AJUST_P_SALIDA_1': '<S1>:1474' */
    rtDW.is_AJUST_P_SALIDA_1 = IN_NO_ACTIVE_CHILD;
    rtDW.is_c2_Ajustos = IN_MAPA2_MENU;

    /* Entry Internal 'MAPA2_MENU': '<S1>:1144' */
    /* Transition: '<S1>:1145' */
    rtDW.is_MAPA2_MENU = IN_MENSAJE_5_INIT;

    /* Entry 'MENSAJE_5_INIT': '<S1>:1148' */
    estat = 5U;
    rtDW.finish = false;
    rtDW.ajustant = false;
    mensajePantalla = 5U;
    mensajePantalla_IsUpdated = true;
  } else if ((mes_adcFrenoSafe <= 990U) && (!rtDW.ajustant)) {
    /* Transition: '<S1>:1397' */
    /* Exit Internal 'MAPA1_MENU': '<S1>:978' */
    rtDW.is_MAPA1_MENU = IN_NO_ACTIVE_CHILD;

    /* Exit Internal 'MAPA1': '<S1>:586' */
    /* Exit Internal 'AJUST_P_FINAL_1': '<S1>:1509' */
    rtDW.is_AJUST_P_FINAL_1 = IN_NO_ACTIVE_CHILD;
    rtDW.is_MAPA1 = IN_NO_ACTIVE_CHILD;

    /* Exit Internal 'AJUST_P_SALIDA_1': '<S1>:1474' */
    rtDW.is_AJUST_P_SALIDA_1 = IN_NO_ACTIVE_CHILD;
    rtDW.is_c2_Ajustos = IN_POS_FRE_MAPA2_MENU;

    /* Entry Internal 'POS_FRE_MAPA2_MENU': '<S1>:1369' */
    /* Transition: '<S1>:1370' */
    rtDW.is_POS_FRE_MAPA2_MENU = IN_MENSAJE_4_INIT;

    /* Entry 'MENSAJE_4_INIT': '<S1>:1373' */
    estat = 16U;
    rtDW.finish = false;
    rtDW.ajustant = false;
    mensajePantalla = 16U;
    mensajePantalla_IsUpdated = true;
  } else if (rtDW.finish) {
    /* Transition: '<S1>:1062' */
    /* Exit Internal 'MAPA1_MENU': '<S1>:978' */
    rtDW.is_MAPA1_MENU = IN_NO_ACTIVE_CHILD;

    /* Exit Internal 'MAPA1': '<S1>:586' */
    /* Exit Internal 'AJUST_P_FINAL_1': '<S1>:1509' */
    rtDW.is_AJUST_P_FINAL_1 = IN_NO_ACTIVE_CHILD;
    rtDW.is_MAPA1 = IN_NO_ACTIVE_CHILD;

    /* Exit Internal 'AJUST_P_SALIDA_1': '<S1>:1474' */
    rtDW.is_AJUST_P_SALIDA_1 = IN_NO_ACTIVE_CHILD;
    rtDW.is_c2_Ajustos = IN_RE_INIT;

    /* Entry 'RE_INIT': '<S1>:1055' */
    rtDW.ajustant = false;
  } else {
    switch (rtDW.is_MAPA1_MENU) {
     case IN_DEBOUNCE_4:
      /* During 'DEBOUNCE_4': '<S1>:687' */
      if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
        /* Transition: '<S1>:707' */
        rtDW.is_MAPA1_MENU = IN_MAPA1;

        /* Entry Internal 'MAPA1': '<S1>:586' */
        /* Transition: '<S1>:1101' */
        rtDW.is_MAPA1 = IN_MENSAJE_P_SALIDA_1;

        /* Entry 'MENSAJE_P_SALIDA_1': '<S1>:1073' */
        mensajePantalla = 14U;

        /*  msg14 = Punto Cuva Salida  */
        mensajePantalla_IsUpdated = true;
      } else {
        qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
        if (qY < rtDW.debounceBoto) {
          qY = MAX_uint32_T;
        }

        rtDW.debounceBoto = qY;
      }
      break;

     case IN_MAPA1:
      MAPA1(Switch1, Switch2);
      break;

     default:
      /* During 'MENSAJE_4_INIT': '<S1>:688' */
      if (*Switch1) {
        /* Transition: '<S1>:686' */
        rtDW.is_MAPA1_MENU = IN_DEBOUNCE_4;

        /* Entry 'DEBOUNCE_4': '<S1>:687' */
        rtDW.debounceBoto = 0U;
        rtDW.ajustant = true;
      } else {
        mensajePantalla_IsUpdated = false;
      }
      break;
    }
  }

  /* End of Inport: '<Root>/mes_adcFrenoSafe' */
}

/* Function for Chart: '<Root>/Ajustos' */
static void MAPA2(const boolean_T *Switch1, const boolean_T *Switch2)
{
  uint32_T qY;

  /* During 'MAPA2': '<S1>:1267' */
  switch (rtDW.is_MAPA2) {
   case IN_AJUST_P_FINAL_2:
    /* During 'AJUST_P_FINAL_2': '<S1>:1579' */
    if (*Switch1) {
      /* Transition: '<S1>:1284' */
      /* Exit Internal 'AJUST_P_FINAL_2': '<S1>:1579' */
      rtDW.is_AJUST_P_FINAL_2 = IN_NO_ACTIVE_CHILD;
      rtDW.is_MAPA2 = IN_DEBOUNCE_FINISH_AJUST_P_FI_c;

      /* Entry 'DEBOUNCE_FINISH_AJUST_P_FINAL_2': '<S1>:1314' */
      rtDW.debounceBoto = 0U;
      flashWrite_IsUpdatedValorFinal2 = true;
    } else {
      switch (rtDW.is_AJUST_P_FINAL_2) {
       case IN_AJUST_P_FINAL_VALOR_1:
        /* During 'AJUST_P_FINAL_VALOR_1': '<S1>:1605' */
        if (*Switch2) {
          /* Transition: '<S1>:1594' */
          rtDW.is_AJUST_P_FINAL_2 = IN_DEBOUNCE_1_AJUST_P_FINAL_2;

          /* Entry 'DEBOUNCE_1_AJUST_P_FINAL_2': '<S1>:1607' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntFinal2 = false;
        }
        break;

       case IN_AJUST_P_FINAL_VALOR_2:
        /* During 'AJUST_P_FINAL_VALOR_2': '<S1>:1608' */
        if (*Switch2) {
          /* Transition: '<S1>:1592' */
          rtDW.is_AJUST_P_FINAL_2 = IN_DEBOUNCE_2_AJUST_P_FINAL_2;

          /* Entry 'DEBOUNCE_2_AJUST_P_FINAL_2': '<S1>:1611' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntFinal2 = false;
        }
        break;

       case IN_AJUST_P_FINAL_VALOR_3:
        /* During 'AJUST_P_FINAL_VALOR_3': '<S1>:1609' */
        if (*Switch2) {
          /* Transition: '<S1>:1591' */
          rtDW.is_AJUST_P_FINAL_2 = IN_DEBOUNCE_2_AJUST_P_FINAL_3;

          /* Entry 'DEBOUNCE_2_AJUST_P_FINAL_3': '<S1>:1612' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntFinal2 = false;
        }
        break;

       case IN_AJUST_P_FINAL_VALOR_4:
        /* During 'AJUST_P_FINAL_VALOR_4': '<S1>:1610' */
        /* Transition: '<S1>:1599' */
        if (*Switch2) {
          /* Transition: '<S1>:1601' */
          rtDW.is_AJUST_P_FINAL_2 = IN_DEBOUNCE_4_AJUST_P_FINAL_2;

          /* Entry 'DEBOUNCE_4_AJUST_P_FINAL_2': '<S1>:1613' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntFinal2 = false;
        }
        break;

       case IN_AJUST_P_FINAL_VALOR_RALLY_1:
        /* During 'AJUST_P_FINAL_VALOR_RALLY_1': '<S1>:1602' */
        if (*Switch2) {
          /* Transition: '<S1>:1590' */
          rtDW.is_AJUST_P_FINAL_2 = IN_DEBOUNCE_1_AJUST_P_FINAL_RAL;

          /* Entry 'DEBOUNCE_1_AJUST_P_FINAL_RALLY_1': '<S1>:1603' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntFinal2 = false;
        }
        break;

       case IN_AJUST_P_FINAL_VALOR_RALLY_2:
        /* During 'AJUST_P_FINAL_VALOR_RALLY_2': '<S1>:1604' */
        if (*Switch2) {
          /* Transition: '<S1>:1589' */
          rtDW.is_AJUST_P_FINAL_2 = IN_DEBOUNCE_2_AJUST_P_FINAL_RAL;

          /* Entry 'DEBOUNCE_2_AJUST_P_FINAL_RALLY_2': '<S1>:1606' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntFinal2 = false;
        }
        break;

       case IN_DEBOUNCE_1_AJUST_P_FINAL_2:
        /* During 'DEBOUNCE_1_AJUST_P_FINAL_2': '<S1>:1607' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1595' */
          rtDW.is_AJUST_P_FINAL_2 = IN_AJUST_P_FINAL_VALOR_2;

          /* Entry 'AJUST_P_FINAL_VALOR_2': '<S1>:1608' */
          flashWrite_ValorFinal2 = 2U;
          enviarValorPuntFinal2 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_DEBOUNCE_1_AJUST_P_FINAL_RAL:
        /* During 'DEBOUNCE_1_AJUST_P_FINAL_RALLY_1': '<S1>:1603' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1593' */
          rtDW.is_AJUST_P_FINAL_2 = IN_AJUST_P_FINAL_VALOR_RALLY_2;

          /* Entry 'AJUST_P_FINAL_VALOR_RALLY_2': '<S1>:1604' */
          flashWrite_ValorFinal2 = 6U;
          enviarValorPuntFinal2 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_DEBOUNCE_2_AJUST_P_FINAL_2:
        /* During 'DEBOUNCE_2_AJUST_P_FINAL_2': '<S1>:1611' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1596' */
          rtDW.is_AJUST_P_FINAL_2 = IN_AJUST_P_FINAL_VALOR_3;

          /* Entry 'AJUST_P_FINAL_VALOR_3': '<S1>:1609' */
          flashWrite_ValorFinal2 = 3U;
          enviarValorPuntFinal2 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_DEBOUNCE_2_AJUST_P_FINAL_3:
        /* During 'DEBOUNCE_2_AJUST_P_FINAL_3': '<S1>:1612' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1597' */
          rtDW.is_AJUST_P_FINAL_2 = IN_AJUST_P_FINAL_VALOR_4;

          /* Entry 'AJUST_P_FINAL_VALOR_4': '<S1>:1610' */
          flashWrite_ValorFinal2 = 4U;
          enviarValorPuntFinal2 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_DEBOUNCE_2_AJUST_P_FINAL_RAL:
        /* During 'DEBOUNCE_2_AJUST_P_FINAL_RALLY_2': '<S1>:1606' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1588' */
          rtDW.is_AJUST_P_FINAL_2 = IN_AJUST_P_FINAL_VALOR_1;

          /* Entry 'AJUST_P_FINAL_VALOR_1': '<S1>:1605' */
          flashWrite_ValorFinal2 = 1U;
          enviarValorPuntFinal2 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       default:
        /* During 'DEBOUNCE_4_AJUST_P_FINAL_2': '<S1>:1613' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1600' */
          /* Transition: '<S1>:1598' */
          rtDW.is_AJUST_P_FINAL_2 = IN_AJUST_P_FINAL_VALOR_RALLY_1;

          /* Entry 'AJUST_P_FINAL_VALOR_RALLY_1': '<S1>:1602' */
          flashWrite_ValorFinal2 = 5U;
          enviarValorPuntFinal2 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;
      }
    }
    break;

   case IN_AJUST_P_SALIDA_2:
    /* During 'AJUST_P_SALIDA_2': '<S1>:1544' */
    if (*Switch1) {
      /* Transition: '<S1>:1275' */
      /* Exit Internal 'AJUST_P_SALIDA_2': '<S1>:1544' */
      rtDW.is_AJUST_P_SALIDA_2 = IN_NO_ACTIVE_CHILD;
      rtDW.is_MAPA2 = IN_DEBOUNCE_FINISH_AJUST_P_SA_c;

      /* Entry 'DEBOUNCE_FINISH_AJUST_P_SALIDA_2': '<S1>:1310' */
      rtDW.debounceBoto = 0U;
      flashWrite_IsUpdatedValorInicial2 = true;
    } else {
      switch (rtDW.is_AJUST_P_SALIDA_2) {
       case IN_AJUST_P_SALIDA_VALOR_1:
        /* During 'AJUST_P_SALIDA_VALOR_1': '<S1>:1570' */
        if (*Switch2) {
          /* Transition: '<S1>:1558' */
          rtDW.is_AJUST_P_SALIDA_2 = IN_DEBOUNCE_1_AJUST_P_SALIDA_2;

          /* Entry 'DEBOUNCE_1_AJUST_P_SALIDA_2': '<S1>:1572' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntInicial2 = false;
        }
        break;

       case IN_AJUST_P_SALIDA_VALOR_2:
        /* During 'AJUST_P_SALIDA_VALOR_2': '<S1>:1573' */
        if (*Switch2) {
          /* Transition: '<S1>:1556' */
          rtDW.is_AJUST_P_SALIDA_2 = IN_DEBOUNCE_2_AJUST_P_SALIDA_2;

          /* Entry 'DEBOUNCE_2_AJUST_P_SALIDA_2': '<S1>:1576' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntInicial2 = false;
        }
        break;

       case IN_AJUST_P_SALIDA_VALOR_3:
        /* During 'AJUST_P_SALIDA_VALOR_3': '<S1>:1574' */
        if (*Switch2) {
          /* Transition: '<S1>:1555' */
          rtDW.is_AJUST_P_SALIDA_2 = IN_DEBOUNCE_3_AJUST_P_SALIDA_2;

          /* Entry 'DEBOUNCE_3_AJUST_P_SALIDA_2': '<S1>:1577' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntInicial2 = false;
        }
        break;

       case IN_AJUST_P_SALIDA_VALOR_4:
        /* During 'AJUST_P_SALIDA_VALOR_4': '<S1>:1575' */
        /* Transition: '<S1>:1564' */
        if (*Switch2) {
          /* Transition: '<S1>:1566' */
          rtDW.is_AJUST_P_SALIDA_2 = IN_DEBOUNCE_4_AJUST_P_SALIDA_2;

          /* Entry 'DEBOUNCE_4_AJUST_P_SALIDA_2': '<S1>:1578' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntInicial2 = false;
        }
        break;

       case IN_AJUST_P_SALIDA_VALOR_RALLY_1:
        /* During 'AJUST_P_SALIDA_VALOR_RALLY_1': '<S1>:1567' */
        if (*Switch2) {
          /* Transition: '<S1>:1554' */
          rtDW.is_AJUST_P_SALIDA_2 = IN_DEBOUNCE_1_AJUST_P_SALIDA_RA;

          /* Entry 'DEBOUNCE_1_AJUST_P_SALIDA_RALLY_1': '<S1>:1568' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntInicial2 = false;
        }
        break;

       case IN_AJUST_P_SALIDA_VALOR_RALLY_2:
        /* During 'AJUST_P_SALIDA_VALOR_RALLY_2': '<S1>:1569' */
        if (*Switch2) {
          /* Transition: '<S1>:1553' */
          rtDW.is_AJUST_P_SALIDA_2 = IN_DEBOUNCE_1_AJUST_P_SALIDA__m;

          /* Entry 'DEBOUNCE_1_AJUST_P_SALIDA_RALLY_2': '<S1>:1571' */
          rtDW.debounceBoto = 0U;
        } else {
          enviarValorPuntInicial2 = false;
        }
        break;

       case IN_DEBOUNCE_1_AJUST_P_SALIDA_2:
        /* During 'DEBOUNCE_1_AJUST_P_SALIDA_2': '<S1>:1572' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1560' */
          rtDW.is_AJUST_P_SALIDA_2 = IN_AJUST_P_SALIDA_VALOR_2;

          /* Entry 'AJUST_P_SALIDA_VALOR_2': '<S1>:1573' */
          flashWrite_ValorInicial2 = 2U;
          enviarValorPuntInicial2 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_DEBOUNCE_1_AJUST_P_SALIDA_RA:
        /* During 'DEBOUNCE_1_AJUST_P_SALIDA_RALLY_1': '<S1>:1568' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1557' */
          rtDW.is_AJUST_P_SALIDA_2 = IN_AJUST_P_SALIDA_VALOR_RALLY_2;

          /* Entry 'AJUST_P_SALIDA_VALOR_RALLY_2': '<S1>:1569' */
          flashWrite_ValorInicial2 = 6U;
          enviarValorPuntInicial2 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_DEBOUNCE_1_AJUST_P_SALIDA__m:
        /* During 'DEBOUNCE_1_AJUST_P_SALIDA_RALLY_2': '<S1>:1571' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1559' */
          rtDW.is_AJUST_P_SALIDA_2 = IN_AJUST_P_SALIDA_VALOR_1;

          /* Entry 'AJUST_P_SALIDA_VALOR_1': '<S1>:1570' */
          flashWrite_ValorInicial2 = 1U;
          enviarValorPuntInicial2 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_DEBOUNCE_2_AJUST_P_SALIDA_2:
        /* During 'DEBOUNCE_2_AJUST_P_SALIDA_2': '<S1>:1576' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1562' */
          rtDW.is_AJUST_P_SALIDA_2 = IN_AJUST_P_SALIDA_VALOR_3;

          /* Entry 'AJUST_P_SALIDA_VALOR_3': '<S1>:1574' */
          flashWrite_ValorInicial2 = 3U;
          enviarValorPuntInicial2 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_DEBOUNCE_3_AJUST_P_SALIDA_2:
        /* During 'DEBOUNCE_3_AJUST_P_SALIDA_2': '<S1>:1577' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1561' */
          rtDW.is_AJUST_P_SALIDA_2 = IN_AJUST_P_SALIDA_VALOR_4;

          /* Entry 'AJUST_P_SALIDA_VALOR_4': '<S1>:1575' */
          flashWrite_ValorInicial2 = 4U;
          enviarValorPuntInicial2 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       default:
        /* During 'DEBOUNCE_4_AJUST_P_SALIDA_2': '<S1>:1578' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Transition: '<S1>:1565' */
          /* Transition: '<S1>:1563' */
          rtDW.is_AJUST_P_SALIDA_2 = IN_AJUST_P_SALIDA_VALOR_RALLY_1;

          /* Entry 'AJUST_P_SALIDA_VALOR_RALLY_1': '<S1>:1567' */
          flashWrite_ValorInicial2 = 5U;
          enviarValorPuntInicial2 = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;
      }
    }
    break;

   case IN_DEBOUNCE_FINISH_5:
    /* During 'DEBOUNCE_FINISH_5': '<S1>:1313' */
    if (rtDW.debounceBoto >= 200U) {
      /* Transition: '<S1>:1282' */
      rtDW.is_MAPA2 = IN_FINISH_5;

      /* Entry 'FINISH_5': '<S1>:1315' */
      rtDW.finish = true;
    } else {
      qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
      if (qY < rtDW.debounceBoto) {
        qY = MAX_uint32_T;
      }

      rtDW.debounceBoto = qY;
    }
    break;

   case IN_DEBOUNCE_FINISH_AJUST_P_FI_c:
    /* During 'DEBOUNCE_FINISH_AJUST_P_FINAL_2': '<S1>:1314' */
    if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
      /* Transition: '<S1>:1283' */
      /* Transition: '<S1>:1278' */
      /* Transition: '<S1>:1277' */
      rtDW.is_MAPA2 = IN_MENSAJE_FINISH_5;

      /* Entry 'MENSAJE_FINISH_5': '<S1>:1309' */
      mensajePantalla = 11U;
      mensajePantalla_IsUpdated = true;
    } else {
      flashWrite_IsUpdatedValorFinal2 = false;
      qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
      if (qY < rtDW.debounceBoto) {
        qY = MAX_uint32_T;
      }

      rtDW.debounceBoto = qY;
    }
    break;

   case IN_DEBOUNCE_FINISH_AJUST_P_SA_c:
    /* During 'DEBOUNCE_FINISH_AJUST_P_SALIDA_2': '<S1>:1310' */
    if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
      /* Transition: '<S1>:1276' */
      rtDW.is_MAPA2 = IN_MENSAJE_FINISH_5;

      /* Entry 'MENSAJE_FINISH_5': '<S1>:1309' */
      mensajePantalla = 11U;
      mensajePantalla_IsUpdated = true;
    } else {
      flashWrite_IsUpdatedValorInicial2 = false;
      qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
      if (qY < rtDW.debounceBoto) {
        qY = MAX_uint32_T;
      }

      rtDW.debounceBoto = qY;
    }
    break;

   case IN_DEBOUNCE_MENSAJE_P_FINAL_2:
    /* During 'DEBOUNCE_MENSAJE_P_FINAL_2': '<S1>:1337' */
    if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
      /* Transition: '<S1>:1286' */
      rtDW.is_MAPA2 = IN_AJUST_P_FINAL_2;

      /* Entry Internal 'AJUST_P_FINAL_2': '<S1>:1579' */
      /* Transition: '<S1>:1584' */
      rtDW.is_AJUST_P_FINAL_2 = IN_AJUST_P_FINAL_VALOR_1;

      /* Entry 'AJUST_P_FINAL_VALOR_1': '<S1>:1605' */
      flashWrite_ValorFinal2 = 1U;
      enviarValorPuntFinal2 = true;
    } else {
      qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
      if (qY < rtDW.debounceBoto) {
        qY = MAX_uint32_T;
      }

      rtDW.debounceBoto = qY;
    }
    break;

   case IN_DEBOUNCE_MENSAJE_P_SALIDA_2:
    /* During 'DEBOUNCE_MENSAJE_P_SALIDA_2': '<S1>:1308' */
    if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
      /* Transition: '<S1>:1270' */
      rtDW.is_MAPA2 = IN_AJUST_P_SALIDA_2;

      /* Entry Internal 'AJUST_P_SALIDA_2': '<S1>:1544' */
      /* Transition: '<S1>:1549' */
      rtDW.is_AJUST_P_SALIDA_2 = IN_AJUST_P_SALIDA_VALOR_1;

      /* Entry 'AJUST_P_SALIDA_VALOR_1': '<S1>:1570' */
      flashWrite_ValorInicial2 = 1U;
      enviarValorPuntInicial2 = true;
    } else {
      qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
      if (qY < rtDW.debounceBoto) {
        qY = MAX_uint32_T;
      }

      rtDW.debounceBoto = qY;
    }
    break;

   case IN_DEBOUNCE_SUBMENU_3:
    /* During 'DEBOUNCE_SUBMENU_3': '<S1>:1311' */
    if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
      /* Transition: '<S1>:1280' */
      rtDW.is_MAPA2 = IN_MENSAJE_P_FINAL_2;

      /* Entry 'MENSAJE_P_FINAL_2': '<S1>:1336' */
      mensajePantalla = 15U;

      /*  msg15 = Punto Curva Final  */
      mensajePantalla_IsUpdated = true;
    } else {
      qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
      if (qY < rtDW.debounceBoto) {
        qY = MAX_uint32_T;
      }

      rtDW.debounceBoto = qY;
    }
    break;

   case IN_DEBOUNCE_SUBMENU_4:
    /* During 'DEBOUNCE_SUBMENU_4': '<S1>:1312' */
    if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
      /* Transition: '<S1>:1274' */
      rtDW.is_MAPA2 = IN_MENSAJE_P_SALIDA_2;

      /* Entry 'MENSAJE_P_SALIDA_2': '<S1>:1307' */
      mensajePantalla = 14U;

      /*  msg14 = Punto Cuva Salida  */
      mensajePantalla_IsUpdated = true;
    } else {
      qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
      if (qY < rtDW.debounceBoto) {
        qY = MAX_uint32_T;
      }

      rtDW.debounceBoto = qY;
    }
    break;

   case IN_FINISH_5:
    /* During 'FINISH_5': '<S1>:1315' */
    break;

   case IN_MENSAJE_FINISH_5:
    /* During 'MENSAJE_FINISH_5': '<S1>:1309' */
    /* Transition: '<S1>:1279' */
    mensajePantalla_IsUpdated = false;
    rtDW.is_MAPA2 = IN_DEBOUNCE_FINISH_5;

    /* Entry 'DEBOUNCE_FINISH_5': '<S1>:1313' */
    rtDW.debounceBoto = 0U;
    break;

   case IN_MENSAJE_P_FINAL_2:
    /* During 'MENSAJE_P_FINAL_2': '<S1>:1336' */
    if (*Switch2) {
      /* Transition: '<S1>:1281' */
      rtDW.is_MAPA2 = IN_DEBOUNCE_SUBMENU_4;

      /* Entry 'DEBOUNCE_SUBMENU_4': '<S1>:1312' */
      rtDW.debounceBoto = 0U;
    } else if (*Switch1) {
      /* Transition: '<S1>:1285' */
      rtDW.is_MAPA2 = IN_DEBOUNCE_MENSAJE_P_FINAL_2;

      /* Entry 'DEBOUNCE_MENSAJE_P_FINAL_2': '<S1>:1337' */
      rtDW.debounceBoto = 0U;
    } else {
      mensajePantalla_IsUpdated = false;
    }
    break;

   default:
    /* During 'MENSAJE_P_SALIDA_2': '<S1>:1307' */
    if (*Switch2) {
      /* Transition: '<S1>:1273' */
      rtDW.is_MAPA2 = IN_DEBOUNCE_SUBMENU_3;

      /* Entry 'DEBOUNCE_SUBMENU_3': '<S1>:1311' */
      rtDW.debounceBoto = 0U;
    } else if (*Switch1) {
      /* Transition: '<S1>:1272' */
      rtDW.is_MAPA2 = IN_DEBOUNCE_MENSAJE_P_SALIDA_2;

      /* Entry 'DEBOUNCE_MENSAJE_P_SALIDA_2': '<S1>:1308' */
      rtDW.debounceBoto = 0U;
    } else {
      mensajePantalla_IsUpdated = false;
    }
    break;
  }
}

/* Function for Chart: '<Root>/Ajustos' */
static void MAPA2_MENU(const boolean_T *Switch1, const boolean_T *Switch2)
{
  uint32_T qY;

  /* Inport: '<Root>/mes_adcFrenoSafe' */
  /* During 'MAPA2_MENU': '<S1>:1144' */
  if ((mes_adcFrenoSafe >= 1400U) && (!rtDW.ajustant)) {
    /* Transition: '<S1>:1012' */
    /* Exit Internal 'MAPA2_MENU': '<S1>:1144' */
    rtDW.is_MAPA2_MENU = IN_NO_ACTIVE_CHILD;

    /* Exit Internal 'MAPA2': '<S1>:1267' */
    /* Exit Internal 'AJUST_P_FINAL_2': '<S1>:1579' */
    rtDW.is_AJUST_P_FINAL_2 = IN_NO_ACTIVE_CHILD;
    rtDW.is_MAPA2 = IN_NO_ACTIVE_CHILD;

    /* Exit Internal 'AJUST_P_SALIDA_2': '<S1>:1544' */
    rtDW.is_AJUST_P_SALIDA_2 = IN_NO_ACTIVE_CHILD;
    rtDW.is_c2_Ajustos = IN_SALIR;

    /* Entry Internal 'SALIR': '<S1>:1401' */
    /* Transition: '<S1>:1402' */
    rtDW.retornoInit = false;
    rtDW.is_SALIR = IN_MENSAJE_18_INIT;

    /* Entry 'MENSAJE_18_INIT': '<S1>:1405' */
    estat = 18U;
    rtDW.finish = false;
    mensajePantalla = 18U;
    mensajePantalla_IsUpdated = true;
  } else if ((mes_adcFrenoSafe <= 1190U) && (!rtDW.ajustant)) {
    /* Transition: '<S1>:996' */
    /* Exit Internal 'MAPA2_MENU': '<S1>:1144' */
    rtDW.is_MAPA2_MENU = IN_NO_ACTIVE_CHILD;

    /* Exit Internal 'MAPA2': '<S1>:1267' */
    /* Exit Internal 'AJUST_P_FINAL_2': '<S1>:1579' */
    rtDW.is_AJUST_P_FINAL_2 = IN_NO_ACTIVE_CHILD;
    rtDW.is_MAPA2 = IN_NO_ACTIVE_CHILD;

    /* Exit Internal 'AJUST_P_SALIDA_2': '<S1>:1544' */
    rtDW.is_AJUST_P_SALIDA_2 = IN_NO_ACTIVE_CHILD;
    rtDW.is_c2_Ajustos = IN_MAPA1_MENU;

    /* Entry Internal 'MAPA1_MENU': '<S1>:978' */
    /* Transition: '<S1>:980' */
    rtDW.is_MAPA1_MENU = IN_MENSAJE_4_INIT;

    /* Entry 'MENSAJE_4_INIT': '<S1>:688' */
    estat = 4U;
    rtDW.finish = false;
    rtDW.ajustant = false;
    mensajePantalla = 4U;
    mensajePantalla_IsUpdated = true;
  } else if (rtDW.finish) {
    /* Transition: '<S1>:1065' */
    /* Exit Internal 'MAPA2_MENU': '<S1>:1144' */
    rtDW.is_MAPA2_MENU = IN_NO_ACTIVE_CHILD;

    /* Exit Internal 'MAPA2': '<S1>:1267' */
    /* Exit Internal 'AJUST_P_FINAL_2': '<S1>:1579' */
    rtDW.is_AJUST_P_FINAL_2 = IN_NO_ACTIVE_CHILD;
    rtDW.is_MAPA2 = IN_NO_ACTIVE_CHILD;

    /* Exit Internal 'AJUST_P_SALIDA_2': '<S1>:1544' */
    rtDW.is_AJUST_P_SALIDA_2 = IN_NO_ACTIVE_CHILD;
    rtDW.is_c2_Ajustos = IN_RE_INIT;

    /* Entry 'RE_INIT': '<S1>:1055' */
    rtDW.ajustant = false;
  } else {
    switch (rtDW.is_MAPA2_MENU) {
     case IN_DEBOUNCE_5:
      /* During 'DEBOUNCE_5': '<S1>:1176' */
      if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
        /* Transition: '<S1>:1147' */
        rtDW.is_MAPA2_MENU = IN_MAPA2;

        /* Entry Internal 'MAPA2': '<S1>:1267' */
        /* Transition: '<S1>:1271' */
        rtDW.is_MAPA2 = IN_MENSAJE_P_SALIDA_2;

        /* Entry 'MENSAJE_P_SALIDA_2': '<S1>:1307' */
        mensajePantalla = 14U;

        /*  msg14 = Punto Cuva Salida  */
        mensajePantalla_IsUpdated = true;
      } else {
        qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
        if (qY < rtDW.debounceBoto) {
          qY = MAX_uint32_T;
        }

        rtDW.debounceBoto = qY;
      }
      break;

     case IN_MAPA2:
      MAPA2(Switch1, Switch2);
      break;

     default:
      /* During 'MENSAJE_5_INIT': '<S1>:1148' */
      if (*Switch1) {
        /* Transition: '<S1>:1146' */
        rtDW.is_MAPA2_MENU = IN_DEBOUNCE_5;

        /* Entry 'DEBOUNCE_5': '<S1>:1176' */
        rtDW.debounceBoto = 0U;
        rtDW.ajustant = true;
      } else {
        mensajePantalla_IsUpdated = false;
      }
      break;
    }
  }

  /* End of Inport: '<Root>/mes_adcFrenoSafe' */
}

/* Function for Chart: '<Root>/Ajustos' */
static void POS_FONDO_MENU(const boolean_T *Switch1)
{
  uint32_T qY;

  /* Inport: '<Root>/mes_adcFrenoSafe' */
  /* During 'POS_FONDO_MENU': '<S1>:970' */
  if ((mes_adcFrenoSafe >= 800U) && (!rtDW.ajustant)) {
    /* Transition: '<S1>:987' */
    /* Exit Internal 'POS_FONDO_MENU': '<S1>:970' */
    rtDW.is_POS_FONDO_MENU = IN_NO_ACTIVE_CHILD;

    /* Exit Internal 'POS_FONDO': '<S1>:551' */
    rtDW.is_POS_FONDO = IN_NO_ACTIVE_CHILD;
    rtDW.is_c2_Ajustos = IN_POS_FRE_MAPA2_MENU;

    /* Entry Internal 'POS_FRE_MAPA2_MENU': '<S1>:1369' */
    /* Transition: '<S1>:1370' */
    rtDW.is_POS_FRE_MAPA2_MENU = IN_MENSAJE_4_INIT;

    /* Entry 'MENSAJE_4_INIT': '<S1>:1373' */
    estat = 16U;
    rtDW.finish = false;
    rtDW.ajustant = false;
    mensajePantalla = 16U;
    mensajePantalla_IsUpdated = true;
  } else if ((mes_adcFrenoSafe <= 590U) && (!rtDW.ajustant)) {
    /* Transition: '<S1>:977' */
    /* Exit Internal 'POS_FONDO_MENU': '<S1>:970' */
    rtDW.is_POS_FONDO_MENU = IN_NO_ACTIVE_CHILD;

    /* Exit Internal 'POS_FONDO': '<S1>:551' */
    rtDW.is_POS_FONDO = IN_NO_ACTIVE_CHILD;
    rtDW.is_c2_Ajustos = IN_POS_FRENO_MENU;

    /* Entry Internal 'POS_FRENO_MENU': '<S1>:967' */
    /* Transition: '<S1>:979' */
    rtDW.is_POS_FRENO_MENU = IN_MENSAJE_2_INIT;

    /* Entry 'MENSAJE_2_INIT': '<S1>:676' */
    estat = 2U;
    rtDW.finish = false;
    rtDW.ajustant = false;
    mensajePantalla = 2U;
    mensajePantalla_IsUpdated = true;
  } else if (rtDW.finish) {
    /* Transition: '<S1>:1060' */
    /* Exit Internal 'POS_FONDO_MENU': '<S1>:970' */
    rtDW.is_POS_FONDO_MENU = IN_NO_ACTIVE_CHILD;

    /* Exit Internal 'POS_FONDO': '<S1>:551' */
    rtDW.is_POS_FONDO = IN_NO_ACTIVE_CHILD;
    rtDW.is_c2_Ajustos = IN_RE_INIT;

    /* Entry 'RE_INIT': '<S1>:1055' */
    rtDW.ajustant = false;
  } else {
    switch (rtDW.is_POS_FONDO_MENU) {
     case IN_DEBOUNCE_3:
      /* During 'DEBOUNCE_3': '<S1>:684' */
      if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
        /* Transition: '<S1>:706' */
        rtDW.is_POS_FONDO_MENU = IN_POS_FONDO;

        /* Entry Internal 'POS_FONDO': '<S1>:551' */
        /* Transition: '<S1>:860' */
        rtDW.is_POS_FONDO = IN_MENSAJE_VALOR_GATELL_3;

        /* Entry 'MENSAJE_VALOR_GATELL_3': '<S1>:865' */
        enviarValorGatell = true;
      } else {
        qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
        if (qY < rtDW.debounceBoto) {
          qY = MAX_uint32_T;
        }

        rtDW.debounceBoto = qY;
      }
      break;

     case IN_MENSAJE_4_INIT_d:
      /* During 'MENSAJE_4_INIT': '<S1>:685' */
      if (*Switch1) {
        /* Transition: '<S1>:683' */
        rtDW.is_POS_FONDO_MENU = IN_DEBOUNCE_3;

        /* Entry 'DEBOUNCE_3': '<S1>:684' */
        rtDW.debounceBoto = 0U;
        rtDW.ajustant = true;
      } else {
        mensajePantalla_IsUpdated = false;
      }
      break;

     default:
      /* During 'POS_FONDO': '<S1>:551' */
      switch (rtDW.is_POS_FONDO) {
       case IN_DEBOUNCE_3:
        /* During 'DEBOUNCE_3': '<S1>:863' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Inport: '<Root>/mes_gatellFiltratFinal' */
          /* Transition: '<S1>:861' */
          /*  GatellMinHigh - 40 >  GatellMaxHigh  */
          qY = mes_gatellFiltratFinal - /*MW:OvSatOk*/ 50U;
          if (qY > mes_gatellFiltratFinal) {
            qY = 0U;
          }

          /* End of Inport: '<Root>/mes_gatellFiltratFinal' */

          /* Inport: '<Root>/flashRead_GatellMinLow' */
          if (qY > flashRead_GatellMinLow) {
            /* Transition: '<S1>:874' */
            /* Transition: '<S1>:856' */
            rtDW.is_POS_FONDO = IN_MENSAJE_FINISH_3;

            /* Entry 'MENSAJE_FINISH_3': '<S1>:864' */
            mensajePantalla = 11U;
            mensajePantalla_IsUpdated = true;
            flashWrite_IsUpdatedPosFondo = true;
          } else {
            /* Transition: '<S1>:857' */
            rtDW.is_POS_FONDO = IN_PosFondoNok;

            /* Entry 'PosFondoNok': '<S1>:871' */
            mensajePantalla = 10U;
            mensajePantalla_IsUpdated = true;
          }

          /* End of Inport: '<Root>/flashRead_GatellMinLow' */
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_DEBOUNCE_FINISH_3:
        /* During 'DEBOUNCE_FINISH_3': '<S1>:866' */
        if (rtDW.debounceBoto >= 200U) {
          /* Transition: '<S1>:855' */
          rtDW.is_POS_FONDO = IN_FINISH_3;

          /* Entry 'FINISH_3': '<S1>:859' */
          rtDW.finish = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_DEBOUNCE_NOK_3:
        /* During 'DEBOUNCE_NOK_3': '<S1>:869' */
        if (rtDW.debounceBoto >= 200U) {
          /* Transition: '<S1>:870' */
          rtDW.is_POS_FONDO = IN_FINISH_NOK_3;

          /* Entry 'FINISH_NOK_3': '<S1>:873' */
          rtDW.finish = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_FINISH_3:
        /* During 'FINISH_3': '<S1>:859' */
        break;

       case IN_FINISH_NOK_3:
        /* During 'FINISH_NOK_3': '<S1>:873' */
        break;

       case IN_MENSAJE_FINISH_3:
        /* During 'MENSAJE_FINISH_3': '<S1>:864' */
        /* Transition: '<S1>:862' */
        mensajePantalla_IsUpdated = false;
        flashWrite_IsUpdatedPosFondo = false;
        rtDW.is_POS_FONDO = IN_DEBOUNCE_FINISH_3;

        /* Entry 'DEBOUNCE_FINISH_3': '<S1>:866' */
        rtDW.debounceBoto = 0U;
        break;

       case IN_MENSAJE_VALOR_GATELL_3:
        /* During 'MENSAJE_VALOR_GATELL_3': '<S1>:865' */
        if (*Switch1) {
          /* Transition: '<S1>:858' */
          rtDW.is_POS_FONDO = IN_DEBOUNCE_3;

          /* Entry 'DEBOUNCE_3': '<S1>:863' */
          rtDW.debounceBoto = 0U;
          enviarValorGatell = false;
        }
        break;

       default:
        /* During 'PosFondoNok': '<S1>:871' */
        /* Transition: '<S1>:872' */
        mensajePantalla_IsUpdated = false;
        rtDW.is_POS_FONDO = IN_DEBOUNCE_NOK_3;

        /* Entry 'DEBOUNCE_NOK_3': '<S1>:869' */
        rtDW.debounceBoto = 0U;
        break;
      }
      break;
    }
  }

  /* End of Inport: '<Root>/mes_adcFrenoSafe' */
}

/* Function for Chart: '<Root>/Ajustos' */
static void POS_FRENO_MENU(const boolean_T *Switch1)
{
  uint32_T qY;

  /* Inport: '<Root>/mes_adcFrenoSafe' */
  /* During 'POS_FRENO_MENU': '<S1>:967' */
  if ((mes_adcFrenoSafe <= 390U) && (!rtDW.ajustant)) {
    /* Transition: '<S1>:969' */
    /* Exit Internal 'POS_FRENO_MENU': '<S1>:967' */
    rtDW.is_POS_FRENO_MENU = IN_NO_ACTIVE_CHILD;

    /* Exit Internal 'POS_FRENO': '<S1>:174' */
    rtDW.is_POS_FRENO = IN_NO_ACTIVE_CHILD;
    rtDW.is_c2_Ajustos = IN_VISOR_GATELL_MENU;

    /* Entry Internal 'VISOR_GATELL_MENU': '<S1>:942' */
    /* Transition: '<S1>:958' */
    rtDW.is_VISOR_GATELL_MENU = IN_MENSAJE_1_INIT1;

    /* Entry 'MENSAJE_1_INIT1': '<S1>:943' */
    estat = 1U;
    rtDW.finish = false;
    rtDW.ajustant = false;
    mensajePantalla = 1U;
    mensajePantalla_IsUpdated = true;
  } else if ((mes_adcFrenoSafe >= 600U) && (!rtDW.ajustant)) {
    /* Transition: '<S1>:976' */
    /* Exit Internal 'POS_FRENO_MENU': '<S1>:967' */
    rtDW.is_POS_FRENO_MENU = IN_NO_ACTIVE_CHILD;

    /* Exit Internal 'POS_FRENO': '<S1>:174' */
    rtDW.is_POS_FRENO = IN_NO_ACTIVE_CHILD;
    rtDW.is_c2_Ajustos = IN_POS_FONDO_MENU;

    /* Entry Internal 'POS_FONDO_MENU': '<S1>:970' */
    /* Transition: '<S1>:981' */
    rtDW.is_POS_FONDO_MENU = IN_MENSAJE_4_INIT_d;

    /* Entry 'MENSAJE_4_INIT': '<S1>:685' */
    estat = 3U;
    rtDW.finish = false;
    rtDW.ajustant = false;
    mensajePantalla = 3U;
    mensajePantalla_IsUpdated = true;
  } else if (rtDW.finish) {
    /* Transition: '<S1>:1058' */
    /* Exit Internal 'POS_FRENO_MENU': '<S1>:967' */
    rtDW.is_POS_FRENO_MENU = IN_NO_ACTIVE_CHILD;

    /* Exit Internal 'POS_FRENO': '<S1>:174' */
    rtDW.is_POS_FRENO = IN_NO_ACTIVE_CHILD;
    rtDW.is_c2_Ajustos = IN_RE_INIT;

    /* Entry 'RE_INIT': '<S1>:1055' */
    rtDW.ajustant = false;
  } else {
    switch (rtDW.is_POS_FRENO_MENU) {
     case IN_DEBOUNCE_2:
      /* During 'DEBOUNCE_2': '<S1>:678' */
      if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
        /* Transition: '<S1>:679' */
        rtDW.is_POS_FRENO_MENU = IN_POS_FRENO;

        /* Entry Internal 'POS_FRENO': '<S1>:174' */
        /* Transition: '<S1>:714' */
        rtDW.is_POS_FRENO = IN_MENSAJE_VALOR_GATELL_2;

        /* Entry 'MENSAJE_VALOR_GATELL_2': '<S1>:721' */
        enviarValorGatell = true;
      } else {
        qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
        if (qY < rtDW.debounceBoto) {
          qY = MAX_uint32_T;
        }

        rtDW.debounceBoto = qY;
      }
      break;

     case IN_MENSAJE_2_INIT:
      /* During 'MENSAJE_2_INIT': '<S1>:676' */
      if (*Switch1) {
        /* Transition: '<S1>:677' */
        rtDW.is_POS_FRENO_MENU = IN_DEBOUNCE_2;

        /* Entry 'DEBOUNCE_2': '<S1>:678' */
        rtDW.debounceBoto = 0U;
        rtDW.ajustant = true;
      } else {
        mensajePantalla_IsUpdated = false;
      }
      break;

     default:
      /* During 'POS_FRENO': '<S1>:174' */
      switch (rtDW.is_POS_FRENO) {
       case IN_DEBOUNCE_2:
        /* During 'DEBOUNCE_2': '<S1>:720' */
        if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
          /* Inport: '<Root>/mes_gatellFiltratFinal' */
          /* Transition: '<S1>:718' */
          /*  GatellMinHigh + 40 <  GatellMaxHigh  */
          qY = mes_gatellFiltratFinal + /*MW:OvSatOk*/ 50U;
          if (qY < mes_gatellFiltratFinal) {
            qY = MAX_uint32_T;
          }

          /* End of Inport: '<Root>/mes_gatellFiltratFinal' */

          /* Inport: '<Root>/flashRead_GatellMaxHigh' */
          if (qY < flashRead_GatellMaxHigh) {
            /* Transition: '<S1>:852' */
            /* Transition: '<S1>:853' */
            rtDW.is_POS_FRENO = IN_MENSAJE_FINISH_2;

            /* Entry 'MENSAJE_FINISH_2': '<S1>:717' */
            mensajePantalla = 11U;
            mensajePantalla_IsUpdated = true;
            flashWrite_IsUpdatedPosFreno = true;
          } else {
            /* Transition: '<S1>:854' */
            rtDW.is_POS_FRENO = IN_MENSAJE_PosFrenoNok;

            /* Entry 'MENSAJE_PosFrenoNok': '<S1>:847' */
            mensajePantalla = 9U;
            mensajePantalla_IsUpdated = true;
          }

          /* End of Inport: '<Root>/flashRead_GatellMaxHigh' */
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_DEBOUNCE_FINISH_2:
        /* During 'DEBOUNCE_FINISH_2': '<S1>:712' */
        if (rtDW.debounceBoto >= 200U) {
          /* Transition: '<S1>:715' */
          rtDW.is_POS_FRENO = IN_FINISH_2;

          /* Entry 'FINISH_2': '<S1>:713' */
          rtDW.finish = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_DEBOUNCE_NOK_2:
        /* During 'DEBOUNCE_NOK_2': '<S1>:848' */
        if (rtDW.debounceBoto >= 200U) {
          /* Transition: '<S1>:844' */
          rtDW.is_POS_FRENO = IN_FINISH_NOK_2;

          /* Entry 'FINISH_NOK_2': '<S1>:845' */
          rtDW.finish = true;
        } else {
          qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
          if (qY < rtDW.debounceBoto) {
            qY = MAX_uint32_T;
          }

          rtDW.debounceBoto = qY;
        }
        break;

       case IN_FINISH_2:
        /* During 'FINISH_2': '<S1>:713' */
        break;

       case IN_FINISH_NOK_2:
        /* During 'FINISH_NOK_2': '<S1>:845' */
        break;

       case IN_MENSAJE_FINISH_2:
        /* During 'MENSAJE_FINISH_2': '<S1>:717' */
        /* Transition: '<S1>:716' */
        mensajePantalla_IsUpdated = false;
        flashWrite_IsUpdatedPosFreno = false;
        rtDW.is_POS_FRENO = IN_DEBOUNCE_FINISH_2;

        /* Entry 'DEBOUNCE_FINISH_2': '<S1>:712' */
        rtDW.debounceBoto = 0U;
        break;

       case IN_MENSAJE_PosFrenoNok:
        /* During 'MENSAJE_PosFrenoNok': '<S1>:847' */
        /* Transition: '<S1>:846' */
        mensajePantalla_IsUpdated = false;
        rtDW.is_POS_FRENO = IN_DEBOUNCE_NOK_2;

        /* Entry 'DEBOUNCE_NOK_2': '<S1>:848' */
        rtDW.debounceBoto = 0U;
        break;

       default:
        /* During 'MENSAJE_VALOR_GATELL_2': '<S1>:721' */
        if (*Switch1) {
          /* Transition: '<S1>:719' */
          rtDW.is_POS_FRENO = IN_DEBOUNCE_2;

          /* Entry 'DEBOUNCE_2': '<S1>:720' */
          rtDW.debounceBoto = 0U;
          enviarValorGatell = false;
        }
        break;
      }
      break;
    }
  }

  /* End of Inport: '<Root>/mes_adcFrenoSafe' */
}

/* Model step function */
void Ajustos_step(void)
{
  boolean_T Switch1;
  boolean_T Switch2;
  uint32_T qY;

  /* Switch: '<S2>/Switch1' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Inport: '<Root>/DI_BUTTON_1'
   *  Inport: '<Root>/DI_BUTTON_2'
   *  Logic: '<S2>/Logical Operator1'
   *  Logic: '<S2>/Logical Operator2'
   *  Switch: '<S2>/Switch2'
   */
  if (TIPO_MANDO) {
    Switch1 = !IOM_ReadInput__DI_BUTTON_1();
    Switch2 = !IOM_ReadInput__DI_BUTTON_2();
  } else {
    Switch1 = IOM_ReadInput__DI_BUTTON_1();
    Switch2 = IOM_ReadInput__DI_BUTTON_2();
  }

  /* End of Switch: '<S2>/Switch1' */

  /* Chart: '<Root>/Ajustos' incorporates:
   *  Inport: '<Root>/mes_adcFrenoSafe'
   */
  /* Gateway: Ajustos */
  /* During: Ajustos */
  if (rtDW.is_active_c2_Ajustos == 0U) {
    /* Entry: Ajustos */
    rtDW.is_active_c2_Ajustos = 1U;

    /* Entry Internal: Ajustos */
    /* Transition: '<S1>:1016' */
    rtDW.is_c2_Ajustos = IN_INIT;

    /* Entry 'INIT': '<S1>:964' */
    estat = 0U;
    rtDW.finish = false;
    rtDW.ajustant = false;
    enviarValorGatell = false;
    mensajePantalla = 0U;
    mensajePantalla_IsUpdated = true;
  } else {
    switch (rtDW.is_c2_Ajustos) {
     case IN_INIT:
      /* During 'INIT': '<S1>:964' */
      if ((mes_adcFrenoSafe >= 200U) && (!rtDW.ajustant)) {
        /* Transition: '<S1>:965' */
        rtDW.is_c2_Ajustos = IN_VISOR_GATELL_MENU;

        /* Entry Internal 'VISOR_GATELL_MENU': '<S1>:942' */
        /* Transition: '<S1>:958' */
        rtDW.is_VISOR_GATELL_MENU = IN_MENSAJE_1_INIT1;

        /* Entry 'MENSAJE_1_INIT1': '<S1>:943' */
        estat = 1U;
        rtDW.finish = false;
        rtDW.ajustant = false;
        mensajePantalla = 1U;
        mensajePantalla_IsUpdated = true;
      } else {
        mensajePantalla_IsUpdated = false;
      }
      break;

     case IN_MAPA1_MENU:
      MAPA1_MENU(&Switch1, &Switch2);
      break;

     case IN_MAPA2_MENU:
      MAPA2_MENU(&Switch1, &Switch2);
      break;

     case IN_POS_FONDO_MENU:
      POS_FONDO_MENU(&Switch1);
      break;

     case IN_POS_FRENO_MENU:
      POS_FRENO_MENU(&Switch1);
      break;

     case IN_POS_FRE_MAPA2_MENU:
      /* During 'POS_FRE_MAPA2_MENU': '<S1>:1369' */
      if ((mes_adcFrenoSafe >= 1000U) && (!rtDW.ajustant)) {
        /* Transition: '<S1>:1398' */
        /* Exit Internal 'POS_FRE_MAPA2_MENU': '<S1>:1369' */
        rtDW.is_POS_FRE_MAPA2_MENU = IN_NO_ACTIVE_CHILD;

        /* Exit Internal 'FRE_MAPA2': '<S1>:1374' */
        rtDW.is_FRE_MAPA2 = IN_NO_ACTIVE_CHILD;
        rtDW.is_c2_Ajustos = IN_MAPA1_MENU;

        /* Entry Internal 'MAPA1_MENU': '<S1>:978' */
        /* Transition: '<S1>:980' */
        rtDW.is_MAPA1_MENU = IN_MENSAJE_4_INIT;

        /* Entry 'MENSAJE_4_INIT': '<S1>:688' */
        estat = 4U;
        rtDW.finish = false;
        rtDW.ajustant = false;
        mensajePantalla = 4U;
        mensajePantalla_IsUpdated = true;
      } else if ((mes_adcFrenoSafe <= 790U) && (!rtDW.ajustant)) {
        /* Transition: '<S1>:988' */
        /* Exit Internal 'POS_FRE_MAPA2_MENU': '<S1>:1369' */
        rtDW.is_POS_FRE_MAPA2_MENU = IN_NO_ACTIVE_CHILD;

        /* Exit Internal 'FRE_MAPA2': '<S1>:1374' */
        rtDW.is_FRE_MAPA2 = IN_NO_ACTIVE_CHILD;
        rtDW.is_c2_Ajustos = IN_POS_FONDO_MENU;

        /* Entry Internal 'POS_FONDO_MENU': '<S1>:970' */
        /* Transition: '<S1>:981' */
        rtDW.is_POS_FONDO_MENU = IN_MENSAJE_4_INIT_d;

        /* Entry 'MENSAJE_4_INIT': '<S1>:685' */
        estat = 3U;
        rtDW.finish = false;
        rtDW.ajustant = false;
        mensajePantalla = 3U;
        mensajePantalla_IsUpdated = true;
      } else if (rtDW.finish) {
        /* Transition: '<S1>:1400' */
        /* Exit Internal 'POS_FRE_MAPA2_MENU': '<S1>:1369' */
        rtDW.is_POS_FRE_MAPA2_MENU = IN_NO_ACTIVE_CHILD;

        /* Exit Internal 'FRE_MAPA2': '<S1>:1374' */
        rtDW.is_FRE_MAPA2 = IN_NO_ACTIVE_CHILD;
        rtDW.is_c2_Ajustos = IN_RE_INIT;

        /* Entry 'RE_INIT': '<S1>:1055' */
        rtDW.ajustant = false;
      } else {
        switch (rtDW.is_POS_FRE_MAPA2_MENU) {
         case IN_DEBOUNCE_3:
          /* During 'DEBOUNCE_3': '<S1>:1395' */
          if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
            /* Transition: '<S1>:1372' */
            rtDW.is_POS_FRE_MAPA2_MENU = IN_FRE_MAPA2;

            /* Entry Internal 'FRE_MAPA2': '<S1>:1374' */
            /* Transition: '<S1>:1377' */
            rtDW.is_FRE_MAPA2 = IN_MENSAJE_VALOR_GATELL_3_m;

            /* Entry 'MENSAJE_VALOR_GATELL_3': '<S1>:1387' */
            enviarValorGatell = true;
          } else {
            qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
            if (qY < rtDW.debounceBoto) {
              qY = MAX_uint32_T;
            }

            rtDW.debounceBoto = qY;
          }
          break;

         case IN_FRE_MAPA2:
          /* During 'FRE_MAPA2': '<S1>:1374' */
          switch (rtDW.is_FRE_MAPA2) {
           case IN_DEBOUNCE_3:
            /* During 'DEBOUNCE_3': '<S1>:1388' */
            if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
              /* Transition: '<S1>:1379' */
              rtDW.is_FRE_MAPA2 = IN_MENSAJE_FINISH_3_n;

              /* Entry 'MENSAJE_FINISH_3': '<S1>:1390' */
              mensajePantalla = 11U;
              mensajePantalla_IsUpdated = true;
              flashWrite_IsUpdatedlPosFreMapa2 = true;
            } else {
              qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
              if (qY < rtDW.debounceBoto) {
                qY = MAX_uint32_T;
              }

              rtDW.debounceBoto = qY;
            }
            break;

           case IN_DEBOUNCE_FINISH_3:
            /* During 'DEBOUNCE_FINISH_3': '<S1>:1392' */
            if (rtDW.debounceBoto >= 200U) {
              /* Transition: '<S1>:1386' */
              rtDW.is_FRE_MAPA2 = IN_FINISH_3_n;

              /* Entry 'FINISH_3': '<S1>:1393' */
              rtDW.finish = true;
            } else {
              qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
              if (qY < rtDW.debounceBoto) {
                qY = MAX_uint32_T;
              }

              rtDW.debounceBoto = qY;
            }
            break;

           case IN_FINISH_3_n:
            /* During 'FINISH_3': '<S1>:1393' */
            break;

           case IN_MENSAJE_FINISH_3_n:
            /* During 'MENSAJE_FINISH_3': '<S1>:1390' */
            /* Transition: '<S1>:1384' */
            mensajePantalla_IsUpdated = false;
            flashWrite_IsUpdatedlPosFreMapa2 = false;
            rtDW.is_FRE_MAPA2 = IN_DEBOUNCE_FINISH_3;

            /* Entry 'DEBOUNCE_FINISH_3': '<S1>:1392' */
            rtDW.debounceBoto = 0U;
            break;

           default:
            /* During 'MENSAJE_VALOR_GATELL_3': '<S1>:1387' */
            if (Switch1) {
              /* Transition: '<S1>:1378' */
              rtDW.is_FRE_MAPA2 = IN_DEBOUNCE_3;

              /* Entry 'DEBOUNCE_3': '<S1>:1388' */
              rtDW.debounceBoto = 0U;
              enviarValorGatell = false;
            }
            break;
          }
          break;

         default:
          /* During 'MENSAJE_4_INIT': '<S1>:1373' */
          if (Switch1) {
            /* Transition: '<S1>:1371' */
            rtDW.is_POS_FRE_MAPA2_MENU = IN_DEBOUNCE_3;

            /* Entry 'DEBOUNCE_3': '<S1>:1395' */
            rtDW.debounceBoto = 0U;
            rtDW.ajustant = true;
          } else {
            mensajePantalla_IsUpdated = false;
          }
          break;
        }
      }
      break;

     case IN_RE_INIT:
      /* During 'RE_INIT': '<S1>:1055' */
      if (mes_adcFrenoSafe < 200U) {
        /* Transition: '<S1>:1064' */
        rtDW.is_c2_Ajustos = IN_INIT;

        /* Entry 'INIT': '<S1>:964' */
        estat = 0U;
        rtDW.finish = false;
        rtDW.ajustant = false;
        enviarValorGatell = false;
        mensajePantalla = 0U;
        mensajePantalla_IsUpdated = true;
      } else if ((mes_adcFrenoSafe >= 200U) && (mes_adcFrenoSafe < 400U)) {
        /* Transition: '<S1>:1057' */
        rtDW.is_c2_Ajustos = IN_VISOR_GATELL_MENU;

        /* Entry Internal 'VISOR_GATELL_MENU': '<S1>:942' */
        /* Transition: '<S1>:958' */
        rtDW.is_VISOR_GATELL_MENU = IN_MENSAJE_1_INIT1;

        /* Entry 'MENSAJE_1_INIT1': '<S1>:943' */
        estat = 1U;
        rtDW.finish = false;
        rtDW.ajustant = false;
        mensajePantalla = 1U;
        mensajePantalla_IsUpdated = true;
      } else if ((mes_adcFrenoSafe >= 800U) && (mes_adcFrenoSafe < 1000U)) {
        /* Transition: '<S1>:1399' */
        rtDW.is_c2_Ajustos = IN_POS_FRE_MAPA2_MENU;

        /* Entry Internal 'POS_FRE_MAPA2_MENU': '<S1>:1369' */
        /* Transition: '<S1>:1370' */
        rtDW.is_POS_FRE_MAPA2_MENU = IN_MENSAJE_4_INIT;

        /* Entry 'MENSAJE_4_INIT': '<S1>:1373' */
        estat = 16U;
        rtDW.finish = false;
        rtDW.ajustant = false;
        mensajePantalla = 16U;
        mensajePantalla_IsUpdated = true;
      } else if ((mes_adcFrenoSafe >= 400U) && (mes_adcFrenoSafe < 600U)) {
        /* Transition: '<S1>:1059' */
        rtDW.is_c2_Ajustos = IN_POS_FRENO_MENU;

        /* Entry Internal 'POS_FRENO_MENU': '<S1>:967' */
        /* Transition: '<S1>:979' */
        rtDW.is_POS_FRENO_MENU = IN_MENSAJE_2_INIT;

        /* Entry 'MENSAJE_2_INIT': '<S1>:676' */
        estat = 2U;
        rtDW.finish = false;
        rtDW.ajustant = false;
        mensajePantalla = 2U;
        mensajePantalla_IsUpdated = true;
      } else if ((mes_adcFrenoSafe >= 600U) && (mes_adcFrenoSafe < 800U)) {
        /* Transition: '<S1>:1061' */
        rtDW.is_c2_Ajustos = IN_POS_FONDO_MENU;

        /* Entry Internal 'POS_FONDO_MENU': '<S1>:970' */
        /* Transition: '<S1>:981' */
        rtDW.is_POS_FONDO_MENU = IN_MENSAJE_4_INIT_d;

        /* Entry 'MENSAJE_4_INIT': '<S1>:685' */
        estat = 3U;
        rtDW.finish = false;
        rtDW.ajustant = false;
        mensajePantalla = 3U;
        mensajePantalla_IsUpdated = true;
      } else if ((mes_adcFrenoSafe >= 1000U) && (mes_adcFrenoSafe < 1200U)) {
        /* Transition: '<S1>:1063' */
        rtDW.is_c2_Ajustos = IN_MAPA1_MENU;

        /* Entry Internal 'MAPA1_MENU': '<S1>:978' */
        /* Transition: '<S1>:980' */
        rtDW.is_MAPA1_MENU = IN_MENSAJE_4_INIT;

        /* Entry 'MENSAJE_4_INIT': '<S1>:688' */
        estat = 4U;
        rtDW.finish = false;
        rtDW.ajustant = false;
        mensajePantalla = 4U;
        mensajePantalla_IsUpdated = true;
      } else if ((mes_adcFrenoSafe >= 1200U) && (mes_adcFrenoSafe < 1400U)) {
        /* Transition: '<S1>:1066' */
        rtDW.is_c2_Ajustos = IN_MAPA2_MENU;

        /* Entry Internal 'MAPA2_MENU': '<S1>:1144' */
        /* Transition: '<S1>:1145' */
        rtDW.is_MAPA2_MENU = IN_MENSAJE_5_INIT;

        /* Entry 'MENSAJE_5_INIT': '<S1>:1148' */
        estat = 5U;
        rtDW.finish = false;
        rtDW.ajustant = false;
        mensajePantalla = 5U;
        mensajePantalla_IsUpdated = true;
      } else {
        /* Transition: '<S1>:1072' */
        rtDW.is_c2_Ajustos = IN_SALIR;

        /* Entry Internal 'SALIR': '<S1>:1401' */
        /* Transition: '<S1>:1402' */
        rtDW.retornoInit = false;
        rtDW.is_SALIR = IN_MENSAJE_18_INIT;

        /* Entry 'MENSAJE_18_INIT': '<S1>:1405' */
        estat = 18U;
        rtDW.finish = false;
        mensajePantalla = 18U;
        mensajePantalla_IsUpdated = true;
      }
      break;

     case IN_SALIR:
      /* During 'SALIR': '<S1>:1401' */
      if (rtDW.retornoInit) {
        /* Transition: '<S1>:1049' */
        /* Transition: '<S1>:1052' */
        menuAjustos = false;

        /* Transition: '<S1>:1051' */
        /* Transition: '<S1>:1047' */
        /* Exit Internal 'SALIR': '<S1>:1401' */
        rtDW.is_SALIR = IN_NO_ACTIVE_CHILD;

        /* Exit Internal 'SALIR': '<S1>:1406' */
        rtDW.is_SALIR_i = IN_NO_ACTIVE_CHILD;
        rtDW.is_c2_Ajustos = IN_INIT;

        /* Entry 'INIT': '<S1>:964' */
        estat = 0U;
        rtDW.finish = false;
        rtDW.ajustant = false;
        enviarValorGatell = false;
        mensajePantalla = 0U;
        mensajePantalla_IsUpdated = true;
      } else {
        switch (rtDW.is_SALIR) {
         case IN_DEBOUNCE_8:
          /* During 'DEBOUNCE_8': '<S1>:1415' */
          if (rtDW.debounceBoto >= DEBOUNCE_BOTO) {
            /* Transition: '<S1>:1404' */
            rtDW.is_SALIR = IN_SALIR_k;

            /* Entry Internal 'SALIR': '<S1>:1406' */
            /* Transition: '<S1>:1407' */
            rtDW.is_SALIR_i = IN_MENSAJE_FINISH_3_n;

            /* Entry 'MENSAJE_FINISH_3': '<S1>:1411' */
            mensajePantalla = 13U;
            mensajePantalla_IsUpdated = true;
          } else {
            qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
            if (qY < rtDW.debounceBoto) {
              qY = MAX_uint32_T;
            }

            rtDW.debounceBoto = qY;
          }
          break;

         case IN_MENSAJE_18_INIT:
          /* During 'MENSAJE_18_INIT': '<S1>:1405' */
          if (Switch1) {
            /* Transition: '<S1>:1403' */
            rtDW.is_SALIR = IN_DEBOUNCE_8;

            /* Entry 'DEBOUNCE_8': '<S1>:1415' */
            rtDW.debounceBoto = 0U;
          } else {
            mensajePantalla_IsUpdated = false;
          }
          break;

         default:
          /* During 'SALIR': '<S1>:1406' */
          switch (rtDW.is_SALIR_i) {
           case IN_DEBOUNCE_FINISH_3_g:
            /* During 'DEBOUNCE_FINISH_3': '<S1>:1412' */
            if (rtDW.debounceBoto >= 200U) {
              /* Transition: '<S1>:1409' */
              rtDW.is_SALIR_i = IN_DU;

              /* Entry 'DU': '<S1>:1413' */
              enviarValorGatell = false;
              mensajePantalla = 0U;
            } else {
              qY = rtDW.debounceBoto + /*MW:OvSatOk*/ 1U;
              if (qY < rtDW.debounceBoto) {
                qY = MAX_uint32_T;
              }

              rtDW.debounceBoto = qY;
            }
            break;

           case IN_DU:
            /* During 'DU': '<S1>:1413' */
            /* Transition: '<S1>:1410' */
            rtDW.is_SALIR_i = IN_FINISH_3_n;

            /* Entry 'FINISH_3': '<S1>:1414' */
            rtDW.retornoInit = true;
            break;

           case IN_FINISH_3_n:
            /* During 'FINISH_3': '<S1>:1414' */
            break;

           default:
            /* During 'MENSAJE_FINISH_3': '<S1>:1411' */
            /* Transition: '<S1>:1408' */
            mensajePantalla_IsUpdated = false;
            rtDW.is_SALIR_i = IN_DEBOUNCE_FINISH_3_g;

            /* Entry 'DEBOUNCE_FINISH_3': '<S1>:1412' */
            rtDW.debounceBoto = 0U;
            break;
          }
          break;
        }
      }
      break;

     default:
      VISOR_GATELL_MENU(&Switch1);
      break;
    }
  }

  /* End of Chart: '<Root>/Ajustos' */
}

/* Model initialize function */
void Ajustos_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
