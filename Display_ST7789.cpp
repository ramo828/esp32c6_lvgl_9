#include "Display_ST7789.h"

// ==================== SPI Makros ====================
#define SPI_WRITE(_dat) SPI.transfer(_dat)         // Bir bayt göndər
#define SPI_WRITE_Word(_dat) SPI.transfer16(_dat)  // Bir söz göndər

// ==================== SPI İnisializasiyası ====================
/**
 * @brief SPI modu hazırla
 */
void spiInit() {
  SPI.begin(EXAMPLE_PIN_NUM_SCLK, EXAMPLE_PIN_NUM_MISO, EXAMPLE_PIN_NUM_MOSI);
}

// ==================== LCD Əmr Göndərməsi ====================
/**
 * @brief LCD-yə əmr göndər
 * 
 * Prosedur:
 * 1. SPI tranzaksiyasını başlat
 * 2. CS pinini aç (LOW)
 * 3. DC pinini əmr rejiminə qoy (LOW)
 * 4. Əmr baytını göndər
 * 5. CS pinini kapat (HIGH)
 * 6. Tranzaksiyasını bitir
 */
void lcdWriteCommand(uint8_t Cmd) {
  SPI.beginTransaction(SPISettings(SPIFreq, MSBFIRST, SPI_MODE0));
  digitalWrite(EXAMPLE_PIN_NUM_LCD_CS, LOW);
  digitalWrite(EXAMPLE_PIN_NUM_LCD_DC, LOW);
  SPI_WRITE(Cmd);
  digitalWrite(EXAMPLE_PIN_NUM_LCD_CS, HIGH);
  SPI.endTransaction();
}

// ==================== LCD Məlumat Göndərməsi (Bir Bayt) ====================
/**
 * @brief LCD-yə bir bayt məlumat göndər
 * 
 * Prosedur:
 * 1. SPI tranzaksiyasını başlat
 * 2. CS pinini aç (LOW)
 * 3. DC pinini məlumat rejiminə qoy (HIGH)
 * 4. Məlumat baytını göndər
 * 5. CS pinini kapat (HIGH)
 * 6. Tranzaksiyasını bitir
 */
void lcdWriteData(uint8_t Data) {
  SPI.beginTransaction(SPISettings(SPIFreq, MSBFIRST, SPI_MODE0));
  digitalWrite(EXAMPLE_PIN_NUM_LCD_CS, LOW);
  digitalWrite(EXAMPLE_PIN_NUM_LCD_DC, HIGH);
  SPI_WRITE(Data);
  digitalWrite(EXAMPLE_PIN_NUM_LCD_CS, HIGH);
  SPI.endTransaction();
}

// ==================== LCD Məlumat Göndərməsi (Bir Söz) ====================
/**
 * @brief LCD-yə bir söz (16-bit) məlumat göndər
 * 
 * Rəng məlumatı üçün istifadə olunur (RGB565)
 */
void lcdWriteDataWord(uint16_t Data) {
  SPI.beginTransaction(SPISettings(SPIFreq, MSBFIRST, SPI_MODE0));
  digitalWrite(EXAMPLE_PIN_NUM_LCD_CS, LOW);
  digitalWrite(EXAMPLE_PIN_NUM_LCD_DC, HIGH);
  SPI_WRITE_Word(Data);
  digitalWrite(EXAMPLE_PIN_NUM_LCD_CS, HIGH);
  SPI.endTransaction();
}

// ==================== LCD Məlumat Göndərməsi (Çoxbayt) ====================
/**
 * @brief LCD-yə çoxbaytlı məlumat göndər
 * 
 * Bu funksiya böyük məlumat ötürmə üçün istifadə olunur
 * (məsələn, tam ekran rəng məlumatı)
 */
void lcdWriteDataNbyte(uint8_t* SetData, uint8_t* ReadData, uint32_t Size) {
  SPI.beginTransaction(SPISettings(SPIFreq, MSBFIRST, SPI_MODE0));
  digitalWrite(EXAMPLE_PIN_NUM_LCD_CS, LOW);
  digitalWrite(EXAMPLE_PIN_NUM_LCD_DC, HIGH);
  SPI.transferBytes(SetData, ReadData, Size);
  digitalWrite(EXAMPLE_PIN_NUM_LCD_CS, HIGH);
  SPI.endTransaction();
}

// ==================== LCD Reset Funksiyası ====================
/**
 * @brief LCD-ni reset et (başlanğıc sıfırlama)
 * 
 * Prosedur:
 * 1. CS pinini aç (güvənlik)
 * 2. Reset pinini aç (LOW) - reset stəmiş şərti
 * 3. 50ms gözlə
 * 4. Reset pinini yüksəlt (HIGH) - reset tamamlandı
 * 5. 50ms gözlə (stabilizasiya)
 */
void lcdReset(void) {
  digitalWrite(EXAMPLE_PIN_NUM_LCD_CS, LOW);
  delay(50);
  digitalWrite(EXAMPLE_PIN_NUM_LCD_RST, LOW);
  delay(50);
  digitalWrite(EXAMPLE_PIN_NUM_LCD_RST, HIGH);
  delay(50);
}

// ==================== LCD İnisializasiyası ====================
/**
 * @brief LCD-ni tamamilə inisializə et
 * 
 * Bu funksiya:
 * 1. GPIO pinlərini konfiqurə edir
 * 2. Arxa işığı inisializə edir
 * 3. SPI modu hazırlayır
 * 4. LCD-ni reset edir
 * 5. ST7789 kontroller dəyərləri göndərir
 * 6. Ekranı göstərilmə rejiminə keçirir
 */
void lcdInit(void) {
  // GPIO pinlərini çıxış rejiminə təyin et
  pinMode(EXAMPLE_PIN_NUM_LCD_CS, OUTPUT);
  pinMode(EXAMPLE_PIN_NUM_LCD_DC, OUTPUT);
  pinMode(EXAMPLE_PIN_NUM_LCD_RST, OUTPUT);

  // Arxa işığı inisializə et
  Backlight_Init();

  // SPI modu başlat
  spiInit();

  // LCD-ni reset et
  lcdReset();

  // ==================== ST7789 Kontroller İnisializasiya ====================
  lcdWriteCommand(0x11);  // Exit Sleep Mode
  delay(120);

  lcdWriteCommand(0x36);     // Memory Data Access Control (MADCTL)
  lcdWriteData(MADCTL_VAL);  // Display_ST7789.h içindən gəlir

  lcdWriteCommand(0x3A);  // Interface Pixel Format
  lcdWriteData(0x05);     // 16-bit/piksel (RGB565)

  lcdWriteCommand(0xB0);  // AVDD / AVCL / VDH / VDL Voltage
  lcdWriteData(0x00);
  lcdWriteData(0xE8);

  lcdWriteCommand(0xB2);  // Frame Rate Control
  lcdWriteData(0x0C);
  lcdWriteData(0x0C);
  lcdWriteData(0x00);
  lcdWriteData(0x33);
  lcdWriteData(0x33);

  lcdWriteCommand(0xB7);  // Gate Voltage
  lcdWriteData(0x35);

  lcdWriteCommand(0xBB);  // VCOM Setting
  lcdWriteData(0x35);

  lcdWriteCommand(0xC0);  // Power Control 1
  lcdWriteData(0x2C);

  lcdWriteCommand(0xC2);  // Power Control 3
  lcdWriteData(0x01);

  lcdWriteCommand(0xC3);  // Power Control 4
  lcdWriteData(0x13);

  lcdWriteCommand(0xC4);  // Power Control 5
  lcdWriteData(0x20);

  lcdWriteCommand(0xC6);  // Frame Rate Control in Normal Mode
  lcdWriteData(0x0F);

  lcdWriteCommand(0xD0);  // Power Control 2
  lcdWriteData(0xA4);
  lcdWriteData(0xA1);

  lcdWriteCommand(0xD6);  // Power Control 7
  lcdWriteData(0xA1);

  lcdWriteCommand(0xE0);  // Positive Voltage Gamma Control
  lcdWriteData(0xF0);
  lcdWriteData(0x00);
  lcdWriteData(0x04);
  lcdWriteData(0x04);
  lcdWriteData(0x04);
  lcdWriteData(0x05);
  lcdWriteData(0x29);
  lcdWriteData(0x33);
  lcdWriteData(0x3E);
  lcdWriteData(0x38);
  lcdWriteData(0x12);
  lcdWriteData(0x12);
  lcdWriteData(0x28);
  lcdWriteData(0x30);

  lcdWriteCommand(0xE1);  // Negative Voltage Gamma Control
  lcdWriteData(0xF0);
  lcdWriteData(0x07);
  lcdWriteData(0x0A);
  lcdWriteData(0x0D);
  lcdWriteData(0x0B);
  lcdWriteData(0x07);
  lcdWriteData(0x28);
  lcdWriteData(0x33);
  lcdWriteData(0x3E);
  lcdWriteData(0x36);
  lcdWriteData(0x14);
  lcdWriteData(0x14);
  lcdWriteData(0x29);
  lcdWriteData(0x32);

  lcdWriteCommand(0x21);  // Display Inversion On
  lcdWriteCommand(0x11);  // Exit Sleep Mode
  delay(120);

  lcdWriteCommand(0x29);  // Display ON
}

// ==================== LCD Nəzarət Sahəsi Təyini ====================
/**
 * @brief LCD-nin göstəriləcək sahəsini təyin et
 * 
 * Bu funksiya, LCD kontroller-inə hansı piksellərin yenilənəcəyini bildir
 * 
 * @param Xstart: Başlanğıc X koordinatı
 * @param Ystart: Başlanğıc Y koordinatı
 * @param Xend: Son X koordinatı
 * @param Yend: Son Y koordinatı
 */
void lcdSetCursor(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend) {
  uint16_t x1 = Xstart + Offset_X;
  uint16_t x2 = Xend + Offset_X;
  uint16_t y1 = Ystart + Offset_Y;
  uint16_t y2 = Yend + Offset_Y;

  // Column address (X)
  lcdWriteCommand(0x2A);
  lcdWriteData(x1 >> 8);
  lcdWriteData(x1 & 0xFF);
  lcdWriteData(x2 >> 8);
  lcdWriteData(x2 & 0xFF);

  // Row address (Y)
  lcdWriteCommand(0x2B);
  lcdWriteData(y1 >> 8);
  lcdWriteData(y1 & 0xFF);
  lcdWriteData(y2 >> 8);
  lcdWriteData(y2 & 0xFF);

  lcdWriteCommand(0x2C);  // memory write
}

// ==================== LCD Sahə Yenilənməsi ====================
/**
 * @brief LCD-nin bir sahəsinə rəng məlumatı göndər
 * 
 * Bu funksiya LVGL-dən gələn rəng məlumatını LCD-ə ötürür.
 * Buffer-lik məlumat göndərmə üçün optimizə edilmişdir.
 * 
 * @param Xstart: Başlanğıc X koordinatı
 * @param Ystart: Başlanğıc Y koordinatı
 * @param Xend: Son X koordinatı
 * @param Yend: Son Y koordinatı
 * @param color: RGB565 rəng məlumatı
 */
void lcdAddWindow(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t* color) {
  // Sahə ölçülərini hesabla
  uint16_t Show_Width = Xend - Xstart + 1;
  uint16_t Show_Height = Yend - Ystart + 1;
  uint32_t numBytes = Show_Width * Show_Height * sizeof(uint16_t);

  // Qəbul buffer-i (geri məlumat üçün, istifadə edilmir)
  uint8_t Read_D[numBytes];

  // Nəzarət sahəsini təyin et
  lcdSetCursor(Xstart, Ystart, Xend, Yend);

  // Rəng məlumatını göndər
  lcdWriteDataNbyte((uint8_t*)color, Read_D, numBytes);
}

// ==================== Arxa Işıq (PWM) ====================
/**
 * @brief Arxa işığı (backlight) inisializə et
 * 
 * PWM istifadə edərək parlaqlıq səviyyəsi tənzimlənir
 */
void Backlight_Init(void) {
  // PWM üçün LED kanallı konfiqurə et
  ledcAttach(EXAMPLE_PIN_NUM_BK_LIGHT, Frequency, Resolution);

  // Arxa işığını %100 parlaqlığına qoy
  ledcWrite(EXAMPLE_PIN_NUM_BK_LIGHT, 100);
}

// ==================== Arxa Işıq Tənzimləyicisi ====================
/**
 * @brief Arxa işığın parlaqlığını təyin et
 * 
 * @param Light: Parlaqlıq səviyyəsi (0-100)
 *              0   = Söndür
 *              100 = Maksimum parlaqlıq
 */
void Set_Backlight(uint8_t Light) {
  // Girdi doğrulama
  if (Light > 100 || Light < 0) {
    Serial.println("Arxa işıq parametri 0-100 aralığında olmalıdır");
    return;
  }

  // PWM dəyərini hesabla (0-100 → 0-1023)
  uint32_t Backlight = Light * 10;
  ledcWrite(EXAMPLE_PIN_NUM_BK_LIGHT, Backlight);
}
