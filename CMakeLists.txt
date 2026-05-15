cmake_minimum_required(VERSION 3.10)
project(AsteroidsGame C)

# C standardýný belirliyoruz
set(CMAKE_C_STANDARD 99)

# SDL2 dosyalarýnýn yolunu gösteriyoruz (Kendi external klasörümüz)
set(SDL2_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2/include")
set(SDL2_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2/lib/x64")

# Baþlýk dosyalarýný (header) tanýtýyoruz
include_directories(${SDL2_INCLUDE_DIR})

# Çalýþtýrýlabilir dosyamýzý ve kaynak kodlarýmýzý belirtiyoruz
# WIN32 komutu arka plandaki siyah CMD ekranýný gizler
add_executable(${PROJECT_NAME} WIN32 
    main.c 
    gemiVeMermi.h gemiVeMermi.c 
    meteor.h meteor.c 
    carpisma.h carpisma.c 
    arayuz.h arayuz.c
)

# Kütüphane (.lib) dosyalarýnýn nerede olduðunu gösteriyoruz
target_link_directories(${PROJECT_NAME} PRIVATE ${SDL2_LIB_DIR})

# Bütün kütüphaneleri (SDL2, Image ve TTF) tek bir satýrda projeye baðlýyoruz
target_link_libraries(${PROJECT_NAME} SDL2 SDL2main SDL2_image SDL2_ttf)


# --- OTOMATÝK DLL KOPYALAMA ÝÞLEMLERÝ ---
# Oyunun sorunsuz açýlmasý için gereken 3 DLL dosyasýný EXE'nin yanýna kopyalar

# 1. SDL2.dll
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2/lib/x64/SDL2.dll"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# 2. SDL2_image.dll
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2/lib/x64/SDL2_image.dll"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# 3. SDL2_ttf.dll (YENÝ EKLENEN)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2/lib/x64/SDL2_ttf.dll"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>)

    # resimler klasörünü içindekilerle birlikte otomatik olarak EXE'nin yanýna kopyala
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/resimler"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resimler")