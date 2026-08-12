/*
 * SquareLine Studio tərəfindən yaradılmış Screen1 Header Faylı
 * LVGL Versiyası: 9.5
 * 
 * Bu fayl Screen1 ekranının tanımlamalarını ehtiva edir
 */

#ifndef UI_SCREEN1_H
#define UI_SCREEN1_H

#ifdef __cplusplus
extern "C" {
#endif

// ==================== Screen1 Ekranı ====================

/**
 * @brief Screen1 ekranını inisializə et
 */
extern void uiScreen1ScreenInit(void);

/**
 * @brief Screen1 ekranını yox et
 */
extern void uiScreen1ScreenDestroy(void);

// ==================== Screen1 Objektləri ====================

/** @brief Screen1 kök objekti */
extern lv_obj_t * uiScreen1;

/** @brief Düymə komponenti */
extern lv_obj_t * uiButton1;

/** @brief Etiket/Label komponenti */
extern lv_obj_t * uiLabel1;

/** @brief Spinner (yüklənmə göstəricisi) komponenti */
extern lv_obj_t * uiSpinner1;

/** @brief Tərəqqi şəridi (Bar) komponenti */
extern lv_obj_t * uiBar1;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif