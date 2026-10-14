/* Author:   Sergio Martinez Porras
 * Date:     29/08/2020
 */

#ifndef MCALM_API_H_
#define MCALM_API_H_

    #define MCALM_MAJOR_VERSION     1
    #define MCALM_MINOR_VERSION     2
    #define MCALM_PATCH_VERSION     6


    /* Include's -----------------------------------------------------------------*/
        #include "stm32f4xx_hal.h"
        #include "mcalm_cfg.h"
        #include "core_cm4.h"

    /* Public Defines ------------------------------------------------------------*/


    /* Enumerates / Structures ---------------------------------------------------*/

        /* Enumerates */
        typedef enum {
            E_MCALM__NO_reset                    = 0u,
            E_MCALM__LSI_on_reset                = 1u,
            E_MCALM__LSI_ready_reset             = 2u,
            E_MCALM__RMVF_reset                  = 3u,
            E_MCALM__BOR_reset                   = 4u,
            E_MCALM__BUTTON_RST_BOARD_reset      = 5u,
            E_MCALM__POR_reset                   = 6u,
            E_MCALM__SW_reset                    = 7u,
            E_MCALM__Independent_Watchdog_reset  = 8u,
            E_MCALM__Window_Watchdog_reset       = 9u,
            E_MCALM__LowPower_reset              = 10u
        }E_MCALM__ResetReason;

        typedef enum {
            E_MCALM__OTP_Word00__ProductSerialNumber = 0u,
            E_MCALM__OTP_Word01                      = 1u,
            E_MCALM__OTP_Word02                      = 2u,
            E_MCALM__OTP_Word03                      = 3u,
            E_MCALM__OTP_Word04                      = 4u,
            E_MCALM__OTP_Word05                      = 5u,
            E_MCALM__OTP_Word06                      = 6u,
            E_MCALM__OTP_Word07                      = 7u,
            E_MCALM__OTP_Word08                      = 8u,
            E_MCALM__OTP_Word09                      = 9u,
            E_MCALM__OTP_Word10                      = 10u,
            E_MCALM__OTP_Word11                      = 11u,
            E_MCALM__OTP_Word12                      = 12u,
            E_MCALM__OTP_Word13                      = 13u,
            E_MCALM__OTP_Word14                      = 14u,
            E_MCALM__OTP_Word15                      = 15u,
            //
            E_MCALM__OTP_WordsNumber                 = 16u
        }E_MCALM__OTP_Word_ID;


    /* Public functions ----------------------------------------------------------*/

        /* Init actions */
        void MCALM_PeripheralsInit(void);
        void MCALM_PostInit(void);

        /* Resets */
        void MCALM_ResetSW(void);
        E_MCALM__ResetReason MCALM_GetLastResetReason(void);
        void MCALM_ReportResetsLog(void);

        /* Interrupts */
        #define MCALM_EnableInterrupt(IRQn)         (HAL_NVIC_EnableIRQ( (IRQn_Type)IRQn ) )     /* See file "stm32f401x6.h for IRQn numbers */
        #define MCALM_DisableInterrupt(IRQn)        (HAL_NVIC_DisableIRQ( (IRQn_Type)IRQn ) )    /* See file "stm32f401x6.h for IRQn numbers */

        /* OneTimeProgramming */
        uint32_t MCALM_OTP_ReadWord(E_MCALM__OTP_Word_ID word_ID );

        /* Read Memory */
        #define MCALM_MEMORY_READ8(address)          (*(volatile uint8_t *)(address))
        #define MCALM_MEMORY_READ16(address)         (*(volatile uint16_t *)(address))
        #define MCALM_MEMORY_READ32(address)         (*(volatile uint32_t *)(address))

        /* Flash */
        uint8_t MCALM_IsFlashBusy(void);

#endif /* MCALM_API_H_ */
