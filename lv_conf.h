/**
 * @file lv_conf.h
 * @brief LVGL 9.5 Konfigürasyonu
 * 
 * ESP32-C6 üçün tənzimlənmiş LVGL seçənəkləri
 */

#ifndef LV_CONF_H
#define LV_CONF_H

// ==================== LVGL Versiya ====================
#define LVGL_VERSION_MAJOR     9
#define LVGL_VERSION_MINOR     5

// ==================== Rəng Dərinliyi ====================
#define LV_COLOR_DEPTH         16      // 16-bit RGB565

// ==================== Display Eni/Hündürlüyü ====================
#define LV_HOR_RES_MAX   320
#define LV_VER_RES_MAX   172

// ==================== LVGL Buffer ====================
#define LV_BUFFER_ALLOC_STATIC 1       // Statik buffer ayırması

// ==================== Display Driver Seçənəkləri ====================
// TFT_eSPI istifadə ETMƏ - Biz öz Display_ST7789 sürücüsü istifadə edirik
#define LV_USE_TFT_ESPI        0

// Diğər display sürücülərini devre dışı bırak
#define LV_USE_ST7735          0
#define LV_USE_ST7789          0
#define LV_USE_ILI9341         0
#define LV_USE_LINUX_FBDEV     0

// ==================== Touch Driver Seçənəkləri ====================
#define LV_USE_LINUX_INPUT     0
#define LV_USE_EVDEV           0

// ==================== Widget Seçənəkləri ====================
// Yalnız istifadə olunan widget-ləri aktivləştir
#define LV_USE_OBJ             1
#define LV_USE_BUTTON          1
#define LV_USE_LABEL           1
#define LV_USE_IMAGE           1
#define LV_USE_BAR             1
#define LV_USE_SLIDER          1
#define LV_USE_SPINNER         1
#define LV_USE_ARC             1

// Digər widget-ləri devre dışı bırak (memory qənaəti)
#define LV_USE_TEXTBOX         0
#define LV_USE_ROLLER          1
#define LV_USE_KEYBOARD        1
#define LV_USE_CHECKBOX        0
#define LV_USE_SWITCH          0
#define LV_USE_DROPDOWN        1
#define LV_USE_CALENDAR        0
#define LV_USE_MSGBOX          0
#define LV_USE_COLORPICKER     0
#define LV_USE_QRCODE          0
#define LV_USE_TABLE           0
#define LV_USE_TABVIEW         0
#define LV_USE_SPANGROUP       0
#define LV_USE_FLEX            1       // Layouting için gerekli
#define LV_USE_GRID            1       // Layouting için gerekli

// ==================== Animasiya ====================
#define LV_USE_ANIMATION       1
#define LV_ANIM_SPEED_DEF      200

// ==================== Stil ====================
#define LV_USE_THEME_DEFAULT   1
#define LV_USE_OUTLINE         1
#define LV_USE_SHADOW          0

// ==================== Input ====================
#define LV_USE_POINTER         1

// ==================== Rendering ====================
#define LV_USE_DRAW_SW         1       // Software rendering

// ==================== Debugging ====================
#define LV_USE_LOG             0       // Loq yazım devre dışı (performance üçün)
#define LV_USE_ASSERT          0       // Assert devre dışı

// ==================== Diğər Seçənəklər ====================
#define LV_USE_FONT_UNSCII_8   1
#define LV_USE_FONT_UNSCII_16  1
#define LV_USE_FONT_MONTSERRAT_20  1

#endif /* LV_CONF_H */
