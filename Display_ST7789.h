#pragma once
#include <Arduino.h>
#include <SPI.h>

// ==================== Ekran Yönlənməsi ====================
// 0 = Portrait (şaquli), 1 = Landscape (üfüqi)
#define DISPLAY_ORIENTATION 1  // <-- Landscape için 1, Portrait için 0

#if DISPLAY_ORIENTATION == 1
// Landscape
#define LCD_WIDTH 320
#define LCD_HEIGHT 172
#define Offset_X 0
#define Offset_Y 34
#define MADCTL_VAL 0x60  // gerekirse 0x60 / 0xA0 / 0xC0 dene
#else
// Portrait (şu an çalışan ayar)
#define LCD_WIDTH 172
#define LCD_HEIGHT 320
#define Offset_X 40
#define Offset_Y 0
#define MADCTL_VAL 0x00
#endif

// ==================== SPI ====================
#define SPIFreq 80000000

// ==================== GPIO ====================
#define EXAMPLE_PIN_NUM_MISO 5
#define EXAMPLE_PIN_NUM_MOSI 6
#define EXAMPLE_PIN_NUM_SCLK 7
#define EXAMPLE_PIN_NUM_LCD_CS 14
#define EXAMPLE_PIN_NUM_LCD_DC 15
#define EXAMPLE_PIN_NUM_LCD_RST 21
#define EXAMPLE_PIN_NUM_BK_LIGHT 22

// ==================== Backlight PWM ====================
#define Frequency 1000
#define Resolution 10

// ==================== Fonksiyonlar ====================
void lcdWriteCommand(uint8_t cmd);
void lcdWriteData(uint8_t data);
void lcdWriteDataWord(uint16_t data);
void lcdWriteDataNbyte(uint8_t* SetData, uint8_t* ReadData, uint32_t Size);
void lcdReset(void);
void lcdInit(void);
void lcdSetCursor(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend);
void lcdAddWindow(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t* color);
void Backlight_Init(void);
void Set_Backlight(uint8_t Light);