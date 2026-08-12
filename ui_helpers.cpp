/*
 * SquareLine Studio tərəfindən yaradılmış Helper Funksiyaları İmplementasiya Faylı
 * LVGL Versiyası: 9.5
 * 
 * Bu fayl UI komponentlərinin dəyərlərini dəyişdirmək üçün yardımçı funksiyaların
 * təsisindən təşkil olunur (LVGL 9.5 ilə uyumlu)
 */

#include "ui_helpers.h"

// ==================== Tərəqqi Şeridi (Bar) Dəyər Təyini ====================
/**
 * @brief Tərəqqi şeridinin dəyərini təyin et
 * 
 * @param target: Hədəf tərəqqi şeridi
 * @param id: Əməliyyat ID-si (_UI_BAR_PROPERTY_VALUE və ya _UI_BAR_PROPERTY_VALUE_WITH_ANIM)
 * @param val: Yeni dəyər
 */
void _ui_bar_set_property(lv_obj_t *target, int id, int val) {
  if (id == _UI_BAR_PROPERTY_VALUE_WITH_ANIM)
    lv_bar_set_value(target, val, LV_ANIM_ON);   // Animasyon ilə
  if (id == _UI_BAR_PROPERTY_VALUE)
    lv_bar_set_value(target, val, LV_ANIM_OFF);  // Animasyon olmadan
}

// ==================== Əsas Xüsusiyyət Təyini ====================
/**
 * @brief Əsas xüsusiyyətləri (mövqe, ölçü) təyin et
 */
void _ui_basic_set_property(lv_obj_t *target, int id, int val) {
  if (id == _UI_BASIC_PROPERTY_POSITION_X)
    lv_obj_set_x(target, val);          // X mövqeyi
  if (id == _UI_BASIC_PROPERTY_POSITION_Y)
    lv_obj_set_y(target, val);          // Y mövqeyi
  if (id == _UI_BASIC_PROPERTY_WIDTH)
    lv_obj_set_width(target, val);      // Eni
  if (id == _UI_BASIC_PROPERTY_HEIGHT)
    lv_obj_set_height(target, val);     // Hündürlüyü
}

// ==================== Dropdown Seçimi ====================
/**
 * @brief Dropdown seçilmiş elementini dəyişdir
 */
#if LV_USE_DROPDOWN
void _ui_dropdown_set_property(lv_obj_t *target, int id, int val) {
  if (id == _UI_DROPDOWN_PROPERTY_SELECTED)
    lv_dropdown_set_selected(target, val);
}
#endif

// ==================== Şəkil Mənbəyi ====================
/**
 * @brief Şəkil mənbəyini dəyişdir
 */
void _ui_image_set_property(lv_obj_t *target, int id, uint8_t *val) {
  if (id == _UI_IMAGE_PROPERTY_IMAGE)
    lv_img_set_src(target, val);
}

// ==================== Etiket Mətnini ====================
/**
 * @brief Etiket mətnini dəyişdir
 */
void _ui_label_set_property(lv_obj_t *target, int id, const char *val) {
  if (id == _UI_LABEL_PROPERTY_TEXT)
    lv_label_set_text(target, val);
}

// ==================== Roller Seçimi ====================
/**
 * @brief Roller seçilmiş elementini dəyişdir
 */
#if LV_USE_ROLLER
void _ui_roller_set_property(lv_obj_t *target, int id, int val) {
  if (id == _UI_ROLLER_PROPERTY_SELECTED)
    lv_roller_set_selected(target, val, LV_ANIM_ON);   // Animasyon ilə
  if (id == _UI_ROLLER_PROPERTY_SELECTED_WITHOUT_ANIM)
    lv_roller_set_selected(target, val, LV_ANIM_OFF);  // Animasyon olmadan
}
#endif

// ==================== Slider Dəyəri ====================
/**
 * @brief Slider dəyərini dəyişdir
 */
void _ui_slider_set_property(lv_obj_t *target, int id, int val) {
  if (id == _UI_SLIDER_PROPERTY_VALUE_WITH_ANIM)
    lv_slider_set_value(target, val, LV_ANIM_ON);    // Animasyon ilə
  if (id == _UI_SLIDER_PROPERTY_VALUE)
    lv_slider_set_value(target, val, LV_ANIM_OFF);   // Animasyon olmadan
}

// ==================== Ekran Dəyişdirmə ====================
/**
 * @brief Bir ekrandan digərinə keç
 * 
 * LVGL 9.5-də lv_screen_load_anim() istifadə olunur (əvvəlcə lv_scr_load_anim())
 */
void _ui_screen_change(lv_obj_t **target, lv_scr_load_anim_t fademode, int spd, int delay, void (*target_init)(void)) {
  if (*target == NULL)
    target_init();  // Ekran yaradılmamışsa yaradılması
  
  // LVGL 9.5 API (son parametr: en_mod = false)
  lv_screen_load_anim(*target, fademode, spd, delay, false);
}

// ==================== Ekran Silişi ====================
/**
 * @brief Ekranı silindir
 */
void _ui_screen_delete(void (*target)(void)) {
  if (target != NULL) {
    target();  // Destroy funksiyasını çağır
  }
}

// ==================== Arc Artırıcısı ====================
/**
 * @brief Arc-ın dəyərini artır/azalt
 */
void _ui_arc_increment(lv_obj_t *target, int val) {
  int old = lv_arc_get_value(target);
  lv_arc_set_value(target, old + val);
  lv_obj_send_event(target, LV_EVENT_VALUE_CHANGED, NULL);  // Event göndər
}

// ==================== Tərəqqi Şeridi Artırıcısı ====================
/**
 * @brief Tərəqqi şeridinin dəyərini artır/azalt
 */
void _ui_bar_increment(lv_obj_t *target, int val, int anm) {
  int old = lv_bar_get_value(target);
  lv_bar_set_value(target, old + val, (lv_anim_enable_t)anm);
}

// ==================== Slider Artırıcısı ====================
/**
 * @brief Slider-in dəyərini artır/azalt
 */
void _ui_slider_increment(lv_obj_t *target, int val, int anm) {
  int old = lv_slider_get_value(target);
  lv_slider_set_value(target, old + val, (lv_anim_enable_t)anm);
  lv_obj_send_event(target, LV_EVENT_VALUE_CHANGED, NULL);  // Event göndər
}

// ==================== Klaviatura Bağlanması ====================
/**
 * @brief Klaviaturanı textarea ilə bağla
 */
#if LV_USE_KEYBOARD
void _ui_keyboard_set_target(lv_obj_t *keyboard, lv_obj_t *textarea) {
  lv_keyboard_set_textarea(keyboard, textarea);
}
#endif

// ==================== Flag Modifikasiyası ====================
/**
 * @brief Objektin flag-ını əlavə et/çıxart/aç-qapla
 */
void _ui_flag_modify(lv_obj_t *target, int32_t flag, int value) {
  if (value == _UI_MODIFY_FLAG_TOGGLE) {
    // Toggle: əgər varsa çıxart, yoxdursa əlavə et
    if (lv_obj_has_flag(target, (lv_obj_flag_t)flag))
      lv_obj_remove_flag(target, (lv_obj_flag_t)flag);
    else
      lv_obj_add_flag(target, (lv_obj_flag_t)flag);
  } else if (value == _UI_MODIFY_FLAG_ADD) {
    // Əlavə et
    lv_obj_add_flag(target, (lv_obj_flag_t)flag);
  } else {
    // Çıxart
    lv_obj_remove_flag(target, (lv_obj_flag_t)flag);
  }
}

// ==================== State Modifikasiyası ====================
/**
 * @brief Objektin state-ini əlavə et/çıxart/aç-qapla
 */
void _ui_state_modify(lv_obj_t *target, int32_t state, int value) {
  if (value == _UI_MODIFY_STATE_TOGGLE) {
    // Toggle: əgər varsa çıxart, yoxdursa əlavə et
    if (lv_obj_has_state(target, (lv_state_t)state))
      lv_obj_remove_state(target, (lv_state_t)state);
    else
      lv_obj_add_state(target, (lv_state_t)state);
  } else if (value == _UI_MODIFY_STATE_ADD) {
    // Əlavə et
    lv_obj_add_state(target, (lv_state_t)state);
  } else {
    // Çıxart
    lv_obj_remove_state(target, (lv_state_t)state);
  }
}

// ==================== Textarea Kursor Hərəkəti ====================
/**
 * @brief Textarea-daki kursoru hərəkit et
 */
void _ui_textarea_move_cursor(lv_obj_t *target, int val) {
  if (val == UI_MOVE_CURSOR_UP)
    lv_textarea_cursor_up(target);     // Yuxarı
  if (val == UI_MOVE_CURSOR_RIGHT)
    lv_textarea_cursor_right(target);  // Sağa
  if (val == UI_MOVE_CURSOR_DOWN)
    lv_textarea_cursor_down(target);   // Aşağı
  if (val == UI_MOVE_CURSOR_LEFT)
    lv_textarea_cursor_left(target);   // Sola

  // Fokus əlavə et
  lv_obj_add_state(target, LV_STATE_FOCUSED);
}

// ==================== Ekran Yüklənməsi Callback ====================
/** Ekran silinmə callback-i tərifi */
typedef void (*screen_destroy_cb_t)(void);

/**
 * @brief Ekran yüklənmədikdən sonra onu silindir
 */
void scr_unloaded_delete_cb(lv_event_t *e) {
  // Istifadəçi məlumatından destroy callback əl
  screen_destroy_cb_t destroy_cb = (screen_destroy_cb_t)lv_event_get_user_data(e);
  if (destroy_cb) {
    destroy_cb();  // Spesifik ekran destroy funksiyasını çağır
  }
}

// ==================== Şəffaflıq ====================
/**
 * @brief Objektin şəffaflığını təyin et (0-100%)
 */
void _ui_opacity_set(lv_obj_t *target, int val) {
  lv_obj_set_style_opa(target, val, LV_PART_MAIN);
}

// ==================== Animasiya Callback-ləri ====================

/**
 * @brief Animasiya istifadəçi məlumatını azad et
 */
void _ui_anim_callback_free_user_data(lv_anim_t *a) {
  lv_free(a->user_data);
  a->user_data = NULL;
}

/**
 * @brief X mövqeyi animasiyası
 */
void _ui_anim_callback_set_x(lv_anim_t *a, int32_t v) {
  ui_anim_user_data_t *usr = (ui_anim_user_data_t *)a->user_data;
  lv_obj_set_x(usr->target, v);
}

/**
 * @brief Y mövqeyi animasiyası
 */
void _ui_anim_callback_set_y(lv_anim_t *a, int32_t v) {
  ui_anim_user_data_t *usr = (ui_anim_user_data_t *)a->user_data;
  lv_obj_set_y(usr->target, v);
}

/**
 * @brief Eni animasiyası
 */
void _ui_anim_callback_set_width(lv_anim_t *a, int32_t v) {
  ui_anim_user_data_t *usr = (ui_anim_user_data_t *)a->user_data;
  lv_obj_set_width(usr->target, v);
}

/**
 * @brief Hündürlüyü animasiyası
 */
void _ui_anim_callback_set_height(lv_anim_t *a, int32_t v) {
  ui_anim_user_data_t *usr = (ui_anim_user_data_t *)a->user_data;
  lv_obj_set_height(usr->target, v);
}

/**
 * @brief Şəffaflıq animasiyası
 */
void _ui_anim_callback_set_opacity(lv_anim_t *a, int32_t v) {
  ui_anim_user_data_t *usr = (ui_anim_user_data_t *)a->user_data;
  lv_obj_set_style_opa(usr->target, v, 0);
}

/**
 * @brief Şəkil zoom animasiyası
 */
void _ui_anim_callback_set_image_zoom(lv_anim_t *a, int32_t v) {
  ui_anim_user_data_t *usr = (ui_anim_user_data_t *)a->user_data;
  lv_img_set_zoom(usr->target, v);
}

/**
 * @brief Şəkil bucağı animasiyası
 */
void _ui_anim_callback_set_image_angle(lv_anim_t *a, int32_t v) {
  ui_anim_user_data_t *usr = (ui_anim_user_data_t *)a->user_data;
  lv_img_set_angle(usr->target, v);
}

/**
 * @brief Şəkil frame animasiyası
 */
void _ui_anim_callback_set_image_frame(lv_anim_t *a, int32_t v) {
  ui_anim_user_data_t *usr = (ui_anim_user_data_t *)a->user_data;
  usr->val = v;
  if (v < 0) v = 0;
  if (v >= usr->imgset_size) v = usr->imgset_size - 1;
  lv_img_set_src(usr->target, usr->imgset[v]);
}

// ==================== Animasiya Getter Callback-ləri ====================

/**
 * @brief X mövqeyi getter
 */
int32_t _ui_anim_callback_get_x(lv_anim_t *a) {
  ui_anim_user_data_t *usr = (ui_anim_user_data_t *)a->user_data;
  return lv_obj_get_x_aligned(usr->target);
}

/**
 * @brief Y mövqeyi getter
 */
int32_t _ui_anim_callback_get_y(lv_anim_t *a) {
  ui_anim_user_data_t *usr = (ui_anim_user_data_t *)a->user_data;
  return lv_obj_get_y_aligned(usr->target);
}

/**
 * @brief Eni getter
 */
int32_t _ui_anim_callback_get_width(lv_anim_t *a) {
  ui_anim_user_data_t *usr = (ui_anim_user_data_t *)a->user_data;
  return lv_obj_get_width(usr->target);
}

/**
 * @brief Hündürlüyü getter
 */
int32_t _ui_anim_callback_get_height(lv_anim_t *a) {
  ui_anim_user_data_t *usr = (ui_anim_user_data_t *)a->user_data;
  return lv_obj_get_height(usr->target);
}

/**
 * @brief Şəffaflıq getter
 */
int32_t _ui_anim_callback_get_opacity(lv_anim_t *a) {
  ui_anim_user_data_t *usr = (ui_anim_user_data_t *)a->user_data;
  return lv_obj_get_style_opa(usr->target, LV_PART_MAIN);
}

/**
 * @brief Şəkil zoom getter
 */
int32_t _ui_anim_callback_get_image_zoom(lv_anim_t *a) {
  ui_anim_user_data_t *usr = (ui_anim_user_data_t *)a->user_data;
  return lv_img_get_zoom(usr->target);
}

/**
 * @brief Şəkil bucağı getter
 */
int32_t _ui_anim_callback_get_image_angle(lv_anim_t *a) {
  ui_anim_user_data_t *usr = (ui_anim_user_data_t *)a->user_data;
  return lv_img_get_angle(usr->target);
}

/**
 * @brief Şəkil frame getter
 */
int32_t _ui_anim_callback_get_image_frame(lv_anim_t *a) {
  ui_anim_user_data_t *usr = (ui_anim_user_data_t *)a->user_data;
  return usr->val;
}

// ==================== Dəyər Mətn Təyini ====================

/**
 * @brief Arc dəyərini mətn üçün mətn ilə təyin et
 * 
 * @param trg: Hədəf label
 * @param src: Mənbə arc
 * @param prefix: Ön sözlə
 * @param postfix: Arxa sözlə
 */
void _ui_arc_set_text_value(lv_obj_t *trg, lv_obj_t *src, const char *prefix, const char *postfix) {
  char buf[_UI_TEMPORARY_STRING_BUFFER_SIZE];
  lv_snprintf(buf, sizeof(buf), "%s%d%s", prefix, (int)lv_arc_get_value(src), postfix);
  lv_label_set_text(trg, buf);
}

/**
 * @brief Slider dəyərini mətn üçün mətn ilə təyin et
 */
void _ui_slider_set_text_value(lv_obj_t *trg, lv_obj_t *src, const char *prefix, const char *postfix) {
  char buf[_UI_TEMPORARY_STRING_BUFFER_SIZE];
  lv_snprintf(buf, sizeof(buf), "%s%d%s", prefix, (int)lv_slider_get_value(src), postfix);
  lv_label_set_text(trg, buf);
}

/**
 * @brief Checkbox/Switch dəyərini mətnlə təyin et
 */
void _ui_checked_set_text_value(lv_obj_t *trg, lv_obj_t *src, const char *txt_on, const char *txt_off) {
  if (lv_obj_has_state(src, LV_STATE_CHECKED))
    lv_label_set_text(trg, txt_on);   // Aktivdə
  else
    lv_label_set_text(trg, txt_off);  // Passivdə
}

/**
 * @brief Spinbox addımını dəyişdir
 */
void _ui_spinbox_step(lv_obj_t *target, int val) {
  if (val > 0)
    lv_spinbox_increment(target);  // Artır
  else
    lv_spinbox_decrement(target);  // Azalt

  lv_obj_send_event(target, LV_EVENT_VALUE_CHANGED, NULL);
}

/**
 * @brief Temayı dəyişdir
 */
void _ui_switch_theme(int val) {
#ifdef UI_THEME_ACTIVE
  ui_theme_set(val);
#endif
}
