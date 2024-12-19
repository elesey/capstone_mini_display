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
#include "mcc_generated_files/system.h"
#include "ssd1306_conf.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#define FCY 75000000UL    // main clock 75MHz
#include "libpic30.h"
#include <xc.h>
#include "pin_manager.h"




int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    Initialize_CFAL12832C();
   
	ssd1306_Fill(White);
	while(1){ 
		ssd1306_Fill(White);					
		ssd1306_SetCursor(2,0);
		ssd1306_UpdateScreen();
		__delay_ms(2000);
        ssd1306_WriteString("My ", Font_7x10, Black);		
        ssd1306_UpdateScreen();
        __delay_ms(2000);
        ssd1306_WriteString("Name ", Font_7x10, Black);		
        ssd1306_UpdateScreen();
        __delay_ms(2000);				
        ssd1306_WriteString("Is ", Font_7x10, Black);		
        ssd1306_UpdateScreen();
        __delay_ms(2000);
        ssd1306_WriteString("Slim ", Font_7x10, Black);		
        ssd1306_UpdateScreen();
        __delay_ms(2000);	
        ssd1306_WriteString("Shady", Font_7x10, Black);		
        ssd1306_UpdateScreen();
        __delay_ms(2000);
	}
    return 1; 
}

void Initialize_CFAL12832C(void)
{
  //Thump the reset.  
  __delay_ms(1);
  LCD_R_SetLow();
  __delay_ms(1);
  LCD_R_SetHigh();
  __delay_ms(5);

  //Set the display to sleep mode for the rest of the init.
  send_command(SSD1306B_DISPLAY_OFF_YES_SLEEP_AE);

  //Set the clock speed, nominal ~105FPS
  //Low nibble is divide ratio
  //High level is oscillator frequency
  send_command(SSD1306B_CLOCK_DIVIDE_PREFIX_D5);
  send_command(0x80);//177Hz measured

  //Set the multiplex ratio to 1/32
  //Default is 0x3F (1/64 Duty), we need 0x1F (1/32 Duty)
  send_command(SSD1306B_MULTIPLEX_RATIO_PREFIX_A8);
  send_command(0x1F);

  //Set the display offset to 0 (default)
  send_command(SSD1306B_DISPLAY_OFFSET_PREFIX_D3);
  send_command(0x00);

  //Set the display RAM display start line to 0 (default)
  //Bits 0-5 can be set to 0-63 with a bitwise or
  send_command(SSD1306B_DISPLAY_START_LINE_40);

  //Enable DC/DC converter, 7.5v
  send_command(SSD1306B_DCDC_CONFIG_PREFIX_8D);
  send_command(SSD1306B_DCDC_CONFIG_7p5v_14);

  //Map the columns correctly for our OLED glass layout
  send_command(SSD1306B_SEG0_IS_COL_127_A1);

  //Set COM output scan correctly for our OLED glass layout
  send_command(SSD1306B_SCAN_DIR_UP_C0);

  //Set COM pins correctly for our OLED glass layout
  send_command(SSD1306B_COM_CONFIG_PREFIX_DA);
  send_command(SSD1306B_COM_CONFIG_SEQUENTIAL_LEFT_02);

  //Set Contrast Control / SEG Output Current / Iref
  send_command(SSD1306B_CONTRAST_PREFIX_81);
  send_command(0xBF);  //magic # from factory

  //Set precharge (low nibble) / discharge (high nibble) timing
  //precharge = 1 clock
  //discharge = 15 clocks
  send_command(SSD1306B_PRECHARGE_PERIOD_PREFIX_D9); //Set Pre-Charge period        
  send_command(0xF1);

  //Set VCOM Deselect Level
  send_command(SSD1306B_VCOMH_DESELECT_PREFIX_DB);
  send_command(SSD1306B_VCOMH_DESELECT_0p83xVCC_30);

  //Make sure Entire Display On is disabled (default)
  send_command(SSD1306B_ENTIRE_DISPLAY_NORMAL_A4);

  //Make sure display is not inverted (default)
  send_command(SSD1306B_INVERSION_NORMAL_A6);

  //Get out of sleep mode, into normal operation
  send_command(SSD1306B_DISPLAY_ON_NO_SLEEP_AF);
}
