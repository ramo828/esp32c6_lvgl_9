#pragma once
#include <Arduino.h>
#include <SPI.h>

// ==================== Ekran Ölçüləri ====================
#define LCD_WIDTH   172  // Ekranın eni (piksel)
#define LCD_HEIGHT  320  // Ekranın hündürlüyü (piksel)

// ==================== SPI Tənzimləməsi ====================
#define SPIFreq                        80000000  // SPI sürətliyi (80 MHz)

// ==================== GPIO Pinləri ====================
#define EXAMPLE_PIN_NUM_MISO           5         // SPI Master In Slave Out
#define EXAMPLE_PIN_NUM_MOSI           6         // SPI Master Out Slave In
#define EXAMPLE_PIN_NUM_SCLK           7         // SPI Clock (Saat)
#define EXAMPLE_PIN_NUM_LCD_CS         14        // LCD Chip Select
#define EXAMPLE_PIN_NUM_LCD_DC         15        // LCD Data/Command
#define EXAMPLE_PIN_NUM_LCD_RST        21        // LCD Reset
#define EXAMPLE_PIN_NUM_BK_LIGHT       22        // Arxa işıq (Backlight)

// ==================== Arxa Işıq (PWM) Ayarları ====================
#define Frequency       1000           // PWM tezliyi (Hz)
#define Resolution      10             // PWM əhəmiyyəti (10-bit = 0-1023)

// ==================== Ekran Yönlənməsi ====================
#define VERTICAL   0                   // Şaquli yönlənmə
#define HORIZONTAL 1                   // Üfüqi yönlənmə

// ==================== Ofset Dəyərləri ====================
#define Offset_X 34                    // X ofset (piksel)
#define Offset_Y 0                     // Y ofset (piksel)

// ==================== Funksiya Deklarasiyaları ====================
/**
 * @brief LCD-yə əmr göndər
 * @param cmd: ST7789 əmri
 */
void lcdWriteCommand(uint8_t cmd);

/**
 * @brief LCD-yə bir bayt məlumat göndər
 * @param data: Göndəriləcək bayt
 */
void lcdWriteData(uint8_t data);

/**
 * @brief LCD-yə bir söz (16-bit) məlumat göndər
 * @param data: Göndəriləcək söz
 */
void lcdWriteDataWord(uint16_t data);

/**
 * @brief LCD-yə çoxbaytlı məlumat göndər
 * @param SetData: Göndəriləcək məlumat
 * @param ReadData: Qayıdan məlumat (istifadə edilmir)
 * @param Size: Məlumat böyüklüyü
 */
void lcdWriteDataNbyte(uint8_t* SetData, uint8_t* ReadData, uint32_t Size);

/**
 * @brief LCD-ni reset et
 */
void lcdReset(void);

/**
 * @brief LCD-ni inisializə et (başlat)
 */
void lcdInit(void);

/**
 * @brief LCD-nin nəzarət sahəsini təyin et
 * @param Xstart: Başlanğıc X koordinatı
 * @param Ystart: Başlanğıc Y koordinatı
 * @param Xend: Son X koordinatı
 * @param Yend: Son Y koordinatı
 */
void lcdSetCursor(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend);

/**
 * @brief LCD-nin bir sahəsinə rənglik məlumatı göndər
 * @param Xstart: Başlanğıc X
 * @param Ystart: Başlanğıc Y
 * @param Xend: Son X
 * @param Yend: Son Y
 * @param color: Rəng məlumatı (RGB565)
 */
void lcdAddWindow(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t* color);

/**
 * @brief Arxa işığı (backlight) inisializə et
 */
void Backlight_Init(void);

/**
 * @brief Arxa işığın parlaqlığını təyin et
 * @param Light: Parlaqlıq səviyyəsi (0-100)
 */
void Set_Backlight(uint8_t Light);
