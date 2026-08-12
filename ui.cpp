/*
 * SquareLine Studio tərəfindən yaradılmış UI İmplementasiya Faylı
 * LVGL Versiyası: 9.5
 * Layihə adı: esp32c6_lvgl_8
 * 
 * Bu fayl LVGL 9.5 ilə tamamilə uyumlu olacaq şəkildə yenidən yazılmışdır.
 */

#include "ui.h"
#include "ui_helpers.h"

// ==================== DƏYIŞƏNLƏR ====================

// Event Object-ləri
lv_obj_t * uiInitialActions0 = NULL;

// ==================== LVGL Ayarlarının Yoxlanması ====================

/**
 * LVGL 9.5 ilə uyumluluq yoxlaması
 * 
 * Qeyd: LVGL 9.5-də rəng dərinliyi ayarları lv_conf.h-da konfiqurə edilir
 * Tipik olarak RGB565 (16-bit) istifadə olunur
 */

// ==================== Animasiyalar ====================
// (Mövcud deyil - custom animasiyalar gerekti halda əlavə edilə bilər)

// ==================== Funksiyalar ====================

/**
 * @brief UI sistemini inisializə et
 * 
 * Bu funksiya:
 * 1. LVGL default temasi təyin edir
 * 2. Screen1-i inisializə edir
 * 3. Başlanğıc ekranı göstərir
 */
void uiInit(void)
{
  // Default display-i əl
  lv_display_t *dispp = lv_display_get_default();

  if (dispp == NULL) {
    // Xəta: Display tapa bilmədi
    return;
  }

  // LVGL 9.5 şəkildə tema yaradılması
  // Default mavi-qırmızı tema
  lv_theme_t * theme = lv_theme_default_init(
    dispp,
    lv_palette_main(LV_PALETTE_BLUE),      // Əsas rəng: Mavi
    lv_palette_main(LV_PALETTE_RED),       // İkinci rəng: Qırmızı
    true,                                   // Təmiz stil (dark mode)
    LV_FONT_DEFAULT                         // Default font
  );

  // Temani display-ə əlavə et
  lv_display_set_theme(dispp, theme);

  // Screen1-i inisializə et
  uiScreen1ScreenInit();

  // Initial actions object-i yaratılması
  uiInitialActions0 = lv_obj_create(NULL);

  // Default ekranı göstər
  lv_screen_load(uiScreen1);
}

/**
 * @brief Bütün UI elementlərini yox et (silindir)
 * 
 * Bu funksiya tüm UI-ni təmizləyər və yaddaşı azad edir
 */
void uiDestroy(void)
{
  // Screen1-i yox et
  uiScreen1ScreenDestroy();

  // Initial actions object-ini sil
  if (uiInitialActions0 != NULL) {
    lv_obj_delete(uiInitialActions0);
    uiInitialActions0 = NULL;
  }
}
