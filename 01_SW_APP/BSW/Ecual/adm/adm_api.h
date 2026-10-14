/* Author:   Sergio Martinez Porras
 * Date:     29/12/2023
 */

#ifndef ADM_API_H_
#define ADM_API_H_

    #define ADM_MAJOR_VERSION       1
    #define ADM_MINOR_VERSION       1
    #define ADM_PATCH_VERSION       2


    /* Include's -----------------------------------------------------------------*/
        #include "libTypes_api.h"
        #include "adm_cfg.h"

    /* Public Defines ------------------------------------------------------------*/


    /* Enumerates / Structures ---------------------------------------------------*/
        /* Enumerates */
        typedef enum {
            // IMPORTANT: Follow same AI Signals order than in the MCAL ADC Conversion Sequence, to allow correct reading from ADC+DMA
            E_ADM__AI_SENSOR_HALL_GATELL,      /* First ADC to read */
            E_ADM__AI_POT_FRENO,
            E_ADM__AI_POT_POTENCIA,
            E_ADM__AI_POT_CURVA,
            E_ADM__AI_SUPPLY_12V_PROTECTED,
            E_ADM__AI_UC_INTERNAL_ADC_REF,  /* Last ADC to read */
            //
            E_ADM_TOTAL_AI_SIGNALS
        } E_ADM_AnalogInputs;


        /* Structures */


    /* Public functions ----------------------------------------------------------*/

        /* Init actions */
        void ADM_Init(void);
        void ADM_DeInit(void);

        /* Conversion functions */
        void ADM_TriggerNewADCconversion(void);
        void ADM_ReadADCconversions(void);

#endif /* ADM_API_H_ */
