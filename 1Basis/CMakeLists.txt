# Минимальная версия
cmake_minimum_required(VERSION 3.23.0)

# Название проекта
project(main)

# Этот CMakeLists написан на основе:
# https://github.com/tsoding/nothing/blob/master/CMakeLists.txt
# https://github.com/bradharding/doomretro/blob/master/CMakeLists.txt

# Только для WINDOWS

# Без этого не работает и я не знаю почему
# При чём обязательно в самое начало
if(MINGW)
    # https://stackoverflow.com/a/25089610
    add_compile_definitions(SDL_MAIN_HANDLED)
    # https://github.com/trink/symtseries/issues/49#issuecomment-160843756
    add_compile_definitions(__USE_MINGW_ANSI_STDIO)
endif()

# В моей папке SDL2 помимо SDL2 так же находятся:
# SDL2_image
# SDL2_mixer
# SDL2_ttf

# Определение разрядности системы
# для подключения SDL2
if(${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_PATH "${CMAKE_SOURCE_DIR}/../SDL2/x86_64-w64-mingw32")
else()
    set(SDL2_PATH "${CMAKE_SOURCE_DIR}/../SDL2/i686-w64-mingw32")
endif()

# Пути подключения SDL2
set(SDL2_INCLUDE_DIRS "${SDL2_PATH}/include/SDL2")
set(SDL2_LIBRARIES "${SDL2_PATH}/lib/libSDL2.a;${SDL2_PATH}/lib/libSDL2main.a;${SDL2_PATH}/lib/libSDL2_image.a;${SDL2_PATH}/lib/libSDL2_mixer.a;${SDL2_PATH}/lib/libSDL2_ttf.a")

# Подключение папки src, SDL2
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${SDL2_INCLUDE_DIRS}
)

# Исполняемые файлы
add_executable(main
    src/main.c
)

# Подключение библиотеки SDL2
target_link_libraries(main
    ${SDL2_LIBRARIES}
)

# Перенос ресурсов
ADD_CUSTOM_TARGET(link_assets ALL COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets)

# Без этого не работает и я не знаю почему x2
if(MINGW)
    target_link_libraries(main hid setupapi Imm32 Version winmm)
elseif(WIN32)
    target_link_libraries(main Imm32 Version winmm)
endif()