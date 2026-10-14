/*
 * File: Ajustos.h
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

#ifndef RTW_HEADER_Ajustos_h_
#define RTW_HEADER_Ajustos_h_
#ifndef Ajustos_COMMON_INCLUDES_
# define Ajustos_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Ajustos_COMMON_INCLUDES_ */

/* Includes for objects with custom storage classes. */
#include "valors.h"
#include "m2b.h"

/* Macros for accessing real-time model data structure */

/* Block signals and states (auto storage) for system '<Root>' */
typedef struct {
  uint32_T debounceBoto;               /* '<Root>/Ajustos' */
  uint8_T is_active_c2_Ajustos;        /* '<Root>/Ajustos' */
  uint8_T is_c2_Ajustos;               /* '<Root>/Ajustos' */
  uint8_T is_MAPA1_MENU;               /* '<Root>/Ajustos' */
  uint8_T is_MAPA1;                    /* '<Root>/Ajustos' */
  uint8_T is_AJUST_P_SALIDA_1;         /* '<Root>/Ajustos' */
  uint8_T is_AJUST_P_FINAL_1;          /* '<Root>/Ajustos' */
  uint8_T is_MAPA2_MENU;               /* '<Root>/Ajustos' */
  uint8_T is_MAPA2;                    /* '<Root>/Ajustos' */
  uint8_T is_AJUST_P_SALIDA_2;         /* '<Root>/Ajustos' */
  uint8_T is_AJUST_P_FINAL_2;          /* '<Root>/Ajustos' */
  uint8_T is_POS_FONDO_MENU;           /* '<Root>/Ajustos' */
  uint8_T is_POS_FONDO;                /* '<Root>/Ajustos' */
  uint8_T is_POS_FRE_MAPA2_MENU;       /* '<Root>/Ajustos' */
  uint8_T is_FRE_MAPA2;                /* '<Root>/Ajustos' */
  uint8_T is_VISOR_GATELL_MENU;        /* '<Root>/Ajustos' */
  uint8_T is_VISOR_GATELL;             /* '<Root>/Ajustos' */
  uint8_T is_POS_FRENO_MENU;           /* '<Root>/Ajustos' */
  uint8_T is_POS_FRENO;                /* '<Root>/Ajustos' */
  uint8_T is_SALIR;                    /* '<Root>/Ajustos' */
  uint8_T is_SALIR_i;                  /* '<Root>/Ajustos' */
  boolean_T finish;                    /* '<Root>/Ajustos' */
  boolean_T retornoInit;               /* '<Root>/Ajustos' */
  boolean_T ajustant;                  /* '<Root>/Ajustos' */
} DW;

/* Imported (extern) block signals */
extern uint32_T mes_adcFrenoSafe;      /* '<Root>/mes_adcFrenoSafe' */
extern uint32_T mes_gatellFiltratFinal;/* '<Root>/mes_gatellFiltratFinal' */
extern uint32_T mes_adcEixida;         /* '<Root>/mes_adcEixida' */
extern uint32_T flashRead_GatellMinLow;/* '<Root>/flashRead_GatellMinLow' */
extern uint32_T flashRead_GatellMaxHigh;/* '<Root>/flashRead_GatellMaxHigh' */
extern uint32_T flashRead_GatellFreMapa2;/* '<Root>/flashRead_GatellFreMapa2' */
extern uint32_T flashRead_ValorInicial1;/* '<Root>/flashRead_ValorInicial1' */
extern uint32_T flashRead_ValorFinal1; /* '<Root>/flashRead_ValorFinal1' */
extern uint32_T flashRead_ValorInicial2;/* '<Root>/flashRead_ValorInicial2' */
extern uint32_T flashRead_ValorFinal2; /* '<Root>/flashRead_ValorFinal2' */

/* Block signals and states (auto storage) */
extern DW rtDW;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern uint32_T estat;                 /* '<Root>/Ajustos' */
extern uint32_T mensajePantalla;       /* '<Root>/Ajustos' */
extern uint32_T flashWrite_ValorInicial1;/* '<Root>/Ajustos' */
extern uint32_T flashWrite_ValorFinal1;/* '<Root>/Ajustos' */
extern uint32_T flashWrite_ValorInicial2;/* '<Root>/Ajustos' */
extern uint32_T flashWrite_ValorFinal2;/* '<Root>/Ajustos' */
extern uint32_T flashWrite_deltaGatell;/* '<Root>/Ajustos' */
extern uint32_T flashWrite_extraPWM;   /* '<Root>/Ajustos' */
extern boolean_T mensajePantalla_IsUpdated;/* '<Root>/Ajustos' */
extern boolean_T enviarValorGatell;    /* '<Root>/Ajustos' */
extern boolean_T enviarValorPuntInicial1;/* '<Root>/Ajustos' */
extern boolean_T enviarValorPuntFinal1;/* '<Root>/Ajustos' */
extern boolean_T enviarValorPuntInicial2;/* '<Root>/Ajustos' */
extern boolean_T enviarValorPuntFinal2;/* '<Root>/Ajustos' */
extern boolean_T menuAjustos;          /* '<Root>/Ajustos' */
extern boolean_T flashWrite_IsUpdatedPosFreno;/* '<Root>/Ajustos' */
extern boolean_T flashWrite_IsUpdatedPosFondo;/* '<Root>/Ajustos' */
extern boolean_T flashWrite_IsUpdatedlPosFreMapa2;/* '<Root>/Ajustos' */
extern boolean_T flashWrite_IsUpdatedValorInicial1;/* '<Root>/Ajustos' */
extern boolean_T flashWrite_IsUpdatedValorFinal1;/* '<Root>/Ajustos' */
extern boolean_T flashWrite_IsUpdatedValorInicial2;/* '<Root>/Ajustos' */
extern boolean_T flashWrite_IsUpdatedValorFinal2;/* '<Root>/Ajustos' */
extern boolean_T flashWrite_IsUpdatedDeltaGatell;/* '<Root>/Ajustos' */
extern boolean_T flashWrite_IsUpdatedExtraPWM;/* '<Root>/Ajustos' */
extern boolean_T enviarVoltajeEixida;  /* '<Root>/Ajustos' */

/* Model entry point functions */
extern void Ajustos_initialize(void);
extern void Ajustos_step(void);

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Ajustos'
 * '<S1>'   : 'Ajustos/Ajustos'
 * '<S2>'   : 'Ajustos/Subsystem'
 */
#endif                                 /* RTW_HEADER_Ajustos_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
