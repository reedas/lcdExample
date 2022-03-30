/* Hello World! for the TextLCD Enhanced Library*/

#include "mbed.h"
#include "TextLCD.h"
//#include "Adafruit_SSD1306.h"
//#include "GUI.h"
//#include "cy8ckit_028_tft.h"

DigitalOut myled(LED1);


// Host PC Communication channels
//Serial pc(USBTX, USBRX); // tx, rx

// I2C Communication
#define SDA P6_1
#define SCL P6_0
I2C i2c_lcd(SDA, SCL); // SDA, SCL
//I2C i2c_lcd(p28,p27); // SDA, SCL

// SPI Communication
//SPI spi_lcd(P5_1, NC, P5_0); // MOSI, MISO, SCLK

// LCD instantiation
//TextLCD lcd(p15, p16, p17, p18, p19, p20, TextLCD::LCD20x2);        // 4bit bus: rs, e, d4-d7
TextLCD_I2C lcd(&i2c_lcd, 0x4e, TextLCD::LCD16x2 /*, TextLCD::WS0010*/);                  // I2C exp: I2C bus, PCF8574 Slaveaddress, LCD Type
//TextLCD_I2C lcd(&i2c_lcd, 0x42, TextLCD::LCD16x2, TextLCD::WS0010); // I2C exp: I2C bus, PCF8574 Slaveaddress, LCD Type, Ctrl Type
//TextLCD_I2C lcd(&spi_lcd, p8, TextLCD::LCD24x4D);                   // I2C exp: SPI bus, CS pin, LCD Type
//TextLCD_SPI_N lcd(&spi_lcd, p8, p9, TextLCD::LCD16x2, NC, TextLCD::ST7032_3V3); // SPI native: SPI bus, CS pin, RS pin, LCDType=LCD16x2, BL=NC, LCDTCtrl=ST7032
//TextLCD_I2C_N lcd(&i2c_lcd, ST7032_SA, TextLCD::LCD16x2, NC, TextLCD::ST7032_3V3); // I2C native: I2C bus, slaveaddress, LCDType=LCD16x2, BL=NC, LCDTCtrl=ST7032 =Ok
//TextLCD_I2C_N lcd(&i2c_lcd, SSD1803_SA1, TextLCD::LCD20x4D, NC, TextLCD::SSD1803_3V3); // I2C native: I2C bus, slaveaddress, LCDType=LCD20x4D, BL=NC, LCDTCtrl=SSD1803 =Ok

//Adafruit_SSD1306_I2c gOled2(i2c_lcd, P0_2, 0x78, 64, 128);


void Display_Init(void)
{

    /* memory buffer for sprintf */
//    char outputString[80];

    /* Set font size, foreground and background Colours */
//    GUI_SetFont(GUI_FONT_16B_1);
//    GUI_SetColor(GUI_WHITE);
//    GUI_SetBkColor(GUI_BLACK);

    /* Clear screen and print splash screen */
//    GUI_Clear();
//    GUI_SetTextAlign(GUI_TA_HCENTER);
//    GUI_DispStringAt("Display Demo", 160, 20);
//    GUI_SetFont(GUI_FONT_24B_1);
//    GUI_SetTextAlign(GUI_TA_HCENTER);
//    GUI_DispStringAt("TFT Hello World", 160, 60);
    printf("\r\nHello World\r\n");
    ThisThread::sleep_for(100);
}

int main()
{
    Timer t;
        /* Initialise EmWin driver*/
//    GUI_Init();

    char outputString[80];

    /* Initialise display */
//    Display_Init();

    lcd.setBacklight(TextLCD::LightOn);
    for (int i = 32; i < 33; i++) {
        lcd.printf("Tester...");
    }
    /*  i2c_lcd.frequency(100000);
     */
    printf("TextLCD Enhanced Test. Columns=%d, Rows=%d\n\r", lcd.columns(), lcd.rows());

    for (int row=0; row<lcd.rows(); row++) {
        int col=0;

        printf("MemAddr(Col=%d, Row=%d)=0x%02X\n\r", col, row, lcd.getAddress(col, row));
//    lcd.putc('-');
        lcd.putc('0' + row);

        for (col=1; col<lcd.columns()-1; col++) {
            lcd.putc('*');
        }

        printf("MemAddr(Col=%d, Row=%d)=0x%02X\n\r", col, row, lcd.getAddress(col, row));
        lcd.putc('+');
    }

// Fill screen again and time it
    t.start();

    for (int row=0; row<lcd.rows(); row++) {
        int col=0;

        lcd.putc('0' + row);

        for (col=1; col<lcd.columns()-1; col++) {
            lcd.putc('*');
        }

        lcd.putc('+');
    }
 //   t.stop();
    printf("All my hard work took %f sec\r\n", t.read());

// Show cursor as blinking character or turn off

    lcd.setCursor(TextLCD::CurOff_BlkOff);

// Set and show user defined characters. A maximum of 8 UDCs are supported by the HD44780.
// They are defined by a 5x7 bitpattern.
    lcd.setUDC(0, (char *) udc_0);  // Show |>
    lcd.putc(0);
    lcd.setUDC(1, (char *) udc_1);  // Show <|
    lcd.putc(1);
    lcd.locate(0,0);
    lcd.printf("line 1");
    lcd.locate(0,1);
    lcd.printf("line 2");
    uint16_t count = 0;
//    gOled2.clearDisplay();
//    gOled2.printf("OLED Hello World");
//    gOled2.setTextSize(1);
    ThisThread::sleep_for(2000);
    lcd.cls();
    lcd.printf("LCD Hello World");
//    GUI_SetFont(GUI_FONT_8X16X2X2);
    while(1) {
        sprintf(outputString, "Count is: %5u", count++);
        lcd.locate(0, 1);
        lcd.printf("%s",outputString);
        myled = !myled;
//        gOled2.setTextCursor(10,40);
//        gOled2.printf("%s",outputString);
//        gOled2.display();
//        GUI_SetTextAlign(GUI_TA_HCENTER);
//        GUI_DispStringAt(outputString, 160, 200);

        ThisThread::sleep_for(100);
    }
    t.stop();
    printf("All the counting took %f sec\r\n", t.read());

    printf("Bye now\r\n");

}



