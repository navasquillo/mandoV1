/*
 * TaskFlash.c
 *
 *  Created on: 17 ene. 2024
 *      Author: Albert, Sergio
 */


/* ################## Include's ####################### */

    /* Include types */
    #include "libTypes_api.h"
    #include "dataFormat_api.h"
    #include "rtwtypes.h"
    #include "valors.h"

    /* Local prototypes */
    #include "TaskFlash_api.h"

    /* DFA's */

    /* Include external API's */
    #include "main.h"
    #include "cmsis_os.h"
    #include "queue.h"
    #include "semphr.h"
    //
    #include "mcalm_api.h"
    #include "FLASH_SECTOR_F4.h"


/* ################## Define's ######################### */
    #define FLASHADDR_MAPA_FRENO                  (0x08020000u)
    #define FLASHADDR_POTENCIA_DIN                (0x08020004u)
    #define FLASHADDR_POS_FRENO                   (0x08020008u)
    #define FLASHADDR_POS_FONDO                   (0x0802000Cu)
    #define FLASHADDR_PUNTO_INICIAL_1             (0x08020010u)
    #define FLASHADDR_PUNTO_FINAL_1               (0x08020014u)
    #define FLASHADDR_PUNTO_INICIAL_2             (0x08020018u)
    #define FLASHADDR_PUNTO_FINAL_2               (0x0802001Cu)
    #define FLASHADDR_DELTA_GATELL                (0x08020020u)  // No utilitzada a partir de SW v1.3.4
    #define FLASHADDR_EXTRA_PWM                   (0x08020024u)  // No utilitzada a partir de SW v1.3.4
    #define FLASHADDR_POS_FRE_MAPA_2              (0x08020028u)
    //
    #define FLASHADDR_CALIBRATION_START_ADDRESS   (FLASHADDR_MAPA_FRENO)


/* ################## Global variables ################# */
    /* External variables */
    extern osMessageQId MapaFrenoHandle;
    extern osMessageQId PotenciaDinHandle;
    extern osMessageQId PosFrenoFlashHandle;
    extern osMessageQId PosFondoFlashHandle;
    extern osMessageQId PosFrenoMapa2FlashHandle;
    extern osMessageQId OffsetFlashHandle;
    extern osMessageQId PotenciaFlashHandle;
    extern osMessageQId DiffGatellFlashHandle;
    extern osMessageQId ExtraPWMFlashHandle;
    //
    extern osMessageQId ValorInicial1FlashHandle;
    extern osMessageQId ValorFinal1FlashHandle;
    extern osMessageQId ValorInicial2FlashHandle;
    extern osMessageQId ValorFinal2FlashHandle;

    /* swC variables */
    uint32_t flashParameter[E_FLASHPARAM_TOTAL_PARAMETERS];
    uint8_t  flashWriteTrigger;
    //
    uint32_T flashRead_mapaFreno;
    uint32_T flashRead_potenciaDin;
    uint32_T flashRead_GatellMinLow;
    uint32_T flashRead_GatellMaxHigh;
    uint32_T flashRead_GatellFreMapa2;
    uint32_T flashRead_ValorInicial1;
    uint32_T flashRead_ValorFinal1;
    uint32_T flashRead_ValorInicial2;
    uint32_T flashRead_ValorFinal2;
    uint32_T flashRead_DeltaGatell;
    uint32_T flashRead_ExtraPWM;
    //
    uint32_T flashRead_GatellMinHigh;
    uint32_T flashRead_GatellMaxLow;
    //
    uint32_T indexStart;
    uint32_t puntsTotalLoockupTable;
    //
    float factorOffsetMapa1;
    float factorPotenciaMapa1;
    float factorOffsetMapa2;
    float factorPotenciaMapa2;


/* ################## Local functions / Macros ######### */
    static inline void flash_LlegirParametres(void);
    static inline void flash_ComprovarValorsGatell(void);
    static inline void flash_ComprovarFactorsMapa(void);
    static inline void flash_SetejarFactorsMapa(void);



//#####################################################
//#####################  SW Code  #####################
//#####################################################
void TASKFLASH_Init(void) {
    flashWriteTrigger = FALSE;

    // 1) Llegir Parameteres de FLASH
    flash_LlegirParametres();

    // 2) Relacionat amb LookUpTable
    flashRead_GatellMinHigh = flashParameter[E_FLASHPARAM__POS_FRENO] + 10u;
    flashRead_GatellMaxLow  = flashParameter[E_FLASHPARAM__POS_FONDO] - 10u;
    //
    puntsTotalLoockupTable  = flashParameter[E_FLASHPARAM__POS_FONDO] - flashParameter[E_FLASHPARAM__POS_FRENO];
    //
    /* Degut a la histèresi, al inici de recorregut de gatell, la corba se menja els 10 primers punts, per la qual cosa */
    /* tot i que el ajust de SALIDA estiga a 0, el cotxe ix molt fort */
    /* La resta de -15 es per asegurar que almenys (degut a la histèresi de 10 valors) 5 valors de la corba siguen la velocitat mínima */
    indexStart = DIFF - puntsTotalLoockupTable - 15u;

    // 3) Relacionat amb Gatell i Factors Mapa
    flash_ComprovarValorsGatell();
    //
    flash_ComprovarFactorsMapa();
    flash_SetejarFactorsMapa();
}

void TASKFLASH_MainTask(void) {

    configASSERT( xPortIsInsideInterrupt() == pdFALSE );   // nunca debe ejecutarse en ISR
    TickType_t       xLastWakeTime = xTaskGetTickCount();  // inicializar antes de vTaskDelayUntil
    const TickType_t xFrequency    = pdMS_TO_TICKS(30u);

    uint8_t firstRun = 1u;

    /* Forçar al OS per a que la tasca del ADC s'execute primer */
    vTaskDelay( pdMS_TO_TICKS(40u) );  // Ordre execucions inicial per a un bon arranc del Display:   Task_MesurarAdc -> TaskParams -> TaskPantalla-> TaskFlash -> TaskFreeRtosMonitor

    /* Infinite loop */
    for(;;)
    {
        /*IOM_SetOutput__DO_SW_TEST_02( TRUE );*/  // Only for SW Testing

        /* Mapa Freno */
        if (xQueueReceive( MapaFrenoHandle, &flashParameter[E_FLASHPARAM__MAPA_FRENO], (TickType_t) 0u ) == pdTRUE && firstRun == 0u) {
            flashWriteTrigger = TRUE;
        }

        /* Potència dinàmica */
        if (xQueueReceive( PotenciaDinHandle, &flashParameter[E_FLASHPARAM__POTENCIA_DIN], (TickType_t) 0u ) == pdTRUE && firstRun == 0u) {
            flashWriteTrigger = TRUE;
        }

        /* GatellMinLow */
        if (xQueueReceive( PosFrenoFlashHandle, &flashParameter[E_FLASHPARAM__POS_FRENO], (TickType_t) 0u ) == pdTRUE && firstRun == 0u) {
            /* Guardar en RAM el valor el nou valor de la posició de freno GatellMinLow */
            /* El valor flashRead_GatellMinLow será utilitzat per el model "Ajustos" per asegurar-se de que siga SEMPRE MENOR que flashRead_GatellMaxHigh */
            flash_ComprovarValorsGatell();
            //
            flashParameter[E_FLASHPARAM__POS_FRENO] += 10u;
            flashRead_GatellMinLow                   = flashParameter[E_FLASHPARAM__POS_FRENO];
            flashRead_GatellMinHigh                  = flashParameter[E_FLASHPARAM__POS_FRENO] + 10u;

            /* Recalcular numero de punts de la lockup table per acurtar o allargar el vector mes_valorsCalculats[]*/
            puntsTotalLoockupTable  = flashParameter[E_FLASHPARAM__POS_FONDO] - flashParameter[E_FLASHPARAM__POS_FRENO];
            indexStart              = DIFF - puntsTotalLoockupTable - 15u;
            //
            flashWriteTrigger = TRUE;
        }

        /* GatellMaxHigh */
        if (xQueueReceive( PosFondoFlashHandle, &flashParameter[E_FLASHPARAM__POS_FONDO], (TickType_t) 0u ) == pdTRUE && firstRun == 0u) {
            /* Guardar en RAM el valor el nou valor de la posició de fondo _GatellMaxHigh */
            /* El valor flashRead_GatellMaxHigh será utilitzat per el model "Ajustos" per asegurar-se de que siga SEMPRE MAJOR que flashRead_GatellMinLow */
            flash_ComprovarValorsGatell();
            //
            flashParameter[E_FLASHPARAM__POS_FONDO] -= 10u;
            flashRead_GatellMaxHigh                  = flashParameter[E_FLASHPARAM__POS_FONDO];
            flashRead_GatellMaxLow                   = flashParameter[E_FLASHPARAM__POS_FONDO] - 10u;

            /* Recalcular numero de punts de la lockup table per acurtar o allargar el vector mes_valorsCalculats[]*/
            puntsTotalLoockupTable  = flashParameter[E_FLASHPARAM__POS_FONDO] - flashParameter[E_FLASHPARAM__POS_FRENO];
            indexStart              = DIFF - puntsTotalLoockupTable - 15u;

            /* Comprovar Valors Gatell */
            //
            flashWriteTrigger = TRUE;
        }

        /* Guardar en FLASH ValorInicial1 (offset del mapa 1)*/
        if (xQueueReceive( ValorInicial1FlashHandle, &flashParameter[E_FLASHPARAM__PUNTO_INICIAL_1], (TickType_t) 0u ) == pdTRUE && firstRun == 0u) {
            flash_ComprovarFactorsMapa();
            flash_SetejarFactorsMapa();
            //
            flashWriteTrigger = TRUE;
        }

        /* Guardar en FLASH ValorFinal1 (curva del mapa 1)*/
        if (xQueueReceive( ValorFinal1FlashHandle, &flashParameter[E_FLASHPARAM__PUNTO_FINAL_1], (TickType_t) 0u ) == pdTRUE && firstRun == 0u) {
            /* Comprovar i setejar els valors dels mapes */
            flash_ComprovarFactorsMapa();
            flash_SetejarFactorsMapa();
            //
            flashWriteTrigger = TRUE;
        }

        /* Guardar en FLASH ValorInicial2 (offset del mapa 2)*/
        if (xQueueReceive( ValorInicial2FlashHandle, &flashParameter[E_FLASHPARAM__PUNTO_INICIAL_2], (TickType_t) 0u ) == pdTRUE && firstRun == 0u) {
            /* Comprovar i setejar els valors dels mapes */
            flash_ComprovarFactorsMapa();
            flash_SetejarFactorsMapa();
            //
            flashWriteTrigger = TRUE;
        }

        /* Guardar en FLASH ValorFinal2 (curva del mapa 2)*/
        if (xQueueReceive( ValorFinal2FlashHandle, &flashParameter[E_FLASHPARAM__PUNTO_FINAL_2], (TickType_t) 0u ) == pdTRUE && firstRun == 0u) {
            /* Comprovar i setejar els valors dels mapes */
            flash_ComprovarFactorsMapa();
            flash_SetejarFactorsMapa();
            //
            flashWriteTrigger = TRUE;
        }

        /* GatellFreMapa2 */
        if (xQueueReceive( PosFrenoMapa2FlashHandle, &flashParameter[E_FLASHPARAM__POS_FRE_MAPA_2], (TickType_t) 0u ) == pdTRUE && firstRun == 0u) {
            flash_ComprovarValorsGatell();
            //
            flashWriteTrigger = TRUE;
        }


        // Actualitzar Flash si cal
        if( flashWriteTrigger ) {
            if( MCALM_IsFlashBusy() == FALSE ) {
                Flash_Write_Data( FLASHADDR_MAPA_FRENO, flashParameter, sizeof(flashParameter) );
                flash_LlegirParametres();
                //
                flashWriteTrigger = FALSE;
            }
        }
        //
        firstRun = 0u;

        /*IOM_SetOutput__DO_SW_TEST_02( FALSE );*/  // Only for SW Testing
        vTaskDelayUntil( &xLastWakeTime, xFrequency );
    }
}


static inline void flash_LlegirParametres(void) {
    //
    // 1) Llegir desde FLASH
    flashRead_mapaFreno      = MCALM_MEMORY_READ32( FLASHADDR_MAPA_FRENO );
    flashRead_potenciaDin    = MCALM_MEMORY_READ32( FLASHADDR_POTENCIA_DIN );
    flashRead_GatellMinLow   = MCALM_MEMORY_READ32( FLASHADDR_POS_FRENO );
    flashRead_GatellMaxHigh  = MCALM_MEMORY_READ32( FLASHADDR_POS_FONDO );
    flashRead_ValorInicial1  = MCALM_MEMORY_READ32( FLASHADDR_PUNTO_INICIAL_1 );
    flashRead_ValorFinal1    = MCALM_MEMORY_READ32( FLASHADDR_PUNTO_FINAL_1 );
    flashRead_ValorInicial2  = MCALM_MEMORY_READ32( FLASHADDR_PUNTO_INICIAL_2 );
    flashRead_ValorFinal2    = MCALM_MEMORY_READ32( FLASHADDR_PUNTO_FINAL_2 );
    flashRead_DeltaGatell    = MCALM_MEMORY_READ32( FLASHADDR_DELTA_GATELL );
    flashRead_ExtraPWM       = MCALM_MEMORY_READ32( FLASHADDR_EXTRA_PWM );
    flashRead_GatellFreMapa2 = MCALM_MEMORY_READ32( FLASHADDR_POS_FRE_MAPA_2 );

    // 2) Copiar al Buffer intern
    flashParameter[E_FLASHPARAM__MAPA_FRENO]      = flashRead_mapaFreno;
    flashParameter[E_FLASHPARAM__POTENCIA_DIN]    = flashRead_potenciaDin;
    flashParameter[E_FLASHPARAM__POS_FRENO]       = flashRead_GatellMinLow;
    flashParameter[E_FLASHPARAM__POS_FONDO]       = flashRead_GatellMaxHigh;
    flashParameter[E_FLASHPARAM__PUNTO_INICIAL_1] = flashRead_ValorInicial1;
    flashParameter[E_FLASHPARAM__PUNTO_FINAL_1]   = flashRead_ValorFinal1;
    flashParameter[E_FLASHPARAM__PUNTO_INICIAL_2] = flashRead_ValorInicial2;
    flashParameter[E_FLASHPARAM__PUNTO_FINAL_2]   = flashRead_ValorFinal2;
    flashParameter[E_FLASHPARAM__DELTA_GATELL]    = flashRead_DeltaGatell;
    flashParameter[E_FLASHPARAM__EXTRA_PWM]       = flashRead_ExtraPWM;
    flashParameter[E_FLASHPARAM__POS_FRE_MAPA_2]  = flashRead_GatellFreMapa2;
}

static inline void flash_ComprovarValorsGatell() {
    /* Posar valors per defecte si la FLASH es corrompeix */
    if (flashParameter[E_FLASHPARAM__POS_FRENO] > 4000u) {
        flashParameter[E_FLASHPARAM__POS_FRENO] = 2300u;
        flashRead_GatellMinLow                  = flashParameter[E_FLASHPARAM__POS_FRENO];
    }

    if (flashParameter[E_FLASHPARAM__POS_FONDO] > 4000u) {
        flashParameter[E_FLASHPARAM__POS_FONDO] = 3000u;
        flashRead_GatellMaxHigh                 = flashParameter[E_FLASHPARAM__POS_FONDO];
    }

    if (flashParameter[E_FLASHPARAM__POS_FRENO] >= flashParameter[E_FLASHPARAM__POS_FONDO]) {
        flashParameter[E_FLASHPARAM__POS_FRENO] = 2300u;
        flashRead_GatellMinLow                  = flashParameter[E_FLASHPARAM__POS_FRENO];
        //
        flashParameter[E_FLASHPARAM__POS_FONDO] = 3000u;
        flashRead_GatellMaxHigh                 = flashParameter[E_FLASHPARAM__POS_FONDO];
    }

    if (flashParameter[E_FLASHPARAM__POS_FRE_MAPA_2] >= 4000u || flashParameter[E_FLASHPARAM__POS_FRE_MAPA_2] <= 1900u) {
        flashParameter[E_FLASHPARAM__POS_FRE_MAPA_2] = 2500u;
        flashRead_GatellFreMapa2                     = flashParameter[E_FLASHPARAM__POS_FRE_MAPA_2];
    }
}

static inline void flash_ComprovarFactorsMapa(void) {
    /* Valor Inicial 1 */
    if (flashParameter[E_FLASHPARAM__PUNTO_INICIAL_1] >= 7u || flashParameter[E_FLASHPARAM__PUNTO_INICIAL_1] <= 0u) {
        flashParameter[E_FLASHPARAM__PUNTO_INICIAL_1] = 1u;
        flash_SetejarFactorsMapa();
    }

    if (flashParameter[E_FLASHPARAM__PUNTO_FINAL_1] >= 7u || flashParameter[E_FLASHPARAM__PUNTO_FINAL_1] <= 0u) {
        flashParameter[E_FLASHPARAM__PUNTO_FINAL_1] = 1u;
        flash_SetejarFactorsMapa();
    }

    if (flashParameter[E_FLASHPARAM__PUNTO_INICIAL_2] >= 7u || flashParameter[E_FLASHPARAM__PUNTO_INICIAL_2] <= 0u) {
        flashParameter[E_FLASHPARAM__PUNTO_INICIAL_2] = 2u;
        flash_SetejarFactorsMapa();
    }

    if (flashParameter[E_FLASHPARAM__PUNTO_FINAL_2] >= 7u || flashParameter[E_FLASHPARAM__PUNTO_FINAL_2] <= 0u) {
        flashParameter[E_FLASHPARAM__PUNTO_FINAL_2] = 2u;
        flash_SetejarFactorsMapa();
    }
 }

static inline void flash_SetejarFactorsMapa(void) {
    /* Valor Inicial 1 */
    switch( flashParameter[E_FLASHPARAM__PUNTO_INICIAL_1] ) {
        case 1:
            factorOffsetMapa1 = FACTOR_OFFSET_1;
            break;
        case 2:
            factorOffsetMapa1 = FACTOR_OFFSET_2;
            break;
        case 3:
            factorOffsetMapa1 = FACTOR_OFFSET_3;
            break;
        case 4:
            factorOffsetMapa1 = FACTOR_OFFSET_4;
            break;
        case 5:
            factorOffsetMapa1 = FACTOR_OFFSET_RALLY_1;
            break;
        case 6:
            factorOffsetMapa1 = FACTOR_OFFSET_RALLY_2;
            break;
        default:
            factorOffsetMapa1 = FACTOR_OFFSET_1;
            break;
    }
    /* Valor Inicial 2 */
    switch( flashParameter[E_FLASHPARAM__PUNTO_INICIAL_2] ) {
        case 1:
            factorOffsetMapa2 = FACTOR_OFFSET_1;
            break;
        case 2:
            factorOffsetMapa2 = FACTOR_OFFSET_2;
            break;
        case 3:
            factorOffsetMapa2 = FACTOR_OFFSET_3;
            break;
        case 4:
            factorOffsetMapa2 = FACTOR_OFFSET_4;
            break;
        case 5:
        	factorOffsetMapa2 = FACTOR_OFFSET_RALLY_1;
            break;
        case 6:
        	factorOffsetMapa2 = FACTOR_OFFSET_RALLY_2;
            break;
        default:
            factorOffsetMapa2 = FACTOR_OFFSET_1;
            break;
    }
    /* Valor Final 1 */
    switch ( flashParameter[E_FLASHPARAM__PUNTO_FINAL_1] ) {
        case 1:
            factorPotenciaMapa1 = FACTOR_POTENCIA_1;
            break;
        case 2:
            factorPotenciaMapa1 = FACTOR_POTENCIA_2;
            break;
        case 3:
            factorPotenciaMapa1 = FACTOR_POTENCIA_3;
            break;
        case 4:
            factorPotenciaMapa1 = FACTOR_POTENCIA_4;
            break;
        case 5:
        	factorPotenciaMapa1 = FACTOR_POTENCIA_RALLY_1;
            break;
        case 6:
        	factorPotenciaMapa1 = FACTOR_POTENCIA_RALLY_2;
            break;
        default:
            factorPotenciaMapa1 = FACTOR_POTENCIA_1;
            break;
    }

    switch ( flashParameter[E_FLASHPARAM__PUNTO_FINAL_2] ) {
        case 1:
            factorPotenciaMapa2 = FACTOR_POTENCIA_1;
            break;
        case 2:
            factorPotenciaMapa2 = FACTOR_POTENCIA_2;
            break;
        case 3:
            factorPotenciaMapa2 = FACTOR_POTENCIA_3;
            break;
        case 4:
            factorPotenciaMapa2 = FACTOR_POTENCIA_4;
            break;
        case 5:
        	factorPotenciaMapa2 = FACTOR_POTENCIA_RALLY_1;
            break;
        case 6:
        	factorPotenciaMapa2 = FACTOR_POTENCIA_RALLY_2;
            break;
        default:
            factorPotenciaMapa2 = FACTOR_POTENCIA_1;
            break;
    }
}
