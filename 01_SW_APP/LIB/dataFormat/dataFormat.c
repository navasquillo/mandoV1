
/* ################## Include's ####################### */

    /* Include types */
    #include "libTypes_api.h"

    /* Local prototypes */
    #include "dataFormat_api.h"

    /* Include external API's */


/* ################## Define's ######################### */


/* ################## Global variables ################# */


/* ################## Local functions / Macros ######### */



//#####################################################
//#####################  SW Code  #####################
//#####################################################

T_u16 lib__Asci2Dec_2digits( T_u8 asci_dec, T_u8 asci_uni ) {
    T_u16 data, outValue;
    //
    outValue = asci_uni - 0x30u;
    if( asci_dec > 0x30u ) {
        data = (asci_dec - 0x30u) * 10u;
        outValue += data;
    }
    //
    return( outValue );
}
