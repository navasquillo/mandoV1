/* Author:   Sergio Martinez Porras
 * Date:     03/10/2020
 */


/* Configuration Defines -------------------------------------------------------------------*/

    /* General Options */
        #define mcalm_NUMBER_RESETS_TO_STORE      (8u)

    /* Clock Initialization */
        #define mcalm_DELAY_ms_BEFORE_START_HSE   (10u)

    /* System Frequencies */
        #define mcalm_APB1_PCLK1_FREQ             (42000000u)
        #define mcalm_APB2_PCLK2_FREQ             (84000000u)
        #define mcalm_APB1_TIMER_FREQ             (84000000u)
        #define mcalm_APB2_TIMER_FREQ             (84000000u)

    /* Timer Frequencies */
        #define mcalm_TIM1_FREQ                   (mcalm_APB2_TIMER_FREQ)
        #define mcalm_TIM2_FREQ                   (mcalm_APB1_TIMER_FREQ)
        #define mcalm_TIM3_FREQ                   (mcalm_APB1_TIMER_FREQ)
        #define mcalm_TIM4_FREQ                   (mcalm_APB1_TIMER_FREQ)
        #define mcalm_TIM5_FREQ                   (mcalm_APB1_TIMER_FREQ)
        #define mcalm_TIM9_FREQ                   (mcalm_APB2_TIMER_FREQ)
        #define mcalm_TIM10_FREQ                  (mcalm_APB2_TIMER_FREQ)
        #define mcalm_TIM11_FREQ                  (mcalm_APB2_TIMER_FREQ)
        //
        #define mcalm_TIM1_PRESCALER              (20u)
        #define mcalm_TIM2_PRESCALER              (0u)
        #define mcalm_TIM3_PRESCALER              (0u)
        #define mcalm_TIM4_PRESCALER              (0u)
        #define mcalm_TIM5_PRESCALER              (41u)
        #define mcalm_TIM9_PRESCALER              (0u)
        #define mcalm_TIM10_PRESCALER             (0u)
        #define mcalm_TIM11_PRESCALER             (0u)

    /* ADC frequencies */
        #define mcalm_ADC1_FREQ                   (mcalm_APB2_PCLK2_FREQ)

    /* WDG frequencies */
        #define mcalm_WWDG_FREQ                   (mcalm_APB1_PCLK1_FREQ)
        #define mcalm_IWDG_FREQ                   (mcalm_APB1_PCLK1_FREQ)

    /* I2C frequencies */
        #define mcalm_I2C1_FREQ                   (mcalm_APB1_PCLK1_FREQ)
        #define mcalm_I2C2_FREQ                   (mcalm_APB1_PCLK1_FREQ)
        #define mcalm_I2C3_FREQ                   (mcalm_APB1_PCLK1_FREQ)

    /* SPI frequencies */
        #define mcalm_SPI1_FREQ                   (mcalm_APB2_PCLK2_FREQ)
        #define mcalm_SPI2_FREQ                   (mcalm_APB1_PCLK1_FREQ)
        #define mcalm_SPI3_FREQ                   (mcalm_APB1_PCLK1_FREQ)

    /* USART frequencies */
        #define mcalm_USART1_FREQ                 (mcalm_APB2_PCLK2_FREQ)
        #define mcalm_USART2_FREQ                 (mcalm_APB1_PCLK1_FREQ)
        #define mcalm_USART6_FREQ                 (mcalm_APB2_PCLK2_FREQ)

    /* Comm */
        #define mcalm_MsgTX_length                (50u)
