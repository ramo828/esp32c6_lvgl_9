#pragma once

#include <lvgl.h>
#include <esp_heap_caps.h>
#include "Display_ST7789.h"

// ==================== LVGL 9.5 Konfigürasyonu ====================
#define LVGL_WIDTH    (LCD_WIDTH)    // Ekranın eni piksellərdə
#define LVGL_HEIGHT   LCD_HEIGHT      // Ekranın hündürlüyü piksellərdə
#define LVGL_BUF_LEN  (LVGL_WIDTH * LVGL_HEIGHT / 10)  // Buffer böyüklüyü

// LVGL ticker periodu (millisaniyə)
#define EXAMPLE_LVGL_TICK_PERIOD_MS  5

// ==================== Funksiya Deklarasiyaları ====================
/**
 * @brief LVGL-ə ekranın fərdi xətlərini boyanması (static)
 * @param disp_drv: Display driver göstəricisi
 * @param area: Boyanacaq sahə
 * @param px_map: Piksel məlumatı
 */
static void lvglDisplayLcd(lv_display_t *disp_drv, const lv_area_t *area, uint8_t *px_map);

/**
 * @brief Toxunma panelindən məlumat oxu (static)
 * @param indev: İnput device driver
 * @param data: İnput məlumatı
 */
static void lvglTouchpadRead(lv_indev_t *indev, lv_indev_data_t *data);

/**
 * @brief LVGL ticker callback
 */
void exampleIncreaseLvglTick(void *arg);

/**
 * @brief LVGL sistemini inisializə et
 */
void lvglInit(void);

/**
 * @brief LVGL timer loop-unu icra et
 */
void timerLoop(void);
