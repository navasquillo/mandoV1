/*
 * TaskParams.c
 *
 *  Created on: 9 dic. 2022
 *      Author: Albert
 */


/* ################## Include's ####################### */

    /* Include types */
    #include "libTypes_api.h"
    #include "dataFormat_api.h"

    /* Local prototypes */
    #include "TaskParams_api.h"

    /* DFA's */

    /* Include external API's */
    #include "main.h"
    #include "cmsis_os.h"
    #include "queue.h"
    #include "semphr.h"
    //
    #include "math.h"
    #include "Inc/adc_exp.h"
    //
    #include "iom_api.h"


/* ################## Define's ######################### */
    #define NUM_MOSTRES         (3)


/* ################## Global variables ################# */
    /* External variables */
    extern osMessageQId PotenciaAdcHandle;
    extern osMessageQId PotenciaAdcFiltratHandle;
    extern osMessageQId PotenciaParamFHandle;

    extern osMessageQId CorbaAdcHandle;
    extern osMessageQId CorbaAdcFiltratHandle;
    extern osMessageQId CorbaParamFHandle;


    /* Internal variables */
    float expLast                      = 0.0F;

    uint16_t param_potenciaAdc         = 0u;
    uint16_t param_potenciaAdcFiltrat  = 0u;
    uint16_t param_potenciaAdcFiltrat2 = 0u;
    float    param_potenciaParamF      = 0.0F;

    uint16_t param_corbaAdc            = 0u;
    uint16_t param_corbaAdcFiltrat     = 0u;
    uint16_t param_corbaAdcFiltrat2    = 0u;
    float    param_corbaParamF         = 0.0F;


/* ################## Local functions / Macros ######### */

    // Offset = (MAX_OFF/MAX_CONTE_ADC) * conteADC;
    // Offset = (0.4/4096) * conteADC
    // Offset = conteAdc / (4096/0.4)
    // Offset = conteAdc / 10240
    #define Offset(conteAdc)        ((float)((float)conteAdc / 256.0))

    // Exponent = (MAX_EXP/MAX_CONTE_ADC) * conteADC;
    // Exponent = (2.0/4096) * conteADC
    // Exponent = conteAdc / (4096/2.0)
    // Exponent = conteAdc / (2048.0)
    #define Exponent(conteAdc)      ((float)((float)conteAdc / 50.0))



//#####################################################
//#####################  SW Code  #####################
//#####################################################
void TASKPARAMS_Init(void) {
    expLast                  = 0.0F;

    param_potenciaAdc        = 0u;
    param_corbaAdc           = 0u;

    param_potenciaAdcFiltrat = 0u;
    param_corbaAdcFiltrat    = 0u;

    param_potenciaParamF     = 0.0F;
    param_corbaParamF        = 0.0F;
}

void TASKPARAMS_MainTask(void) {

    configASSERT( xPortIsInsideInterrupt() == pdFALSE );   // nunca debe ejecutarse en ISR
    TickType_t       xLastWakeTime = xTaskGetTickCount();  // inicializar antes de vTaskDelayUntil
    const TickType_t xFrequency    = pdMS_TO_TICKS(30u);

    /* Forçar al OS per a que la tasca del ADC s'execute primer */
    vTaskDelay( pdMS_TO_TICKS(10u) );  // Ordre execucions inicial per a un bon arranc del Display:   Task_MesurarAdc -> TaskParams -> TaskPantalla-> TaskFlash -> TaskFreeRtosMonitor

    /* Infinite loop */
    for(;;)
    {
        /*IOM_SetOutput__DO_SW_TEST_01( TRUE );*/  // Only for SW Testing

        if (uxQueueMessagesWaiting(PotenciaAdcHandle) >= NUM_MOSTRES)
        {
            param_potenciaAdcFiltrat = 0u;
            for (uint16_t i = 0u; i < NUM_MOSTRES; i++) {
                xQueueReceive( PotenciaAdcHandle, &param_potenciaAdc, (TickType_t) 0u);
                /* acumular les lectures del ADC. Conforme es van fent lectures de la cua, el buffer de la cua es buida */
                param_potenciaAdcFiltrat += param_potenciaAdc;
            }
            /* Traure la mitja */
            param_potenciaAdcFiltrat /= NUM_MOSTRES;
            param_potenciaAdcFiltrat2 = param_potenciaAdcFiltrat / 40u; //enviar en una nova queue este valor
            param_potenciaParamF      = Offset(param_potenciaAdcFiltrat2);
            //
            xQueueSend( PotenciaAdcFiltratHandle, &param_potenciaAdcFiltrat, (TickType_t) 0u );
            xQueueSend( PotenciaParamFHandle,     &param_potenciaParamF,     (TickType_t) 0u );
        }

        if (uxQueueMessagesWaiting(CorbaAdcHandle) >= NUM_MOSTRES)
        {
            param_corbaAdcFiltrat = 0u;
            for (uint16_t i = 0u; i < NUM_MOSTRES; i++) {
                xQueueReceive( CorbaAdcHandle, &param_corbaAdc, (TickType_t) 0u);
                /* acumular les lectures del ADC. Conforme es van fent lectures de la cua, el buffer de la cua es buida */
                param_corbaAdcFiltrat += param_corbaAdc;
            }
            /* Traure la mitja */
            param_corbaAdcFiltrat /= NUM_MOSTRES;
            /* Calcular el exponent en funcio del conte del ADC */
            param_corbaAdcFiltrat2 = param_corbaAdcFiltrat / 40u;

            /* evitar la corba 0 */
            if (param_corbaAdcFiltrat2 == 0u)
            {
                param_corbaAdcFiltrat2 = 1u;
                param_corbaAdcFiltrat  = 50u;
            }

            param_corbaParamF = Exponent(param_corbaAdcFiltrat2);
            //
            xQueueSend( CorbaAdcFiltratHandle, &param_corbaAdcFiltrat, (TickType_t) 0u );
            xQueueSend( CorbaParamFHandle,     &param_corbaParamF,     (TickType_t) 0u );
        }

        /*IOM_SetOutput__DO_SW_TEST_01( FALSE );*/  // Only for SW Testing
        vTaskDelayUntil( &xLastWakeTime, xFrequency );
    }
}
