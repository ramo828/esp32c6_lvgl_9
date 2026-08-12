/*
 * SquareLine Studio tərəfindən yaradılmış Helper Funksiyaları Header Faylı
 * LVGL Versiyası: 9.5
 * 
 * Bu fayl UI komponentlərinin dəyərlərini dəyişdirmək üçün yardımçı funksiyaları ehtiva edir
 */

#ifndef _SQUARELINE_PROJECT_UI_HELPERS_H
#define _SQUARELINE_PROJECT_UI_HELPERS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ui.h"

// ==================== Helper Makros ====================

/** Müvəqqəti string buffer böyüklüyü */
#define _UI_TEMPORARY_STRING_BUFFER_SIZE 32

// ==================== Tərəqqi Şeridi (Bar) Dəyər Macroları ====================
#define _UI_BAR_PROPERTY_VALUE 0              // Animasyon olmadan dəyər
#define _UI_BAR_PROPERTY_VALUE_WITH_ANIM 1   // Animasyon ilə dəyər

/**
 * @brief Tərəqqi şeridinin dəyərini təyin et
 */
void _ui_bar_set_property(lv_obj_t * target, int id, int val);

// ==================== Əsas Xüsusiyyət Macroları ====================
#define _UI_BASIC_PROPERTY_POSITION_X 0  // X mövqeyi
#define _UI_BASIC_PROPERTY_POSITION_Y 1  // Y mövqeyi
#define _UI_BASIC_PROPERTY_WIDTH 2       // Eni
#define _UI_BASIC_PROPERTY_HEIGHT 3      // Hündürlüyü

/**
 * @brief Əsas xüsusiyyəti təyin et (mövqe, ölçü)
 */
void _ui_basic_set_property(lv_obj_t * target, int id, int val);

// ==================== Dropdown Makros ====================
#define _UI_DROPDOWN_PROPERTY_SELECTED 0  // Seçilmiş element

/**
 * @brief Dropdown-un seçilmiş elementini təyin et
 */
void _ui_dropdown_set_property(lv_obj_t * target, int id, int val);

// ==================== Şəkil Makros ====================
#define _UI_IMAGE_PROPERTY_IMAGE 0  // Şəkil mənbəyi

/**
 * @brief Şəkilin mənbəyini təyin et
 */
void _ui_image_set_property(lv_obj_t * target, int id, uint8_t * val);

// ==================== Etiket (Label) Makros ====================
#define _UI_LABEL_PROPERTY_TEXT 0  // Mətin

/**
 * @brief Etiketin mətnini təyin et
 */
void _ui_label_set_property(lv_obj_t * target, int id, const char * val);

// ==================== Roller Makros ====================
#define _UI_ROLLER_PROPERTY_SELECTED 0            // Seçilmiş (animasyon yoxdur)
#define _UI_ROLLER_PROPERTY_SELECTED_WITH_ANIM 1  // Seçilmiş (animasyon ilə)

/**
 * @brief Roller-in seçilmiş elementini təyin et
 */
void _ui_roller_set_property(lv_obj_t * target, int id, int val);

// ==================== Slider Makros ====================
#define _UI_SLIDER_PROPERTY_VALUE 0            // Dəyər (animasyon yoxdur)
#define _UI_SLIDER_PROPERTY_VALUE_WITH_ANIM 1  // Dəyər (animasyon ilə)

/**
 * @brief Slider-in dəyərini təyin et
 */
void _ui_slider_set_property(lv_obj_t * target, int id, int val);

// ==================== Ekran Dəyişdirmə ====================
/**
 * @brief Bir ekrandan başqa ekrana keç
 */
void _ui_screen_change(lv_obj_t ** target, lv_scr_load_anim_t fademode, int spd, int delay, void (*target_init)(void));

/**
 * @brief Ekranı silindir
 */
void _ui_screen_delete(void (*target)(void));

// ==================== Arc Makros ====================
/**
 * @brief Arc-ın dəyərini artır
 */
void _ui_arc_increment(lv_obj_t * target, int val);

// ==================== Bar Artırıcı ====================
/**
 * @brief Tərəqqi şeridinin dəyərini artır
 */
void _ui_bar_increment(lv_obj_t * target, int val, int anm);

// ==================== Slider Artırıcı ====================
/**
 * @brief Slider-in dəyərini artır
 */
void _ui_slider_increment(lv_obj_t * target, int val, int anm);

// ==================== Klaviatura ====================
/**
 * @brief Klaviaturanın hədəf textarea-sını təyin et
 */
void _ui_keyboard_set_target(lv_obj_t * keyboard, lv_obj_t * textarea);

// ==================== Flag Modifikasiyası ====================
#define _UI_MODIFY_FLAG_ADD 0     // Flag əlavə et
#define _UI_MODIFY_FLAG_REMOVE 1  // Flag çıxart
#define _UI_MODIFY_FLAG_TOGGLE 2  // Flag aç/qapla

/**
 * @brief Objektin flag-ını modifiqə et
 */
void _ui_flag_modify(lv_obj_t * target, int32_t flag, int value);

// ==================== State Modifikasiyası ====================
#define _UI_MODIFY_STATE_ADD 0     // State əlavə et
#define _UI_MODIFY_STATE_REMOVE 1  // State çıxart
#define _UI_MODIFY_STATE_TOGGLE 2  // State aç/qapla

/**
 * @brief Objektin state-ini modifiqə et
 */
void _ui_state_modify(lv_obj_t * target, int32_t state, int value);

// ==================== Textarea Cursor ====================
#define UI_MOVE_CURSOR_UP 0     // Kursor yuxarı
#define UI_MOVE_CURSOR_RIGHT 1  // Kursor sağa
#define UI_MOVE_CURSOR_DOWN 2   // Kursor aşağı
#define UI_MOVE_CURSOR_LEFT 3   // Kursor sola

/**
 * @brief Textarea-daki kursoru hərəkit et
 */
void _ui_textarea_move_cursor(lv_obj_t * target, int val);

// ==================== Event Callback ====================
/**
 * @brief Ekran yüklənmədən sonra onu silindir
 */
void scr_unloaded_delete_cb(lv_event_t * e);

// ==================== Şəffaflıq ====================
/**
 * @brief Objektin şəffaflığını təyin et (0-100)
 */
void _ui_opacity_set(lv_obj_t * target, int val);

// ==================== Animasiya Dəyişkənləri ====================

/** Animasiya istifadəçi məlumatı */
typedef struct _ui_anim_user_data_t {
    lv_obj_t * target;              // Hədəf objekti
    lv_img_dsc_t ** imgset;         // Şəkil seti
    int32_t imgset_size;            // Şəkil set ölçüsü
    int32_t val;                    // Cari dəyər
} ui_anim_user_data_t;

/**
 * @brief Animasiya istifadəçi məlumatını azad et
 */
void _ui_anim_callback_free_user_data(lv_anim_t * a);

/**
 * @brief X mövqeyi animasiya callback-i
 */
void _ui_anim_callback_set_x(lv_anim_t * a, int32_t v);

/**
 * @brief Y mövqeyi animasiya callback-i
 */
void _ui_anim_callback_set_y(lv_anim_t * a, int32_t v);

/**
 * @brief Eni animasiya callback-i
 */
void _ui_anim_callback_set_width(lv_anim_t * a, int32_t v);

/**
 * @brief Hündürlüyü animasiya callback-i
 */
void _ui_anim_callback_set_height(lv_anim_t * a, int32_t v);

/**
 * @brief Şəffaflıq animasiya callback-i
 */
void _ui_anim_callback_set_opacity(lv_anim_t * a, int32_t v);

/**
 * @brief Şəkil zoom animasiya callback-i
 */
void _ui_anim_callback_set_image_zoom(lv_anim_t * a, int32_t v);

/**
 * @brief Şəkil bucağı animasiya callback-i
 */
void _ui_anim_callback_set_image_angle(lv_anim_t * a, int32_t v);

/**
 * @brief Şəkil frame animasiya callback-i
 */
void _ui_anim_callback_set_image_frame(lv_anim_t * a, int32_t v);

/**
 * @brief X mövqeyi əl animasiya getter
 */
int32_t _ui_anim_callback_get_x(lv_anim_t * a);

/**
 * @brief Y mövqeyi əl animasiya getter
 */
int32_t _ui_anim_callback_get_y(lv_anim_t * a);

/**
 * @brief Eni əl animasiya getter
 */
int32_t _ui_anim_callback_get_width(lv_anim_t * a);

/**
 * @brief Hündürlüyü əl animasiya getter
 */
int32_t _ui_anim_callback_get_height(lv_anim_t * a);

/**
 * @brief Şəffaflıq əl animasiya getter
 */
int32_t _ui_anim_callback_get_opacity(lv_anim_t * a);

/**
 * @brief Şəkil zoom əl animasiya getter
 */
int32_t _ui_anim_callback_get_image_zoom(lv_anim_t * a);

/**
 * @brief Şəkil bucağı əl animasiya getter
 */
int32_t _ui_anim_callback_get_image_angle(lv_anim_t * a);

/**
 * @brief Şəkil frame əl animasiya getter
 */
int32_t _ui_anim_callback_get_image_frame(lv_anim_t * a);

// ==================== Dəyər Təyin Funksiyaları ====================

/**
 * @brief Arc-ın mətn dəyərini təyin et
 */
void _ui_arc_set_text_value(lv_obj_t * trg, lv_obj_t * src, const char * prefix, const char * postfix);

/**
 * @brief Slider-in mətn dəyərini təyin et
 */
void _ui_slider_set_text_value(lv_obj_t * trg, lv_obj_t * src, const char * prefix, const char * postfix);

/**
 * @brief Kontrol edilən mətn dəyərini təyin et
 */
void _ui_checked_set_text_value(lv_obj_t * trg, lv_obj_t * src, const char * txt_on, const char * txt_off);

/**
 * @brief Spinbox addımını dəyişdir
 */
void _ui_spinbox_step(lv_obj_t * target, int val);

/**
 * @brief Tema dəyişdir
 */
void _ui_switch_theme(int val);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
