
/* ################## Include's ####################### */

    /* Include types */
    #include "libTypes_api.h"
    //
    #include "stdio.h"
    #include "stdlib.h"
    #include "string.h"

    /* Local prototypes */
    #include "ssd1306_api.h"
    #include "ssd1306_cfg.h"

    /* Include external API's */
    #include "mcalm_api.h"
    #include "i2cm_cfg.h"
    #include "iom_api.h"
    //
    #include "ver_api.h"


/* ################## Define's ######################### */
    // SSD1306 Commands
    #define SSD1306_RIGHT_HORIZONTAL_SCROLL              0x26
    #define SSD1306_LEFT_HORIZONTAL_SCROLL               0x27
    #define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
    #define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  0x2A
    #define SSD1306_DEACTIVATE_SCROLL                    0x2E // Stop scroll
    #define SSD1306_ACTIVATE_SCROLL                      0x2F // Start scroll
    #define SSD1306_SET_VERTICAL_SCROLL_AREA             0xA3 // Set scroll range
    //
    #define SSD1306_NORMALDISPLAY                        0xA6
    #define SSD1306_INVERTDISPLAY                        0xA7

    // Other


/* ################## Global variables ################# */
    // External Variables
        extern I2C_HandleTypeDef i2cm_MODULE_DISPLAY;

    // Local Variables
        __attribute__((section(".Ram_SSD1306"))) SSD1306_t SSD1306;
        __attribute__((section(".Ram_SSD1306"))) uint8_t   ssd1306_CommandsList[30u];
        __attribute__((section(".Ram_SSD1306"))) uint8_t   ssd1306_Buffer[SSD1306_WIDTH * SSD1306_HEIGHT / 8];  /* SSD1306 data buffer */
        __attribute__((section(".Ram_SSD1306"))) uint8_t   ssd1306_dt_Write[2u];
        __attribute__((section(".Ram_SSD1306"))) uint8_t   ssd1306_dt_WriteMulti[SSD1306_WIDTH + 1u];


/* ################## Local functions / Macros ######### */
    // Macros
    #define ssd1306_WRITECOMMAND(command)       ssd1306_I2C_Write(SSD1306_I2C_ADDR, 0x00, (command))
    #define ssd1306_WRITEDATA(data)             ssd1306_I2C_Write(SSD1306_I2C_ADDR, 0x40, (data))
    #define ABS(x)                              ((x) > 0 ? (x) : -(x))


    // Local functions
    static inline __attribute__((always_inline)) void ssd1306_OFF(void);
    static inline __attribute__((always_inline)) void ssd1306_ON(void);

    static inline __attribute__((always_inline)) void ssd1306_GotoXY(uint16_t x, uint16_t y);

    static inline __attribute__((always_inline)) char ssd1306_Puts(char* str, FontDef_t* Font, SSD1306_COLOR_t color);

    /**
     * @brief  Puts character to internal RAM
     * @note   @ref ssd1306_UpdateScreen() must be called after that in order to see updated LCD screen
     * @param  ch: Character to be written
     * @param  *Font: Pointer to @ref FontDef_t structure with used font
     * @param  color: Color used for drawing. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
     * @retval Character written
     */
    static inline __attribute__((always_inline)) char ssd1306_Putc(char ch, FontDef_t* Font, SSD1306_COLOR_t color);

    /**
     * @brief  Draws pixel at desired location
     * @note   @ref ssd1306_UpdateScreen() must called after that in order to see updated LCD screen
     * @param  x: X location. This parameter can be a value between 0 and SSD1306_WIDTH - 1
     * @param  y: Y location. This parameter can be a value between 0 and SSD1306_HEIGHT - 1
     * @param  color: Color to be used for screen fill. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
     * @retval None
     */
    static inline __attribute__((always_inline)) void ssd1306_DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color);
    static inline __attribute__((always_inline)) void ssd1306_DrawPixel_White(uint16_t x, uint16_t y);
    static inline __attribute__((always_inline)) void ssd1306_DrawPixel_Black(uint16_t x, uint16_t y);

    /**
     * @brief  Draws line on LCD
     * @note   @ref ssd1306_UpdateScreen() must be called after that in order to see updated LCD screen
     * @param  x0: Line X start point. Valid input is 0 to SSD1306_WIDTH - 1
     * @param  y0: Line Y start point. Valid input is 0 to SSD1306_HEIGHT - 1
     * @param  x1: Line X end point. Valid input is 0 to SSD1306_WIDTH - 1
     * @param  y1: Line Y end point. Valid input is 0 to SSD1306_HEIGHT - 1
     * @param  c: Color to be used. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
     * @retval None
     */
    static inline __attribute__((always_inline)) void ssd1306_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, SSD1306_COLOR_t c);

    /**
     * @brief  Fills entire LCD with desired color
     * @note   @ref ssd1306_UpdateScreen() must be called after that in order to see updated LCD screen
     * @param  Color: Color to be used for screen fill. This parameter can be a value of @ref SSD1306_COLOR_t enumeration
     * @retval None
     */
    static inline __attribute__((always_inline)) void ssd1306_Fill(SSD1306_COLOR_t Color);

    /**
     * @brief  Updates buffer from internal RAM to LCD
     * @note   This function must be called each time you do some changes to LCD, to update buffer from RAM to LCD
     * @param  None
     * @retval None
     */
    static inline void ssd1306_UpdateScreen(void);

    /**
     * @brief  Writes multi bytes to slave
     * @param  *I2Cx: I2C used
     * @param  address: 7 bit slave address, left aligned, bits 7:1 are used, LSB bit is not used
     * @param  reg: register to write to
     * @param  *data: pointer to data array to write it to slave
     * @param  count: how many bytes will be written
     * @retval None
     */
    static inline __attribute__((always_inline)) void ssd1306_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t *data, uint16_t count);
    static inline __attribute__((always_inline)) void ssd1306_I2C_WriteMulti_DMA(uint8_t address, uint8_t reg, uint8_t *data, uint16_t count);

    /**
     * @brief  Writes single byte to slave
     * @param  *I2Cx: I2C used
     * @param  address: 7 bit slave address, left aligned, bits 7:1 are used, LSB bit is not used
     * @param  reg: register to write to
     * @param  data: data to be written
     * @retval None
     */
    static inline __attribute__((always_inline)) void ssd1306_I2C_Write(uint8_t address, uint8_t reg, uint8_t data);



//#####################################################
//#####################  SW Code  #####################
//#####################################################
void SSD1306_ScrollRight(uint8_t start_row, uint8_t end_row)
{
    /* Write multi command */
    ssd1306_CommandsList[0u] = SSD1306_RIGHT_HORIZONTAL_SCROLL; // send 0x26
    ssd1306_CommandsList[1u] = 0x00;                            // send dummy
    ssd1306_CommandsList[2u] = start_row;                       // start page address
    ssd1306_CommandsList[3u] = 0x00;                            // time interval 5 frames
    ssd1306_CommandsList[4u] = end_row;                         // end page address
    ssd1306_CommandsList[5u] = 0x00;                            // start page address
    ssd1306_CommandsList[6u] = 0xFF;                            // start page address
    ssd1306_CommandsList[7u] = SSD1306_ACTIVATE_SCROLL;         // start scroll
    //
    ssd1306_I2C_WriteMulti( SSD1306_I2C_ADDR, 0x00u, ssd1306_CommandsList, 8u );
}


void SSD1306_ScrollLeft(uint8_t start_row, uint8_t end_row)
{
    /* Write multi command */
    ssd1306_CommandsList[0u] = SSD1306_LEFT_HORIZONTAL_SCROLL;  // send 0x26
    ssd1306_CommandsList[1u] = 0x00;                            // send dummy
    ssd1306_CommandsList[2u] = start_row;                       // start page address
    ssd1306_CommandsList[3u] = 0x00;                            // time interval 5 frames
    ssd1306_CommandsList[4u] = end_row;                         // end page address
    ssd1306_CommandsList[5u] = 0x00;                            // start page address
    ssd1306_CommandsList[6u] = 0xFF;                            // start page address
    ssd1306_CommandsList[7u] = SSD1306_ACTIVATE_SCROLL;         // start scroll
    //
    ssd1306_I2C_WriteMulti( SSD1306_I2C_ADDR, 0x00u, ssd1306_CommandsList, 8u );
}


void SSD1306_Scrolldiagright(uint8_t start_row, uint8_t end_row)
{
    /* Write multi command */
    ssd1306_CommandsList[0u] = SSD1306_SET_VERTICAL_SCROLL_AREA;    // sect the area
    ssd1306_CommandsList[1u] = 0x00;                                // write dummy
    ssd1306_CommandsList[2u] = SSD1306_HEIGHT;
    //
    ssd1306_CommandsList[3u] = SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL;
    ssd1306_CommandsList[4u] = 0x00;
    ssd1306_CommandsList[5u] = start_row;
    ssd1306_CommandsList[6u] = 0x00;
    ssd1306_CommandsList[7u] = end_row;
    ssd1306_CommandsList[8u] = 0x01;
    ssd1306_CommandsList[9u] = SSD1306_ACTIVATE_SCROLL;
    //
    ssd1306_I2C_WriteMulti( SSD1306_I2C_ADDR, 0x00u, ssd1306_CommandsList, 10u );
}


void SSD1306_Scrolldiagleft(uint8_t start_row, uint8_t end_row)
{
    /* Write multi command */
    ssd1306_CommandsList[0u] = SSD1306_SET_VERTICAL_SCROLL_AREA;    // sect the area
    ssd1306_CommandsList[1u] = 0x00;                                // write dummy
    ssd1306_CommandsList[2u] = SSD1306_HEIGHT;
    //
    ssd1306_CommandsList[3u] = SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL;
    ssd1306_CommandsList[4u] = 0x00;
    ssd1306_CommandsList[5u] = start_row;
    ssd1306_CommandsList[6u] = 0x00;
    ssd1306_CommandsList[7u] = end_row;
    ssd1306_CommandsList[8u] = 0x01;
    ssd1306_CommandsList[9u] = SSD1306_ACTIVATE_SCROLL;
    //
    ssd1306_I2C_WriteMulti( SSD1306_I2C_ADDR, 0x00u, ssd1306_CommandsList, 10u );
}


void SSD1306_Stopscroll(void)
{
    ssd1306_WRITECOMMAND(SSD1306_DEACTIVATE_SCROLL);
}



void SSD1306_InvertDisplay (int i)
{
    if (i) {
        ssd1306_WRITECOMMAND (SSD1306_INVERTDISPLAY);
    } else {
        ssd1306_WRITECOMMAND (SSD1306_NORMALDISPLAY);
    }
}


void SSD1306_DrawBitmap(int16_t x, int16_t y, const unsigned char* bitmap, int16_t w, int16_t h, uint16_t color)
{

    int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t byte = 0;

    for(int16_t j=0; j<h; j++, y++)
    {
        for(int16_t i=0; i<w; i++)
        {
            if(i & 7)
            {
               byte <<= 1;
            }
            else
            {
               byte = (*(const unsigned char *)(&bitmap[j * byteWidth + i / 8]));
            }
            if(byte & 0x80) ssd1306_DrawPixel(x+i, y, color);
        }
    }
}



E_LcdInitDetection SSD1306_Init(void) {
    //
    // Check if LCD is connected to I2C and send SSD1306 Configuration and Clear Screen
    if (HAL_I2C_IsDeviceReady( &i2cm_MODULE_DISPLAY, SSD1306_I2C_ADDR, 1, ssd1306_I2C_TIMEOUT_INIT) == HAL_OK ) {
        // 1) Send SSD1306 Configuration
        ssd1306_CommandsList[0u]  = 0xAE;   // Turn OFF SSD1306 Screen
        ssd1306_CommandsList[1u]  = 0x20;   // Set Memory Addressing Mode
        ssd1306_CommandsList[2u]  = 0x10;   // 00,Horizontal Addressing Mode; 01,Vertical Addressing Mode; 10,Page Addressing Mode (RESET); 11,Invalid
        ssd1306_CommandsList[3u]  = 0xB0;   // Set Page Start Address for Page Addressing Mode,0-7
        ssd1306_CommandsList[4u]  = 0xC8;   // Set COM Output Scan Direction
        ssd1306_CommandsList[5u]  = 0x00;   // ---set low column address
        ssd1306_CommandsList[6u]  = 0x10;   // ---set high column address
        ssd1306_CommandsList[7u]  = 0x40;   // --set start line address
        ssd1306_CommandsList[8u]  = 0x81;   // --set contrast control register
        ssd1306_CommandsList[9u]  = 0xFF;   //
        ssd1306_CommandsList[10u] = 0xA1;   // --set segment re-map 0 to 127
        ssd1306_CommandsList[11u] = 0xA6;   // --set normal display
        ssd1306_CommandsList[12u] = 0xA8;   // --set multiplex ratio(1 to 64)
        ssd1306_CommandsList[13u] = 0x3F;   //
        ssd1306_CommandsList[14u] = 0xA4;   // 0xa4,Output follows RAM content; 0xa5,Output ignores RAM content
        ssd1306_CommandsList[15u] = 0xD3;   // -set display offset
        ssd1306_CommandsList[16u] = 0x00;   // -not offset
        ssd1306_CommandsList[17u] = 0xD5;   // --set display clock divide ratio/oscillator frequency
        ssd1306_CommandsList[18u] = 0xF0;   // --set divide ratio
        ssd1306_CommandsList[19u] = 0xD9;   // --set pre-charge period
        ssd1306_CommandsList[20u] = 0x22;   //
        ssd1306_CommandsList[21u] = 0xDA;   // --set com pins hardware configuration
        ssd1306_CommandsList[22u] = 0x12;
        ssd1306_CommandsList[23u] = 0xDB;   // --set vcomh
        ssd1306_CommandsList[24u] = 0x20;   // 0x20,0.77xVcc
        ssd1306_CommandsList[25u] = 0x8D;   // --set DC-DC enable
        ssd1306_CommandsList[26u] = 0x14;   //
        ssd1306_CommandsList[27u] = SSD1306_DEACTIVATE_SCROLL;
        ssd1306_CommandsList[28u] = 0xAF;   // Turn ON SSD1306 Screen
        //
        ssd1306_I2C_WriteMulti( SSD1306_I2C_ADDR, 0x00u, ssd1306_CommandsList, 29u );

        // 2) To load correctly the SSD1306 Configuration the MCU must wait a bit before send new things to the SSD1306.
        //    Instead of put a sw delay, this MCU wait will be done doing the SSD1306 swC Variables initialization.
        SSD1306.CurrentX            = 0u;
        SSD1306.CurrentY            = 0u;
        SSD1306.Inverted            = FALSE;
        SSD1306.LcdDetected         = E_LCD_DETECTED;
        SSD1306.UpdateScreenStatus  = E_SSD1306_READY_TO_UPDATE;
        SSD1306.UpdateScreenBlock   = 0u;
        SSD1306.UpdateScreenCmdType = 0u;

        // 3) After a wait time, Clear SSD1306 Screen
        SSD1306_Clear();
        #if (VER_PRODUCT_CODE != 10) && (VER_PRODUCT_CODE != 11)
            // For MandoSlot project, the following line will be avoided due to few ms later
            // the TaskPantalla updates the SSD1306 Screen and consequently it's not needed
            // to block the CPU 25 ms during the MCU Start-Up
            SSD1306_UpdateScreen();
        #endif

        // 5) Clear swC buffers
        memset( ssd1306_CommandsList,  0x00u, sizeof(ssd1306_CommandsList) );
        memset( ssd1306_dt_Write,      0x00u, sizeof(ssd1306_dt_Write) );
        memset( ssd1306_dt_WriteMulti, 0x00u, sizeof(ssd1306_dt_WriteMulti) );
    }
    else {
        SSD1306.LcdDetected         = E_LCD_NOT_DETECTED;
        SSD1306.UpdateScreenStatus  = E_SSD1306_NOT_POSSIBLE_TO_UPDATE;
    }
    return( SSD1306.LcdDetected );
}


E_LcdInitDetection SSD1306_IsLcdDetected(void) {
    return( (E_LcdInitDetection)SSD1306.LcdDetected );
}


void SSD1306_UpdateScreen(void) {
    ssd1306_UpdateScreen();
}

static inline void ssd1306_UpdateScreen(void) {
    //
    if( SSD1306.LcdDetected == E_LCD_DETECTED ) {
        for (uint8_t m = 0u; m < 8u; m++) {
            /* Write multi command */
            ssd1306_CommandsList[0u] = 0xB0u + m;
            ssd1306_CommandsList[1u] = 0x00u;
            ssd1306_CommandsList[2u] = 0x10u;
            ssd1306_I2C_WriteMulti( SSD1306_I2C_ADDR, 0x00u, ssd1306_CommandsList, 3u );

            /* Write multi data */
            ssd1306_I2C_WriteMulti( SSD1306_I2C_ADDR, 0x40u, &ssd1306_Buffer[SSD1306_WIDTH * m], SSD1306_WIDTH );
        }
    }
}

void SSD1306_UpdateScreenDMA_Trigger(void) {
    //
    if( SSD1306.LcdDetected == E_LCD_DETECTED ) {
        SSD1306.UpdateScreenStatus = E_SSD1306_UPDATE_BLOCK1_CMD;
        SSD1306_UpdateScreenDMA_Step();
    }
    else {
        SSD1306.UpdateScreenStatus = E_SSD1306_NOT_POSSIBLE_TO_UPDATE;
    }
}


void SSD1306_UpdateScreenDMA_Step(void) {  // ISR Callback
    //
    /*IOM_SetOutput__DO_SW_TEST_02( TRUE );*/  // Only for SW Testing

    if (SSD1306.UpdateScreenStatus <= E_SSD1306_UPDATE_BLOCK8_DATA) {
        SSD1306.UpdateScreenBlock   = SSD1306.UpdateScreenStatus >> 1u;     // Screen Block index
        SSD1306.UpdateScreenCmdType = SSD1306.UpdateScreenStatus & 0x01u;   // I2C Message type --> 0 = CMD, 1 = DATA
        //
        if( SSD1306.UpdateScreenCmdType == 0u ) {
            // CMD
            ssd1306_CommandsList[0u] = 0xB0u + SSD1306.UpdateScreenBlock;
            ssd1306_CommandsList[1u] = 0x00u;
            ssd1306_CommandsList[2u] = 0x10u;
            ssd1306_I2C_WriteMulti_DMA( SSD1306_I2C_ADDR, 0x00u, ssd1306_CommandsList, 3u );
        } else {
            // DATA
            ssd1306_I2C_WriteMulti_DMA( SSD1306_I2C_ADDR, 0x40u, &ssd1306_Buffer[SSD1306_WIDTH * SSD1306.UpdateScreenBlock], SSD1306_WIDTH );
        }

        // Next State
        if (SSD1306.UpdateScreenStatus < E_SSD1306_UPDATE_BLOCK8_DATA) {
            SSD1306.UpdateScreenStatus++;
        } else {
            SSD1306_Clear();  // Clear SSD1306 Buffer to be prepared for next Screen update
            SSD1306.UpdateScreenStatus = E_SSD1306_READY_TO_UPDATE;
        }

    } else if( SSD1306.UpdateScreenStatus != E_SSD1306_READY_TO_UPDATE ) {
        // Wrong State
        SSD1306.UpdateScreenStatus = E_SSD1306_NOT_POSSIBLE_TO_UPDATE;
    }

    /*IOM_SetOutput__DO_SW_TEST_02( FALSE );*/  // Only for SW Testing
}

E_SSD1306_UpdateScreenStatus SSD1306_UpdateScreenDMA_Status(void) {
    return( SSD1306.UpdateScreenStatus );
}


void SSD1306_ToggleInvert(void) {
    /* Toggle invert */
    SSD1306.Inverted = !SSD1306.Inverted;

    /* Do memory toggle */
    for (uint16_t i = 0u; i < sizeof(ssd1306_Buffer); i++) {
        ssd1306_Buffer[i] = ~ssd1306_Buffer[i];
    }
}

static inline __attribute__((always_inline)) void ssd1306_Fill(SSD1306_COLOR_t color) {
    /* Set memory */
    memset(ssd1306_Buffer, (color == SSD1306_COLOR_BLACK) ? 0x00u : 0xFFu, sizeof(ssd1306_Buffer));
}


void SSD1306_DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color) {
    ssd1306_DrawPixel( x, y, color );
}

static inline __attribute__((always_inline)) void ssd1306_DrawPixel(uint16_t x, uint16_t y, SSD1306_COLOR_t color) {
    if ( (x >= SSD1306_WIDTH) || (y >= SSD1306_HEIGHT) ) {
        return;  // Error
    }

    #if 0
    /* Check if pixels are inverted */
    if (SSD1306.Inverted) {
        color = (SSD1306_COLOR_t)!color;
    }
    #endif

    /* Set color */
    if (color == SSD1306_COLOR_WHITE) {
        ssd1306_Buffer[x + (y >> 3u) * SSD1306_WIDTH] |= 1 << (y % 8);
    } else {
        ssd1306_Buffer[x + (y >> 3u) * SSD1306_WIDTH] &= ~(1 << (y % 8));
    }
}

void SSD1306_DrawPixel_White(uint16_t x, uint16_t y) {
    ssd1306_DrawPixel_White(x, y);
}

static inline __attribute__((always_inline)) void ssd1306_DrawPixel_White(uint16_t x, uint16_t y) {
    ssd1306_Buffer[x + (y >> 3u) * SSD1306_WIDTH] |= 1 << (y % 8);
}

void SSD1306_DrawPixel_Black(uint16_t x, uint16_t y) {
    ssd1306_DrawPixel_Black(x, y);
}

static inline __attribute__((always_inline)) void ssd1306_DrawPixel_Black(uint16_t x, uint16_t y) {
    ssd1306_Buffer[x + (y >> 3u) * SSD1306_WIDTH] &= ~(1 << (y % 8));
}


void SSD1306_GotoXY(uint16_t x, uint16_t y) {
    ssd1306_GotoXY( x, y );
}

static inline __attribute__((always_inline)) void ssd1306_GotoXY(uint16_t x, uint16_t y) {
    /* Set write pointers */
    SSD1306.CurrentX = x;
    SSD1306.CurrentY = y;
}


static inline __attribute__((always_inline)) char ssd1306_Putc(char ch, FontDef_t* Font, SSD1306_COLOR_t color) {
    /* Check available space in LCD */
    if (
        SSD1306_WIDTH <= (SSD1306.CurrentX + Font->FontWidth) ||
        SSD1306_HEIGHT <= (SSD1306.CurrentY + Font->FontHeight)
    ) {
        return 0;  // Error
    }

    /* Go through font */
    uint32_t b;
    for (uint8_t i = 0; i < Font->FontHeight; i++) {
        b = Font->data[(ch - 32) * Font->FontHeight + i];
        for (uint8_t j = 0; j < Font->FontWidth; j++) {
            if ((b << j) & 0x8000) {
                ssd1306_DrawPixel_White( SSD1306.CurrentX + j, (SSD1306.CurrentY + i) );
            }
            #if 0
            // As SSD1306_Clear() has been executed before, it's not needed to redraw the Black colour pixels
            else {
                ssd1306_DrawPixel_Black( SSD1306.CurrentX + j, (SSD1306.CurrentY + i) );
            }
            #endif
        }
    }

    /* Increase pointer */
    SSD1306.CurrentX += Font->FontWidth;

    /* Return character written */
    return ch;
}


char SSD1306_Puts(char* str, FontDef_t* Font, SSD1306_COLOR_t color) {
    return( ssd1306_Puts( str, Font, color) );
}

static inline __attribute__((always_inline)) char ssd1306_Puts(char* str, FontDef_t* Font, SSD1306_COLOR_t color) {
    /* Write characters */
    while (*str) {
        /* Write character by character */
        if (ssd1306_Putc(*str, Font, color) != *str) {
            /* Return error */
            return *str;
        }

        /* Increase string pointer */
        str++;
    }

    /* Everything OK, zero should be returned */
    return *str;
}


static inline void ssd1306_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, SSD1306_COLOR_t c) {
    int16_t dx, dy, sx, sy, err;

    /* Check for overflow */
    if (x0 >= SSD1306_WIDTH) {
        x0 = SSD1306_WIDTH - 1;
    }
    if (x1 >= SSD1306_WIDTH) {
        x1 = SSD1306_WIDTH - 1;
    }
    if (y0 >= SSD1306_HEIGHT) {
        y0 = SSD1306_HEIGHT - 1;
    }
    if (y1 >= SSD1306_HEIGHT) {
        y1 = SSD1306_HEIGHT - 1;
    }

    dx = (x0 < x1) ? (x1 - x0) : (x0 - x1);
    dy = (y0 < y1) ? (y1 - y0) : (y0 - y1);
    sx = (x0 < x1) ? 1 : -1;
    sy = (y0 < y1) ? 1 : -1;
    err = ((dx > dy) ? dx : -dy) / 2;

    if (dx == 0) {
        int16_t tmp;
        if (y1 < y0) {
            tmp = y1;
            y1 = y0;
            y0 = tmp;
        }

        if (x1 < x0) {
            tmp = x1;
            x1 = x0;
            x0 = tmp;
        }

        /* Vertical line */
        for (int16_t i = y0; i <= y1; i++) {
            ssd1306_DrawPixel(x0, i, c);
        }

        /* Return from function */
        return;
    }

    if (dy == 0) {
        int16_t tmp;
        if (y1 < y0) {
            tmp = y1;
            y1 = y0;
            y0 = tmp;
        }

        if (x1 < x0) {
            tmp = x1;
            x1 = x0;
            x0 = tmp;
        }

        /* Horizontal line */
        for (int16_t i = x0; i <= x1; i++) {
            ssd1306_DrawPixel(i, y0, c);
        }

        /* Return from function */
        return;
    }

    int16_t e2;
    while (1) {
        ssd1306_DrawPixel(x0, y0, c);
        if (x0 == x1 && y0 == y1) {
            break;
        }
        e2 = err;
        if (e2 > -dx) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dy) {
            err += dx;
            y0 += sy;
        }
    }
}

void SSD1306_DrawRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c) {
    /* Check input parameters */
    if (
        x >= SSD1306_WIDTH ||
        y >= SSD1306_HEIGHT
    ) {
        /* Return error */
        return;
    }

    /* Check width and height */
    if ((x + w) >= SSD1306_WIDTH) {
        w = SSD1306_WIDTH - x;
    }
    if ((y + h) >= SSD1306_HEIGHT) {
        h = SSD1306_HEIGHT - y;
    }

    /* Draw 4 lines */
    ssd1306_DrawLine(x, y, x + w, y, c);         /* Top line */
    ssd1306_DrawLine(x, y + h, x + w, y + h, c); /* Bottom line */
    ssd1306_DrawLine(x, y, x, y + h, c);         /* Left line */
    ssd1306_DrawLine(x + w, y, x + w, y + h, c); /* Right line */
}

void SSD1306_DrawFilledRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, SSD1306_COLOR_t c) {
    /* Check input parameters */
    if (
        x >= SSD1306_WIDTH ||
        y >= SSD1306_HEIGHT
    ) {
        /* Return error */
        return;
    }

    /* Check width and height */
    if ((x + w) >= SSD1306_WIDTH) {
        w = SSD1306_WIDTH - x;
    }
    if ((y + h) >= SSD1306_HEIGHT) {
        h = SSD1306_HEIGHT - y;
    }

    /* Draw lines */
    for (uint8_t i = 0; i <= h; i++) {
        /* Draw lines */
        ssd1306_DrawLine(x, y + i, x + w, y + i, c);
    }
}

void SSD1306_DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, SSD1306_COLOR_t color) {
    /* Draw lines */
    ssd1306_DrawLine(x1, y1, x2, y2, color);
    ssd1306_DrawLine(x2, y2, x3, y3, color);
    ssd1306_DrawLine(x3, y3, x1, y1, color);
}


void SSD1306_DrawFilledTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, SSD1306_COLOR_t color) {
    int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
    yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
    curpixel = 0;

    deltax = ABS(x2 - x1);
    deltay = ABS(y2 - y1);
    x = x1;
    y = y1;

    if (x2 >= x1) {
        xinc1 = 1;
        xinc2 = 1;
    } else {
        xinc1 = -1;
        xinc2 = -1;
    }

    if (y2 >= y1) {
        yinc1 = 1;
        yinc2 = 1;
    } else {
        yinc1 = -1;
        yinc2 = -1;
    }

    if (deltax >= deltay){
        xinc1 = 0;
        yinc2 = 0;
        den = deltax;
        num = deltax / 2;
        numadd = deltay;
        numpixels = deltax;
    } else {
        xinc2 = 0;
        yinc1 = 0;
        den = deltay;
        num = deltay / 2;
        numadd = deltax;
        numpixels = deltay;
    }

    for (curpixel = 0; curpixel <= numpixels; curpixel++) {
        ssd1306_DrawLine(x, y, x3, y3, color);

        num += numadd;
        if (num >= den) {
            num -= den;
            x += xinc1;
            y += yinc1;
        }
        x += xinc2;
        y += yinc2;
    }
}

void SSD1306_DrawCircle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    ssd1306_DrawPixel(x0, y0 + r, c);
    ssd1306_DrawPixel(x0, y0 - r, c);
    ssd1306_DrawPixel(x0 + r, y0, c);
    ssd1306_DrawPixel(x0 - r, y0, c);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        ssd1306_DrawPixel(x0 + x, y0 + y, c);
        ssd1306_DrawPixel(x0 - x, y0 + y, c);
        ssd1306_DrawPixel(x0 + x, y0 - y, c);
        ssd1306_DrawPixel(x0 - x, y0 - y, c);

        ssd1306_DrawPixel(x0 + y, y0 + x, c);
        ssd1306_DrawPixel(x0 - y, y0 + x, c);
        ssd1306_DrawPixel(x0 + y, y0 - x, c);
        ssd1306_DrawPixel(x0 - y, y0 - x, c);
    }
}

void SSD1306_DrawFilledCircle(int16_t x0, int16_t y0, int16_t r, SSD1306_COLOR_t c) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    ssd1306_DrawPixel(x0, y0 + r, c);
    ssd1306_DrawPixel(x0, y0 - r, c);
    ssd1306_DrawPixel(x0 + r, y0, c);
    ssd1306_DrawPixel(x0 - r, y0, c);
    ssd1306_DrawLine(x0 - r, y0, x0 + r, y0, c);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        ssd1306_DrawLine(x0 - x, y0 + y, x0 + x, y0 + y, c);
        ssd1306_DrawLine(x0 + x, y0 - y, x0 - x, y0 - y, c);

        ssd1306_DrawLine(x0 + y, y0 + x, x0 - y, y0 + x, c);
        ssd1306_DrawLine(x0 + y, y0 - x, x0 - y, y0 - x, c);
    }
}



void SSD1306_Clear(void) {
    ssd1306_Fill( SSD1306_COLOR_BLACK );
}

static inline __attribute__((always_inline)) void ssd1306_OFF(void) {
    /* Write multi command */
    ssd1306_CommandsList[0u] = 0x8D;
    ssd1306_CommandsList[1u] = 0x10;
    ssd1306_CommandsList[2u] = 0xAE;
    ssd1306_I2C_WriteMulti( SSD1306_I2C_ADDR, 0x00u, ssd1306_CommandsList, 3u );
}

static inline __attribute__((always_inline)) void ssd1306_ON(void) {
    /* Write multi command */
    ssd1306_CommandsList[0u] = 0x8D;
    ssd1306_CommandsList[1u] = 0x14;
    ssd1306_CommandsList[2u] = 0xAF;
    ssd1306_I2C_WriteMulti( SSD1306_I2C_ADDR, 0x00u, ssd1306_CommandsList, 3u );
}


void SSD1306_Write1Line_PrepareScreen( uint16_t line1_x, uint16_t line1_y, char* line1_str, FontDef_t* line1_Font ) {
    ssd1306_GotoXY( line1_x, line1_y );
    ssd1306_Puts( line1_str, line1_Font, SSD1306_COLOR_WHITE );
}


void SSD1306_Write2Lines_PrepareScreen( uint16_t line1_x, uint16_t line1_y, char* line1_str, FontDef_t* line1_Font,
                                       uint16_t line2_x, uint16_t line2_y, char* line2_str, FontDef_t* line2_Font ) {
    ssd1306_GotoXY( line1_x, line1_y );
    ssd1306_Puts( line1_str, line1_Font, SSD1306_COLOR_WHITE );
    //
    ssd1306_GotoXY( line2_x, line2_y );
    ssd1306_Puts( line2_str, line2_Font, SSD1306_COLOR_WHITE );
}

void SSD1306_Write3Lines_PrepareScreen( uint16_t line1_x, uint16_t line1_y, char* line1_str, FontDef_t* line1_Font,
                                       uint16_t line2_x, uint16_t line2_y, char* line2_str, FontDef_t* line2_Font,
                                       uint16_t line3_x, uint16_t line3_y, char* line3_str, FontDef_t* line3_Font ) {
    ssd1306_GotoXY( line1_x, line1_y );
    ssd1306_Puts( line1_str, line1_Font, SSD1306_COLOR_WHITE );
    //
    ssd1306_GotoXY( line2_x, line2_y );
    ssd1306_Puts( line2_str, line2_Font, SSD1306_COLOR_WHITE );
    //
    ssd1306_GotoXY( line3_x, line3_y );
    ssd1306_Puts( line3_str, line3_Font, SSD1306_COLOR_WHITE );
}

void SSD1306_Write4Lines_PrepareScreen( uint16_t line1_x, uint16_t line1_y, char* line1_str, FontDef_t* line1_Font,
                                       uint16_t line2_x, uint16_t line2_y, char* line2_str, FontDef_t* line2_Font,
                                       uint16_t line3_x, uint16_t line3_y, char* line3_str, FontDef_t* line3_Font,
                                       uint16_t line4_x, uint16_t line4_y, char* line4_str, FontDef_t* line4_Font ) {
    ssd1306_GotoXY( line1_x, line1_y );
    ssd1306_Puts( line1_str, line1_Font, SSD1306_COLOR_WHITE );
    //
    ssd1306_GotoXY( line2_x, line2_y );
    ssd1306_Puts( line2_str, line2_Font, SSD1306_COLOR_WHITE );
    //
    ssd1306_GotoXY( line3_x, line3_y );
    ssd1306_Puts( line3_str, line3_Font, SSD1306_COLOR_WHITE );
    //
    ssd1306_GotoXY( line4_x, line4_y );
    ssd1306_Puts( line4_str, line4_Font, SSD1306_COLOR_WHITE );
}

void SSD1306_Write5Lines_PrepareScreen( uint16_t line1_x, uint16_t line1_y, char* line1_str, FontDef_t* line1_Font,
                                       uint16_t line2_x, uint16_t line2_y, char* line2_str, FontDef_t* line2_Font,
                                       uint16_t line3_x, uint16_t line3_y, char* line3_str, FontDef_t* line3_Font,
                                       uint16_t line4_x, uint16_t line4_y, char* line4_str, FontDef_t* line4_Font,
                                       uint16_t line5_x, uint16_t line5_y, char* line5_str, FontDef_t* line5_Font ) {
    ssd1306_GotoXY( line1_x, line1_y );
    ssd1306_Puts( line1_str, line1_Font, SSD1306_COLOR_WHITE );
    //
    ssd1306_GotoXY( line2_x, line2_y );
    ssd1306_Puts( line2_str, line2_Font, SSD1306_COLOR_WHITE );
    //
    ssd1306_GotoXY( line3_x, line3_y );
    ssd1306_Puts( line3_str, line3_Font, SSD1306_COLOR_WHITE );
    //
    ssd1306_GotoXY( line4_x, line4_y );
    ssd1306_Puts( line4_str, line4_Font, SSD1306_COLOR_WHITE );
    //
    ssd1306_GotoXY( line5_x, line5_y );
    ssd1306_Puts( line5_str, line5_Font, SSD1306_COLOR_WHITE );
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  _____ ___   _____
// |_   _|__ \ / ____|
//   | |    ) | |
//   | |   / /| |
//  _| |_ / /_| |____
// |_____|____|\_____|
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////

static inline __attribute__((always_inline)) void ssd1306_I2C_Write(uint8_t address, uint8_t reg, uint8_t data) {
    ssd1306_dt_Write[0u] = reg;
    ssd1306_dt_Write[1u] = data;
    HAL_I2C_Master_Transmit( &i2cm_MODULE_DISPLAY, address, ssd1306_dt_Write, 2u, ssd1306_I2C_TIMEOUT_WRITE );
}

static inline __attribute__((always_inline)) void ssd1306_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count) {
    ssd1306_dt_WriteMulti[0u] = reg;
    memcpy( &ssd1306_dt_WriteMulti[1u], data, count );
    HAL_I2C_Master_Transmit( &i2cm_MODULE_DISPLAY, address, ssd1306_dt_WriteMulti, count+1u, ssd1306_I2C_TIMEOUT_WRITE_MULTI );
}

static inline __attribute__((always_inline)) void ssd1306_I2C_WriteMulti_DMA(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count) {
    ssd1306_dt_WriteMulti[0u] = reg;
    memcpy( &ssd1306_dt_WriteMulti[1u], data, count );
    HAL_I2C_Master_Transmit_DMA( &i2cm_MODULE_DISPLAY, address, ssd1306_dt_WriteMulti, count+1u );
}
