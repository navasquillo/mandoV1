
/* ################## Include's ####################### */

    /* Include types */
    #include "libTypes_api.h"
    #include <stdio.h>
    #include <string.h>

    /* Include prototypes */
    #include "ver_api.h"

    /* Include external API's */
    #include "mcalm_api.h"


/* ################## Define's ######################### */
      #define VER_NULL_CHARACTER          ('\0')


/* ################## Global variables ################# */
      char ver_ProductName_DataTx[VER__PRODUCT_NAME__MAX_LENGTH];
      char ver_ProductSerialNumber_DataTx[VER__PRODUCT_SERIAL_NUMBER__MAX_LENGTH];
      char ver_SwAppVersionName_DataTx[VER__SW_APP_VERSION_NAME__MAX_LENGTH];


/* ################## Local functions / Macros ######### */
    /* Macros */

    /* Local functions */
      static inline void ver_Init__ProductName(void);
      static inline void ver_Init__ProductSerialNumber(void);
      //
      static inline void ver_Init__SW_APP_Version_Name(void);



//#####################################################
//#####################  SW Code  #####################
//#####################################################

/* ********************************* INIT ********************************* */
void VER_Init(void) {
    // 1) Buffer clearing
    memset( ver_ProductName_DataTx,          VER_NULL_CHARACTER,  VER__PRODUCT_NAME__MAX_LENGTH );
    memset( ver_ProductSerialNumber_DataTx,  VER_NULL_CHARACTER,  VER__PRODUCT_SERIAL_NUMBER__MAX_LENGTH );
    memset( ver_SwAppVersionName_DataTx,     VER_NULL_CHARACTER,  VER__SW_APP_VERSION_NAME__MAX_LENGTH );

    // 2) Buffer filling
    ver_Init__ProductName();
    ver_Init__ProductSerialNumber();
    ver_Init__SW_APP_Version_Name();
}


void VER_PostInit(void) {
    /* Nothing to do */
}



/* ********************************* OTHER FUNCTIONS ********************************* */
static inline void ver_Init__ProductName(void) {  // Provides a response in ASCII format
    //
    snprintf( ver_ProductName_DataTx, sizeof(ver_ProductName_DataTx), VER_PRODUCT_NAME );
}


static inline void ver_Init__ProductSerialNumber(void) {  // Provides a response in ASCII format
    //
    // 1) Get data
    uint32_t otp_word         = MCALM_OTP_ReadWord( E_MCALM__OTP_Word00__ProductSerialNumber );
    uint16_t data_OTP_Byte3_2 = (otp_word >> 8u) & 0xFFFFu;  // Byte 3+2 = Mando Number

    // 2) Generate full string
    snprintf( ver_ProductSerialNumber_DataTx, sizeof(ver_ProductSerialNumber_DataTx), "%02u-%05u", VER_PRODUCT_CODE, data_OTP_Byte3_2 );
}


static inline void ver_Init__SW_APP_Version_Name(void) {  // Provides a response in ASCII format
    //
    #ifdef DEBUG
        snprintf( ver_SwAppVersionName_DataTx, sizeof(ver_SwAppVersionName_DataTx), "v%u.%u.%uDBG-%s", VERsion_SW_APP_MAJOR_VERSION, VERsion_SW_APP_MINOR_VERSION, VERsion_SW_APP_PATCH_VERSION, VER_SW_APP_NAME );
    #else
        snprintf( ver_SwAppVersionName_DataTx, sizeof(ver_SwAppVersionName_DataTx), "v%u.%u.%u %s", VERsion_SW_APP_MAJOR_VERSION, VERsion_SW_APP_MINOR_VERSION, VERsion_SW_APP_PATCH_VERSION, VER_SW_APP_NAME );
    #endif
}
