/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.1
        Device            :  dsPIC33CK128MP202
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.70
        MPLAB 	          :  MPLAB X v5.50
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/mcc.h"
//#include "ssd1306_conf.h"
//#include "ssd1306.h"
//#include "ssd1306_fonts.h"
#define FCY 75000000UL    // main clock 75MHz
#include "libpic30.h"
#include <stdint.h>


#define SSD1306_DISPLAY_OFF 0xAE
#define SSD1306_DISPLAY_ON 0xAF
#define SSD1306_SET_DISPLAY_CLOCK_DIV 0xD5
#define SSD1306_SET_MULTIPLEX 0xA8
#define SSD1306_SET_DISPLAY_OFFSET 0xD3
#define SSD1306_SET_START_LINE 0x40
#define SSD1306_CHARGE_PUMP 0x8D
#define SSD1306_MEMORY_MODE 0x20
#define SSD1306_SEGREMAP 0xA0
#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_SETCOMPINS 0xDA
#define SSD1306_SETCONTRAST 0x81
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETVCOMDETECT 0xDB
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR 0x22
#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10
#define SSD1306_SETSTARTPAGE 0xB0
#define SSD1306_SETMULTIPLEX 0xA8
#define SSD1306_EXTERNALVCC 0x01  ///< External display voltage source
#define SSD1306_SWITCHCAPVCC 0x02 ///< Gen. display voltage from 3.3V
#define SSD1306_LCDWIDTH 128
#define SSD1306_LCDHEIGHT 32

void SSD1306_SendCommand(uint8_t c);
void SSD1306_SendData(uint8_t c);
void SSD1306_Init(void);
void SSD1306_DrawHorizontalLine(uint8_t x, uint8_t y, uint8_t length);
void ssd1306_fillScreen(uint8_t pattern);
void ssd1306_clearScreen(void);
void ssd1306_flashScreen(uint8_t pattern, uint16_t delay_ms);
void SSD1306_HalfWhiteHalfBlack(void);

int main(void) {
    // Initialize system and peripherals
    SYSTEM_Initialize();
    __delay_ms(100);
    // Initialize SSD1306
    SSD1306_Init();
    
    while (1) {
        SSD1306_HalfWhiteHalfBlack();
    }

    return 0;
}

//void Oled_Init(void){
//TRIS_CS = 0; TRIS_DC = 0; TRIS_RES = 0;
//OLED_CS = 1; OLED_DC = 0; OLED_RES = 0;
//Delay_ms(500);
//Oled_Reset();
//Oled_Command(0xAE);                     // Set Display OFF
//Oled_Command(0x81); Oled_Command(0xCF); // Set Contrast Control
//Oled_Command(0xA4);                     // Entire Display ON
//Oled_Command(0xA6);                     // Set Normal
//
//Oled_Command(0x20); Oled_Command(0x02); // Set Memory Addressing Mode
//Oled_Command(0x00);                     // Set Lower Column
//Oled_Command(0x10);                     // Set Higher Column
//Oled_Command(0xB0);                     // Set Page Start
//
//Oled_Command(0x40);                     // Set Display Start Line
//Oled_Command(0xA1);                     // Set Segment Re-map
//Oled_Command(0xA8); Oled_Command(0x3F); // Set Multiplex Ratio
//Oled_Command(0xC8);                     // Set COM Output
//Oled_Command(0xD3); Oled_Command(0x00); // Set Display Offset
//Oled_Command(0xDA); Oled_Command(0x12); // Set COM Pins Hardware Configuration
//
//Oled_Command(0xD5); Oled_Command(0x80); // Set Display Clock
//Oled_Command(0xD9); Oled_Command(0xF1); // Set Pre-charge Period
//Oled_Command(0xDB); Oled_Command(0x40); // Set VCOMH Deselect Level
//Oled_Command(0x8D); Oled_Command(0x14); // Charge Pump Setting
//
//Oled_Command(0xAF);                     // Set Display ON
//Oled_FillScreen(0x00);                  // Clear screen
//}

void SSD1306_Init(void) {
    // Perform a hardware reset
    __delay_ms(1000);
    LCD_R_SetLow();
    __delay_ms(10);
    LCD_R_SetHigh();
    __delay_ms(10);

    // Begin SSD1306 OLED display initialization sequence
//    SSD1306_SendCommand(0xAE);          // Turn display off
//    SSD1306_SendCommand(0x81);                          // Suggested value by datasheet
//    SSD1306_SendCommand(0xCF); 
//    SSD1306_SendCommand(0xA4);        // Set multiplex ratio (N+1)
//    SSD1306_SendCommand(0xA6);
//
//    SSD1306_SendCommand(0x40);                     // Set Display Start Line
//    SSD1306_SendCommand(0xA1);                     // Set Segment Re-map
//    SSD1306_SendCommand(0xA8); SSD1306_SendCommand(0x3F); // Set Multiplex Ratio
//    SSD1306_SendCommand(0xC8);                     // Set COM Output
//    SSD1306_SendCommand(0xD3); SSD1306_SendCommand(0x00); // Set Display Offset
//    SSD1306_SendCommand(0xDA); SSD1306_SendCommand(0x12); // Set COM Pins Hardware Configuration
//    
//    SSD1306_SendCommand(0xB0);
//    SSD1306_SendCommand(0xB0);
//    SSD1306_SendCommand(0xB0);
//    SSD1306_SendCommand(0xB0);
//    SSD1306_SendCommand(0xB0);
//    SSD1306_SendCommand(0xB0);
//    
//    SSD1306_SendCommand(0xD5); SSD1306_SendCommand(0x80); // Set Display Clock
//    SSD1306_SendCommand(0xD9); SSD1306_SendCommand(0xF1); // Set Pre-charge Period
//    SSD1306_SendCommand(0xDB); SSD1306_SendCommand(0x40); // Set VCOMH Deselect Level
//    SSD1306_SendCommand(0x8D); SSD1306_SendCommand(0x14); // Charge Pump Setting
//
//    SSD1306_SendCommand(0xAF);                     // Set Display ON
    
    
    // Begin SSD1306 OLED display initialization sequence
    //these are the values and sequence pulled from the arduino
    //to the right I labled them as what I was able to find that values refered to on the data sheet, 
    SSD1306_SendCommand(0xAE);          // Turn display off
    SSD1306_SendCommand(0xD5);          // Set display clock divide ratio/oscillator frequency
    SSD1306_SendCommand(0x80);          // Suggested value by datasheet
    SSD1306_SendCommand(0xA8);          // Set multiplex ratio (N+1)
    SSD1306_SendCommand(0x1F);          // Set the value of the multiplex ratio

    SSD1306_SendCommand(0xD3);          // Set display offset
    SSD1306_SendCommand(0x00);          // No offset
    SSD1306_SendCommand(0x40);          // Set display start line
    SSD1306_SendCommand(0x8D);          // Charge pump setting
    SSD1306_SendCommand(0x14);          // Enable charge pump
    SSD1306_SendCommand(0x20);          // Set memory addressing mode
    SSD1306_SendCommand(0x00);          // Horizontal addressing mode

    SSD1306_SendCommand(0xA1);          // Set segment remap
    SSD1306_SendCommand(0xC8);          // Set COM output scan direction
    SSD1306_SendCommand(0xDA);          // Set COM pins hardware configuration
    SSD1306_SendCommand(0x02);          // Sequential COM pin configuration
    SSD1306_SendCommand(0x81);          // Set contrast control
    SSD1306_SendCommand(0x8F);          // Set the value of the contrast control

    SSD1306_SendCommand(0xD9);          // Set pre-charge period
    SSD1306_SendCommand(0xF1);          // Set the value of the pre-charge period
    SSD1306_SendCommand(0xDB);          // Set VCOMH deselect level
    SSD1306_SendCommand(0x40);          // Set the value of the VCOMH deselect level
    SSD1306_SendCommand(0xA4);          // Entire display ON, resume to RAM content display
    SSD1306_SendCommand(0xA6);          // Set normal display mode
    SSD1306_SendCommand(0x2E);          // Deactivate scroll
    
    SSD1306_SendCommand(0xAF);          // Set display ON
    __delay_ms(2);
    SSD1306_SendCommand(0x22);          // Set page address
    SSD1306_SendCommand(0x00);          // Set the start page address
    SSD1306_SendCommand(0xFF);          // Set the end page address
    SSD1306_SendCommand(0x21);          // Set column address
    SSD1306_SendCommand(0x00);          // Set the start column address
    SSD1306_SendCommand(0x7F);          // Set the end column address
    
    
    //these signals were me trying to replicate all of the code that the signal analyzer found with the delays (mine are larger than the ones I saw, wanted to try it just in case)
    //not usre what the 0x04 does, maybe its not a command but was supposed to be data
    __delay_ms(4);
    SSD1306_SendCommand(0x04);
    __delay_ms(1);
    SSD1306_SendCommand(0x04);
    __delay_ms(2);
    SSD1306_SendCommand(0x04);
    __delay_ms(1);
    SSD1306_SendCommand(0x04);
    __delay_ms(4);
    SSD1306_SendCommand(0x22); 
    SSD1306_SendCommand(0x00); 
    SSD1306_SendCommand(0xFF); 
    SSD1306_SendCommand(0x21); 
    SSD1306_SendCommand(0x00); 
    SSD1306_SendCommand(0x7F); 
}

void SSD1306_SendData(uint8_t data) {
    LCD_DC_SetHigh(); // Set the Data/Command pin to high (data mode)
    SPI1_Exchange8bit(data); // Send the data
}

void SSD1306_SendCommand(uint8_t command) {
    LCD_DC_SetLow(); // Set the Data/Command pin to low (command mode)
    SPI1_Exchange8bit(command); // Send the command
}


void SSD1306_HalfWhiteHalfBlack(void) {
    // Set the patterns for white and black
    uint8_t whitePattern = 0xFF;
    uint8_t blackPattern = 0x00;

    // Set the column address range
    SSD1306_SendCommand(SSD1306_COLUMNADDR); // Set the start column address
    SSD1306_SendCommand(0); // Start column address set to 0
    SSD1306_SendCommand(SSD1306_LCDWIDTH - 1); // End column address set to the display width - 1

    // Set the page address range
    SSD1306_SendCommand(SSD1306_PAGEADDR); // Set the start page address
    SSD1306_SendCommand(0); // Start page address set to 0
    SSD1306_SendCommand((SSD1306_LCDHEIGHT / 8) - 1); // End page address set to (display height / 8) - 1

    // Calculate the total number of bytes on the display and half of that value
    uint16_t totalBytes = (SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT) / 8;
    uint16_t halfBytes = totalBytes / 2;

    // Fill the first half of the display with the white pattern
    for (uint16_t i = 0; i < halfBytes; i++) {
        SSD1306_SendData(whitePattern);
    }

    // Fill the second half of the display with the black pattern
    for (uint16_t i = halfBytes; i < totalBytes; i++) {
        SSD1306_SendData(blackPattern);
    }
}


