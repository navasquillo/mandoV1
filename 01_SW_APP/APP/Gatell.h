/*
 * File: Gatell.h
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

#ifndef RTW_HEADER_Gatell_h_
#define RTW_HEADER_Gatell_h_
#include "rtwtypes.h"
#include <math.h>
#ifndef Gatell_COMMON_INCLUDES_
# define Gatell_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Gatell_COMMON_INCLUDES_ */

/* Includes for objects with custom storage classes. */
#include "valors.h"
#include "m2b.h"

/* Macros for accessing real-time model data structure */
#ifndef DEFINED_TYPEDEF_FOR_TipoMando_
#define DEFINED_TYPEDEF_FOR_TipoMando_

typedef uint8_T TipoMando;

#define TipoMando_DS                   ((TipoMando)0)            /* Default value */
#define TipoMando_Difalco              ((TipoMando)1)
#endif

/* Block signals and states (auto storage) for system '<Root>' */
typedef struct {
    uint32_T Switch4;                  /* '<Root>/Switch4' */
    uint32_T mapaFreno_DSTATE;         /* '<Root>/mapaFreno' */
    uint32_T potenciaDin_DSTATE;       /* '<Root>/potenciaDin' */
    uint32_T debounceBoto;             /* '<Root>/Gatell' */
    uint32_T minGatellFiltratFinal;    /* '<Root>/Gatell' */
    uint32_T gatellFiltratFinalAnterior;/* '<Root>/Gatell' */
    uint32_T blinkLedPC13;             /* '<Root>/Gatell' */
    uint32_T tempsRectaLlarga;         /* '<Root>/Gatell' */
    uint32_T tempsGasFondo;            /* '<Root>/Gatell' */
    uint32_T tempsVoltaLocal;          /* '<Root>/Gatell' */
    uint8_T icLoad;                    /* '<Root>/mapaFreno' */
    uint8_T icLoad_n;                  /* '<Root>/potenciaDin' */
    uint8_T is_active_c2_Gatell;       /* '<Root>/Gatell' */
    uint8_T is_MAPES_FRENO;            /* '<Root>/Gatell' */
    uint8_T is_MAPA_FRENO_2;           /* '<Root>/Gatell' */
    uint8_T is_MAPA_FRENO_4;           /* '<Root>/Gatell' */
    uint8_T is_BOTON_FRENO;            /* '<Root>/Gatell' */
    uint8_T is_POTENCIA_DINAMICA;      /* '<Root>/Gatell' */
    uint8_T is_BOTON_CHANGE;           /* '<Root>/Gatell' */
    uint8_T is_GATELL;                 /* '<Root>/Gatell' */
    boolean_T fondo;                   /* '<Root>/Gatell' */
} DW;

/* Imported (extern) block signals */
extern uint32_T mes_adcSupply12v_mV;   /* '<Root>/mes_adcSupply12v_mV' */
extern uint32_T mes_adcFreno;          /* '<Root>/mes_adcFreno' */
extern uint32_T mes_gatellFiltratFinal;/* '<Root>/mes_gatellFiltratFinal' */
extern uint32_T mes_valorsCalculatsMapa1[1500];/* '<Root>/mes_valorsCalculatsMapa1' */
extern uint32_T mes_valorsCalculatsMapa2[1500];/* '<Root>/mes_valorsCalculatsMapa2' */
extern uint32_T indexStart;            /* '<Root>/indexStart' */
extern uint32_T flashRead_GatellMinLow;/* '<Root>/flashRead_GatellMinLow' */
extern uint32_T flashRead_GatellMinHigh;/* '<Root>/flashRead_GatellMinHigh' */
extern uint32_T flashRead_GatellMaxLow;/* '<Root>/flashRead_GatellMaxLow' */
extern uint32_T flashRead_GatellMaxHigh;/* '<Root>/flashRead_GatellMaxHigh' */
extern uint32_T flashRead_GatellFreMapa2;/* '<Root>/flashRead_GatellFreMapa2' */
extern boolean_T mandoArc;             /* '<Root>/mandoArc' */
extern uint32_T flashRead_mapaFreno;   /* '<Root>/flashRead_mapaFreno' */
extern uint32_T flashRead_potenciaDin; /* '<Root>/flashRead_potenciaDin' */

/* Block signals and states (auto storage) */
extern DW DW_l;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  Code generation will declare the memory for
 * these signals and export their symbols.
 *
 */
extern uint32_T mes_gatellFiltratFinalSim;/* '<Root>/mes_gatellFiltratFinalSim' */
extern uint32_T pwmRoig;               /* '<Root>/Gatell' */
extern uint32_T pwmVerd;               /* '<Root>/Gatell' */
extern uint32_T pwmGas;                /* '<Root>/Gatell' */
extern uint32_T pwmFreno;              /* '<Root>/Gatell' */
extern uint32_T pwmBlau;               /* '<Root>/Gatell' */
extern uint32_T diffGatell;            /* '<Root>/Gatell' */
extern uint32_T tempsVolta;            /* '<Root>/Gatell' */
extern uint32_T flashWrite_mapaFreno;  /* '<Root>/Gatell' */
extern uint32_T flashWrite_potenciaDin;/* '<Root>/Gatell' */
extern uint32_T pwmArcFreno;           /* '<Root>/Gatell' */
extern boolean_T flashWrite_IsUpdatedMapaFreno;/* '<Root>/Gatell' */
extern boolean_T flashWrite_IsUpdatedPotenciaDin;/* '<Root>/Gatell' */

/* Model entry point functions */
extern void Gatell_initialize(void);
extern void Gatell_step(void);

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
 * '<Root>' : 'Gatell'
 * '<S1>'   : 'Gatell/Gatell'
 */
#endif                                 /* RTW_HEADER_Gatell_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
