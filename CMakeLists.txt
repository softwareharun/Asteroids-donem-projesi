cmake_minimum_required(VERSION 3.10)
project(AsteroidsGame C)

# C standardýný belirliyoruz
set(CMAKE_C_STANDARD 99)

# SDL2 dosyalarýnýn yolunu gösteriyoruz
set(SDL2_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2/include")
set(SDL2_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2/lib/x64") 

# Baþlýk dosyalarýný (header) tanýtýyoruz
include_directories(${SDL2_INCLUDE_DIR})

# Çalýþtýrýlabilir dosyamýzý ve kaynak kodumuzu belirtiyoruz
add_executable(${PROJECT_NAME} WIN32 main.c "gemiVeMermi.h" "gemiVeMermi.c" "meteor.h" "meteor.c" "carpisma.h" "carpisma.c" "arayuz.h" "arayuz.c") #WIN32 yaparak uygulamayla birlikde cmd açýlmasýný engelledik

# Kütüphane dosyalarýný baðlamasý için yolu gösteriyoruz
target_link_directories(${PROJECT_NAME} PRIVATE ${SDL2_LIB_DIR})

# SDL2 kütüphanelerini projeye linkliyoruz
target_link_libraries(${PROJECT_NAME} SDL2 SDL2main)
target_link_libraries(${PROJECT_NAME} SDL2 SDL2main SDL2_image)

# EXE dosyamýz her oluþtuðunda SDL2.dll dosyasýný EXE'nin yanýna otomatik kopyala
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2/lib/x64/SDL2.dll"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>)
   
    # SDL2_image.dll dosyamýzý da EXE'nin yanýna otomatik kopyala
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2/lib/x64/SDL2_image.dll"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>)