/* Author:   Sergio Martinez Porras
 * Date:     29/08/2020
 */

#ifndef DATAFORMAT_API_H
#define DATAFORMAT_API_H


    #define DATAFORMAT_MAJOR_VERSION        1
    #define DATAFORMAT_MINOR_VERSION        0
    #define DATAFORMAT_PATCH_VERSION        3


    /* Public Defines ------------------------------------------------------------*/


    /* Enumerates ----------------------------------------------------------------*/


    /* Public functions/macros ---------------------------------------------------*/


        /* ***** CONVERSIONS ***** */
        // Concatenate 4 variables of 8 bits into a variable of 32 bits
        #define lib__Convert_4bytes_into_32bitVar( byte_3, byte_2, byte_1, byte_0 )     (T_u32)( ((byte_3 & 0xFFu) << 24u) | ((byte_2 & 0xFFu) << 16u) | ((byte_1 & 0xFFu) << 8u) | (byte_0 & 0xFFu) )

        // Concatenate 3 variables of 8 bits into a variable of 32 bits
        #define lib__Convert_3bytes_into_32bitVar( byte_2, byte_1, byte_0 )             (T_u32)( ((byte_2 & 0xFFu) << 16u) | ((byte_1 & 0xFFu) << 8u) | (byte_0 & 0xFFu) )

        // Obtain a 3 Decimal Digits number from 3 different ASCI numbers
        #define lib__Asci2Dec_3digits( cen, dec, uni, out ) { \
            out = 0u; \
            /**/ \
            if ( (cen >= 0x30u) && (cen <= 0x39u) ) {           /* Digit x100 */ \
                if ( (dec >= 0x30u) && (dec <= 0x39u) ) {       /* Digit  x10 */ \
                    if ( (uni >= 0x30u) && (uni <= 0x39u) ) {   /* Digit   x1 */ \
                        out  = (T_u16)( (T_u16)(cen - 0x30u)*(T_u16)100u ); \
                        out += (T_u16)( (T_u16)(dec - 0x30u)*(T_u16)10u ); \
                        out += (T_u16)(uni - 0x30u); \
                    } \
                } \
            } \
        }

        // Obtain a 8 HEX Digits number from 8 ASCI numbers
        #define lib__Asci2Hex_8digits( u10000000, u1000000, u100000, u10000, u1000, u100, u10, u1 )  ( ((u10000000 & 0x0Fu) << 28u) | ((u1000000 & 0x0Fu) << 24u) | ((u100000 & 0x0Fu) << 20u) | ((u10000 & 0x0Fu) << 16u) | ((u1000 & 0x0Fu) << 12u) | ((u100 & 0x0Fu) << 8u) | ((u10 & 0x0Fu) << 4u) | (u1 & 0x0Fu) )

        // Obtain a 7 HEX Digits number from 7 ASCI numbers
        #define lib__Asci2Hex_7digits( u1000000, u100000, u10000, u1000, u100, u10, u1 )             ( ((u1000000 & 0x0Fu) << 24u) | ((u100000 & 0x0Fu) << 20u) | ((u10000 & 0x0Fu) << 16u) | ((u1000 & 0x0Fu) << 12u) | ((u100 & 0x0Fu) << 8u) | ((u10 & 0x0Fu) << 4u) | (u1 & 0x0Fu) )

        // Obtain a 6 HEX Digits number from 6 ASCI numbers
        #define lib__Asci2Hex_6digits( u100000, u10000, u1000, u100, u10, u1 )                       ( ((u100000 & 0x0Fu) << 20u) | ((u10000 & 0x0Fu) << 16u) | ((u1000 & 0x0Fu) << 12u) | ((u100 & 0x0Fu) << 8u) | ((u10 & 0x0Fu) << 4u) | (u1 & 0x0Fu) )

        // Obtain a 4 HEX Digits number from 4 ASCI numbers
        #define lib__Asci2Hex_4digits( mil, cen, dec, uni )  ( ((mil & 0x0Fu) << 12u) | ((cen & 0x0Fu) << 8u) | ((dec & 0x0Fu) << 4u) | (uni & 0x0Fu) )

        // Obtain a 3 HEX Digits number from 3 ASCI numbers
        #define lib__Asci2Hex_3digits( cen, dec, uni )       ( ((cen & 0x0Fu) << 8u) | ((dec & 0x0Fu) << 4u) | (uni & 0x0Fu) )

        // Obtain a 2 HEX Digits number from 2 ASCI numbers
        #define lib__Asci2Hex_2digits( dec, uni )            ( ((dec & 0x0Fu) << 4u) | (uni & 0x0Fu) )

        // Obtain a 1 HEX Digits number from 1 ASCI numbers
        #define lib__Asci2Hex_1digit( uni )                  (uni & 0x0Fu)

        // Obtain a BOOL variable from an ASCI number
        #define lib__Asci2Bool( asciValue )                  (asciValue & 0x0Fu)

        // Obtain a DEC number from 2 ASCI numbers
        T_u16 lib__Asci2Dec_2digits( T_u8 asci_dec, T_u8 asci_uni );

        // Obtain a DEC number from an Hex Char (received via USB/BT)
        #define lib__HexChar2Dec( dataIn_HexChar, dataOut ) { \
            if( (dataIn_HexChar >= 'A') && (dataIn_HexChar <= 'F') ) {  dataOut = dataIn_HexChar - 0x37u;  } \
            else {                                                      dataOut = dataIn_HexChar - 0x30u;  } \
            }


        /* ***** EXTRACT DATA ***** */
        // Obtain mil value from an HEX number
        #define lib__ObtainHexValue_mil( hexValue )          ((hexValue >> 12u) & 0x0Fu)

        // Obtain cen value from an HEX number
        #define lib__ObtainHexValue_cen( hexValue )          ((hexValue >> 8u) & 0x0Fu)

        // Obtain dec value from an HEX number
        #define lib__ObtainHexValue_dec( hexValue )          ((hexValue >> 4u) & 0x0Fu)

        // Obtain uni value from an HEX number
        #define lib__ObtainHexValue_uni( hexValue )          (hexValue & 0x0Fu)



        /* ***** CRC CUSTOM ***** */
        // Sum all the bytes (except the last byte) of the data_buffer provided and invert their value
        #define lib__CalculateCRC_custom( crc_result, data_buffer, length_data_buffer ) { \
            T_u16 ii = 0u; \
            T_u16 temp = 0u; \
            crc_result = 0u; \
            /**/ \
            /* Sum all the bytes except the last byte (it is reserved for the CRC_Custom value) */ \
            for (ii=0u; ii < (length_data_buffer - 1u); ii++) {  \
                temp += data_buffer[ii];\
            }\
            crc_result = (T_u16)(0xFFFFu - temp);   /* Invert value */  \
        }

#endif /* DATAFORMAT_API_H */
