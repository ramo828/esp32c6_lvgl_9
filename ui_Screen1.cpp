/*
 * SquareLine Studio tərəfindən yaradılmış Screen1 İmplementasiya Faylı
 * LVGL Versiyası: 9.5
 * 
 * LVGL 9.5 API ilə uyumlu olacaq şəkildə yenidən yazılmışdır
 */

#include "ui.h"

// ==================== Screen1 Objektləri ====================

/** @brief Screen1 kök ekranı */
lv_obj_t * uiScreen1 = NULL;

/** @brief Düymə komponenti */
lv_obj_t * uiButton1 = NULL;

/** @brief Düymənin daxilində etiket */
lv_obj_t * uiLabel1 = NULL;

/** @brief Yüklənmə göstəricisi (Spinner) */
lv_obj_t * uiSpinner1 = NULL;

/** @brief Tərəqqi şəridi (Progress Bar) */
lv_obj_t * uiBar1 = NULL;

// ==================== Event Funksiyaları ====================
// (Mövcud deyil - gerekti halda əlavə edilə bilər)

// ==================== Screen1 İnisializasiyası ====================
/**
 * @brief Screen1 ekranını inisializə et
 * 
 * Bu funksiya:
 * 1. Kök ekranı yaradır
 * 2. Arxa şəklini təyin edir
 * 3. Düymə, label, spinner və bar komponentlərini yaradır
 * 4. Hər komponentin dəyərlərini və stillərinə təyin edir
 */
void uiScreen1ScreenInit(void)
{
  // ==================== Kök Ekranı Yaradılması ====================
  uiScreen1 = lv_obj_create(NULL);

  // Ekranın sürüşməsini qora (static screen)
  lv_obj_remove_flag(uiScreen1, LV_OBJ_FLAG_SCROLLABLE);

  // Arxa şəklini təyin et
  lv_obj_set_style_bg_image_src(uiScreen1, &ui_img_waveshare_image10_png, LV_PART_MAIN | LV_STATE_DEFAULT);

  // ==================== Düymə (Button1) ====================
  uiButton1 = lv_button_create(uiScreen1);

  // Ölçülər
  lv_obj_set_width(uiButton1, 100);    // Eni
  lv_obj_set_height(uiButton1, 50);    // Hündürlüyü

  // Mövqe
  lv_obj_set_x(uiButton1, 3);
  lv_obj_set_y(uiButton1, -84);
  lv_obj_set_align(uiButton1, LV_ALIGN_CENTER);

  // Flaglar
  lv_obj_add_flag(uiButton1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     // Fokus olduqda sürüşmə
  lv_obj_remove_flag(uiButton1, LV_OBJ_FLAG_SCROLLABLE);        // Özü sürüşənməz

  // Fon rəngi (ağ, %20 şəffaflıq)
  lv_obj_set_style_bg_color(uiButton1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(uiButton1, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

  // ==================== Etiket (Label1) ====================
  uiLabel1 = lv_label_create(uiButton1);

  // Ölçülər (məzmun ölçüsü)
  lv_obj_set_width(uiLabel1, LV_SIZE_CONTENT);
  lv_obj_set_height(uiLabel1, LV_SIZE_CONTENT);

  // Hizalama (mərkəz)
  lv_obj_set_align(uiLabel1, LV_ALIGN_CENTER);

  // Mətin
  lv_label_set_text(uiLabel1, "Klik");

  // ==================== Spinner (Yüklənmə Göstəricisi) ====================
  // LVGL 9.5-də spinner yaradılması
  uiSpinner1 = lv_spinner_create(uiScreen1);

  // Ölçülər
  lv_obj_set_width(uiSpinner1, 80);
  lv_obj_set_height(uiSpinner1, 80);

  // Mövqe
  lv_obj_set_x(uiSpinner1, 2);
  lv_obj_set_y(uiSpinner1, 5);
  lv_obj_set_align(uiSpinner1, LV_ALIGN_CENTER);

  // Flaglar (klikləyə bilməz)
  lv_obj_remove_flag(uiSpinner1, LV_OBJ_FLAG_CLICKABLE);

  // Stil: Ağ fon, şəffaf
  lv_obj_set_style_bg_color(uiSpinner1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(uiSpinner1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  // ==================== Tərəqqi Şeridi (Progress Bar) ====================
  uiBar1 = lv_bar_create(uiScreen1);

  // Başlanğıc dəyər
  lv_bar_set_value(uiBar1, 25, LV_ANIM_OFF);
  lv_bar_set_start_value(uiBar1, 0, LV_ANIM_OFF);

  // Ölçülər
  lv_obj_set_width(uiBar1, 150);
  lv_obj_set_height(uiBar1, 10);

  // Mövqe
  lv_obj_set_x(uiBar1, -1);
  lv_obj_set_y(uiBar1, 100);
  lv_obj_set_align(uiBar1, LV_ALIGN_CENTER);
}

/**
 * @brief Screen1 ekranını yox et (silindir)
 * 
 * Bu funksiya Screen1-i və bütün altında olan objektləri silindir
 * və dəyişkənləri NULL-a qoya
 */
void uiScreen1ScreenDestroy(void)
{
  // Screen1-i sil (bütün alt-objektlər də silinir)
  if (uiScreen1 != NULL) {
    lv_obj_delete(uiScreen1);
  }

  // Bütün dəyişkənləri NULL-a qoy
  uiScreen1 = NULL;
  uiButton1 = NULL;
  uiLabel1 = NULL;
  uiSpinner1 = NULL;
  uiBar1 = NULL;
}
