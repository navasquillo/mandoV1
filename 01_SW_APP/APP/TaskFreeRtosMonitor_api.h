/* Author:   Sergio Martinez
 * Date:     09/12/2025
 */

#ifndef TASKFREERTOSMONITOR_API_H_
#define TASKFREERTOSMONITOR_API_H_

    #define TASKFREERTOSMONITOR_MAJOR_VERSION       1
    #define TASKFREERTOSMONITOR_MINOR_VERSION       0
    #define TASKFREERTOSMONITOR_PATCH_VERSION       0


    /* Include's -----------------------------------------------------------------*/
        #include "libTypes_api.h"
        #include "mcalm_api.h"


    /* Public Defines ------------------------------------------------------------*/
        #define TASKFREERTOSMONITOR_DWT_CNT()        DWT->CYCCNT

    /* Enumerates / Structures ---------------------------------------------------*/
        // Enumerates

        // Structures
        #ifdef DEBUG
            typedef struct {
                T_u32 TotalCpuLoad;
                //
                T_u32 TaskMesurarAdc;
                T_u32 TaskParams;
                T_u32 TaskPantalla;
                T_u32 TaskFlash;
                T_u32 TaskFreeRtosMonitor;
                T_u32 IdleTask;
            }S_FreeRtosMonitor_CpuLoad;

            typedef struct {
                T_u32 TaskMesurarAdc;
                T_u32 TaskParams;
                T_u32 TaskPantalla;
                T_u32 TaskFlash;
                T_u32 TaskFreeRtosMonitor;
            }S_FreeRtosMonitor_StackFreeBytes;

            typedef struct {
                T_u32 HeapMin;
                T_u32 HeapUsed;
            }S_FreeRtosMonitor_HeapFreeBytes;

            typedef struct {
                //S_FreeRtosMonitor_CpuLoad         CpuLoad;
                S_FreeRtosMonitor_StackFreeBytes  StackFree_Bytes;
                S_FreeRtosMonitor_HeapFreeBytes   HeapFree_Bytes;
            }S_FreeRtosMonitor_Data;
        #endif


    /* Public functions ----------------------------------------------------------*/

        /* Init actions */
        void TASKFREERTOSMONITOR_Init(void);
        void TASKFREERTOSMONITOR_DWT_Init(void);

        /* Periodic tasks */
        void TASKFREERTOSMONITOR_MainTask(void);

#endif /* TASKFREERTOSMONITOR_API_H_ */

