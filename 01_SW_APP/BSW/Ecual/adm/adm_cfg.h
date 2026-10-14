/* Author:   Sergio Martinez Porras
 * Date:     14/11/2020
 */


/* Configuration Defines -------------------------------------------------------------------*/

    /* Compilation defines */
        //#define ADM_TEST_FUNCTIONS_ENABLED


    /* General Options */
        #define adm_ADC_MODULE                              hadc1
        #define adm_DMA_MODULE                              hdma_adc1
        //
        #define adm_VADC_MAX_mV                             (3300u)
        #define adm_MAX_VALUE_mV                            (adm_VADC_MAX_mV)
        //
        #define adm_ADC_COUNTS_MAX_10bits                   (1023u)    /* 10 bits ADC --> 2^10-1 = adcCounts_max */
        #define adm_ADC_COUNTS_MAX_12bits                   (4095u)    /* 12 bits ADC --> 2^12-1 = adcCounts_max */
        #define adm_MAX_VALUE_counts                        adm_ADC_COUNTS_MAX_12bits
        //
        #define adm_DIODE_1N4004_vForward_mV                (700u)     /*  700 mV */


    /* ADC Supply_12v_Protected - Conversion AdcCounts 2 mV */
        /* Vin = Vadc * ((Rp+Rs)/Rp) = Vadc * Gain_raw_mV
            -- Gain_raw_mV = adm_MAX_VALUE_mV / ((adm_MAX_VALUE_counts*Rp)/(Rp+Rs))
            -- Gain_raw_mV = 3300 / ((4095*2200)/(2200+10000)))
            -- Gain_raw_mV = 3300 / (9009000/12200)
            -- Gain_raw_mV = 40260000 / 9009000          = 4,4688644688644688644688644688645
            -- Gain_raw_mV = 40260 / 9009                = 4,4688644688644688644688644688645
            -- Gain_raw_mV = 36609 / 8192 = 36609 >> 13u = 4,4688720703125  (less CPU Load)
           */
        #define adm_raw2mV_Supply12vProtected(adcCounts)    ( ((adcCounts*36609u) >> 13u) + adm_DIODE_1N4004_vForward_mV )


    /* Other */
