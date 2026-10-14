/*
 * TASKFREERTOSMONITOR.c
 *
 *  Created on: 09/12/2025
 *      Author: Sergio Martinez
 */


/* ################## Include's ####################### */

    /* Include types */
    #include "libTypes_api.h"
    #include "dataFormat_api.h"
    #include "string.h"

    /* Local prototypes */
    #include "TaskFreeRtosMonitor_api.h"

    /* Include external API's */
    #include "mcalm_api.h"
    #include "cmsis_os.h"
    #include "task.h"


/* ################## Define's ######################### */


/* ################## Global variables ################# */
    #ifdef DEBUG
    /* External variables */
        extern osThreadId MesurarAdcHandle;
        extern osThreadId PantallaHandle;
        extern osThreadId ParamsHandle;
        extern osThreadId FlashHandle;
        extern osThreadId FreeRtosMonitorHandle;

    /* Internal variables */
        S_FreeRtosMonitor_Data  FreeRtosMonitor_Data;
        #if 0
            char                    runtimeStats[200u];
        #endif
    #endif


/* ################## Local functions / Macros ######### */
    #ifdef DEBUG
        static inline void Init_CpuLoad(void);
        static inline void Init_FreeStack(void);
        static inline void Init_FreeHeap(void);
        //
        static inline void Get_CpuLoad(void);
        static inline void Get_FreeStack(void);
        static inline void Get_FreeHeap(void);
    #endif


//#####################################################
//#####################  SW Code  #####################
//#####################################################
void TASKFREERTOSMONITOR_Init(void) {
    //
    #ifdef DEBUG
        // 1) Initialize swC variables
        //Init_CpuLoad();
        Init_FreeStack();
        Init_FreeHeap();
    #endif
}


void TASKFREERTOSMONITOR_MainTask(void) {

    configASSERT( xPortIsInsideInterrupt() == pdFALSE );    // nunca debe ejecutarse en ISR
    TickType_t       xLastWakeTime = xTaskGetTickCount();   // inicializar antes de vTaskDelayUntil
    const TickType_t xFrequency    = pdMS_TO_TICKS(1000u);

    /* Forçar al OS per a que la tasca del ADC s'execute primer */
    vTaskDelay( pdMS_TO_TICKS(50u) );  // Ordre execucions inicial per a un bon arranc del Display:   Task_MesurarAdc -> TaskParams -> TaskPantalla-> TaskFlash -> TaskFreeRtosMonitor

    /* Infinite loop */
    for(;;)
    {
        #ifdef DEBUG
            /*IOM_SetOutput__DO_SW_TEST_01( TRUE );*/  // Only for SW Testing

            //Get_CpuLoad();
            Get_FreeStack();
            Get_FreeHeap();

            /*IOM_SetOutput__DO_SW_TEST_01( FALSE );*/  // Only for SW Testing
        #endif
        vTaskDelayUntil( &xLastWakeTime, xFrequency );
    }
}


/* ################## Internal functions ######### */
#ifdef DEBUG
    static inline void Init_CpuLoad(void) {
        #if 0
            memset( runtimeStats, NULL_CHARACTER, sizeof(runtimeStats) );

            FreeRtosMonitor_Data.CpuLoad.TotalCpuLoad                = T_U32_MIN;
            //
            FreeRtosMonitor_Data.CpuLoad.TaskMesurarAdc              = T_U32_MIN;
            FreeRtosMonitor_Data.CpuLoad.TaskParams                  = T_U32_MIN;
            FreeRtosMonitor_Data.CpuLoad.TaskPantalla                = T_U32_MIN;
            FreeRtosMonitor_Data.CpuLoad.TaskFlash                   = T_U32_MIN;
            FreeRtosMonitor_Data.CpuLoad.TaskFreeRtosMonitor         = T_U32_MIN;
            FreeRtosMonitor_Data.CpuLoad.IdleTask                    = T_U32_MIN;
        #endif
    }


    static inline void Init_FreeStack(void) {
        FreeRtosMonitor_Data.StackFree_Bytes.TaskMesurarAdc      = T_U32_MIN;
        FreeRtosMonitor_Data.StackFree_Bytes.TaskParams          = T_U32_MIN;
        FreeRtosMonitor_Data.StackFree_Bytes.TaskPantalla        = T_U32_MIN;
        FreeRtosMonitor_Data.StackFree_Bytes.TaskFlash           = T_U32_MIN;
        FreeRtosMonitor_Data.StackFree_Bytes.TaskFreeRtosMonitor = T_U32_MIN;
    }


    static inline void Init_FreeHeap(void) {
        FreeRtosMonitor_Data.HeapFree_Bytes.HeapMin              = T_U32_MIN;
        FreeRtosMonitor_Data.HeapFree_Bytes.HeapUsed             = T_U32_MIN;
    }


    static inline void Get_CpuLoad(void) {
        #if 0
            vTaskGetRunTimeStats( runtimeStats );
            //
            FreeRtosMonitor_Data.CpuLoad.TotalCpuLoad        = T_U32_MIN;
            //
            FreeRtosMonitor_Data.CpuLoad.TaskMesurarAdc      = T_U32_MIN;
            FreeRtosMonitor_Data.CpuLoad.TaskParams          = T_U32_MIN;
            FreeRtosMonitor_Data.CpuLoad.TaskPantalla        = T_U32_MIN;
            FreeRtosMonitor_Data.CpuLoad.TaskFlash           = T_U32_MIN;
            FreeRtosMonitor_Data.CpuLoad.TaskFreeRtosMonitor = T_U32_MIN;
            //
            //FreeRtosMonitor_Data.CpuLoad.IdleTask          = ulTaskGetIdleRunTimeCounter();
        #endif
    }


    static inline void Get_FreeStack(void) {
        /*
         *   ≥ 100 bytes  → Stack OK
         *   50–100 bytes → Be careful
         *   < 50 bytes   → Possible Reset soon! Increase Stack
         */
        FreeRtosMonitor_Data.StackFree_Bytes.TaskMesurarAdc      = 4u * uxTaskGetStackHighWaterMark( MesurarAdcHandle );
        FreeRtosMonitor_Data.StackFree_Bytes.TaskParams          = 4u * uxTaskGetStackHighWaterMark( ParamsHandle );
        FreeRtosMonitor_Data.StackFree_Bytes.TaskPantalla        = 4u * uxTaskGetStackHighWaterMark( PantallaHandle );
        FreeRtosMonitor_Data.StackFree_Bytes.TaskFlash           = 4u * uxTaskGetStackHighWaterMark( FlashHandle );
        FreeRtosMonitor_Data.StackFree_Bytes.TaskFreeRtosMonitor = 4u * uxTaskGetStackHighWaterMark( FreeRtosMonitorHandle );
    }


    static inline void Get_FreeHeap(void) {
        FreeRtosMonitor_Data.HeapFree_Bytes.HeapMin  = 4u * xPortGetMinimumEverFreeHeapSize();
        FreeRtosMonitor_Data.HeapFree_Bytes.HeapUsed = 4u * xPortGetFreeHeapSize();
    }
#endif



/* ################## FreeRtos_v1:  configGENERATE_RUN_TIME_STATS ######### */
void TASKFREERTOSMONITOR_DWT_Init(void) {
    #ifdef DEBUG
        // Use DWT Cycle Counter (simpler and precise)
        CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
        DWT->CYCCNT       = 0u;
        DWT->CTRL        |= DWT_CTRL_CYCCNTENA_Msk;
    #endif
}


void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    // USER NOTE:  Read with Debugger the variable pcTaskName to know which Task has done a Stack Overflow
    (void)xTask;
    (void)pcTaskName;
    __disable_irq();
    //
    #if 0  // For Debug
        while (1);
    #else  // For Production
        MCALM_ResetSW();
    #endif
}
