# ESP32-C6 LVGL 9.5 Layihəsi

Bu repositoriy **ESP32-C6** mikrokontroller üzərində **LVGL 9.5** (Light and Versatile Graphics Library) işə salmaq üçün yüngül bir başlanğıc şablonu təmin edir. **SquareLine Studio** kimi UI dizayn alətləri ilə hərtərəfli inteqrasiyaya hazırlanmışdır.

---

## 🚀 Xüsusiyyətlər

- **Mikrokontroller:** ESP32-C6 (RISC-V arxitekturası) yerli dəstəyi
- **Qrafika Engine:** LVGL 9.5 inteqrasiyası
- **UI İşəlliyətləndirmə:** SquareLine Studio ixrac parametrlərinə uyğun tənzimlənmiş
- **Periferik Dəstəyi:** SPI/I2C pin-lərini ekran və toxunma paneli sürücüləri üçün tənzimləməniz siz tərəfindən
- **Tam Dokumentasiya:** Azərbaycanca şərh əlavəsi ilə ətraflı

---

## 🛠️ Aparat və Proqram Tələbləri

### Aparat

- **ESP32-C6 Əvvəldən quraşdırılmış Plata**
- **SPI/RGB Ekran Modulu** (məs., ST7789, ILI9341, GC9A01)
- **Toxunma Paneli Nəzarətçi** (seçmə, məs., CST816S, FT6336)

### Proqram

- **Arduino IDE** (v2.0+) və ya **PlatformIO**
- **ESP32 Arduino Core** (v3.0.0+ - ESP32-C6 dəstəyi üçün tələb olunur)
- **LVGL Kütübxanəsi** (`v9.5+` tövsiyə olunur)

---

## ⚙️ Qurulum və Tənzimləmə

### 1. Repositoriyni Klonlamaq

```bash
git clone https://github.com/ramo828/esp32c6_lvgl_8.git
cd esp32c6_lvgl_8
```

### 2. Arduino IDE-də Açmaq

1. Arduino IDE-ni açın
2. **File** → **Open** seçin
3. `esp32c6_lvgl_8.ino` faylını seçin

### 3. Lövhə Seçimi

1. **Tools** → **Board** seçin
2. **ESP32** → **ESP32-C6 Dev Module** seçin

### 4. Port Seçimi

1. **Tools** → **Port** seçin
2. ESP32-C6-ın bağlı olduğu seriyanı seçin (məs., `/dev/ttyUSB0`)

### 5. Yükləmə

1. **Sketch** → **Upload** seçin
2. Kod ESP32-C6-ya yüklənəcəkdir

---

## 📋 Pin Konfiqürasyonu

`Display_ST7789.h` faylında pin-ləri tənzimləyin:

```c
#define EXAMPLE_PIN_NUM_SCLK    7   // SPI Clock
#define EXAMPLE_PIN_NUM_MOSI    6   // SPI MOSI
#define EXAMPLE_PIN_NUM_MISO    5   // SPI MISO
#define EXAMPLE_PIN_NUM_LCD_CS  14  // LCD Chip Select
#define EXAMPLE_PIN_NUM_LCD_DC  15  // LCD Data/Command
#define EXAMPLE_PIN_NUM_LCD_RST 21  // LCD Reset
#define EXAMPLE_PIN_NUM_BK_LIGHT 22 // Arxa Işıq (PWM)
```

---

## 📁 Fayl Quruluşu

```
esp32c6_lvgl_8/
├── esp32c6_lvgl_8.ino          # Ana Arduino faylı
├── Display_ST7789.h/.cpp       # LCD ST7789 sürücüsü
├── LVGL_Driver.h/.cpp          # LVGL 9.5 sistem sürücüsü
├── ui.h/.cpp                   # LVGL UI əsas faylları
├── ui_Screen1.h/.cpp           # Ekran 1 komponenti
├── ui_helpers.h/.cpp           # UI yardımçı funksiyaları
├── ui_events.h                 # UI event deklarasiyaları
├── ui_comp_hook.cpp            # Komponent hook-ları
├── CMakeLists.txt              # CMake konfiqürasyonu
├── README.md                   # Bu fayl
└── filelist.txt                # Fayl siyahısı
```

---

## 🔌 LVGL 9.5 Xüsusiyyətləri

### API Dəyişiklikləri Cədvəli

| Əməliyyat               | LVGL 8.3                               | LVGL 9.5                          |
| ----------------------- | -------------------------------------- | --------------------------------- |
| **Display Yaradılması** | `lv_disp_drv_t`                        | `lv_display_create()`             |
| **Buffer Təyini**       | `lv_disp_draw_buf_t`                   | `lv_display_set_buffers()`        |
| **Flush Callback**      | `lv_disp_drv_set_flush_cb()`           | `lv_display_set_flush_cb()`       |
| **Ekran Yüklənməsi**    | `lv_scr_load()`                        | `lv_screen_load()`                |
| **Ekran Animasiyası**   | `lv_scr_load_anim()`                   | `lv_screen_load_anim(..., false)` |
| **Input Device**        | `lv_indev_drv_t`                       | `lv_indev_create()`               |
| **Input Callback**      | `lv_indev_drv_set_read_cb()`           | `lv_indev_set_read_cb()`          |
| **Event Göndərmə**      | `lv_event_send()`                      | `lv_obj_send_event()`             |
| **Flag Çıxartma**       | `lv_obj_clear_flag()`                  | `lv_obj_remove_flag()`            |
| **State Çıxartma**      | `lv_obj_clear_state()`                 | `lv_obj_remove_state()`           |
| **Yaddaş Azad**         | `lv_mem_free()`                        | `lv_free()`                       |
| **Spinner Yaradılması** | `lv_spinner_create(parent, time, arc)` | `lv_spinner_create(parent)`       |
| **Şəkil Format**        | `LV_IMG_CF_TRUE_COLOR`                 | `LV_COLOR_FORMAT_RGB565`          |
| **Image Header**        | `always_zero`, `reserved` ilə          | Sadəcə `cf`, `w`, `h`             |

### Display Driver Nümunəsi

**LVGL 8.3 (Köhnə):**

```c
lv_disp_drv_t disp_drv;
lv_disp_drv_init(&disp_drv);
disp_drv.draw_buf = &draw_buf;
disp_drv.hor_res = LCD_WIDTH;
disp_drv.ver_res = LCD_HEIGHT;
disp_drv.flush_cb = flush_cb;
lv_disp_drv_register(&disp_drv);
```

**LVGL 9.5 (Yeni):**

```c
lv_display_t *display = lv_display_create(LCD_WIDTH, LCD_HEIGHT);
lv_display_set_buffers(display, buf1, buf2, buf_size, LV_DISPLAY_RENDER_MODE_PARTIAL);
lv_display_set_flush_cb(display, flush_cb);
```

### Flag və State Type Casting

LVGL 9.5'te daha sıx tip kontrolü var:

```c
// LVGL 8.3: int istifadə olunur
lv_obj_has_flag(obj, flag_int);

// LVGL 9.5: Type casting lazımdır
lv_obj_has_flag(obj, (lv_obj_flag_t)flag_int);
```

### Spinner Dəyişikliyi

```c
// LVGL 8.3
lv_obj_t *spinner = lv_spinner_create(parent, 1000, 90);  // 1000ms, 90°

// LVGL 9.5
lv_obj_t *spinner = lv_spinner_create(parent);  // Parametrələr kaldırıldı
// Dönüş müddəti stillərlə təyin olunur
```

### Image Header Strukturu

---

## 🎨 UI Tənzimləməsi

### SquareLine Studio ilə Dəyişdirmə

1. SquareLine Studio-nu açın
2. Proyektə yükləyin
3. UI komponentlərini rəsmlə dəyişdirin
4. C Header file-ı olaraq ixrac edin
5. Yaradılmış faylları bu layihəyə dəxil edin

---

## 🐛 Sxemat Çəkili Həllər

### Ekran Göstərilmir

- **Həll:** Pin konfiqürasyonunu yoxlayın (`Display_ST7789.h`)
- SPI sürətini azaldın: `#define SPIFreq 40000000`

### LVGL Error Göstəriliyor

- Məlumat yoxlayın: Arduino IDE Serial Monitor-da
- Baud Rate: 115200

### Mikrokontroller Bloka Alındı

- **Həll:** Watchdog timer-ini sıfırla:

```c
void Timer_Loop() {
  lv_timer_handler();
}
```

---

## 📚 Faydalı Resurslar

- **LVGL Sənədləri:** https://docs.lvgl.io/
- **ESP32-C6 Sənədləri:** https://docs.espressif.com/
- **SquareLine Studio:** https://squareline.io/

---

## 📄 Lisenziya

Bu layihə **MIT Lisenziyası** altında buraxılır.

---

## ✨ Əlavə Notlar

### LVGL 9.5 Migrasyonu

- Bütün API çağırışları LVGL 9.5 ilə uyumlu olaraq yenidən yazılmışdır
- Double buffering istifadə edərək maksimum performans əldə edilir
- Gereksiz kod silinmiş, yalnız istifadə olunan komponentlər qalmışdır

### Performans İpuçları

1. Buffer böyüklüyünü tənzimləyin: `LVGL_BUF_LEN` dəyərini artırın
2. SPI sürətini əksən sistemlərdə `80000000` qoya bilərsiniz
3. LVGL tick period: 5ms (`EXAMPLE_LVGL_TICK_PERIOD_MS`)

### Əlavə Xüsusiyyətlər

- ✅ LVGL 9.5 tam uyumluluğu
- ✅ Azərbaycanca ətraflı şərhlər
- ✅ Clean architecture
- ✅ Minimum yaddaş istifadəsi

---

## 👨‍💻 Müəllif

**Ramo828** - ESP32-C6 LVGL 9.5 Layihəsi

Suallar və təkliflər üçün GitHub issues-ə müraciət edin.

---

**Son Yenilənmə:** 2026-01-15  
**LVGL Versiyası:** 9.5  
**Mikrokontroller:** ESP32-C6  
**Ekran:** ST7789 (172×320)
# esp32c6_lvgl_9
# esp32c6_lvgl_9
# esp32c6_lvgl_9
