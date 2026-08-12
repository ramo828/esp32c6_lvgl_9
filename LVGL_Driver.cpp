/*****************************************************************************
  LVGL 9.5 Şöfəri Faylı
  
  İşləyiş: 
  ESP32-C6 üçün LVGL 9.5 göstərişi idarə edir.
  LCD ekranı, buffer-ləri və timer-i inisializə edir.
******************************************************************************/
#include "LVGL_Driver.h"

// ==================== Buffer Dəyişənləri ====================
// Iki fərdi buffer istifadə edərək double buffering tətbiq edirik
static uint8_t buf1[LVGL_BUF_LEN];
static uint8_t buf2[LVGL_BUF_LEN];
static lv_display_t *display = NULL;

// ==================== Callback: Ekran Boyanması ====================
/**
 * @brief LVGL-dən LCD-ə rəngli piksəlləri göndər
 * @param disp: Display göstəricisi
 * @param area: Boyanacaq sahə
 * @param px_map: Piksel məlumatı
 * 
 * LVGL 9.5-dən yeni callback imzası:
 * void callback(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
 */
static void lvglDisplayLcd(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
  // piksel məlumatını LCD-ə göndər
  lcdAddWindow(area->x1, area->y1, area->x2, area->y2, (uint16_t *)px_map);
  
  // LVGL-ə bildirmə: boyanma tamamlandı
  lv_display_flush_ready(disp);
}

// ==================== Callback: Toxunma Paneli ====================
/**
 * @brief Toxunma panelindən məlumat oxu
 * @param indev: İnput device
 * @param data: İnput məlumatı
 * 
 * Qeyd: Həm zaman toxunma paneli istifadə olunmadığı üçün boş qalır.
 */
static void lvglTouchpadRead(lv_indev_t *indev, lv_indev_data_t *data)
{
  // Toxunma paneli aktiv deyil - heç bir məlumat göndərməyirik
  data->state = LV_INDEV_STATE_RELEASED;
}

// ==================== Callback: LVGL Tiker Artırıcı ====================
/**
 * @brief LVGL-ə keçən vaxtı bildirmə
 * @param arg: Arqument (istifadə edilmir)
 */
void exampleIncreaseLvglTick(void *arg)
{
  // LVGL sistemini güncəllə: keçən millisaniyəni sayıcıya əlavə et
  lv_tick_inc(EXAMPLE_LVGL_TICK_PERIOD_MS);
}

// ==================== LVGL Inisializasiyası ====================
/**
 * @brief Bütün LVGL sistem elementlərini inisializə et
 * 
 * Bu funksiya:
 * 1. LVGL kernelini inisializə edir
 * 2. Display driver-i yaradır
 * 3. Input device-i qeydə aparır
 * 4. Timer-i başlatır
 */
void lvglInit(void)
{
  // LVGL 9.5 kernelini inisializə et
  lv_init();

  // ==================== Display Driver Yaradılması ====================
  // LVGL 9.5-də yeni API istifadə olunur
  display = lv_display_create(LVGL_WIDTH, LVGL_HEIGHT);
  
  if (display == NULL) {
    // Xəta: Display yaradıla bilmədi
    return;
  }

  // Display buffer-lərini təyin et (double buffering)
  // LVGL 9.5-də lv_display_set_buffers() istifadə olunur
  lv_display_set_buffers(display, buf1, buf2, LVGL_BUF_LEN, LV_DISPLAY_RENDER_MODE_PARTIAL);

  // Flush callback-i (ekran güncəlləməsi) təyin et
  lv_display_set_flush_cb(display, lvglDisplayLcd);

  // Display sürə'tini kəskin yenilə əvəzinə tam yenilə (sürə səbəbi)
  // lv_display_set_default(display); // Standart olaraq təyin et (seçmə)

  // ==================== İnput Device (Toxunma Paneli) ====================
  // Toxunma paneli driver-i (hələ istifadə olunmur)
  static lv_indev_t *indev_touchpad;
  indev_touchpad = lv_indev_create();
  
  if (indev_touchpad != NULL) {
    lv_indev_set_type(indev_touchpad, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev_touchpad, lvglTouchpadRead);
    lv_indev_set_disp(indev_touchpad, display);
  }

  // ==================== Timer: LVGL Ticker ====================
  // ESP32 daxili timer-i istifadə edərək LVGL ticker-ini sürə
  const esp_timer_create_args_t lvgl_tick_timer_args = {
    .callback = &exampleIncreaseLvglTick,
    .name = "lvgl_tick"
  };
  
  static esp_timer_handle_t lvgl_tick_timer = NULL;
  
  if (lvgl_tick_timer == NULL) {
    esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer);
    esp_timer_start_periodic(lvgl_tick_timer, EXAMPLE_LVGL_TICK_PERIOD_MS * 1000);
  }
}

// ==================== Timer Loop: LVGL İcra ====================
/**
 * @brief Ana loop içində daim çağrılması lazım olan LVGL işçi funksiyası
 * 
 * Bu funksiya aşağıdakı işləri icra edir:
 * - Animasiyaları güncəllə
 * - Event-ləri işlə
 * - Redraw-ları hesabla
 * 
 * Həmin: delay() çağırması ilə gecikdiriliş qələbə gətir (kənar loop-da edilir)
 */
void timerLoop(void)
{
  // LVGL sisteminin cari dövrəsini icra et
  lv_timer_handler();
}