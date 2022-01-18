# Template CMakeLists.txt configuration for STM32 MCUS
cmake_minimum_required(VERSION 3.14)
# ##############################################################################
# Edit your MCU information up to the next border
project(mmbtc_firmware)

set(TEMP_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tmp)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../src)
set(PROJECT_DIR ${SRC_DIR}/PROJECT)
set(PLATFORM_DIR ${SRC_DIR}/Platforms/SimCatalina)
set(MICRO_BITCOIN_DIR ${SRC_DIR}/Libs/uBitcoin/src)
set(LVGL_DIR ${SRC_DIR}/Libs/lvgl)
set(LVGL_DRIVERS_DIR ${SRC_DIR}/Libs/lv_drivers)

set(MCU_FAMILY STM32F3xx)
set(MCU_MODEL STM32F303xx)

# ##############################################################################
set(EXECUTABLE ${CMAKE_PROJECT_NAME})
enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


# Headers
set(PROJECT_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PLATFORM_DIR}
    ${MICRO_BITCOIN_DIR}
    ${MICRO_BITCOIN_DIR}/utility
    ${MICRO_BITCOIN_DIR}/utility/trezor

    # ${LVGL_DIR}
    # ${LVGL_DIR}/demos/benchmark
    # ${MICRO_BITCOIN_DIR}/c_interface
    ${PROJECT_DIR})

# Sources
file(GLOB_RECURSE PROJECT_SOURCES FOLLOW_SYMLINKS
    # ${MICRO_BITCOIN_DIR}/Bitcoin.cpp
    # ${MICRO_BITCOIN_DIR}/Conversion.cpp
    # ${MICRO_BITCOIN_DIR}/Hash.cpp
    ${MICRO_BITCOIN_DIR}/*.cpp
    # ${MICRO_BITCOIN_DIR}/c_interface/interface_w_c.cpp
    ${MICRO_BITCOIN_DIR}/utility/*.c
    ${MICRO_BITCOIN_DIR}/utility/trezor/*.c

    # ${LVGL_DIR}/demos/benchmark

    ${PLATFORM_DIR}/*.c
    ${PROJECT_DIR}/*.cpp
    ${PROJECT_DIR}/*.c)

# Executable files
add_executable(${EXECUTABLE}
    ${PROJECT_SOURCES})

# Embedded macros(defines)
target_compile_definitions(${EXECUTABLE} PRIVATE
    ${MCU_MODEL})

# Add header directories (AFTER add_executable !!)
target_include_directories(${EXECUTABLE} PRIVATE
    ${PROJECT_INCLUDE_DIRECTORIES})


# ADD SDL - BEGIN
list(APPEND CMAKE_MODULE_PATH ${SRC_DIR}/Libs/sdl2)
# list(APPEND CMAKE_MODULE_PATH ${SRC_DIR}/Libs/lvgl/cmake)

find_package(SDL2 REQUIRED)
add_subdirectory(${LVGL_DIR} ${TEMP_BUILD_DIR}/lvgl)
# add_subdirectory(${LVGL_DRIVERS_DIR} ${TEMP_BUILD_DIR}/lv_drivers)
# find_package(lvgl REQUIRED)
# find_package(SDL2_image REQUIRED)
# find_package(SDL2_gfx REQUIRED)

# Link SDL2::Main, SDL2::Image and SDL2::GFX to our project
# target_link_libraries(mmbtc_firmware SDL2::Main lvgl::lvgl)
target_link_libraries(mmbtc_firmware SDL2::Main lvgl)
# target_link_libraries(mmbtc_firmware SDL2::Main)
# ADD SDL - END

# ADD LVGL - BEGIN

# # Specify path to own LVGL config header
# set(LV_CONF_PATH
#     ${PLATFORM_DIR}/lv_conf.h
#     CACHE STRING "" FORCE)

# # Fetch LVGL from GitHub
# include(FetchContent)
# FetchContent_Declare(lvgl URL https://github.com/lvgl/lvgl.git)
# FetchContent_Declare(sdl2 URL https://github.com/lvgl/lvgl.git)
# FetchContent_MakeAvailable(lvgl)

# # The target "mmbtc_firmware" depends on LVGL
# add_subdirectory(${LVGL_DIR})
# target_link_libraries(mmbtc_firmware PRIVATE lvgl::lvgl)

# ADD LVGL - END

target_compile_features(mmbtc_firmware PUBLIC cxx_std_20)

# Compiler and linker options
target_compile_options(${EXECUTABLE} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
    $<$<COMPILE_LANGUAGE:CXX>:
        -Wno-volatile
        -Wold-style-cast
        -Wuseless-cast
        -Wsuggest-override>
    $<$<CONFIG:Debug>:-Og -g3 -ggdb>
    $<$<CONFIG:Release>:-Og -g0>)



# target_link_options(${EXECUTABLE} PRIVATE
#     -lstdc++
#     -lsupc++)

# add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
#     COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>)


# add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
#     COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}>
#     ${EXECUTABLE}.hex
#     COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}>
#     ${EXECUTABLE}.bin)
