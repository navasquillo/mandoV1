/* Author:   Sergio Martinez Porras
 * Date:     29/08/2020
 */

#ifndef LIBTYPES_API_H
#define LIBTYPES_API_H


    #define LIBTYPES_MAJOR_VERSION      1
    #define LIBTYPES_MINOR_VERSION      1
    #define LIBTYPES_PATCH_VERSION      0


    /* Public Defines ------------------------------------------------------------*/

        #define _static static

        #if 1
            typedef unsigned char       T_bit;
            typedef unsigned char       T_u8;   /* T_u8 variables will be read by the debugger with the ASCI code */
            typedef unsigned short int  T_u16;
            typedef unsigned int        T_u32;
            /**/
            typedef signed char         T_s8;
            typedef signed short int    T_s16;
            typedef signed int          T_s32;

        #else
            typedef unsigned int        T_bit;
            typedef unsigned int        T_u8;   /* T_u8 variables will be read by the debugger with the ASCI code */
            typedef unsigned int        T_u16;
            typedef unsigned int        T_u32;
            /**/
            typedef unsigned int        T_s8;
            typedef unsigned int        T_s16;
            typedef unsigned int        T_s32;
        #endif
        /**/
        typedef unsigned long long      T_u64;
        typedef long long               T_s64;
        typedef float                   T_f32;
        /**/
        #define FALSE                   (0u)
        #define TRUE                    (1u)
        /**/
        #define NULL_CHARACTER          ('\0')
        /**/
        #define ACTUATOR_OFF            FALSE
        #define ACTUATOR_ON             TRUE


        /* Limits for types */
        #define T_BIT_MIN               (FALSE)
        #define T_BIT_MAX               (TRUE)
        #define T_U8_MIN                ((T_u8)0u)
        #define T_U8_MAX                ((T_u8)255u)
        /**/
        #define T_U16_MIN               ((T_u16)0u)
        #define T_U16_MAX               ((T_u16)0xFFFFu)
        #define T_U32_MIN               ((T_u32)0u)
        #define T_U32_MAX               ((T_u32)0xFFFFFFFFu)
        #define T_U64_MIN               ((T_u64)0u)
        #define T_U64_MAX               ((T_u64)0xFFFFFFFFFFFFFFFFu)
        /**/
        #define T_S8_MIN                ((T_s8)-128)
        #define T_S8_MAX                ((T_s8)127)
        #define T_S16_MIN               ((T_s16)-32768)
        #define T_S16_MAX               ((T_s16)32767)
        #define T_S32_MIN               ((T_s32)-2147483648)
        #define T_S32_MAX               ((T_s32)2147483647)
        #define T_S64_MIN               ((T_s64)-9223372036854775808)
        #define T_S64_MAX               ((T_s64)9223372036854775807)

    /* Enumerates ----------------------------------------------------------------*/


    /* Public functions ----------------------------------------------------------*/



#endif /* LIBTYPES_API_H */
