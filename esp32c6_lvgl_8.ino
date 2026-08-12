/*
 * ESP32-C6 LVGL 9.5 Layihəsi
 * 
 * Bu fayl ESP32-C6 üzərində LVGL 9.5 GUI-ni işə salır
 * Ekran: ST7789 (SPI)
 * Toxunma paneli: İstifadə olunmur (seçmə)
 * 
 * Lisenziya: MIT
 */

// ==================== Header Faylları ====================
#include "Display_ST7789.h"  // LCD driver
#include "LVGL_Driver.h"     // LVGL driver
#include "ui.h"              // LVGL UI

// ==================== Setup: Sistem Inisializasiyası ====================
/**
 * @brief Arduino setup funksiyası - bir dəfə icra olunur
 * 
 * Prosedur:
 * 1. LCD-ni inisializə et
 * 2. LVGL sistemini inisializə et
 * 3. UI-ni yaradılma funksiyalarını icra et
 */
void setup()
{
  // LCD ST7789 ekranını başlat
  lcdInit();

  // LVGL sistemini başlat
  lvglInit();

  // UI ekranlarını ve komponentlərini yarad
  uiInit();
}

// ==================== Loop: Ana Dövrə ====================
/**
 * @brief Arduino loop funksiyası - sonsuz döngü
 * 
 * Bu funksiya hər millisaniyədə çağrılır:
 * - LVGL timer handler-ini icra et (animasiyalar, event-lər)
 * - Kiçik gecikdirmə əlavə et (CPU yüklənməsi azaltmaq üçün)
 */
void loop()
{
  // LVGL sisteminin cari dövrəsini icra et
  // Bu funksiya:
  // - Animasiyaları güncəllə
  // - Event-ləri emal et
  // - Redraw-ları hesabla
  // - Ekranı güncəllə
  timerLoop();

  // CPU yükünü azaltmaq üçün kiçik gecikdirmə
  delay(5);  // 5 millisaniyə gözlə
}
