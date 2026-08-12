/*
 * SquareLine Studio tərəfindən yaradılmış UI Header Faylı
 * LVGL Versiyası: 9.5
 * Layihə adı: esp32c6_lvgl_8
 * 
 * Bu fayl LVGL 9.5 ilə tamamilə uyumlu olacaq şəkildə yenidən yazılmışdır.
 */

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

// ==================== LVGL Header ====================
#if defined __has_include
  #if __has_include("lvgl.h")
    #include "lvgl.h"
  #elif __has_include("lvgl/lvgl.h")
    #include "lvgl/lvgl.h"
  #else
    #include "lvgl.h"
  #endif
#else
  #include "lvgl.h"
#endif

// ==================== UI Helper Faylları ====================
#include "ui_helpers.h"
#include "ui_events.h"

// ==================== EKRANLAR ====================
#include "ui_Screen1.h"

// ==================== DƏYIŞƏNLƏR ====================

// Event Object-ləri
extern lv_obj_t * uiInitialActions0;

// Şəkillər və Şəkil Setləri
LV_IMG_DECLARE(ui_img_waveshare_image10_png);  // Waveshare şəkili

// ==================== UI Funksiyaları ====================

/**
 * @brief UI-ni inisializə et
 */
void uiInit(void);

/**
 * @brief UI-ni yox et (tam təmizlə)
 */
void uiDestroy(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
