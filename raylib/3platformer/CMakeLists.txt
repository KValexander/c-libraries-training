# Минимальная версия
cmake_minimum_required(VERSION 3.23.0)

# Название проекта
project(main)

# Только для WINDOWS

# Путь до raylib
set(RAYLIB_PATH "${CMAKE_SOURCE_DIR}/../raylib")

# Пути подключения raylib
set(RAYLIB_INCLUDE_DIRS "${RAYLIB_PATH}/include")
set(RAYLIB_LIBRARIES "${RAYLIB_PATH}/lib/libraylib.a;")

# Подключение папки src, raylib
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${RAYLIB_INCLUDE_DIRS}
)

# Получение всех исполняемых файлов
file(GLOB_RECURSE SOURCE "src/*.c" "src/*.h")
# Исполняемые файлы
add_executable(main
    ${SOURCE}
)

# Подключение библиотеки raylib
target_link_libraries(main
    ${RAYLIB_LIBRARIES}
)

# Перенос ресурсов
ADD_CUSTOM_TARGET(link_assets ALL COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_BINARY_DIR}/assets)
ADD_CUSTOM_TARGET(link_levels ALL COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/levels ${CMAKE_BINARY_DIR}/levels)
ADD_CUSTOM_TARGET(link_config ALL COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/config.txt ${CMAKE_BINARY_DIR}/config.txt)

# Без этого не работает и я не знаю почему
if(MINGW)
    target_link_libraries(main hid setupapi Imm32 Version winmm)
elseif(WIN32)
    target_link_libraries(main Imm32 Version winmm)
endif()