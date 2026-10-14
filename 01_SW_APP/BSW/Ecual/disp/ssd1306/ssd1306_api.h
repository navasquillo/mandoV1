/* Author:   Sergio Martinez Porras
 * Date:     17/09/2025
 */

#ifndef SSD1306_API_H_
#define SSD1306_API_H_

    #define SSD1306_MAJOR_VERSION       1
    #define SSD1306_MINOR_VERSION       2
    #define SSD1306_PATCH_VERSION       4


    /* Include's -----------------------------------------------------------------*/
        #include "libTypes_api.h"
        //
        #include "fonts.h"

    /* Public Defines ------------------------------------------------------------*/


    /* Enumerates / Structures ---------------------------------------------------*/
        /* Enumerates */
        typedef enum {
            E_LCD_NOT_DETECTED,
            E_LCD_DETECTED
        } E_LcdInitDetection;

        typedef enum {
            SSD1306_COLOR_BLACK,   /*!< Black color, no pixel */
            SSD1306_COLOR_WHITE    /*!< Pixel is set. Color depends on LCD */
        } SSD1306_COLOR_t;

        typedef enum {
            E_SSD1306_UPDATE_BLOCK1_CMD,
            E_SSD1306_UPDATE_BLOCK1_DATA,
            E_SSD1306_UPDATE_BLOCK2_CMD,
            E_SSD1306_UPDATE_BLOCK2_DATA,
            E_SSD1306_UPDATE_BLOCK3_CMD,
            E_SSD1306_UPDATE_BLOCK3_DATA,
            E_SSD1306_UPDATE_BLOCK4_CMD,
            E_SSD1306_UPDATE_BLOCK4_DATA,
            E_SSD1306_UPDATE_BLOCK5_CMD,
            E_SSD1306_UPDATE_BLOCK5_DATA,
            E_SSD1306_UPDATE_BLOCK6_CMD,
            E_SSD1306_UPDATE_BLOCK6_DATA,
            E_SSD1306_UPDATE_BLOCK7_CMD,
            E_SSD1306_UPDATE_BLOCK7_DATA,
            E_SSD1306_UPDATE_BLOCK8_CMD,
            E_SSD1306_UPDATE_BLOCK8_DATA,
            E_SSD1306_READY_TO_UPDATE,
            E_SSD1306_NOT_POSSIBLE_TO_UPDATE
        } E_SSD1306_UpdateScreenStatus;

        /* Structures */
        typedef struct {
            uint16_t                     CurrentX;
            uint16_t                     CurrentY;
            uint8_t                      Inverted;
            E_LcdInitDetection           LcdDetected;
            //
            E_SSD1306_UpdateScreenStatus UpdateScreenStatus;
            uint8_t                      UpdateScreenBlock;
            uint8_t                      UpdateScreenCmdType;
        } SSD1306_t;


    /* Public functions ----------------------------------------------------------*/

        /* Init actions */

        /**
         * @brief  Initializes SSD1306 LCD
         * @param  None
         * @retval Initialization status:
         *           - 0: LCD was not detected on I2C port
         *           - 1: LCD initialized OK and ready to use
         */
        E_LcdInitDetection SSD1306_Init(void);

        /**
         * @brief  SSD1306 LCD Detection Status
         * @param  None
         * @retval Initialization status:
         *           - 0: LCD was not detected on I2C port
         *           - 1: LCD initialized OK and ready to use
         */
        E_LcdInitDetection SSD1306_IsLcdDetected(void);


        /* Other Tasks */

        /**
         * @brief  Updates buffer from internal RAM to LCD
         * @note   This function must be called each time you do some changes to LCD, to update buffer from RAM to LCD
         * @param  None
         * @retval None
         */
        void SSD1306_UpdateScreen(void);

        void SSD1306_UpdateScreenDMA_Trigger(void);
        void SSD1306_UpdateScreenDMA_Step(void);
        E_SSD1306_UpdateScreenStatus SSD1306_UpdateScreenDMA_Status(void);

        /**
         * @brief  Toggles pixels invertion inside internal RAM
         * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
         * @param  None
         * @retval None
         */
        void SSD1306_ToggleInvert(void);

        /**
         * @brief  Draws pixel at desired location
         * @note   @ref SSD1306_UpdateScreen() must called after that in order to see updated LCD screen
         * @param  x: X location. This parameter can be a value between 0 and SSD1306_WIDTH - 1
         * @param  y: Y location. This parameter can be a value between 0 and SSD1306_HEIGHT - 1
         * @param  color: Color to be used for screen fill. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
         * @retval None
         */
        void SSD1306_DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color);
        void SSD1306_DrawPixel_White(uint16_t x, uint16_t y);
        void SSD1306_DrawPixel_Black(uint16_t x, uint16_t y);

        /**
         * @brief  Sets cursor pointer to desired location for strings
         * @param  x: X location. This parameter can be a value between 0 and SSD1306_WIDTH - 1
         * @param  y: Y location. This parameter can be a value between 0 and SSD1306_HEIGHT - 1
         * @retval None
         */
        void SSD1306_GotoXY(uint16_t x, uint16_t y);

        /**
         * @brief  Sets cursor pointer to desired location for strings
         * @param  line1_x: X location. This parameter can be a value between 0 and SSD1306_WIDTH - 1
         * @param  line1_y: Y location. This parameter can be a value between 0 and SSD1306_HEIGHT - 1
         * @param  *line1_str: String to be written
         * @param  *line1_Font: Pointer to @ref FontDef_t structure with used font
         * @retval None
         */
        void SSD1306_Write1Line_PrepareScreen( uint16_t line1_x, uint16_t line1_y, char* line1_str, FontDef_t* line1_Font );

        /**
         * @brief  Sets cursor pointer to desired location for strings
         * @param  line1_x: X location. This parameter can be a value between 0 and SSD1306_WIDTH - 1
         * @param  line1_y: Y location. This parameter can be a value between 0 and SSD1306_HEIGHT - 1
         * @param  *line1_str: String to be written
         * @param  *line1_Font: Pointer to @ref FontDef_t structure with used font
         * @param  line2_x: X location. This parameter can be a value between 0 and SSD1306_WIDTH - 1
         * @param  line2_y: Y location. This parameter can be a value between 0 and SSD1306_HEIGHT - 1
         * @param  *line2_str: String to be written
         * @param  *line2_Font: Pointer to @ref FontDef_t structure with used font
         * @retval None
         */
        void SSD1306_Write2Lines_PrepareScreen( uint16_t line1_x, uint16_t line1_y, char* line1_str, FontDef_t* line1_Font,
                                               uint16_t line2_x, uint16_t line2_y, char* line2_str, FontDef_t* line2_Font );

        /**
         * @brief  Sets cursor pointer to desired location for strings
         * @param  line1_x: X location. This parameter can be a value between 0 and SSD1306_WIDTH - 1
         * @param  line1_y: Y location. This parameter can be a value between 0 and SSD1306_HEIGHT - 1
         * @param  *line1_str: String to be written
         * @param  *line1_Font: Pointer to @ref FontDef_t structure with used font
         * @param  line2_x: X location. This parameter can be a value between 0 and SSD1306_WIDTH - 1
         * @param  line2_y: Y location. This parameter can be a value between 0 and SSD1306_HEIGHT - 1
         * @param  *line2_str: String to be written
         * @param  *line2_Font: Pointer to @ref FontDef_t structure with used font
         * @param  line3_x: X location. This parameter can be a value between 0 and SSD1306_WIDTH - 1
         * @param  line3_y: Y location. This parameter can be a value between 0 and SSD1306_HEIGHT - 1
         * @param  *line3_str: String to be written
         * @param  *line3_Font: Pointer to @ref FontDef_t structure with used font
         * @retval None
         */
        void SSD1306_Write3Lines_PrepareScreen( uint16_t line1_x, uint16_t line1_y, char* line1_str, FontDef_t* line1_Font,
                                               uint16_t line2_x, uint16_t line2_y, char* line2_str, FontDef_t* line2_Font,
                                               uint16_t line3_x, uint16_t line3_y, char* line3_str, FontDef_t* line3_Font );

        /**
         * @brief  Sets cursor pointer to desired location for strings
         * @param  line1_x: X location. This parameter can be a value between 0 and SSD1306_WIDTH - 1
         * @param  line1_y: Y location. This parameter can be a value between 0 and SSD1306_HEIGHT - 1
         * @param  *line1_str: String to be written
         * @param  *line1_Font: Pointer to @ref FontDef_t structure with used font
         * @param  line2_x: X location. This parameter can be a value between 0 and SSD1306_WIDTH - 1
         * @param  line2_y: Y location. This parameter can be a value between 0 and SSD1306_HEIGHT - 1
         * @param  *line2_str: String to be written
         * @param  *line2_Font: Pointer to @ref FontDef_t structure with used font
         * @param  line3_x: X location. This parameter can be a value between 0 and SSD1306_WIDTH - 1
         * @param  line3_y: Y location. This parameter can be a value between 0 and SSD1306_HEIGHT - 1
         * @param  *line3_str: String to be written
         * @param  *line3_Font: Pointer to @ref FontDef_t structure with used font
         * @param  line4_x: X location. This parameter can be a value between 0 and SSD1306_WIDTH - 1
         * @param  line4_y: Y location. This parameter can be a value between 0 and SSD1306_HEIGHT - 1
         * @param  *line4_str: String to be written
         * @param  *line4_Font: Pointer to @ref FontDef_t structure with used font
         * @retval None
         */
        void SSD1306_Write4Lines_PrepareScreen( uint16_t line1_x, uint16_t line1_y, char* line1_str, FontDef_t* line1_Font,
                                               uint16_t line2_x, uint16_t line2_y, char* line2_str, FontDef_t* line2_Font,
                                               uint16_t line3_x, uint16_t line3_y, char* line3_str, FontDef_t* line3_Font,
                                               uint16_t line4_x, uint16_t line4_y, char* line4_str, FontDef_t* line4_Font );

        /**
         * @brief  Sets cursor pointer to desired location for strings
         * @param  line1_x: X location. This parameter can be a value between 0 and SSD1306_WIDTH - 1
         * @param  line1_y: Y location. This parameter can be a value between 0 and SSD1306_HEIGHT - 1
         * @param  *line1_str: String to be written
         * @param  *line1_Font: Pointer to @ref FontDef_t structure with used font
         * @param  line2_x: X location. This parameter can be a value between 0 and SSD1306_WIDTH - 1
         * @param  line2_y: Y location. This parameter can be a value between 0 and SSD1306_HEIGHT - 1
         * @param  *line2_str: String to be written
         * @param  *line2_Font: Pointer to @ref FontDef_t structure with used font
         * @param  line3_x: X location. This parameter can be a value between 0 and SSD1306_WIDTH - 1
         * @param  line3_y: Y location. This parameter can be a value between 0 and SSD1306_HEIGHT - 1
         * @param  *line3_str: String to be written
         * @param  *line3_Font: Pointer to @ref FontDef_t structure with used font
         * @param  line4_x: X location. This parameter can be a value between 0 and SSD1306_WIDTH - 1
         * @param  line4_y: Y location. This parameter can be a value between 0 and SSD1306_HEIGHT - 1
         * @param  *line4_str: String to be written
         * @param  *line4_Font: Pointer to @ref FontDef_t structure with used font
         * @param  line5_x: X location. This parameter can be a value between 0 and SSD1306_WIDTH - 1
         * @param  line5_y: Y location. This parameter can be a value between 0 and SSD1306_HEIGHT - 1
         * @param  *line5_str: String to be written
         * @param  *line5_Font: Pointer to @ref FontDef_t structure with used font
         * @retval None
         */
        void SSD1306_Write5Lines_PrepareScreen( uint16_t line1_x, uint16_t line1_y, char* line1_str, FontDef_t* line1_Font,
                                               uint16_t line2_x, uint16_t line2_y, char* line2_str, FontDef_t* line2_Font,
                                               uint16_t line3_x, uint16_t line3_y, char* line3_str, FontDef_t* line3_Font,
                                               uint16_t line4_x, uint16_t line4_y, char* line4_str, FontDef_t* line4_Font,
                                               uint16_t line5_x, uint16_t line5_y, char* line5_str, FontDef_t* line5_Font );


        /**
         * @brief  Puts string to internal RAM
         * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
         * @param  *str: String to be written
         * @param  *Font: Pointer to @ref FontDef_t structure with used font
         * @param  color: Color used for drawing. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
         * @retval Zero on success or character value when function failed
         */
        char SSD1306_Puts(char* str, FontDef_t* Font, SSD1306_COLOR_t color);

        /**
         * @brief  Draws rectangle on LCD
         * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
         * @param  x: Top left X start point. Valid input is 0 to SSD1306_WIDTH - 1
         * @param  y: Top left Y start point. Valid input is 0 to SSD1306_HEIGHT - 1
         * @param  w: Rectangle width in units of pixels
         * @param  h: Rectangle height in units of pixels
         * @param  c: Color to be used. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
         * @retval None
         */
        void SSD1306_DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c);

        /**
         * @brief  Draws filled rectangle on LCD
         * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
         * @param  x: Top left X start point. Valid input is 0 to SSD1306_WIDTH - 1
         * @param  y: Top left Y start point. Valid input is 0 to SSD1306_HEIGHT - 1
         * @param  w: Rectangle width in units of pixels
         * @param  h: Rectangle height in units of pixels
         * @param  c: Color to be used. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
         * @retval None
         */
        void SSD1306_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c);

        /**
         * @brief  Draws triangle on LCD
         * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
         * @param  x1: First coordinate X location. Valid input is 0 to SSD1306_WIDTH - 1
         * @param  y1: First coordinate Y location. Valid input is 0 to SSD1306_HEIGHT - 1
         * @param  x2: Second coordinate X location. Valid input is 0 to SSD1306_WIDTH - 1
         * @param  y2: Second coordinate Y location. Valid input is 0 to SSD1306_HEIGHT - 1
         * @param  x3: Third coordinate X location. Valid input is 0 to SSD1306_WIDTH - 1
         * @param  y3: Third coordinate Y location. Valid input is 0 to SSD1306_HEIGHT - 1
         * @param  c: Color to be used. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
         * @retval None
         */
        void SSD1306_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, SSD1306_COLOR_t color);

        /**
         * @brief  Draws circle to STM buffer
         * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
         * @param  x: X location for center of circle. Valid input is 0 to SSD1306_WIDTH - 1
         * @param  y: Y location for center of circle. Valid input is 0 to SSD1306_HEIGHT - 1
         * @param  r: Circle radius in units of pixels
         * @param  c: Color to be used. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
         * @retval None
         */
        void SSD1306_DrawCircle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c);

        /**
         * @brief  Draws filled circle to STM buffer
         * @note   @ref SSD1306_UpdateScreen() must be called after that in order to see updated LCD screen
         * @param  x: X location for center of circle. Valid input is 0 to SSD1306_WIDTH - 1
         * @param  y: Y location for center of circle. Valid input is 0 to SSD1306_HEIGHT - 1
         * @param  r: Circle radius in units of pixels
         * @param  c: Color to be used. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
         * @retval None
         */
        void SSD1306_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c);

        /**
         * @brief  Draws the Bitmap
         * @param  X:  X location to start the Drawing
         * @param  Y:  Y location to start the Drawing
         * @param  *bitmap : Pointer to the bitmap
         * @param  W : width of the image
         * @param  H : Height of the image
         * @param  color : 1-> white/blue, 0-> black
         */
        void SSD1306_DrawBitmap(int16_t x, int16_t y, const unsigned char* bitmap, int16_t w, int16_t h, uint16_t color);

        // scroll the screen for fixed rows
        void SSD1306_ScrollRight(uint8_t start_row, uint8_t end_row);
        void SSD1306_ScrollLeft(uint8_t start_row, uint8_t end_row);
        void SSD1306_Scrolldiagright(uint8_t start_row, uint8_t end_row);
        void SSD1306_Scrolldiagleft(uint8_t start_row, uint8_t end_row);
        void SSD1306_Stopscroll(void);

        // inverts the display i = 1->inverted, i = 0->normal
        void SSD1306_InvertDisplay (int i);

        // clear the display
        void SSD1306_Clear (void);

#endif /* SSD1306_API_H_ */
