cmake_minimum_required(VERSION 3.16)

# ==================== Layihə Konfigürasyonu ====================

# Layihə adı
project(esp32c6_lvgl_8)

# CMake versiyası
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==================== Kaynak Faylları ====================
# UI komponentləri

set(SOURCES
  # Ekran UI faylları
  ui_Screen1.cpp
  
  # Əsas UI faylı
  ui.cpp
  
  # Komponent hook faylı
  ui_comp_hook.cpp
  
  # Yardımçı funksiyalar
  ui_helpers.cpp
  
  # Şəkil veri faylı
  ui_img_waveshare_image10_png.cpp
)

# ==================== UI Library Yaradılması ====================
# Bu library bütün UI komponentlərini ehtiva edir

add_library(ui ${SOURCES})

# ==================== Məlumatlar ====================
# 
# LVGL 9.5 ilə uyumlu:
# - Display driver: LVGL 9.5 API istifadə edir
# - UI komponentləri: SquareLine Studio tərəfindən yaradılmış
# - Buffer management: Double buffering
# 
# Qurulum Addımları:
# 1. ESP32 Arduino Core v3.0.0+ quraşdırılmışdır
# 2. LVGL kütübxanəsi v9.5 quraşdırılmışdır
# 3. SPI və GPIO pinləri Display_ST7789.h-da konfiqurə edilmişdir
#
