/* Author:   Albert Navasquillo, Sergio Martinez
 * Date:     17/01/2024
 */

#ifndef TASKFLASH_API_H_
#define TASKFLASH_API_H_

    #define TASKFLASH_MAJOR_VERSION       2
    #define TASKFLASH_MINOR_VERSION       2
    #define TASKFLASH_PATCH_VERSION       4


    /* Include's -----------------------------------------------------------------*/


    /* Public Defines ------------------------------------------------------------*/


    /* Enumerates / Structures ---------------------------------------------------*/
        /* Enumerates */
        typedef enum {
            E_FLASHPARAM__MAPA_FRENO,
            E_FLASHPARAM__POTENCIA_DIN,
            E_FLASHPARAM__POS_FRENO,
            E_FLASHPARAM__POS_FONDO,
            E_FLASHPARAM__PUNTO_INICIAL_1,
            E_FLASHPARAM__PUNTO_FINAL_1,
            E_FLASHPARAM__PUNTO_INICIAL_2,
            E_FLASHPARAM__PUNTO_FINAL_2,
            E_FLASHPARAM__DELTA_GATELL,     // No utilitzada a partir de SW v1.3.4
            E_FLASHPARAM__EXTRA_PWM,        // No utilitzada a partir de SW v1.3.4
            E_FLASHPARAM__POS_FRE_MAPA_2,
            //
            E_FLASHPARAM_TOTAL_PARAMETERS
        }E_FlashParameterID;

    /* Public functions ----------------------------------------------------------*/

        /* Init actions */
        void TASKFLASH_Init(void);

        /* Periodic tasks */
        void TASKFLASH_MainTask(void);

#endif /* TASKPARAMS_API_H_ */

