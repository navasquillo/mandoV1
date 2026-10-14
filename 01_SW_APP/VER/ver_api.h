/* Author:   Sergio Martinez Porras
 * Date:     29/08/2020
 */

#ifndef VER_API_H_
#define VER_API_H_

    #define VER_MAJOR_VERSION       1
    #define VER_MINOR_VERSION       2
    #define VER_PATCH_VERSION       4


    /* Include's -----------------------------------------------------------------*/


    /* Public Defines ------------------------------------------------------------*/
        // Definitions
        #define VERsion_SW_APP_MAJOR_VERSION             (1u)
        #define VERsion_SW_APP_MINOR_VERSION             (4u)
        #define VERsion_SW_APP_PATCH_VERSION             (1u)
        #define VER_SW_APP_NAME                          ("")                 // Max 15 characters
        //
        #define VER_PRODUCT_NAME                         ("Mando Mana Slot")  // Max 31 characters
        #define VER_PRODUCT_CODE                         (10u)

        // String Data lengths
        #define VER__PRODUCT_NAME__MAX_LENGTH            (32u)  // 31 characters + NULL_CHARACTER
        #define VER__PRODUCT_SERIAL_NUMBER__MAX_LENGTH   (14u)  // 13 characters + NULL_CHARACTER
        #define VER__SW_APP_VERSION_NAME__MAX_LENGTH     (29u)  // 28 characters + NULL_CHARACTER

    /* Enumerates / Structures ---------------------------------------------------*/


    /* Public functions ----------------------------------------------------------*/

        /* Init functions */
        void VER_Init(void);
        void VER_PostInit(void);

#endif /* VER_API_H_ */
