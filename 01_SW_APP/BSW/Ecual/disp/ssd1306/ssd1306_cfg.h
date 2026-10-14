/* Author:   Sergio Martinez Porras
 * Date:     17/09/2025
 */


/* Configuration Defines -------------------------------------------------------------------*/

    /* General Options */
        // I2C Address
            #define SSD1306_I2C_ADDR                    (0x78u)
            //#define SSD1306_I2C_ADDR                  (0x7Au)


        /* I2C Timeouts */
            #define ssd1306_I2C_TIMEOUT_INIT            (2000u)
            #define ssd1306_I2C_TIMEOUT_WRITE_MULTI     (30u)
            #define ssd1306_I2C_TIMEOUT_WRITE           (10u)


        /* SSD1306 settings */
            #define SSD1306_WIDTH                       (128u)   /* SSD1306 width in pixels */
            #define SSD1306_HEIGHT                      (64u)    /* SSD1306 LCD height in pixels */
