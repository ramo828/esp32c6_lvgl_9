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

#include <WiFi.h>
#include <time.h>

const char* ssid = "Cracker";
const char* password = "totu7751055";

const char* ntpServer = "pool.ntp.org";

// Azerbaycan UTC+4
const long gmtOffset_sec = 4 * 3600;
const int daylightOffset_sec = 0;
const long int colors[] = {
  // ==================== MAGENTA ====================
  0x240619, 0x3A072A, 0x52083B, 0x6A094C,
  0x820A5D, 0x9A0B6E, 0xB30C7F, 0xCC0D90,
  0xE50EA1, 0xFF10B2, 0xFF1ABE, 0xFF25CA,
  0xFF30D6, 0xFF3BE2, 0xFF46EE, 0xFF51F4,
  0xFF5CFA, 0xFF67FC, 0xFF72FE, 0xFF80FF
};
// ==================== Setup: Sistem Inisializasiyası ====================
/**
 * @brief Arduino setup funksiyası - bir dəfə icra olunur
 * 
 * Prosedur:
 * 1. LCD-ni inisializə et
 * 2. LVGL sistemini inisializə et
 * 3. UI-ni yaradılma funksiyalarını icra et
 */
#define BOOT_BTN 9
unsigned long int lastTime = 0;
unsigned long int lastCounterTime = 0;
bool reverse_counter = false;

bool split_flag = false;

void time_task_wifi(void* parameter) {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println(F("Wifi baglandi"));
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  struct tm timeinfo;

  // Zaman gelene kadar bekle
  while (!getLocalTime(&timeinfo)) {
    Serial.println(F("Zaman alinanmadi, tekrar yoxlayin..."));
    delay(1000);
  }
  vTaskDelete(NULL);
}

void lvgl_task(void* vParam) {
  while (true) {
    struct tm timeinfo;
    static int counter = 0;
    if (digitalRead(BOOT_BTN) == LOW) {
      lv_screen_load(ui_sc2);
      vTaskDelay(50 / portTICK_PERIOD_MS);
    } else {
      lv_screen_load(ui_sc1);
    }
    if (getLocalTime(&timeinfo)) {
      lv_label_set_text(ui_hour, String(timeinfo.tm_hour).c_str());
      lv_label_set_text(ui_minute, String(timeinfo.tm_min).c_str());
      lv_label_set_text(ui_secondslabel2, String(timeinfo.tm_sec).c_str());

    } else {
      lv_label_set_text(ui_hour, String("nA").c_str());
      lv_label_set_text(ui_minute, String("nA").c_str());
      lv_label_set_text(ui_secondslabel2, String("nA").c_str());

    }
    unsigned long int nowTime = millis();
    if (nowTime - lastTime >= 1000) {
      lastTime = nowTime;
      split_flag = !split_flag;
    }
    if (nowTime - lastCounterTime >= 1) {
      lastCounterTime = nowTime;
      if (counter == (sizeof(colors) / sizeof(colors[0])) - 1) reverse_counter = true;
      else if (counter == 0) reverse_counter = false;
      if (reverse_counter)
        counter--;
      else
        counter++;
    }

    const char* seperator = split_flag == true ? ":" : "";
    lv_label_set_text(ui_splitter, seperator);
    lv_obj_set_style_bg_color(ui_sc1, lv_color_hex(colors[counter]), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_sc2, lv_color_hex(colors[counter]), LV_PART_MAIN | LV_STATE_DEFAULT);
    timerLoop();
    vTaskDelay(5 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  // LCD ST7789 ekranını başlat
  lcdInit();

  // LVGL sistemini başlat
  lvglInit();

  // UI ekranlarını ve komponentlərini yarad
  ui_init();
  xTaskCreate(time_task_wifi,
              "Wifi Task",
              10240,
              NULL,
              1,
              NULL);
  xTaskCreate(lvgl_task,
              "Clock Task",
              10240,
              NULL,
              2,
              NULL);
  pinMode(BOOT_BTN, INPUT_PULLUP);
}

// ==================== Loop: Ana Dövrə ====================
/**
 * @brief Arduino loop funksiyası - sonsuz döngü
 * 
 * Bu funksiya hər millisaniyədə çağrılır:
 * - LVGL timer handler-ini icra et (animasiyalar, event-lər)
 * - Kiçik gecikdirmə əlavə et (CPU yüklənməsi azaltmaq üçün)
 */
void loop() {
  // static int counter = 0;

  // CPU yükünü azaltmaq üçün kiçik gecikdirmə
  delay(5);  // 5 millisaniyə gözlə
}
