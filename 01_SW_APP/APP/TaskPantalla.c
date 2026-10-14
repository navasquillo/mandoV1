/*
 * TaskPantalla.c
 *
 *  Created on: Dec 7, 2022
 *      Author: Albert, Sergio
 */


/* ################## Include's ####################### */

    /* Include types */
    #include "libTypes_api.h"
    #include "dataFormat_api.h"
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    /* Local prototypes */
    #include "TaskPantalla_api.h"
    #include "rtwtypes.h"

    /* Include external API's */
    #include "main.h"
    #include "cmsis_os.h"
    #include "queue.h"
    #include "semphr.h"
    //
    #include "math.h"
    #include "Inc/valors.h"
    //
    #include "iom_api.h"
    #include "i2cm_api.h"
    #include "ssd1306_api.h"
    #include "usbm_api.h"
    //
    #include "ver_api.h"


/* ################## Define's ######################### */


/* ################## Global variables ################# */
    /* External variables */
    extern char ver_ProductSerialNumber_DataTx[VER__PRODUCT_SERIAL_NUMBER__MAX_LENGTH];
    extern char ver_SwAppVersionName_DataTx[VER__SW_APP_VERSION_NAME__MAX_LENGTH];

    extern osMessageQId GatellAdcHandle;
    extern osMessageQId FrenoAdcHandle;
    extern osMessageQId PotenciaAdcFiltratHandle;
    extern osMessageQId PotenciaParamFHandle;
    extern osMessageQId CorbaAdcFiltratHandle;
    extern osMessageQId CorbaParamFHandle;
    extern osMessageQId VoltatgeAdcHandle;
    extern osMessageQId MapaFrenoPantallaHandle;
    extern osMessageQId PotenciaDinPantallaHandle;
    extern osMessageQId ValorInicial1PantallaHandle;
    extern osMessageQId ValorFinal1PantallaHandle;
    extern osMessageQId ValorInicial2PantallaHandle;
    extern osMessageQId ValorFinal2PantallaHandle;

    extern uint32_t flashRead_mapaFreno;
    extern uint32_t flashRead_potenciaDin;
    extern uint32_t flashRead_ValorInicial1;
    extern uint32_t flashRead_ValorFinal1;
    extern uint32_t flashRead_ValorInicial2;
    extern uint32_t flashRead_ValorFinal2;

    /* Variables del menu ajustos */
    extern osMessageQId MensajePantallaHandle;
    extern uint32_t mes_gatellFiltratFinal;
    extern boolean_T menuAjustos;

    /* Variables per calcular la Loockup Table */
    extern uint32_t mes_valorsCalculatsMapa1[DIFF];
    extern uint32_t mes_valorsCalculatsMapa2[DIFF];
    extern uint32_T indexStart;
    float puntLast1;
    float puntLast2;

    extern float factorOffsetMapa1;
    extern float factorPotenciaMapa1;
    extern float factorOffsetMapa2;
    extern float factorPotenciaMapa2;


    /* Internal variables */
    char disp_IdMando[17u];
    char disp_SwVersion[32u];
    //
    char disp_sMapaPotenciaText[11u];
    char disp_sPotExtra[10u];
    char disp_sPotencia[12u];
    char disp_sCorba[9u];
    char disp_sFrenoMapaFrenoText[22u];
    //
    char disp_sGatell[6u];
    char disp_sVoltatge[9u];
    //
    char disp_sValorPuntLast[14u];
    char disp_sValorPunt[14u];
    //
    uint16_t disp_frenoAdc;
    uint16_t disp_frenoAdcLast;
    uint8_t  disp_frenoPercentage;
    //
    uint16_t disp_potenciaAdc;
    uint16_t disp_potenciaAdcLast;
    uint8_t  disp_potenciaPercentage;
    float    disp_potenciaParamF;
    //
    uint16_t disp_corbaAdc;
    uint16_t disp_corbaAdcLast;
    uint8_t  disp_corbaPercentage;
    float    disp_corbaParamF;
    //
    uint8_t  disp_updateLUT_trigger;
    uint8_t  disp_updateScreen_trigger;
    uint8_t  disp_MenuAjustos_now;
    uint8_t  disp_MenuAjustos_old;
    //
    uint32_t disp_MapaFreno;
    uint32_t disp_PotDinamica;
    //
    float    disp_exponentCorba_old;
    float    disp_powLUT_Corba[LUT_CORBA_SIZE];


/* ################## Local functions / Macros ######### */
    static inline __attribute__((always_inline)) void CalcularLookTablePWM (float offset, float exponent);
    static inline __attribute__((always_inline)) void GenerarLUTpow_RepresentarCorba(float exponent);
    static inline __attribute__((always_inline)) void RepresentarCorba  (float offset, float exponentCorba);
    static inline __attribute__((always_inline)) uint16_t InvertirPixel (uint16_t y);
    static inline __attribute__((always_inline)) void PantallaValors (void);
    static inline void AjustosAvansats     (void);
    static inline void VoreValorGatell     (void);
    static inline void AjustPosicioFreno   (void);
    static inline void AjustPosicioFondo   (void);
    static inline void AjustPosFreMapa2    (void);
    static inline void AjustMapa1          (void);
    static inline void AjustMapa2          (void);
    static inline void AjustVoltajeEixida  (void);
    static inline void VoltatgeEixida      (uint32_t voltajeEixida);
    static inline void MensajeOffset       (void);
    static inline void MensajePotencia     (void);
    static inline void ValorPunts          (uint32_t valorPuntLast, uint32_t valorPunt);
    static inline void DiffGatell          (void);
    static inline void ExtraPWM            (void);
    static inline void ValorGatell         (uint32_t valorGatell);
    static inline void EixirAjustos        (void);
    static inline void PosFrenoNok         (void);
    static inline void PosFondoNok         (void);
    static inline void MissatgeOk          (void);
    static inline void MissatgeNok         (void);
    static inline void MissatgeEixir       (void);



//#####################################################
//#####################  SW Code  #####################
//#####################################################

void TASKPANTALLA_Init(void) {
    disp_frenoAdc               = 0u;
    disp_frenoAdcLast           = 0u;
    disp_frenoPercentage        = 0u;
    //
    disp_potenciaAdc            = 0u;
    disp_potenciaAdcLast        = 0u;
    disp_potenciaPercentage     = 0u;
    disp_potenciaParamF         = 0.0F;
    //
    disp_corbaAdc               = 0u;
    disp_corbaAdcLast           = 0u;
    disp_corbaPercentage        = 0u;
    disp_corbaParamF            = 0.0F;
    //
    disp_updateLUT_trigger      = FALSE;
    disp_updateScreen_trigger   = TRUE;  // Forçar un update Display al arrancar
    disp_MenuAjustos_now        = FALSE;
    disp_MenuAjustos_old        = FALSE;

    /* Configuracions dels botons */
    disp_MapaFreno         = 0u;
    disp_PotDinamica       = 0u;

    /* Calcular la lookup table per a fer el PWM per defecte */
    CalcularLookTablePWM( 0.0F, 1.0F );
    //
    memset( disp_powLUT_Corba, 0.0F, sizeof(disp_powLUT_Corba) );
    disp_exponentCorba_old = -1.0F;  // Forçar un update de disp_powLUT_Corba
    GenerarLUTpow_RepresentarCorba( 1.0F );

    /* Inicialitzar buffers */
    memset( disp_sMapaPotenciaText,   NULL_CHARACTER,  sizeof(disp_sMapaPotenciaText) );
    memset( disp_sPotExtra,           NULL_CHARACTER,  sizeof(disp_sPotExtra) );
    memset( disp_sPotencia,           NULL_CHARACTER,  sizeof(disp_sPotencia) );
    memset( disp_sCorba,              NULL_CHARACTER,  sizeof(disp_sCorba) );
    memset( disp_sFrenoMapaFrenoText, NULL_CHARACTER,  sizeof(disp_sFrenoMapaFrenoText) );
    memset( disp_sGatell,             NULL_CHARACTER,  sizeof(disp_sGatell) );
    memset( disp_sVoltatge,           NULL_CHARACTER,  sizeof(disp_sVoltatge) );
    memset( disp_sValorPuntLast,      NULL_CHARACTER,  sizeof(disp_sValorPuntLast) );
    memset( disp_sValorPunt,          NULL_CHARACTER,  sizeof(disp_sValorPunt) );

    /* Inicialitzar buffers amb contingut que no cambia */
    memset( disp_IdMando,             NULL_CHARACTER,  sizeof(disp_IdMando) );
    memset( disp_SwVersion,           NULL_CHARACTER,  sizeof(disp_SwVersion) );
    //
    snprintf( disp_IdMando,   sizeof(disp_IdMando),   "Id:%s", ver_ProductSerialNumber_DataTx );
    snprintf( disp_SwVersion, sizeof(disp_SwVersion), "Sw:%s", ver_SwAppVersionName_DataTx );

    /* Netejar Buffer pantalla per estar preparats pel seguent update de pantalla */
    SSD1306_Clear();
}


void TASKPANTALLA_MainTask(void) {
    uint32_t numMensaje        = 0u;
    uint32_t valorGatell       = 0u;
    uint32_t voltatgeEixida    = 0u;
    uint32_t punt              = 0u;
    uint32_t mapaP             = 1u;
    uint32_t mapaPLast         = 1u;

    configASSERT( xPortIsInsideInterrupt() == pdFALSE );   // nunca debe ejecutarse en ISR
    TickType_t       xLastWakeTime = xTaskGetTickCount();  // inicializar antes de vTaskDelayUntil
    const TickType_t xFrequency    = pdMS_TO_TICKS(30u);

    /* Forçar al OS per a que la tasca del ADC s'execute primer */
    vTaskDelay( pdMS_TO_TICKS(20u) );  // Ordre execucions inicial per a un bon arranc del Display:   Task_MesurarAdc -> TaskParams -> TaskPantalla-> TaskFlash -> TaskFreeRtosMonitor
    I2CM_PostInit();

    /* Infinite loop */
    for(;;)
    {
        /*IOM_SetOutput__DO_SW_TEST_02( TRUE );*/  // Only for SW Testing

        disp_MenuAjustos_now = menuAjustos;
        //
        if ( disp_MenuAjustos_now ) {
            // Forçar update si entrem al Menu Ajustes
            if( disp_MenuAjustos_old == FALSE ) {
                disp_updateScreen_trigger = TRUE;
            }

            /* Per representar els numeros quan se ix del menú ajustos */
            if (uxQueueMessagesWaiting(MensajePantallaHandle)) {
                xQueueReceive( MensajePantallaHandle, &numMensaje, (TickType_t) 0u );
                //
                switch (numMensaje) {
                    case 0:
                        AjustosAvansats();
                        break;
                    case 1:
                        VoreValorGatell();
                        break;
                    case 2:
                        AjustPosicioFreno();
                        break;
                    case 3:
                        AjustPosicioFondo();
                        break;
                    case 4:
                        AjustMapa1();
                        break;
                    case 5:
                        AjustMapa2();
                        break;
                    case 6:
                        DiffGatell();
                        break;
                    case 7:
                        ExtraPWM();
                        break;
                    case 8:
                        EixirAjustos();
                        break;
                    case 9:
                        PosFrenoNok();
                        break;
                    case 10:
                        PosFondoNok();
                        break;
                    case 11:
                        MissatgeOk();
                        break;
                    case 12:
                        MissatgeNok();
                        break;
                    case 13:
                        MissatgeEixir();
                        break;
                    case 14:
                        MensajeOffset();
                        break;
                    case 15:
                        MensajePotencia();
                        break;
                    case 16:
                        AjustPosFreMapa2();
                        break;
                    /*case 17: Model Ajustos 2.59
                        AjustVoltajeEixida();
                        break;*/
                    default:
                        EixirAjustos();
                        break;
                }
                disp_updateScreen_trigger = TRUE;
            }

            if (uxQueueMessagesWaiting(GatellAdcHandle)) {
                xQueueReceive( GatellAdcHandle, &valorGatell, (TickType_t) 0u );
                ValorGatell (valorGatell);
                disp_updateScreen_trigger = TRUE;
            }

            if (uxQueueMessagesWaiting(VoltatgeAdcHandle)) {
                xQueueReceive( VoltatgeAdcHandle, &voltatgeEixida, (TickType_t) 0u );
                VoltatgeEixida (voltatgeEixida);
                disp_updateScreen_trigger = TRUE;
            }


            if (uxQueueMessagesWaiting(ValorInicial1PantallaHandle)) {
                xQueueReceive( ValorInicial1PantallaHandle, &punt, (TickType_t) 0u );
                ValorPunts (flashRead_ValorInicial1, punt);
                disp_updateScreen_trigger = TRUE;
            }

            if (uxQueueMessagesWaiting(ValorFinal1PantallaHandle)) {
                xQueueReceive( ValorFinal1PantallaHandle, &punt, (TickType_t) 0u );
                ValorPunts (flashRead_ValorFinal1, punt);
                disp_updateScreen_trigger = TRUE;
            }

            if (uxQueueMessagesWaiting(ValorInicial2PantallaHandle)) {
                xQueueReceive( ValorInicial2PantallaHandle, &punt, (TickType_t) 0u );
                ValorPunts (flashRead_ValorInicial2, punt);
                disp_updateScreen_trigger = TRUE;
            }

            if (uxQueueMessagesWaiting(ValorFinal2PantallaHandle)) {
                xQueueReceive( ValorFinal2PantallaHandle, &punt, (TickType_t) 0u );
                ValorPunts (flashRead_ValorFinal2, punt);
                disp_updateScreen_trigger = TRUE;
            }

            // Actualitzar pantalla si cal
            if( I2CM_SSD1306_IsReadyForNewTransference() ) {
                if( SSD1306_UpdateScreenDMA_Status() == E_SSD1306_READY_TO_UPDATE ) {
                    if( disp_updateScreen_trigger ) {
                        SSD1306_UpdateScreenDMA_Trigger();  // Iniciar refresc pantalla via I2C-DMA
                        disp_updateScreen_trigger = FALSE;  // Reiniciar trigger
                    }
                }
            }
        }

        /* Finestra principal */
        else {
            // 1) Rebre dades
            xQueueReceive( FrenoAdcHandle,            &disp_frenoAdc,       (TickType_t) 0u );
            xQueueReceive( PotenciaAdcFiltratHandle,  &disp_potenciaAdc,    (TickType_t) 0u );
            xQueueReceive( CorbaAdcFiltratHandle,     &disp_corbaAdc,       (TickType_t) 0u );
            //
            xQueueReceive( PotenciaParamFHandle,      &disp_potenciaParamF, (TickType_t) 0u );
            xQueueReceive( CorbaParamFHandle,         &disp_corbaParamF,    (TickType_t) 0u );
            //
            // Forçar update si sortim del Menu Ajustes
            if( disp_MenuAjustos_old ) {
                disp_updateLUT_trigger    = TRUE;
                disp_updateScreen_trigger = TRUE;
            }


            // 2) Processar dades
            /* Posar el numero de mapa de potencia */
            mapaP = IOM_ReadInput__DI_SWITCH_1() + 1u;
            if (mapaP != mapaPLast) {
                mapaPLast                 = mapaP;
                disp_updateScreen_trigger = TRUE;
            }

            /* Histeresis per al Freno */
            if( abs(disp_frenoAdc - disp_frenoAdcLast) > HISTERESI_PANTALLA ) {
                disp_frenoAdcLast = disp_frenoAdc;
                //
                disp_frenoPercentage = disp_frenoAdc / 40u;
                if (disp_frenoPercentage >= 100u) {
                    disp_frenoPercentage = 100u;
                }
                //
                disp_updateScreen_trigger = TRUE;
            }

            /* Histeresis per la Potencia */
            if( abs(disp_potenciaAdc - disp_potenciaAdcLast) > HISTERESI_PANTALLA_2 ) {
                disp_potenciaAdcLast = disp_potenciaAdc;
                //
                disp_potenciaPercentage = disp_potenciaAdc / 40u;
                if (disp_potenciaPercentage >= 100u) {
                    disp_potenciaPercentage = 100u;
                }
                //
                disp_updateLUT_trigger    = TRUE;
                disp_updateScreen_trigger = TRUE;
            }

            /* Histeresis per la Corba */
            if( abs(disp_corbaAdc - disp_corbaAdcLast) > HISTERESI_PANTALLA_2 ) {
                disp_corbaAdcLast = disp_corbaAdc;
                //
                disp_corbaPercentage = disp_corbaAdc / 40u;
                if (disp_corbaPercentage >= 101u) {
                    disp_corbaPercentage = 101u;
                }
                //
                disp_updateLUT_trigger    = TRUE;
                disp_updateScreen_trigger = TRUE;
            }

            /* Butons */
            if( xQueueReceive( MapaFrenoPantallaHandle, &disp_MapaFreno, (TickType_t) 0u ) ) {
                disp_updateScreen_trigger = TRUE;
            }

            if( xQueueReceive( PotenciaDinPantallaHandle, &disp_PotDinamica, (TickType_t) 0u ) ) {
                disp_updateScreen_trigger = TRUE;
            }


            // 3) Calcular LookUpTable-PWM si cal
            if ( disp_updateLUT_trigger ) {
                /*IOM_SetOutput__DO_SW_TEST_02( FALSE );*/  // Only for SW Testing
                CalcularLookTablePWM( disp_potenciaParamF, disp_corbaParamF );
                disp_updateLUT_trigger = FALSE;
                /*IOM_SetOutput__DO_SW_TEST_02( TRUE );*/   // Only for SW Testing
            }


            // 4) Actualitzar pantalla si cal
            if( I2CM_SSD1306_IsReadyForNewTransference() ) {
                if( SSD1306_UpdateScreenDMA_Status() == E_SSD1306_READY_TO_UPDATE ) {
                    if( disp_updateScreen_trigger ) {
                        RepresentarCorba( disp_potenciaParamF, disp_corbaParamF );  // Representar la corba
                        PantallaValors();                                           // Mostrar valors
                        //
                        SSD1306_UpdateScreenDMA_Trigger();                          // Iniciar refresc pantalla via I2C-DMA
                        disp_updateScreen_trigger = FALSE;                          // Reiniciar trigger
                    }
                }
            }
        }
        //
        disp_MenuAjustos_old = disp_MenuAjustos_now;

        /*IOM_SetOutput__DO_SW_TEST_02( FALSE );*/  // Only for SW Testing
        vTaskDelayUntil( &xLastWakeTime, xFrequency );
    }
}



//
static inline __attribute__((always_inline)) void CalcularLookTablePWM(float offset, float exponent) {
    //
    // Precalcula constantes fuera del bucle
    uint32_t range1     = DIFF - indexStart - 15u;
    float scaleFactor_F = 1000.0F;

    /* -------- Precalculos comunes -------- */
    uint32_t value1    = (indexStart + 15u);
    uint32_t value2    = 0u;
    float    normAdc_F = 0.0F;

    float start1 = factorOffsetMapa1 + offset;
    if ((puntLast1) <= start1)
        start1 = puntLast1;

    float start2 = factorOffsetMapa2 + offset;
    if ((puntLast2) <= start2)
            start2 = puntLast2;

    float delta1 = factorPotenciaMapa1 - start1;
    float delta2 = factorPotenciaMapa2 - start2;

    for (uint16_t adc = indexStart; adc < DIFF; adc++)
    {
        if( adc >= value1 ) {
            value2    = adc - indexStart - 15u;
            normAdc_F = (float)value2 / (float)range1;
        }

        // Curva base normalizada [0..1]
        float curve = powf( normAdc_F, exponent );  // Nota: Gasta molta CPU Load el powf

        /* -------- MAPA 1 -------- */
        float Mapa1_PwmDutyEq_F = ( (start1 + (delta1 * curve)) * scaleFactor_F );
        mes_valorsCalculatsMapa1[adc] = (uint32_t)Mapa1_PwmDutyEq_F;

        /* -------- MAPA 2 -------- */
        float Mapa2_PwmDutyEq_F = ( (start2 + (delta2 * curve)) * scaleFactor_F );
        mes_valorsCalculatsMapa2[adc] = (uint32_t)Mapa2_PwmDutyEq_F;
    }
    puntLast1 = (float) mes_valorsCalculatsMapa1[1499] * 0.001F;
    puntLast2 = (float) mes_valorsCalculatsMapa2[1499] * 0.001F;
}



/* Per a representar la corva en la pantalla*/
static inline __attribute__((always_inline)) void GenerarLUTpow_RepresentarCorba(float exponent) {
    float xFloat;
    //
    for (uint16_t x = 0; x < LUT_CORBA_SIZE; x++) {
        xFloat               = (float)x * (1.0f / (float)LUT_CORBA_SIZE);
        disp_powLUT_Corba[x] = powf(xFloat, exponent);
    }
}
//
static inline __attribute__((always_inline)) void RepresentarCorba(float offset, float exponentCorba) {
    //
    // 1) Recalcular LUT si cambia el exponent
    if( disp_exponentCorba_old != exponentCorba ) {
        GenerarLUTpow_RepresentarCorba( exponentCorba );
    }
    disp_exponentCorba_old = exponentCorba;

    // 2) Representar la Corba
    for (uint16_t x = 0; x < LUT_CORBA_SIZE; x++) {
        float yFloat    = (disp_powLUT_Corba[x] * (1.0f - offset)) + offset;
        uint16_t y      = (uint16_t)(yFloat * 46.0f) + 18;
        uint16_t yFinal = InvertirPixel(y);

        SSD1306_DrawPixel_White(x, yFinal);
    }
}


/* Invertir Pixel */
static inline __attribute__((always_inline)) uint16_t InvertirPixel (uint16_t y) {
    if( (y >= 18u) && (y <= 64u) ) {
        return( 64u - y );
    } else {
        return( 64u );
    }
}

static inline __attribute__((always_inline)) void PantallaValors(void) {
    //
    // 0) Init Text Buffers
    memset( disp_sMapaPotenciaText,   NULL_CHARACTER,  sizeof(disp_sMapaPotenciaText) );
    memset( disp_sPotExtra,           NULL_CHARACTER,  sizeof(disp_sPotExtra) );
    memset( disp_sPotencia,           NULL_CHARACTER,  sizeof(disp_sPotencia) );
    memset( disp_sCorba,              NULL_CHARACTER,  sizeof(disp_sCorba) );
    memset( disp_sFrenoMapaFrenoText, NULL_CHARACTER,  sizeof(disp_sFrenoMapaFrenoText) );

    // 1.1) Linea 1:  MapaP
    snprintf( disp_sMapaPotenciaText, sizeof(disp_sMapaPotenciaText), "MapaP:%u", (IOM_ReadInput__DI_SWITCH_1() + 1u) );

    // 1.2) Linea 2:  P.Extra
    if (disp_PotDinamica == 1u) {
        snprintf( disp_sPotExtra, sizeof(disp_sPotExtra), "P.Xtr:OF" );
    } else {
        snprintf( disp_sPotExtra, sizeof(disp_sPotExtra), "P.Xtr:ON" );
    }

    // 1.3) Linea 3:  Pot. Potencia/Salida
    snprintf( disp_sPotencia, sizeof(disp_sPotencia), "Sal: %u", disp_potenciaPercentage );

    // 1.4) Linea 4:  Pot. Corba
    snprintf( disp_sCorba, sizeof(disp_sCorba), "Cur: %u", (101u-disp_corbaPercentage) );

    // 1.5) Linea 5:  Freno/Ajustes i MapaF
    if (disp_frenoPercentage >= 20u) {
        if (disp_frenoPercentage < 100u) {
            snprintf( disp_sFrenoMapaFrenoText, sizeof(disp_sFrenoMapaFrenoText), "Freno:%u  MapaF:%u", disp_frenoPercentage, (unsigned int)disp_MapaFreno );
        } else {
            snprintf( disp_sFrenoMapaFrenoText, sizeof(disp_sFrenoMapaFrenoText), "Freno:%u MapaF:%u", disp_frenoPercentage, (unsigned int)disp_MapaFreno );
        }
    } else {
        snprintf( disp_sFrenoMapaFrenoText, sizeof(disp_sFrenoMapaFrenoText), "AJUSTES   MapaF:%u", (unsigned int)disp_MapaFreno );
    }


    // 2) Conversio Text a Pixel
    SSD1306_Write5Lines_PrepareScreen( 69u, 0u,  disp_sMapaPotenciaText,     &Font_7x10,
                                       69u, 17u, disp_sPotExtra,             &Font_7x10,
                                       69u, 29u, disp_sPotencia,             &Font_7x10,
                                       69u, 41u, disp_sCorba,                &Font_7x10,
                                        0u, 53u, disp_sFrenoMapaFrenoText,   &Font_7x10 );
}

static inline void AjustosAvansats ()
{
    SSD1306_Write3Lines_PrepareScreen( 0u,  0u, "AJUSTES",       &Font_11x18,
                                       0u, 23u, disp_IdMando,    &Font_11x18,
                                       0u, 45u, disp_SwVersion,  &Font_11x18 );
}

static inline void VoreValorGatell(void)
{
    SSD1306_Write2Lines_PrepareScreen( 0u, 20u, "ADC Valor",     &Font_11x18,
                                       0u, 40u, "Gatillo",       &Font_11x18 );
}

static inline void AjustPosicioFreno(void)
{
    SSD1306_Write2Lines_PrepareScreen( 0u, 20u, "Posicion",      &Font_11x18,
                                       0u, 40u, "Freno",         &Font_11x18 );
}

static inline void AjustPosicioFondo(void)
{
    SSD1306_Write2Lines_PrepareScreen( 0u, 20u, "Posicion",      &Font_11x18,
                                       0u, 40u, "Fondo",         &Font_11x18 );
}

static inline void AjustPosFreMapa2(void)
{
    SSD1306_Write2Lines_PrepareScreen( 0u, 20u, "Posicion",      &Font_11x18,
                                       0u, 40u, "Fre. Mapa 2",   &Font_11x18 );
}

static inline void AjustMapa1(void)
{
    SSD1306_Write2Lines_PrepareScreen( 0u, 20u, "Ajuste",        &Font_11x18,
                                       0u, 40u, "Mapa 1",        &Font_11x18 );
}

static inline void AjustMapa2(void)
{
    SSD1306_Write2Lines_PrepareScreen( 0u, 20u, "Ajuste",        &Font_11x18,
                                       0u, 40u, "Mapa 2",        &Font_11x18 );
}

static inline void MensajeOffset(void)
{
    SSD1306_Write2Lines_PrepareScreen( 0u, 20u, "Posicion",      &Font_11x18,
                                       0u, 40u, "Inicio",        &Font_11x18 );
}

static inline void MensajePotencia(void)
{
    SSD1306_Write2Lines_PrepareScreen( 0u, 20u, "Posicion",      &Font_11x18,
                                       0u, 40u, "Final",         &Font_11x18 );
}

static inline void DiffGatell(void)
{
    SSD1306_Write2Lines_PrepareScreen( 0u, 20u, "Delta",         &Font_11x18,
                                       0u, 40u, "Gatillo",       &Font_11x18 );
}

static inline void ExtraPWM(void)
{
    SSD1306_Write2Lines_PrepareScreen( 0u, 20u, "Extra",         &Font_11x18,
                                       0u, 40u, "PWM",           &Font_11x18 );
}

static inline void AjustVoltajeEixida(void)
{
    SSD1306_Write2Lines_PrepareScreen( 0u, 20u, "Voltaje",       &Font_11x18,
                                       0u, 40u, "Salida",        &Font_11x18 );
}

static inline void EixirAjustos(void)
{
    SSD1306_Write1Line_PrepareScreen( 0u, 20u, "Salir",          &Font_11x18 );
}

static inline void PosFrenoNok(void)
{
    SSD1306_Write3Lines_PrepareScreen( 0u,  0u, "Ajuste NOK",    &Font_11x18,
                                       0u, 23u, "Pos freno >=",  &Font_11x18,
                                       0u, 45u, "Pos fondo",     &Font_11x18 );
}

static inline void PosFondoNok(void)
{
    SSD1306_Write3Lines_PrepareScreen( 0u,  0u, "Ajuste NOK",    &Font_11x18,
                                       0u, 23u, "Pos fondo <=",  &Font_11x18,
                                       0u, 45u, "Pos freno",     &Font_11x18 );
}

static inline void MissatgeOk(void)
{
    SSD1306_Write2Lines_PrepareScreen( 0u, 20u, "Ajuste",        &Font_11x18,
                                       0u, 40u, "Finalizado",    &Font_11x18 );
}

static inline void MissatgeNok(void)
{
    SSD1306_Write2Lines_PrepareScreen( 0u, 20u, "Ajuste no",     &Font_11x18,
                                       0u, 40u, "Implementado",  &Font_11x18 );
}

static inline void MissatgeEixir(void)
{
    SSD1306_Write2Lines_PrepareScreen( 0u, 20u, "Guardando",     &Font_11x18,
                                       0u, 40u, "Ajustes...",    &Font_11x18 );
}

static inline void ValorGatell (uint32_t valorGatell)
{
    memset(   disp_sGatell, NULL_CHARACTER, sizeof(disp_sGatell) );
    //
    snprintf( disp_sGatell, sizeof(disp_sGatell), "%u", (unsigned int)mes_gatellFiltratFinal );
    //
    SSD1306_Write3Lines_PrepareScreen( 0u,  0u, "Valor",         &Font_11x18,
                                       0u, 20u, "Gatillo",       &Font_11x18,
                                       0u, 45u, disp_sGatell,    &Font_11x18 );
}

static inline void VoltatgeEixida (uint32_t voltajeEixida)
{
    memset(   disp_sVoltatge, NULL_CHARACTER, sizeof(disp_sVoltatge) );
    //
    snprintf( disp_sVoltatge, sizeof(disp_sVoltatge), "%u", (unsigned int)voltajeEixida/400 );
    //
    SSD1306_Write3Lines_PrepareScreen( 0u,  0u, "Voltaje",      &Font_11x18,
                                       0u, 20u, "Min Salida",   &Font_11x18,
                                       0u, 45u, disp_sVoltatge, &Font_11x18 );
}

static inline void ValorPunts (uint32_t valorPuntLast, uint32_t valorPunt)
{
    memset( disp_sValorPuntLast, NULL_CHARACTER, sizeof(disp_sValorPuntLast) );
    memset( disp_sValorPunt,     NULL_CHARACTER, sizeof(disp_sValorPunt) );
    //

    if (valorPuntLast == 5) {
    	SSD1306_Write1Line_PrepareScreen( 0u,  20u, "Antes:Ral-1",      &Font_11x18);
    } else if (valorPuntLast == 6) {
   	    SSD1306_Write1Line_PrepareScreen( 0u,  20u, "Antes:Ral-2",      &Font_11x18);
    } else {
    	snprintf( disp_sValorPuntLast, sizeof(disp_sValorPuntLast), "Antes:  %u", (unsigned int)valorPuntLast );
    	SSD1306_Write1Line_PrepareScreen( 0u, 20u, disp_sValorPuntLast, &Font_11x18 );
    }

    if (valorPunt == 5) {
    	SSD1306_Write1Line_PrepareScreen( 0u,  40u, "Nuevo:Ral-1",      &Font_11x18);
    } else if (valorPunt == 6) {
    	SSD1306_Write1Line_PrepareScreen( 0u,  40u, "Nuevo:Ral-2",      &Font_11x18);
    } else {
    	snprintf( disp_sValorPunt,     sizeof(disp_sValorPunt),     "Nuevo:  %u", (unsigned int)valorPunt );
    	SSD1306_Write1Line_PrepareScreen( 0u, 40u, disp_sValorPunt, &Font_11x18 );
    }
    //
}
