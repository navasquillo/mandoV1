/* Author:   Sergio Martinez Porras
 * Date:     20/05/2023
 */


/* Includes --------------------------------------------------------------------------------*/
    #include "main.h"        // Needed for pinout names (from ioc file)


/* Configuration Defines -------------------------------------------------------------------*/

    /* Pinout Digital Inputs */
        #define IOM_PIN_INPUT_BUTTON_1              DI_BUTTON_1_GPIO_Port,      DI_BUTTON_1_Pin
        #define IOM_PIN_INPUT_BUTTON_2              DI_BUTTON_2_GPIO_Port,      DI_BUTTON_2_Pin
        #define IOM_PIN_INPUT_SWITCH_1              DI_SWITCH_1_GPIO_Port,      DI_SWITCH_1_Pin
        //
        #define IOM_PIN_INPUT_IS_ARC_DRIVER         DI_IS_ARC_DRIVER_GPIO_Port, DI_IS_ARC_DRIVER_Pin

    /* Pinout Digital Outputs */
        #define IOM_PIN_OUTPUT_PC13_LED             DO_PC13_LED_GPIO_Port,      DO_PC13_LED_Pin
        //
        #define IOM_PIN_OUTPUT_ARC_CHANGE           DO_ARC_CHANGE_GPIO_Port,    DO_ARC_CHANGE_Pin
        //
        #define IOM_PIN_OUTPUT_DO_SW_TEST_01        DO_SW_TEST_01_GPIO_Port,    DO_SW_TEST_01_Pin
        #define IOM_PIN_OUTPUT_DO_SW_TEST_02        DO_SW_TEST_02_GPIO_Port,    DO_SW_TEST_02_Pin

    /* Comm */
        #define iom_MsgTX_length                    (80u)
