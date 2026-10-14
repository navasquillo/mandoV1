
/* ################## Include's ####################### */

    /* Include types */
    #include "libTypes_api.h"

    /* Local prototypes */
    #include "adm_api.h"

    /* DFA's */

    /* Include external API's */
    #include "mcalm_api.h"


/* ################## Define's ######################### */


/* ################## Global variables ################# */
    extern ADC_HandleTypeDef adm_ADC_MODULE;
    extern DMA_HandleTypeDef adm_DMA_MODULE;
    //
    T_u32 adm_dataDMA[E_ADM_TOTAL_AI_SIGNALS];
    T_u32 adm_dataADC_counts[E_ADM_TOTAL_AI_SIGNALS];
    T_u32 adm_dataADC_mV[E_ADM_TOTAL_AI_SIGNALS];


/* ################## Local functions / Macros ######### */
    /* Macros */

    /* Local functions */
        static inline void adm_InitVariables(void);



//#####################################################
//#####################  SW Code  #####################
//#####################################################

/* ********************************* INIT ********************************* */
void ADM_Init(void) {
    /* 1) Configure the ADC and DMA */
    HAL_ADC_MspInit( &adm_ADC_MODULE );

    /* 2) Initialize swC variables */
    adm_InitVariables();

    /* 3) First trigger to enable ADC+DMA conversions */
    ADM_TriggerNewADCconversion();
}


void ADM_DeInit(void) {
    /* 1) Stop ADC */
    HAL_ADC_Stop_DMA( &adm_ADC_MODULE );
    HAL_ADC_MspDeInit( &adm_ADC_MODULE );

    /* 2) Initialize swC variables */
    adm_InitVariables();
}


static inline void adm_InitVariables(void) {
    //
    for (T_u32 i = T_U32_MIN; i < E_ADM_TOTAL_AI_SIGNALS; i++) {
        adm_dataDMA[i]        = T_U32_MIN;
        adm_dataADC_counts[i] = T_U32_MIN;
        adm_dataADC_mV[i]     = T_U32_MIN;
    }
}



/* ********************************* READING TASKS ********************************* */

void ADM_TriggerNewADCconversion(void) {
    HAL_ADC_Start_DMA( &adm_ADC_MODULE, (uint32_t*)adm_dataDMA, E_ADM_TOTAL_AI_SIGNALS );
}

void ADM_ReadADCconversions(void) {
    //
    /* 1.1) Get ADC Count values (at uC side) */
    adm_dataADC_counts[E_ADM__AI_SENSOR_HALL_GATELL]   = adm_dataDMA[E_ADM__AI_SENSOR_HALL_GATELL];
    adm_dataADC_counts[E_ADM__AI_POT_FRENO]            = adm_dataDMA[E_ADM__AI_POT_FRENO];
    adm_dataADC_counts[E_ADM__AI_POT_POTENCIA]         = adm_dataDMA[E_ADM__AI_POT_POTENCIA];
    adm_dataADC_counts[E_ADM__AI_POT_CURVA]            = adm_dataDMA[E_ADM__AI_POT_CURVA];
    adm_dataADC_counts[E_ADM__AI_SUPPLY_12V_PROTECTED] = adm_dataDMA[E_ADM__AI_SUPPLY_12V_PROTECTED];
    adm_dataADC_counts[E_ADM__AI_UC_INTERNAL_ADC_REF]  = adm_dataDMA[E_ADM__AI_UC_INTERNAL_ADC_REF];

    /* 1.2) Do mV conversions (at uC side) */
    adm_dataADC_mV[E_ADM__AI_SUPPLY_12V_PROTECTED] = adm_raw2mV_Supply12vProtected( adm_dataADC_counts[E_ADM__AI_SUPPLY_12V_PROTECTED] );
}
