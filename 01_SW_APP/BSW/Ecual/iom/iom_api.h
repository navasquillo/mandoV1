/* Author:   Sergio Martinez Porras
 * Date:     20/05/2023
 */

#ifndef IOM_API_H
#define IOM_API_H

    #define IOM_MAJOR_VERSION       1
    #define IOM_MINOR_VERSION       1
    #define IOM_PATCH_VERSION       4


    /* Include's -----------------------------------------------------------------*/
        #include "iom_cfg.h"

    /* Public Defines ------------------------------------------------------------*/
        #define IOM_HIGH                            (1u)
        #define IOM_LOW                             (0u)
        //
        #define IOM_LED_PC13_ON                     (0u)
        #define IOM_LED_PC13_OFF                    (1u)


    /* Enumerates / Structures ---------------------------------------------------*/

        typedef enum {
            E_IOM__DI_BUTTON_1,
            E_IOM__DI_BUTTON_2,
            //
            E_IOM__DI_SWITCH_1,
            //
            E_IOM__DI_IS_ARC_DRIVER,
            //
            E_IOM_TOTAL_DI_SIGNALS
        } E_IOM_DigitalInput;

        typedef enum {
            E_IOM__DO_PC13_LED,
            //
            E_IOM__DO_ARC_CHANGE,
            //
            E_IOM__DO_SW_TEST_01,
            E_IOM__DO_SW_TEST_02,
            //
            E_IOM_TOTAL_DO_SIGNALS
        } E_IOM_DigitalOutput;


    /* Public functions ----------------------------------------------------------*/

        /* Init actions */
        void IOM_Init(void);
        void IOM_DeInit(void);

        /* Periodic IOM tasks */

        /* Inputs functions */
        #define IOM_ReadInput__DI_BUTTON_1()                ( HAL_GPIO_ReadPin( IOM_PIN_INPUT_BUTTON_1 ) )
        #define IOM_ReadInput__DI_BUTTON_2()                ( HAL_GPIO_ReadPin( IOM_PIN_INPUT_BUTTON_2 ) )
        //
        #define IOM_ReadInput__DI_SWITCH_1()                ( HAL_GPIO_ReadPin( IOM_PIN_INPUT_SWITCH_1 ) )
        //
        unsigned char IOM__IsConnected_ARC_DRIVER(void);

        /* Outputs functions */
        #define IOM_SetOutput__DO_PC13_LED(out_value)       ( HAL_GPIO_WritePin( IOM_PIN_OUTPUT_PC13_LED, out_value ) )
        #define IOM_ToggleOutput__DO_PC13_LED()             ( HAL_GPIO_TogglePin( IOM_PIN_OUTPUT_PC13_LED ) )
        //
        #define IOM_SetOutput__DO_RELAY(out_value)          {}      // Sortida obsoleta
        //
        #define IOM_SetOutput__DO_ARC_CHANGE(out_value)     ( HAL_GPIO_WritePin( IOM_PIN_OUTPUT_ARC_CHANGE, out_value ) )
        //
        #define IOM_SetOutput__DO_SW_TEST_01(out_value)     ( HAL_GPIO_WritePin( IOM_PIN_OUTPUT_DO_SW_TEST_01, out_value ) )
        #define IOM_SetOutput__DO_SW_TEST_02(out_value)     ( HAL_GPIO_WritePin( IOM_PIN_OUTPUT_DO_SW_TEST_02, out_value ) )

        /* Reporting tasks */
        void IOM_ReportInputReadings_RAW(void);

#endif /* IOM_API_H */
