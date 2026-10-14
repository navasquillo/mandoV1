/* Author:   Sergio Martinez Porras
 * Date:     03/10/2020
 */

#ifndef I2CM_API_H_
#define I2CM_API_H_

    #define I2CM_MAJOR_VERSION       1
    #define I2CM_MINOR_VERSION       3
    #define I2CM_PATCH_VERSION       0


    /* Include's -----------------------------------------------------------------*/


    /* Public Defines ------------------------------------------------------------*/


    /* Enumerates / Structures ---------------------------------------------------*/


    /* Public functions ----------------------------------------------------------*/

        /* Init actions */
        void I2CM_Init(void);
        void I2CM_PostInit(void);
        void I2CM_DeInit(void);

        /* Checks */
        T_bit I2CM_SSD1306_IsReadyForNewTransference(void);

#endif /* I2CM_API_H_ */
