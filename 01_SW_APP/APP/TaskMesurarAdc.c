/*
 * TaskMesurarAdc.c
 *
 *  Created on: Dec 7, 2022
 *      Author: Albert, Sergio
 */


/* ################## Include's ####################### */

    /* Include types */
    #include "libTypes_api.h"
    #include "dataFormat_api.h"
    #include "rtwtypes.h"

    /* Local prototypes */
    #include "TaskMesurarAdc_api.h"

    /* DFA's */

    /* Include external API's */
    #include "main.h"
    #include "cmsis_os.h"
    #include "queue.h"
    #include "semphr.h"
    #include "portable.h"
    //
    #include "stdlib.h"
    #include "stdio.h"
    #include "string.h"
    //
    #include "iom_api.h"
    #include "adm_api.h"
    #include "usbm_api.h"
    #include "pmm_api.h"
    //
    #include "valors.h"

/* ################## Global variables ################# */
    /* External variables */
    extern osMessageQId GatellAdcHandle;
    extern osMessageQId FrenoAdcHandle;
    extern osMessageQId PotenciaAdcHandle;
    extern osMessageQId CorbaAdcHandle;
    extern osMessageQId VoltatgeAdcHandle;
    //
    extern osMessageQId MapaFrenoHandle;
    extern osMessageQId PotenciaDinHandle;
    //
    extern osMessageQId PosFrenoFlashHandle;
    extern osMessageQId PosFondoFlashHandle;
    extern osMessageQId PosFrenoMapa2FlashHandle;
    extern osMessageQId OffsetFlashHandle;
    extern osMessageQId PotenciaFlashHandle;
    extern osMessageQId DiffGatellFlashHandle;
    extern osMessageQId ExtraPWMFlashHandle;
    extern osMessageQId ValorInicial1FlashHandle;
    extern osMessageQId ValorFinal1FlashHandle;
    extern osMessageQId ValorInicial2FlashHandle;
    extern osMessageQId ValorFinal2FlashHandle;
    //
    extern osMessageQId MensajePantallaHandle;
    extern osMessageQId MapaFrenoPantallaHandle;
    extern osMessageQId PotenciaDinPantallaHandle;
    extern osMessageQId ValorInicial1PantallaHandle;
    extern osMessageQId ValorFinal1PantallaHandle;
    extern osMessageQId ValorInicial2PantallaHandle;
    extern osMessageQId ValorFinal2PantallaHandle;
    //
    extern T_u32 adm_dataADC_counts[E_ADM_TOTAL_AI_SIGNALS];
    extern T_u32 adm_dataADC_mV[E_ADM_TOTAL_AI_SIGNALS];


    /* Internal variables */
    char mes_sDataTX[128u];
    uint32_t mes_valorsCalculatsMapa1[DIFF];
    uint32_t mes_valorsCalculatsMapa2[DIFF];

    uint32_t mes_gatellFiltrat;
    uint32_t mes_gatellFiltratLast;
    uint32_t mes_gatellFiltratFinal;
    uint32_t mes_gatellTransformat;
    uint32_t mes_indexGatell   = 0u;
    uint8_t  mes_valorPreparat = 0u;

    uint32_t mes_adcFrenoAct  = 0u;
    uint32_t mes_frenoTransformat = 0u;
    uint32_t mes_adcFrenoLast = 0u;
    uint32_t mes_adcFreno     = 0u;

    uint32_t mes_adcSupply12v_mV = 0u;

    uint32_t mes_corbaFiltrat;
    uint32_t mes_corbaTransformat;
    uint32_t mes_corbaFiltratLast;
    uint32_t mes_indexCorba = 0u;

    uint32_t mes_potenciaFiltrat;
    uint32_t mes_potenciaTransformat;
    uint32_t mes_potenciaFiltratLast;
    uint32_t mes_indexPotencia = 0u;

    /* Per a model "Gatell" */
    extern uint32_T flashRead_GatellMinHigh;

    extern uint32_t flashWrite_mapaFreno;
    extern boolean_T flashWrite_IsUpdatedMapaFreno;
    extern uint32_t flashWrite_potenciaDin;
    extern boolean_T flashWrite_IsUpdatedPotenciaDin;


    /* FALSE, caixa conexions analògic */
    /* TRUE, caixa conexions digital oXigen */
    T_bit mandoArc;

    /* Per a model "Ajustos" */
    /* Entrades exclusives mode Ajustos */
    uint32_T mes_adcFrenoSafe;
    uint32_T mes_adcEixida;

    /* Eixides model Gatell */
    extern uint32_T pwmGas;
    extern uint32_T pwmFreno;
    extern uint32_T pwmRoig;
    extern uint32_T pwmVerd;
    extern uint32_T pwmBlau;

    /* Eixides model Ajustos */
    extern uint32_T mensajePantalla;
    extern boolean_T mensajePantalla_IsUpdated;
    extern boolean_T enviarValorGatell;
    //extern boolean_T enviarVoltatgeEixida; /* Model ajustos 2.59 */
    extern boolean_T enviarValorPuntInicial1;
    extern boolean_T enviarValorPuntFinal1;
    extern boolean_T enviarValorPuntInicial2;
    extern boolean_T enviarValorPuntFinal2;
    extern boolean_T menuAjustos;
    extern boolean_T flashWrite_IsUpdatedPosFreno;
    extern boolean_T flashWrite_IsUpdatedPosFondo;
    extern boolean_T flashWrite_IsUpdatedlPosFreMapa2;

    /* Recorregut gatell */
    extern uint32_T flashRead_GatellMinHigh;
    extern uint32_T flashRead_GatellMaxHigh;

    /* Per enviar-ho per USB */
    extern uint32_T flashRead_mapaFreno;
    extern uint32_T flashRead_potenciaDin;
    extern uint32_T flashRead_ValorInicial1;
    extern uint32_T flashRead_ValorFinal1;
    extern uint32_T flashRead_ValorInicial2;
    extern uint32_T flashRead_ValorFinal2;
    extern uint32_T flashRead_GatellFreMapa2;

    /* Punts del mapa 1 */
    extern uint32_T flashWrite_ValorInicial1;
    extern boolean_T flashWrite_IsUpdatedValorInicial1;
    extern uint32_T flashWrite_ValorFinal1;
    extern boolean_T flashWrite_IsUpdatedValorFinal1;

    /* Punts del mapa 2 */
    extern uint32_T flashWrite_ValorInicial2;
    extern boolean_T flashWrite_IsUpdatedValorInicial2;
    extern uint32_T flashWrite_ValorFinal2;
    extern boolean_T flashWrite_IsUpdatedValorFinal2;

/* ################## Local functions / Macros ######### */
    extern void Gatell_initialize(void);
    extern void Gatell_step(void);
    extern void Ajustos_initialize(void);
    extern void Ajustos_step(void);

    static inline void TaskMesurar_Potencia(void);
    static inline void TaskMesurar_Corba(void);
    static inline uint16_t TaskMesurar_Gatell(void);
    static inline void TaskMesurar_Frenar(void);
    static inline uint32_t TaskMesurar_FrenarLast(void);
    static inline void TaskMesurar_Supply12v(void);
    static inline uint32_t TaskMesurar_Transformar(uint32_t value, uint32_t init, uint32_t end);
    static inline uint32_t TaskMesurar_Transformar2(uint32_t value);
    static inline uint32_t TaskMesurar_TransformarCorba(uint32_t value);



//#####################################################
//#####################  SW Code  #####################
//#####################################################

void TASKMESURAR_Init(void) {
    //
    // 1) Inicialitzar Variables
    mandoArc            = IOM__IsConnected_ARC_DRIVER();
    //
    menuAjustos         = false;
    //
    mes_adcFreno        = 0u;
    mes_adcFrenoLast    = TaskMesurar_FrenarLast();
    mes_adcSupply12v_mV = 0u;
    //
    memset( mes_sDataTX, NULL_CHARACTER, sizeof(mes_sDataTX) );

    // 2) Inicialitzar Models
    Gatell_initialize();
    Ajustos_initialize();
}


void TASKMESURAR_MainTask(void) {
    /* Si per alguna d'aquelles el mando se queda piripi, que se puga entrar al menú ajustos quan encenga el mando */
    ADM_ReadADCconversions();
    //
    mes_adcFrenoSafe = adm_MAX_VALUE_counts - adm_dataADC_counts[E_ADM__AI_POT_FRENO];
    if (mes_adcFrenoSafe <= 200u) {
        menuAjustos = true;
    }

    for(;;)
    {
        /*IOM_SetOutput__DO_SW_TEST_01( TRUE );*/  // Only for SW Testing

        // 1) Llegir conversions ADC
        ADM_ReadADCconversions();


        // 2) Processar conversions ADC
        /* Sempre valorar el valor del ADC del ajust del freno per si el gatell no pot retornar
         * a la posicio de freno i aixi poder anar al menu ajustos */
        mes_adcFrenoSafe       = adm_MAX_VALUE_counts - adm_dataADC_counts[E_ADM__AI_POT_FRENO];
        mes_adcEixida          = adm_MAX_VALUE_counts - adm_dataADC_counts[E_ADM__AI_POT_POTENCIA];
        mes_gatellFiltratFinal = TaskMesurar_Gatell();
        //
        TaskMesurar_Potencia();
        TaskMesurar_Corba();
        TaskMesurar_Frenar();
        TaskMesurar_Supply12v();

        if ( (mes_adcFrenoSafe <= 200u) && (IOM_ReadInput__DI_BUTTON_1() == false) ) {
            menuAjustos = true;
        }

        if( mes_valorPreparat ) {
            if (menuAjustos == false) {
                Gatell_step(); // Model Gatell
                if (pwmFreno >= 1000) pwmFreno = 1000;
                PMM_MotorArc_SetFreqDuty( pmm_MOTOR_ARC__MODULE_OUTPUT_FREQ_DEF, pwmGas, pwmFreno, pwmFreno );
                //
                if (pwmRoig >= 1000) pwmRoig = 1000;
                PMM_LedRgb_SetFreqDuty( pmm_LED_RGB__MODULE_OUTPUT_FREQ_DEF, pwmRoig, pwmVerd, pwmBlau );
                //
                if (flashWrite_IsUpdatedMapaFreno) {
                    xQueueSend( MapaFrenoHandle,         &flashWrite_mapaFreno, (TickType_t) 0u );
                    xQueueSend( MapaFrenoPantallaHandle, &flashWrite_mapaFreno, (TickType_t) 0u );
                }

                if (flashWrite_IsUpdatedPotenciaDin) {
                    xQueueSend( PotenciaDinHandle,         &flashWrite_potenciaDin, (TickType_t) 0u );
                    xQueueSend( PotenciaDinPantallaHandle, &flashWrite_potenciaDin, (TickType_t) 0u );
                }
            } else {
                Ajustos_step(); // Model Ajustos
                //
                if (mensajePantalla_IsUpdated) {
                    xQueueSend( MensajePantallaHandle, &mensajePantalla, (TickType_t) 0u );
                }

                if (enviarValorGatell) {
                    xQueueSend( GatellAdcHandle, &mes_gatellFiltratFinal, (TickType_t) 0u );
                }

                /* Model ajustos 2.59 */
                /*if (enviarVoltatgeEixida) {
                    xQueueSend( VoltatgeAdcHandle, &mes_adcEixida, (TickType_t) 0u );
                }*/

                if (enviarValorPuntInicial1) {
                    xQueueSend( ValorInicial1PantallaHandle, &flashWrite_ValorInicial1, (TickType_t) 0u );
                }

                if (enviarValorPuntFinal1) {
                    xQueueSend( ValorFinal1PantallaHandle, &flashWrite_ValorFinal1, (TickType_t) 0u );
                }

                if (enviarValorPuntInicial2) {
                    xQueueSend( ValorInicial2PantallaHandle, &flashWrite_ValorInicial2, (TickType_t) 0u );
                }

                if (enviarValorPuntFinal2) {
                    xQueueSend( ValorFinal2PantallaHandle, &flashWrite_ValorFinal2, (TickType_t) 0u );
                }

                /* Guardar en FLASH Posicio Freno*/
                if (flashWrite_IsUpdatedPosFreno) {
                    xQueueSend( PosFrenoFlashHandle, &mes_gatellFiltratFinal, (TickType_t) 0u );
                }

                /* Guardar en FLASH Posicio Fondo*/
                if (flashWrite_IsUpdatedPosFondo) {
                    xQueueSend( PosFondoFlashHandle, &mes_gatellFiltratFinal, (TickType_t) 0u );
                }

                /* Guardar en FLASH Posicio Mapa Freno 2*/
                if (flashWrite_IsUpdatedlPosFreMapa2) {
                    xQueueSend( PosFrenoMapa2FlashHandle, &mes_gatellFiltratFinal, (TickType_t) 0u );
                }

                /* Guardar en FLASH ValorInicial1 (offset del mapa 1)*/
                if (flashWrite_IsUpdatedValorInicial1) {
                    xQueueSend( ValorInicial1FlashHandle, &flashWrite_ValorInicial1, (TickType_t) 0u );
                }

                /* Guardar en FLASH ValorFinal1 (curva del mapa 1)*/
                if (flashWrite_IsUpdatedValorFinal1) {
                    xQueueSend( ValorFinal1FlashHandle, &flashWrite_ValorFinal1, (TickType_t) 0u );
                }

                /* Guardar en FLASH ValorInicial1 (offset del mapa 1)*/
                if (flashWrite_IsUpdatedValorInicial2) {
                    xQueueSend( ValorInicial2FlashHandle, &flashWrite_ValorInicial2, (TickType_t) 0u );
                }

                /* Guardar en FLASH ValorFinal1 (curva del mapa 1)*/
                if (flashWrite_IsUpdatedValorFinal2) {
                    xQueueSend( ValorFinal2FlashHandle, &flashWrite_ValorFinal2, (TickType_t) 0u );
                }
            }

            // 3) Enviar dates per USB
            mes_gatellTransformat   = TaskMesurar_Transformar     ( mes_gatellFiltratFinal, flashRead_GatellMinHigh, flashRead_GatellMaxHigh );
            mes_frenoTransformat    = TaskMesurar_Transformar2    ( mes_adcFrenoLast );
            mes_potenciaTransformat = TaskMesurar_Transformar2    ( mes_potenciaFiltratLast );
            mes_corbaTransformat    = TaskMesurar_TransformarCorba( mes_corbaFiltratLast );
            /*IOM_SetOutput__DO_SW_TEST_01( FALSE );*/  // Only for SW Testing
            //
            /*IOM_SetOutput__DO_SW_TEST_01( TRUE );*/  // Only for SW Testing
            memset(   mes_sDataTX, NULL_CHARACTER, sizeof(mes_sDataTX) );
            snprintf( mes_sDataTX, sizeof(mes_sDataTX), "<gas>%03lu\n<fre>%03lu\n<sal>%03lu\n<cur>%03lu\n<mpf>%01u\n<mpp>%01u\n<pxt>%01u\n<gat>%04lu\n<gmi>%04u\n<gma>%04u\n<mf2>%04u\n<vi1>%01u\n<vf1>%01u\n<vi2>%01u\n<vf2>%01u\n",
                                                mes_gatellTransformat,
                                                mes_frenoTransformat,
                                                mes_potenciaTransformat,
                                                mes_corbaTransformat,
                                                flashRead_mapaFreno,
                                                (IOM_ReadInput__DI_SWITCH_1() + 1u),
                                                flashRead_potenciaDin,
                                                mes_gatellFiltratFinal,
                                                flashRead_GatellMinHigh,
                                                flashRead_GatellMaxHigh,
                                                flashRead_GatellFreMapa2,
                                                flashRead_ValorInicial1,
                                                flashRead_ValorFinal1,
                                                flashRead_ValorInicial2,
                                                flashRead_ValorFinal2);
            USBM_Send( mes_sDataTX, sizeof(mes_sDataTX) );
        }

        // 4) Demanar nova conversio ADC
        ADM_TriggerNewADCconversion();

        #ifdef PMM_TEST_FUNCTIONS_ENABLED__MOTOR_ARC
            static T_u32 i_PmmMotorArc = T_U32_MIN;
            i_PmmMotorArc++;
            if( i_PmmMotorArc > 10u ) {
                PMM_MotorArc_Test01();
                //PMM_MotorArc_Test02_FreqDuty_With2Potentiometers();
                //PMM_MotorArc_Test03_FreqDuty_With2Potentiometers();
                i_PmmMotorArc = T_U32_MIN;
            }
        #endif
        #ifdef PMM_TEST_FUNCTIONS_ENABLED__LED_RGB
            static T_u32 i_PmmLedRgb = T_U32_MIN;
            i_PmmLedRgb++;
            if( i_PmmLedRgb > 10u ) {
                //PMM_LedRgb_Test01();
                PMM_LedRgb_Test02();
                i_PmmLedRgb = T_U32_MIN;
            }
        #endif

        // 5) Esperar 1 ms per no colapsar els envios del USB al movil i per a tenir nova conversio ADC
        /*IOM_SetOutput__DO_SW_TEST_01( FALSE );*/  // Only for SW Testing
        vTaskDelay( pdMS_TO_TICKS(1u) );
    }
}

static inline uint16_t TaskMesurar_Gatell(void)
{
    if (mes_indexGatell < NUM_MOSTRES) {
        mes_gatellFiltrat += adm_dataADC_counts[E_ADM__AI_SENSOR_HALL_GATELL];
        mes_valorPreparat = 0u;
        mes_indexGatell++;
    }
    else {
        /* Abans de fer la mitja, guardar el anterior valor del gatell filtrat */
        mes_gatellFiltratLast = mes_gatellFiltratFinal;

        /* Filtrar gatell */
        mes_gatellFiltratFinal = mes_gatellFiltrat / NUM_MOSTRES;
        mes_gatellFiltrat      = 0u;

        mes_indexGatell   = 0u;
        mes_valorPreparat = 1u;
    }

    return mes_gatellFiltratFinal;
}

static inline void TaskMesurar_Potencia(void)
{
    if (mes_indexPotencia < NUM_MOSTRES) {
        mes_potenciaFiltrat += (adm_MAX_VALUE_counts - adm_dataADC_counts[E_ADM__AI_POT_POTENCIA]);
        mes_indexPotencia++;
    }
    else {
        mes_potenciaFiltratLast = mes_potenciaFiltrat / NUM_MOSTRES;
        xQueueSend( PotenciaAdcHandle, &mes_potenciaFiltratLast, (TickType_t) 0u );
        //
        mes_potenciaFiltrat = 0u;
        mes_indexPotencia   = 0u;
    }
}

static inline void TaskMesurar_Corba(void)
{
    if (mes_indexCorba < NUM_MOSTRES) {
        mes_corbaFiltrat += adm_dataADC_counts[E_ADM__AI_POT_CURVA];
        mes_indexCorba++;
    }
    else {
        mes_corbaFiltratLast = mes_corbaFiltrat / NUM_MOSTRES;
        xQueueSend( CorbaAdcHandle, &mes_corbaFiltratLast, (TickType_t) 0u );
        //
        mes_corbaFiltrat = 0u;
        mes_indexCorba   = 0u;
    }
}

static inline uint32_t TaskMesurar_FrenarLast(void)
{
    return (adm_MAX_VALUE_counts - adm_dataADC_counts[E_ADM__AI_POT_FRENO]);
}

static inline void TaskMesurar_Frenar(void)
{
    mes_adcFrenoAct = TaskMesurar_FrenarLast();
    //
    if (mes_adcFrenoAct < 40u && (abs(mes_adcFrenoAct - mes_adcFrenoLast)) >= 40u) {
        mes_adcFreno     = 0u;
        mes_adcFrenoLast = mes_adcFreno;
    } else if (mes_adcFrenoAct >= 40u && (abs(mes_adcFrenoAct - mes_adcFrenoLast)) > 35u) {
        mes_adcFreno     = mes_adcFrenoAct;
        mes_adcFrenoLast = mes_adcFreno;
    } else if (mes_adcFrenoAct >= 4090u){
        mes_adcFreno     = adm_MAX_VALUE_counts;
        mes_adcFrenoLast = mes_adcFreno;
    } else {
        mes_adcFreno = mes_adcFrenoLast;
    }
    //
    xQueueSend( FrenoAdcHandle, &mes_adcFreno, (TickType_t) 0u );
}


static inline void TaskMesurar_Supply12v(void) {
    mes_adcSupply12v_mV = adm_dataADC_mV[E_ADM__AI_SUPPLY_12V_PROTECTED];
}

// Escala un valor entre dos límites a un rango de 0 a 100
static inline uint32_t TaskMesurar_Transformar(uint32_t value, uint32_t init, uint32_t end) {
    if (end <= init) {
        // Para evitar división por cero o rango inválido
        return( 0u );
    }

    if (value <= init) {
        return( 0u );
    }

    if (value >= end) {
        return( 100u );
    }

    return( (value - init) * 100 / (end - init) + 1 );
}

static inline uint32_t TaskMesurar_Transformar2(uint32_t value) {
    uint32_t transformat = value / 40u;

    if( transformat < 100u ) {
        return( transformat );
    } else {
        return( 100u );
    }
}

static inline uint32_t TaskMesurar_TransformarCorba(uint32_t value) {
    uint32_t transformat = 101u - (value / 40u);

    if( transformat < 100u ) {
        return( transformat );
    } else if( transformat == 0xFFFFFFFFu) {
        return( 0u );
    } else {
        return( 100u );
    }
}
